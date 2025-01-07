use crate::Class;
use std::rc::Rc;

#[derive(Debug, Clone)]
pub struct Package {
    name: String,
    declarations: Vec<Declaration>,
}

impl Package {
    pub fn new<S: Into<String>>(name: S, declarations: Vec<Declaration>) -> Self {
        Self {
            name: name.into(),
            declarations,
        }
    }

    #[must_use]
    pub fn name(&self) -> &str {
        &self.name
    }

    #[must_use]
    pub fn declarations(&self) -> &[Declaration] {
        &self.declarations
    }
}

#[derive(Debug, Clone)]
pub enum Declaration {
    Class(Rc<Class>),
}
