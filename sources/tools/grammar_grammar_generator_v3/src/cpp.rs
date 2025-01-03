use std::fmt::Write;

use anyhow::{ensure, Result};

pub struct CPPGen<W: Write> {
    w: W,
    indent: usize,
}

impl<W: Write> CPPGen<W> {
    pub fn new(w: W) -> Self {
        Self { w, indent: 0 }
    }

    pub fn open_class<S: Into<String>>(&mut self, name: S) -> Result<()> {
        self.indent(self.indent)?;
        self.indent += 1;
        writeln!(self.w, "class {} {{", name.into())?;
        Ok(())
    }

    pub fn close_class(&mut self) -> Result<()> {
        self.indent -= 1;
        self.indent(self.indent)?;
        writeln!(self.w, "}};")?;
        Ok(())
    }

    pub fn open_function<S1, S2>(
        &mut self,
        name: S1,
        return_ty: S2,
        params: Vec<String>,
        trailing_attrs: Vec<String>,
    ) -> Result<()>
    where
        S1: Into<String>,
        S2: Into<String>,
    {
        self.indent(self.indent)?;
        self.indent += 1;
        let attrs = trailing_attrs
            .iter()
            .fold(String::from(""), |a, b| format!("{} {}", a, b));
        writeln!(
            self.w,
            "{} {}({}){} {{",
            return_ty.into(),
            name.into(),
            params.join(", "),
            attrs
        )?;
        Ok(())
    }

    pub fn close_function(&mut self) -> Result<()> {
        self.indent -= 1;
        self.indent(self.indent)?;
        writeln!(self.w, "}}")?;
        Ok(())
    }

    pub fn field<S1, S2>(&mut self, ty: S1, name: S2) -> Result<()>
    where
        S1: Into<String>,
        S2: Into<String>,
    {
        self.indent(self.indent)?;
        writeln!(self.w, "{} {};", ty.into(), name.into())?;
        Ok(())
    }

    pub fn private(&mut self) -> Result<()> {
        self.indent(self.indent - 1)?;
        writeln!(self.w, "  private:")?;
        Ok(())
    }

    pub fn public(&mut self) -> Result<()> {
        self.indent(self.indent - 1)?;
        writeln!(self.w, "  public:")?;
        Ok(())
    }

    pub fn write_line<S: Into<String>>(&mut self, line: S) -> Result<()> {
        self.indent(self.indent)?;
        writeln!(self.w, "{}", line.into())?;
        Ok(())
    }

    fn indent(&mut self, n: usize) -> Result<()> {
        ensure!(n < 30, "Indent size is to big");
        write!(self.w, "{}", " ".repeat(n * 4))?;
        Ok(())
    }
}
