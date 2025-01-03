use super::ty;

pub fn gen_class_from_type(ty: &ty::Type) {
    if !ty.named {
        return;
    }
    println!("class {} {{", ty.ty);
    gen_fields_for_type(&ty);
    println!("}}");
}

fn gen_fields_for_type(ty: &ty::Type) {
    for field in ty.fields.iter() {
        gen_field(&field);
    }
}

fn gen_field(field: &ty::Field) {
    println!("field {}", field.name);
}
