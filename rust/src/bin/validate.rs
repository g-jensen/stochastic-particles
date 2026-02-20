use fraction::Fraction;
use stochastic::basic::{sampling, simulation, theory, validation};
use stochastic::cli::{arg_fraction, arg_uint};

fn main() {
    let args: Vec<String> = std::env::args().collect();
    let granularity = arg_uint(&args, "-granularity", 10);
    let max_travel_time = arg_fraction(&args, "-max-travel-time", Fraction::new(1u64, 1u64));
    let max_laps = arg_uint(&args, "-max-laps", granularity+1);

    let mut count = 0u64;
    let mut error = None;

    sampling::sample(
        granularity,
        max_travel_time,
        &mut |phase, travel_time, on_ratio| {
            if error.is_some() {
                return;
            }
            count += 1;
            if let Err(e) = validation::validate(
                &phase,
                &travel_time,
                &on_ratio,
                theory::lap_count,
                simulation::lap_count,
                max_laps,
            ) {
                error = Some(e);
            }
        },
    );

    println!("Validated {count} input combinations.");

    match error {
        None => println!("All inputs match."),
        Some(e) => {
            println!("Mismatch found!");
            println!("  phase: {}", e.phase);
            println!("  travel_time: {}", e.travel_time);
            println!("  on_ratio: {}", e.on_ratio);
            println!("  simulation: {:?}", e.simulation_result);
            println!("  theory: {:?}", e.theory_result);
        }
    }
}
