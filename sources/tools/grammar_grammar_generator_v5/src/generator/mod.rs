use anyhow::{ensure, Result};
use convert_case::{Case, Casing};
use std::fmt::{Display, Write};

use crate::cpp::{Class, Field, Function, Type, Variable};

#[macro_export]
macro_rules! indent {
    ($this:tt) => {
        $this.indent_level += 1;
    };
}

#[macro_export]
macro_rules! dedent {
    ($this:tt) => {{
        ensure!($this.indent_level > 0, "Try to dedent 0 indent level");
        $this.indent_level -= 1;
    }};
}

#[macro_export]
macro_rules! add {
    ($this:tt, $($arg:tt)*) => {
           $this.buffer.write_fmt(format_args!($($arg)*)).map_err(anyhow::Error::from)
    };
}

#[macro_export]
macro_rules! add_whitespace {
    ($this:tt) => {
        write!(&mut $this.buffer, "{}", "    ".repeat($this.indent_level))
            .map_err(anyhow::Error::from)
    };
}

#[macro_export]
macro_rules! add_half_whitespace {
    ($this:tt) => {
        if $this.indent_level > 0 {
            write!(
                &mut $this.buffer,
                "{}  ",
                "    ".repeat($this.indent_level - 1)
            )
            .map_err(anyhow::Error::from)
        } else {
            Ok(())
        }
    };
}

macro_rules! add_public {
    ($this:tt) => {{
        add_half_whitespace!($this)?;
        writeln!(&mut $this.buffer, "public:").map_err(anyhow::Error::from)
    }};
}

macro_rules! add_private {
    ($this:tt) => {{
        add_half_whitespace!($this)?;
        writeln!(&mut $this.buffer, "private:").map_err(anyhow::Error::from)
    }};
}

#[macro_export]
macro_rules! add_line {
    ($this:tt, $($arg:tt)*) => {{
        add_whitespace!($this)?;
        $this.buffer.write_fmt(format_args!($($arg)*))?;
        $this.buffer.write_str("\n").map_err(anyhow::Error::from)
    }};
}

#[derive(Debug)]
pub struct Generator<W: Write> {
    buffer: W,
    indent_level: usize,
}

impl<W: Write + Default> Default for Generator<W> {
    fn default() -> Self {
        Self::new(W::default())
    }
}

impl<W: Write> Generator<W> {
    pub fn new(buffer: W) -> Self {
        Self {
            buffer,
            indent_level: 0,
        }
    }

    pub fn into_inner(self) -> W {
        self.buffer
    }
}

impl Display for Generator<String> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        f.write_str(&self.buffer)
    }
}

pub trait Generate<T> {
    /// Generates code from given value.
    ///
    /// # Errors
    ///
    /// This function will return an error if generation fails.
    fn generate(&mut self, value: &T) -> Result<()>;

    /// Generates a string from a default generator.
    ///
    /// # Errors
    ///
    /// This function will return an error if the generation fails.
    fn generate_str(value: &T) -> Result<String>
    where
        Self: Display + Default,
    {
        let mut gen = Self::default();
        gen.generate(value)?;
        Ok(format!("{gen}"))
    }
}

pub trait GenerateDecl<T> {
    /// Generates declaration from given value.
    ///
    /// # Errors
    ///
    /// This function will return an error if generation fails.
    fn generate_decl(&mut self, value: &T) -> Result<()>;
}

impl<W: Write> Generate<Type> for Generator<W> {
    fn generate(&mut self, value: &Type) -> Result<()> {
        match value {
            Type::Void => add!(self, "void"),
            Type::String => add!(self, "std::string"),
            Type::Reference(ty) => {
                self.generate(ty.as_ref())?;
                add!(self, "&")
            }
            Type::Qualified(qualifiers, ty) => {
                qualifiers.is_const.then(|| add!(self, "const "));
                self.generate(ty.as_ref())
            }
        }
    }
}

impl<W: Write> Generate<Variable> for Generator<W> {
    fn generate(&mut self, value: &Variable) -> Result<()> {
        self.generate(value.ty())?;
        add!(self, " {}", value.name())
    }
}

impl<W: Write> Generate<Field> for Generator<W> {
    fn generate(&mut self, value: &Field) -> Result<()> {
        self.generate(value.ty())?;
        let name = if value.is_public() {
            value.name().into()
        } else {
            format!("m_{}", value.name().to_case(Case::Camel))
        };
        add!(self, " {}", name)
    }
}

impl<W: Write> GenerateDecl<Variable> for Generator<W> {
    fn generate_decl(&mut self, value: &Variable) -> Result<()> {
        add_whitespace!(self)?;
        self.generate(value)?;
        add!(self, ";\n")
    }
}

impl<W: Write> GenerateDecl<Field> for Generator<W> {
    fn generate_decl(&mut self, value: &Field) -> Result<()> {
        add_whitespace!(self)?;
        self.generate(value)?;
        add!(self, ";\n")
    }
}

impl<W: Write> Generate<Class> for Generator<W> {
    fn generate(&mut self, value: &Class) -> Result<()> {
        add_line!(
            self,
            "{} {} {{",
            if value.is_struct() { "struct" } else { "class" },
            value.name()
        )?;
        indent!(self);
        self.generate_public_fields(value)?;
        add_line!(self, "")?;
        self.generate_access_functions_for_private_fields(value)?;
        add_line!(self, "")?;
        self.generate_private_fields(value)?;
        dedent!(self);
        add_line!(self, "}};")
    }
}

impl<W: Write> Generator<W> {
    fn generate_private_fields(&mut self, value: &Class) -> Result<()> {
        let private_fields: Vec<&Field> =
            value.fields().iter().filter(|v| v.is_private()).collect();
        if private_fields.is_empty() {
            return Ok(());
        }
        add_private!(self)?;
        private_fields
            .into_iter()
            .try_for_each(|v| self.generate_decl(v))
    }

    fn generate_public_fields(&mut self, value: &Class) -> Result<()> {
        let public_fields: Vec<&Field> = value.fields().iter().filter(|v| v.is_public()).collect();
        if public_fields.is_empty() {
            return Ok(());
        }
        add_public!(self)?;
        public_fields
            .into_iter()
            .try_for_each(|v| self.generate_decl(v))
    }

    fn generate_access_functions_for_private_fields(&mut self, value: &Class) -> Result<()> {
        let private_fields: Vec<&Field> =
            value.fields().iter().filter(|v| v.is_private()).collect();
        if private_fields.is_empty() {
            return Ok(());
        }
        add_public!(self)?;
        private_fields
            .into_iter()
            .flat_map(|v| vec![v.get_getter(), v.get_setter()])
            .try_for_each(|v| self.generate(&v))
    }
}

/// # Method generation
impl<W: Write> Generate<Function> for Generator<W> {
    fn generate(&mut self, value: &Function) -> Result<()> {
        add_whitespace!(self)?;
        self.generate_function_signature(value)?;
        add!(self, ";\n")
    }
}

impl<W: Write> Generator<W> {
    fn generate_function_signature(&mut self, value: &Function) -> Result<()> {
        self.generate(value.return_ty())?;
        add!(
            self,
            " {}({})",
            value.name(),
            value
                .params()
                .iter()
                .map(Generator::<String>::generate_str)
                .collect::<Result<Vec<String>>>()?
                .join(", ")
        )
    }
}
