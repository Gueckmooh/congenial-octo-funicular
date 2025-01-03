use crate::{
    error::Error,
    types::{Element, ElementPtr, Type, TypePtr, TypeRef, TypeRegistry},
};

use super::TypeTransformPass;

pub struct TypeLookupPass {}

impl TypeTransformPass for TypeLookupPass {
    fn transform(&self, registry: &TypeRegistry, ty: TypePtr) -> Result<TypePtr, Error> {
        let fields_res: Vec<Result<ElementPtr, Error>> = ty
            .fields
            .to_vec()
            .into_iter()
            .map(|v| self.transform_elt(registry, v))
            .collect();
        match fields_res.iter().find(|v| v.is_err()) {
            Some(Err(e)) => return Err(e.clone()),
            _ => (),
        }
        let fields = fields_res.into_iter().filter_map(|v| v.ok()).collect();
        Ok(TypePtr::new(Type::new(
            ty.name.clone(),
            ty.named,
            fields,
            ty.children.clone(),
        )))
    }
}

impl TypeLookupPass {
    pub fn new() -> Self {
        Self {}
    }

    fn transform_elt(&self, registry: &TypeRegistry, elt: ElementPtr) -> Result<ElementPtr, Error> {
        let looked_up_types_res: Vec<Result<TypePtr, Error>> = elt
            .types
            .iter()
            .map(|tyr| match registry.lookup(tyr) {
                Some(v) => Ok(v),
                None => Err(Error::TypeCheck {
                    msg: format!("Could not lookup type {:?}", tyr),
                }),
            })
            .collect();
        match looked_up_types_res.iter().find(|v| v.is_err()) {
            Some(Err(e)) => return Err(e.clone()),
            _ => (),
        }
        let types = looked_up_types_res
            .into_iter()
            .filter_map(|f| f.ok().and_then(|v| Some(TypeRef::Type(v))))
            .collect();
        Ok(ElementPtr::new(Element::new(
            elt.name.clone(),
            elt.multiple,
            elt.required,
            types,
        )))
    }
}
