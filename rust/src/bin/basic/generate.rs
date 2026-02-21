use std::fs::File;
use std::io::{self, BufWriter, Write};

use fraction::Fraction;
use stochastic::basic::{sampling, simulation, theory};
use stochastic::cli::{arg};

#[derive(Debug)]
enum Strategy {
    THEORY,
    SIMULATION
}

fn main() -> io::Result<()> {
    let args: Vec<String> = std::env::args().collect();
    let granularity = arg(&args, "-granularity", 10);
    let max_travel_time = arg(&args, "-max-travel-time", Fraction::new(1u64, 1u64));
    let max_laps = arg(&args, "-max-laps", granularity+1);
    let output_path = arg(&args, "-output", String::from("output.csv"));
    let strategy_name = arg(&args, "-strategy", String::from("theory"));
    let strategy =
     if strategy_name.to_lowercase() == "theory" 
        {Strategy::THEORY}
        else {Strategy::SIMULATION};
    let file = File::create(output_path)?;
    let mut writer = BufWriter::new(file);

    let mut count = 0u64;

    println!("Using strategy: {:#?}",strategy);
    writeln!(writer, "phase, on_ratio, travel_time, lifespan")?;
    sampling::sample_all(
        granularity,
        max_travel_time,
        &mut |phase, travel_time, on_ratio| {
            count += 1;
            let laps_opt;
            match strategy {
                Strategy::THEORY => laps_opt = theory::lap_count(&phase,&travel_time,&on_ratio),
                Strategy::SIMULATION => laps_opt = simulation::lap_count(&phase,&travel_time,&on_ratio,max_laps),
            }
            let lifespan_opt = laps_opt.and_then(|laps| Some(Fraction::from(laps+1) * travel_time));
            let lifespan_str = lifespan_opt.and_then(|lifespan| Some(lifespan.to_string())).or(Some(String::from("inf"))).unwrap();
            writeln!(writer, "{}, {}, {}, {}", &phase, &on_ratio, &travel_time, lifespan_str).unwrap();
        },
    );

    println!("Simulated {count} input combinations.");
    Ok(())
}
