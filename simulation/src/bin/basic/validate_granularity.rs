use fraction::Fraction;
use stochastic::basic::{laps, theory};
use stochastic::cli::{arg};

fn format_lap_count(lap_count: Option<u64>) -> String {
    match lap_count {
        Some(n) => return n.to_string(),
        None => return "inf".to_string()
    }
}

fn main() {
    let args: Vec<String> = std::env::args().collect();
    let max_travel_time = arg(&args, "-max-travel-time", Fraction::new(1u64, 1u64));
    let phase = arg(&args, "-p", Fraction::new(1_u64,2_u64));
    let on_ratio = arg(&args, "-r", Fraction::new(1_u64,2_u64));
    let first_granularity = arg(&args, "-g1", 120);
    let second_granularity = arg(&args, "-g2", 720);

    let (first_travel_time, first_lap_count) = laps::optimize(phase, on_ratio, first_granularity, max_travel_time, theory::lap_count);
    let (second_travel_time, second_lap_count) = laps::optimize(phase, on_ratio, second_granularity, max_travel_time, theory::lap_count);
    let formatted_first_lap_count = format_lap_count(first_lap_count);
    let formatted_second_lap_count = format_lap_count(second_lap_count);

    if first_lap_count != second_lap_count {
        println!("Found difference: g1={first_granularity}: {{travel_time={first_travel_time},lap_count={formatted_first_lap_count}}}, g2={second_granularity}: {{travel_time={second_travel_time},lap_count={formatted_second_lap_count}}} with phase={phase} and on_ratio={on_ratio}");
    } else {
        println!("Validated g1={first_granularity} vs g2={second_granularity} as {{travel_time={first_travel_time},lap_count={formatted_first_lap_count}}} with phase={phase} on_ratio={on_ratio}");
    }
}
