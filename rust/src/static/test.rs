use super::*;

#[test]
fn mod_f_basic_remainder() {
    assert_eq!(mod_f(10.0, 3.0), 1.0);
}

#[test]
fn mod_f_fractional_input() {
    assert_eq!(mod_f(7.5, 2.0), 1.5);
}

#[test]
fn mod_f_evenly_divisible() {
    assert_eq!(mod_f(5.0, 5.0), 0.0);
}

#[test]
fn mod_f_dividend_smaller_than_divisor() {
    assert_eq!(mod_f(1.0, 3.0), 1.0);
}

#[test]
fn should_pass_lap_zero_phase_within_on_ratio() {
    assert_eq!(should_pass_lap(0.0, 0, 1.0, 0.5), true);
}

#[test]
fn should_pass_lap_phase_beyond_on_ratio() {
    assert_eq!(should_pass_lap(0.6, 0, 1.0, 0.5), false);
}

#[test]
fn should_pass_lap_count_pushes_phase_beyond_on_ratio() {
    assert_eq!(should_pass_lap(0.2, 1, 0.5, 0.5), false);
}

#[test]
fn should_pass_lap_wraps_phase_past_one() {
    assert_eq!(should_pass_lap(0.8, 1, 0.5, 0.5), true);
}

#[test]
fn max_laps_counts_consecutive_passing_laps() {
    assert_eq!(max_laps(0.0, 0.3, 0.5), 1);
}

#[test]
fn max_laps_zero_when_phase_beyond_on_ratio() {
    assert_eq!(max_laps(0.6, 0.3, 0.5), 0);
}

#[test]
fn max_laps_offsets_by_phase() {
    assert_eq!(max_laps(0.06, 0.55, 0.65), 2);
}