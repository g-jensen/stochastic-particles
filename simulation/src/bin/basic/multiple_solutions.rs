use std::io::{self};

use fraction::{ConstOne, Fraction};
use stochastic::basic::simulation::{laps};
use stochastic::basic::{simulation, theory};
use stochastic::cli::{arg};

#[derive(Debug)]
enum Strategy {
    THEORY,
    SIMULATION
}

fn main() -> io::Result<()> {
    let args: Vec<String> = std::env::args().collect();
    let phase = arg(&args, "-phase", Fraction::new(1_u64, 2_u64));
    let on_ratio = arg(&args, "-on_ratio", Fraction::new(1_u64, 2_u64));
    let granularity = arg(&args, "-granularity", 120);
    let max_travel_time = arg(&args, "-max-travel-time", Fraction::ONE);
    let max_laps = arg(&args, "-max-laps", granularity+1);
    // let output_path = arg(&args, "-output", String::from("output.csv"));
    let strategy_name = arg(&args, "-strategy", String::from("theory"));
    let strategy =
     if strategy_name.to_lowercase() == "theory" 
        {Strategy::THEORY}
        else {Strategy::SIMULATION};
    let simulation_lap_fn: &dyn Fn(&Fraction, &Fraction, &Fraction) -> Option<u64> = 
    &|p,t,o| {
        simulation::lap_count(p,t,o,max_laps)
    };

    println!("Using strategy: {:#?}",strategy);
    let lap_fn: &dyn Fn(&Fraction, &Fraction, &Fraction) -> Option<u64>;
    match strategy {
        Strategy::THEORY => lap_fn = &theory::lap_count,
        Strategy::SIMULATION => lap_fn = simulation_lap_fn,
    }
    let (travel_times, laps) = laps::optimize(phase, on_ratio, granularity, max_travel_time, lap_fn);
    println!("phase: {},\non_ratio: {},\ntravel_times: {:?},\nlaps: {:?}", &phase, &on_ratio, travel_times, laps);

    Ok(())
}
