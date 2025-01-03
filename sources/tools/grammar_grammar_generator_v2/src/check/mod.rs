mod lookup_pass;

use std::boxed::Box;
use std::rc::Rc;

use crate::types::{TypePtr, TypeRef};
use crate::{
    error::Error,
    types::{Element, Type, TypeRegistry},
};

pub trait TypeTransformPass {
    fn transform(&self, registry: &TypeRegistry, ty: TypePtr) -> Result<TypePtr, Error>;
}

pub struct TypeTransform {
    passes: Vec<Box<dyn TypeTransformPass>>,
}

impl TypeTransform {
    pub fn new() -> Self {
        Self { passes: Vec::new() }
    }

    pub fn add_pass<T: TypeTransformPass + 'static>(&mut self, pass: T) {
        self.passes.push(Box::new(pass));
    }

    pub fn apply_passes(&self, registry: Rc<TypeRegistry>) -> Result<Rc<TypeRegistry>, Error> {
        let mut types = registry.types.to_vec();
        for pass in self.passes.iter() {
            let type_results: Vec<Result<TypePtr, Error>> = types
                .iter()
                .map(|t| pass.transform(&registry, t.clone()))
                .collect();
            match type_results.iter().find(|v| v.is_err()) {
                Some(Err(e)) => return Err(e.clone()),
                _ => (),
            };
            types = type_results.into_iter().filter_map(|r| r.ok()).collect();
        }

        Ok(Rc::new(TypeRegistry::new(types)))
    }
}

pub use lookup_pass::TypeLookupPass;
