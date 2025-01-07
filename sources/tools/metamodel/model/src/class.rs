use crate::{Function, Variable};
use std::rc::Rc;

#[derive(Debug, Clone)]
pub struct Class {
    name: String,
    methods: Vec<Rc<Function>>,
    fields: Vec<Rc<Variable>>,
}

impl Class {
    #[must_use]
    pub fn new<S: Into<String>>(name: S, methods: Vec<Function>, fields: Vec<Variable>) -> Self {
        let methods: Vec<Rc<Function>> = methods.into_iter().map(Rc::new).collect();
        let fields: Vec<Rc<Variable>> = fields
            .into_iter()
            .map(Variable::as_field)
            .map(Rc::new)
            .collect();
        Self {
            name: name.into(),
            methods,
            fields,
        }
    }

    #[must_use]
    pub fn name(&self) -> &str {
        &self.name
    }

    #[must_use]
    pub fn methods(&self) -> &[Rc<Function>] {
        &self.methods
    }

    #[must_use]
    pub fn fields(&self) -> &[Rc<Variable>] {
        &self.fields
    }

    pub fn add_method(&mut self, method: Rc<Function>) {
        self.methods.push(method);
    }
}
