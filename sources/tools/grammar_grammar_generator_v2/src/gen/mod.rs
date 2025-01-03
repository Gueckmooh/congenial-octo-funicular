use std::{borrow::Borrow, io};

use convert_case::{Case, Casing};

use crate::types::TypePtr;

#[derive(Debug)]
pub struct CPPClass {
    pub name: String,
    pub fields: Vec<CPPField>,
}

#[derive(Debug)]
pub struct CPPField {
    pub name: String,
    pub ty: String,
}

impl CPPField {
    pub fn new(name: String, ty: String) -> Self {
        Self { name, ty }
    }

    pub fn gen<W: io::Write>(&self, stream: &mut W) -> io::Result<()> {
        writeln!(stream, "    {} {};", self.ty, self.name)
    }
}

impl From<&super::types::Element> for CPPField {
    fn from(elt: &super::types::Element) -> Self {
        let named: Vec<TypePtr> = elt.types.iter().filter_map(|v| v.named_type()).collect();
        let ty = if named.is_empty() {
            String::from("error")
        } else if named.len() == 1 {
            named.first().unwrap().name.to_case(Case::Pascal)
        } else {
            format!(
                "std::variant<{}>",
                named
                    .iter()
                    .map(|v| v.name.to_case(Case::Pascal))
                    .collect::<Vec<String>>()
                    .join(", ")
            )
        };
        CPPField::new(format!("m_{}", elt.name.to_case(Case::Camel)), ty)
    }
}

impl From<&super::types::Type> for CPPClass {
    fn from(ty: &super::types::Type) -> Self {
        let mut class = CPPClass::new(ty.name.to_case(Case::Pascal));
        class.fields = ty
            .fields
            .iter()
            .map(|v| CPPField::from(v.borrow()))
            .collect();
        return class;
    }
}

impl CPPClass {
    pub fn new(name: String) -> Self {
        Self {
            name,
            fields: Vec::new(),
        }
    }

    pub fn gen<W: io::Write>(&self, stream: &mut W) -> io::Result<()> {
        writeln!(stream, "class {} {{\n", self.name).unwrap();
        for field in self.fields.iter() {
            field.gen(stream).unwrap();
        }
        writeln!(stream, "}};").unwrap();
        Ok(())
    }
}
