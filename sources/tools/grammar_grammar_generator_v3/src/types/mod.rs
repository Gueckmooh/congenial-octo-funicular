use anyhow::anyhow;
use convert_case::{Case, Casing};

pub mod convert;
pub mod gen;

#[derive(Debug, Clone)]
pub struct Struct {
    name: String,
    fields: Vec<Variable>,
    methods: Vec<Function>,
}

#[derive(Debug, Clone)]
pub struct Variable {
    name: String,
    ty: Type,
}

#[derive(Debug, Clone)]
pub struct Function {
    name: String,
    return_ty: Type,
    params: Vec<Variable>,
    body: Vec<String>,
    is_const: bool,
}

impl Function {
    pub fn new(name: String, return_ty: Type, params: Vec<Variable>, body: Vec<String>) -> Self {
        Self {
            name,
            return_ty,
            params,
            body,
            is_const: false,
        }
    }

    pub fn set_is_const(&mut self, is_const: bool) -> &Self {
        self.is_const = is_const;
        self
    }
}

#[derive(Debug, Clone)]
pub enum Type {
    Struct(String),
    Variant(Vec<Type>),
    Vector(Box<Type>),
    Optional(Box<Type>),
    String,
    Void,

    Ref(Box<Type>),
    Qualified { is_const: bool, ty: Box<Type> },
}

impl Type {
    /// Returns `true` if the type is [`Vector`].
    ///
    /// [`Vector`]: Type::Vector
    #[must_use]
    pub fn is_vector(&self) -> bool {
        matches!(self, Self::Vector(..))
    }

    pub fn make_ref(self) -> Self {
        Self::Ref(Box::new(self))
    }

    pub fn make_qualified(self, is_const: bool) -> Self {
        Self::Qualified {
            is_const,
            ty: Box::new(self),
        }
    }

    pub fn try_into_vector(self) -> Result<Box<Type>, Self> {
        if let Self::Vector(v) = self {
            Ok(v)
        } else {
            Err(self)
        }
    }
}

impl Struct {
    pub fn new<S: Into<String>>(name: S, fields: Vec<Variable>, methods: Vec<Function>) -> Self {
        Self {
            name: name.into(),
            fields,
            methods,
        }
    }
}

impl Variable {
    pub fn new<S: Into<String>>(name: S, ty: Type) -> Self {
        Self {
            name: name.into(),
            ty,
        }
    }

    pub fn var_name(&self) -> String {
        format!("m_{}", self.name.to_case(Case::Camel))
    }

    pub fn getter_name(&self) -> String {
        self.anyer_name("get")
    }

    pub fn setter_name(&self) -> String {
        self.anyer_name("set")
    }

    fn anyer_name<S: Into<String>>(&self, prefix: S) -> String {
        format!("{}{}", prefix.into(), self.name.to_case(Case::Pascal))
    }
}

impl From<&Variable> for String {
    fn from(value: &Variable) -> Self {
        format!("{} {}", String::from(&value.ty), value.name)
    }
}

impl From<Variable> for String {
    fn from(value: Variable) -> Self {
        String::from(&value)
    }
}

impl From<&Type> for String {
    fn from(value: &Type) -> Self {
        match value {
            Type::Struct(s) => s.clone(),
            Type::Variant(vec) => format!(
                "std::variant<{}>",
                vec.iter()
                    .map(Self::from)
                    .collect::<Vec<_>>()
                    .join(", ")
            ),
            Type::Vector(t) => format!("std::vector<{}>", String::from(t.as_ref())),
            Type::Optional(t) => format!("std::optional<{}>", String::from(t.as_ref())),
            Type::String => "std::string".into(),
            Type::Void => "void".into(),
            Type::Ref(t) => format!("{}&", String::from(t.as_ref())),
            Type::Qualified { is_const, ty } => format!(
                "{} {}",
                vec![is_const.then(|| String::from("const"))]
                    .into_iter()
                    .flatten()
                    .collect::<Vec<String>>()
                    .join(" "),
                String::from(ty.as_ref())
            ),
        }
    }
}

impl From<Type> for String {
    fn from(value: Type) -> Self {
        String::from(&value)
    }
}

impl From<Type> for anyhow::Error {
    fn from(value: Type) -> Self {
        anyhow!("Conversion from {}", String::from(value))
    }
}
