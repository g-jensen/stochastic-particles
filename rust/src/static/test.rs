use super::*;
use fraction::Fraction;

fn f(n: u64, d: u64) -> Fraction {
    Fraction::new(n, d)
}

#[test]
fn should_pass_lap_zero_phase_within_on_ratio() {
    assert_eq!(
        should_pass_lap(&Fraction::new(0u64, 1u64), 0, &f(1, 1), &f(1, 2)),
        true
    );
}

#[test]
fn should_pass_lap_phase_beyond_on_ratio() {
    assert_eq!(should_pass_lap(&f(3, 5), 0, &f(1, 1), &f(1, 2)), false);
}

#[test]
fn should_pass_lap_count_pushes_phase_beyond_on_ratio() {
    assert_eq!(should_pass_lap(&f(1, 5), 1, &f(1, 2), &f(1, 2)), false);
}

#[test]
fn should_pass_lap_wraps_phase_past_one() {
    assert_eq!(should_pass_lap(&f(4, 5), 1, &f(1, 2), &f(1, 2)), true);
}

#[test]
fn max_laps_counts_consecutive_passing_laps() {
    assert_eq!(max_laps(&Fraction::new(0u64, 1u64), &f(3, 10), &f(1, 2)), 1);
}

#[test]
fn max_laps_zero_when_phase_beyond_on_ratio() {
    assert_eq!(max_laps(&f(3, 5), &f(3, 10), &f(1, 2)), 0);
}

#[test]
fn max_laps_offsets_by_phase() {
    assert_eq!(max_laps(&f(3, 50), &f(11, 20), &f(13, 20)), 2);
}
