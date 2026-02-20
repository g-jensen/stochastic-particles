use fraction::Fraction;
use stochastic::basic::simulation;
use stochastic::cli::{arg_fraction, arg_uint};

fn main() {
    let args: Vec<String> = std::env::args().collect();
    let phase = arg_fraction(&args, "-phase", Fraction::from(0u64));
    let on_ratio = arg_fraction(&args, "-on-ratio", Fraction::new(1u64, 2u64));
    let travel_time = arg_fraction(&args, "-travel-time", Fraction::new(3u64, 10u64));
    let max_laps = arg_uint(&args, "-max-laps", 1_000_000);
    println!(
        "{:#?}",
        simulation::lap_count(&phase, &travel_time, &on_ratio, max_laps)
    );
}
