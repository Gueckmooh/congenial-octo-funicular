#[derive(clap::Parser, Debug)]
#[command(version, about, long_about=None)]
pub struct Args {
    #[arg(short, long)]
    pub file: String,
}
