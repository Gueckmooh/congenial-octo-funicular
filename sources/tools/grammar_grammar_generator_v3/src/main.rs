mod args;
mod cpp;
mod node_types;
mod types;

use anyhow::Context;
use args::Args;
use clap::Parser;

use anyhow::Result;
use cpp::CPPGen;
use node_types::NodeInfoJSON;
use types::Struct;

use types::gen::GenCPP2;

fn main() -> Result<()> {
    let args = Args::parse();

    let content = std::fs::read_to_string(&args.file)
        .with_context(|| format!("Failed to read file {}", args.file))?;

    let deserialized: Vec<NodeInfoJSON> = serde_json::from_str(content.as_str())?;

    let _structures = deserialized
        .iter()
        .filter(|v| v.named)
        .map(types::convert::convert_node_info)
        .collect::<Result<Vec<Struct>>>()
        .context("When batch converting")?;

    let mut s = String::new();
    let mut gen = CPPGen::new(&mut s);
    _structures
        .iter()
        .map(|v| v.gen_cpp(&mut gen))
        .collect::<Result<Vec<_>>>()?;
    println!("{s}");

    Ok(())
}
