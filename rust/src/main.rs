mod r#static;

use fraction::Fraction;
use r#static::simulation;

fn arg_fraction(args: &[String], flag: &str, default: Fraction) -> Fraction {
    args.windows(2)
        .find(|w| w[0] == flag)
        .and_then(|w| w[1].parse().ok())
        .unwrap_or(default)
}

fn arg_uint(args: &[String], flag: &str, default: u64) -> u64 {
    args.windows(2)
        .find(|w| w[0] == flag)
        .and_then(|w| w[1].parse().ok())
        .unwrap_or(default)
}
 
fn main() {
    let args: Vec<String> = std::env::args().collect();
    let phase = arg_fraction(&args, "-phase", Fraction::from(0u64));
    let on_ratio = arg_fraction(&args, "-on-ratio", Fraction::new(1u64, 2u64));
    let travel_time = arg_fraction(&args, "-travel-time", Fraction::new(3u64, 10u64));
    let max_laps = arg_uint(&args, "-max-laps", 1_000_000);
    println!("{:#?}", simulation::lap_count(&phase, &travel_time, &on_ratio,max_laps));
}
