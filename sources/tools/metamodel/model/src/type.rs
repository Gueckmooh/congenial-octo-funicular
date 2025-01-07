#[derive(Debug, Clone)]
pub enum Type {
    Void,
    Int32,
    String,

    Type(String),
}
