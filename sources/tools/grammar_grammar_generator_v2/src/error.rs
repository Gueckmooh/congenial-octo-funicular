use std::fmt;

#[derive(Clone)]
pub enum Error {
    BadInput { file: String, why: String },
    TypeCheck { msg: String },
}

impl fmt::Display for Error {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        use Error::*;
        match *self {
            BadInput { ref file, ref why } => {
                write!(f, "Bad input file {}: {}", file, why)
            }
            TypeCheck { ref msg } => {
                write!(f, "Error while typechecking types: {}", msg)
            }
        }
    }
}

impl fmt::Debug for Error {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        std::fmt::Display::fmt(&self, f)
    }
}
