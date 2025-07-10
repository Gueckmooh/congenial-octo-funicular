use serde::{Deserialize, Serialize};

#[derive(Serialize)]
pub struct Class {
    pub name: String,
    pub methods: Vec<Function>,
    pub fields: Vec<Variable>,
    pub attributes: ClassAttributes,
}

#[derive(Serialize, Default)]
pub struct ClassAttributes {
    pub has_default: bool,
    pub is_copyable: bool,
    pub is_printable: bool,
    pub is_ref_counted: bool,
    pub may_be_null: bool,
}

#[derive(Serialize)]
pub struct Variable {
    pub name: String,
    pub ty: Type,
    pub attributes: VariableAttributes,
}

#[derive(Serialize, Default)]
pub struct VariableAttributes {
    pub is_mutable: bool,
}

#[derive(Serialize)]
pub struct Function {
    pub name: String,
    pub return_ty: Type,
    pub params: Vec<Variable>,
}

#[derive(Debug, Serialize, Deserialize, Clone, Eq, PartialEq, Hash)]
pub enum Type {
    Void,
    Int32,
    String,
    StringView,

    Object(String),
    Ref(Box<Type>),
    Qualified(Qualifiers, Box<Type>),
}

#[derive(Debug, Serialize, Deserialize, Clone, Eq, PartialEq, Hash)]
pub struct Qualifiers {
    pub is_const: bool,
}

impl Type {
    pub fn make_view(self) -> Self {
        match self {
            Type::Void => Type::Void,
            Type::Int32 => Type::Int32,
            Type::String | Type::StringView => Type::StringView,
            Type::Object(_) => Type::Qualified(
                Qualifiers { is_const: true },
                Box::new(Type::Ref(Box::new(self))),
            ),
            Type::Ref(_) | Type::Qualified(_, _) => self,
        }
    }

    pub fn is_trivialy_copyable(&self) -> bool {
        matches!(self, Type::Void | Type::Int32 | Type::Ref(_))
    }
}

impl From<model::Variable> for Variable {
    fn from(value: model::Variable) -> Self {
        Self {
            name: value.name().into(),
            ty: value.ty().clone().into(),
            attributes: VariableAttributes {
                is_mutable: value.attributes().is_mutable,
            },
        }
    }
}

impl From<model::Type> for Type {
    fn from(value: model::Type) -> Self {
        match value {
            model::Type::Void => Self::Void,
            model::Type::Int32 => Self::Int32,
            model::Type::String => Self::String,
            model::Type::Type(name) => Self::Object(name),
        }
    }
}

impl From<Type> for String {
    fn from(value: Type) -> Self {
        match value {
            Type::Void => "void".into(),
            Type::Int32 => "std::int32_t".into(),
            Type::String => "std::string".into(),
            Type::StringView => "std::string_view".into(),
            Type::Object(s) => s,
            Type::Ref(ty) => format!("{}&", String::from(*ty)),
            Type::Qualified(qualifiers, ty) => {
                let is_const = if qualifiers.is_const { "const " } else { "" };
                format!("{is_const}{}", String::from(*ty))
            }
        }
    }
}
