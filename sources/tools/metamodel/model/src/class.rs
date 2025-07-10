use crate::{Function, Variable};
use std::rc::Rc;

#[derive(Debug, Clone)]
pub struct Class {
    name: String,
    methods: Vec<Rc<Function>>,
    fields: Vec<Rc<Variable>>,
    attributes: Attributes,
}

#[derive(Debug, Clone, Default)]
#[allow(clippy::struct_excessive_bools)]
pub struct Attributes {
    pub is_ref_counted: bool,
    pub may_be_null: bool,
    pub is_printable: bool,
    pub has_default: bool,
    pub can_copy: bool,
}

impl Class {
    #[must_use]
    pub fn new<S: Into<String>>(
        name: S,
        methods: Vec<Function>,
        fields: Vec<Variable>,
        attributes: Attributes,
    ) -> Self {
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
            attributes,
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

    #[must_use]
    pub fn attributes(&self) -> &Attributes {
        &self.attributes
    }
}
