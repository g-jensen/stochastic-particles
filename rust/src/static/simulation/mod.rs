#[cfg(test)]
mod test;

use fraction::Fraction;

pub fn should_pass_lap(
    phase: &Fraction,
    lap_count: u32,
    travel_time: &Fraction,
    on_ratio: &Fraction,
) -> bool {
    let lap_count = Fraction::from(lap_count as u64);
    let one = Fraction::from(1u64);
    (phase + lap_count * (*travel_time)) % one <= (*on_ratio)
}

pub fn max_laps(phase: &Fraction, travel_time: &Fraction, on_ratio: &Fraction) -> u32 {
    let mut laps = 0;
    while should_pass_lap(phase, laps + 1, travel_time, on_ratio) {
        laps += 1;
    }
    laps
}
