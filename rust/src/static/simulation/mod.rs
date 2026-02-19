#[cfg(test)]
mod test;

use fraction::Fraction;

pub fn should_pass_lap(
    phase: &Fraction,
    lap_count: u64,
    travel_time: &Fraction,
    on_ratio: &Fraction,
) -> bool {
    let lap_count = Fraction::from(lap_count);
    let one = Fraction::from(1u64);
    (phase + lap_count * (*travel_time)) % one <= (*on_ratio)
}

pub fn lap_count(
    phase: &Fraction, 
    travel_time: &Fraction, 
    on_ratio: &Fraction, 
    max_laps: u64
)-> Option<u64> {
    let mut num_laps = 0;
    while should_pass_lap(phase, num_laps + 1, travel_time, on_ratio) {
        num_laps += 1;
        if num_laps > max_laps {return None}
    }
    Some(num_laps)
}
