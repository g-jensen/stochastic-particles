mod r#static;

fn arg_float(args: &[String], flag: &str, default: f32) -> f32 {
    args.windows(2)
        .find(|w| w[0] == flag)
        .and_then(|w| w[1].parse().ok())
        .unwrap_or(default)
}

fn main() {
    let args: Vec<String> = std::env::args().collect();
    let phase = arg_float(&args, "-phase", 0.0);
    let on_ratio = arg_float(&args, "-on-ratio", 0.5);
    let travel_time = arg_float(&args, "-travel-time", 0.3);
    println!("{}", r#static::max_laps(phase, travel_time, on_ratio));
}
