use serde::Deserialize;
use std::collections::BTreeMap;

#[derive(Debug, Deserialize, PartialEq, Eq, Default, PartialOrd, Ord)]
pub struct NodeInfoJSON {
    #[serde(rename = "type")]
    pub kind: String,
    pub named: bool,
    #[serde(default)]
    pub root: bool,
    #[serde(default)]
    pub fields: Option<BTreeMap<String, FieldInfoJSON>>,
    #[serde(default)]
    pub children: Option<FieldInfoJSON>,
    #[serde(default)]
    pub subtypes: Option<Vec<NodeTypeJSON>>,
}

#[derive(Clone, Debug, Deserialize, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub struct NodeTypeJSON {
    #[serde(rename = "type")]
    pub kind: String,
    pub named: bool,
}

#[derive(Debug, Deserialize, PartialEq, Eq, PartialOrd, Ord)]
pub struct FieldInfoJSON {
    pub multiple: bool,
    pub required: bool,
    pub types: Vec<NodeTypeJSON>,
}
