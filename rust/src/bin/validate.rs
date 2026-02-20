use fraction::Fraction;
use stochastic::basic::{sampling, simulation, theory, validation};
use stochastic::cli::{arg_fraction, arg_uint};

fn main() {
    let args: Vec<String> = std::env::args().collect();
    let granularity = arg_uint(&args, "-granularity", 10);
    let max_travel_time = arg_fraction(&args, "-max-travel-time", Fraction::new(3u64, 1u64));
    let max_laps = arg_uint(&args, "-max-laps", 1_000_000);

    let mut inputs: Vec<(Fraction, Fraction, Fraction)> = Vec::new();
    sampling::sample(
        granularity,
        max_travel_time,
        &mut |phase, travel_time, on_ratio| {
            inputs.push((phase, travel_time, on_ratio));
        },
    );

    println!("Validating {} input combinations...", inputs.len());

    match validation::validate(&inputs, theory::lap_count, simulation::lap_count, max_laps) {
        Ok(()) => println!("All inputs match."),
        Err(e) => {
            println!("Mismatch found!");
            println!("  phase: {}", e.phase);
            println!("  travel_time: {}", e.travel_time);
            println!("  on_ratio: {}", e.on_ratio);
            println!("  simulation: {:?}", e.simulation_result);
            println!("  theory: {:?}", e.theory_result);
        }
    }
}
