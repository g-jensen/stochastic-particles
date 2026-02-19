#[cfg(test)]
mod test;

pub fn mod_f(a: f32, b: f32) -> f32 {
    a - b * ((a as i32) / (b as i32)) as f32
}

pub fn should_pass_lap(phase: f32, lap_count: u32, travel_time: f32, on_ratio: f32) -> bool {
    mod_f(phase + (lap_count as f32 * travel_time), 1.0) <= on_ratio
}

pub fn max_laps(phase: f32, travel_time: f32, on_ratio: f32) -> u32 {
    let mut laps = 0;
    while should_pass_lap(phase, laps+1, travel_time, on_ratio) {
        laps += 1;
    }
    laps
}
