use std::fs::File;
use std::io::{self, BufWriter, Write};

use fraction::{ConstOne, Fraction};
use stochastic::basic::{lifespan, sampling, simulation, theory};
use stochastic::cli::{arg};

#[derive(Debug)]
enum Strategy {
    THEORY,
    SIMULATION
}

fn main() -> io::Result<()> {
    let args: Vec<String> = std::env::args().collect();
    let granularity = arg(&args, "-granularity", 10);
    let max_travel_time = arg(&args, "-max-travel-time", Fraction::ONE);
    let max_laps = arg(&args, "-max-laps", granularity+1);
    let output_path = arg(&args, "-output", String::from("output.csv"));
    let strategy_name = arg(&args, "-strategy", String::from("theory"));
    let strategy =
     if strategy_name.to_lowercase() == "theory" 
        {Strategy::THEORY}
        else {Strategy::SIMULATION};
    let simulation_lap_fn: &dyn Fn(&Fraction, &Fraction, &Fraction) -> Option<u64> = 
    &|p,t,o| {
        simulation::lap_count(p,t,o,max_laps)
    };
    let file = File::create(output_path)?;
    let mut writer = BufWriter::new(file);

    let mut count = 0u64;

    println!("Using strategy: {:#?}",strategy);
    writeln!(writer, "phase, on_ratio, optimal_travel_time, optimal_lifespan")?;
    sampling::sample_phase(granularity, &mut |phase| {
        sampling::sample_on_ratio(granularity, &mut |on_ratio| {
            let lap_fn: &dyn Fn(&Fraction, &Fraction, &Fraction) -> Option<u64>;
            match strategy {
                Strategy::THEORY => lap_fn = &theory::lap_count,
                Strategy::SIMULATION => lap_fn = simulation_lap_fn,
            }
            let (travel_time, lifespan) = lifespan::optimize(phase, on_ratio, granularity, max_travel_time, lap_fn);
            writeln!(writer, "{}, {}, {}, {}", &phase, &on_ratio, &travel_time, lifespan.to_string()).unwrap();
            count += 1;
        });
    });

    println!("Simulated {count} input combinations.");
    Ok(())
}
