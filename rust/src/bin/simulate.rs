use std::fs::File;
use std::io::{self, BufWriter, Write};

use fraction::Fraction;
use stochastic::basic::{sampling, simulation};
use stochastic::cli::{arg};

fn main() -> io::Result<()> {
    let args: Vec<String> = std::env::args().collect();
    let granularity = arg(&args, "-granularity", 10);
    let max_travel_time = arg(&args, "-max-travel-time", Fraction::new(1u64, 1u64));
    let max_laps = arg(&args, "-max-laps", granularity+1);
    let output_path = arg(&args, "-output", String::from("output.csv"));
    let file = File::create(output_path)?;
    let mut writer = BufWriter::new(file);

    let mut count = 0u64;

    writeln!(writer, "phase, travel_time, on_ratio, laps")?;
    sampling::sample(
        granularity,
        max_travel_time,
        &mut |phase, travel_time, on_ratio| {
            count += 1;
            let laps_opt = simulation::lap_count(&phase,&travel_time,&on_ratio,max_laps);
            let laps_str = laps_opt.and_then(|lap_count| Some(lap_count.to_string())).or(Some(String::from("inf"))).unwrap();
            writeln!(writer, "{}, {}, {}, {}", &phase, &travel_time, &on_ratio, laps_str).unwrap();
        },
    );

    println!("Simulated {count} input combinations.");
    Ok(())
}
