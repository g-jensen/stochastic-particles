#[cfg(test)]
mod test;

pub mod laps;
pub mod lifespan;

use fraction::Fraction;

fn should_pass_lap(
    phase: &Fraction,
    lap_count: u64,
    travel_time: &Fraction,
    on_ratio: &Fraction,
) -> bool {
    (phase + (travel_time * lap_count)) % 1 < (*on_ratio)
}

pub fn lap_count(
    phase: &Fraction,
    travel_time: &Fraction,
    on_ratio: &Fraction,
    max_laps: u64,
) -> Option<u64> {
    let mut num_laps = 0;
    while should_pass_lap(phase, num_laps, travel_time, on_ratio) {
        if num_laps > max_laps {
            return None;
        }
        num_laps += 1;
    }
    Some(num_laps)
}
