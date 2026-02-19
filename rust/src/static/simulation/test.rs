use super::*;
use crate::r#static::test::frac;

#[test]
fn should_pass_lap_zero_phase_within_on_ratio() {
    assert_eq!(
        should_pass_lap(&frac(0, 1), 0, &frac(1, 1), &frac(1, 2)),
        true
    );
}

#[test]
fn should_pass_lap_phase_beyond_on_ratio() {
    assert_eq!(
        should_pass_lap(&frac(3, 5), 0, &frac(1, 1), &frac(1, 2)),
        false
    );
}

#[test]
fn should_pass_lap_count_pushes_phase_beyond_on_ratio() {
    assert_eq!(
        should_pass_lap(&frac(1, 5), 1, &frac(1, 2), &frac(1, 2)),
        false
    );
}

#[test]
fn should_pass_lap_wraps_phase_past_one() {
    assert_eq!(
        should_pass_lap(&frac(4, 5), 1, &frac(1, 2), &frac(1, 2)),
        true
    );
}

#[test]
fn max_laps_counts_consecutive_passing_laps() {
    assert_eq!(max_laps(&frac(0u64, 1u64), &frac(3, 10), &frac(1, 2)), 1);
}

#[test]
fn max_laps_zero_when_phase_beyond_on_ratio() {
    assert_eq!(max_laps(&frac(3, 5), &frac(3, 10), &frac(1, 2)), 0);
}

#[test]
fn max_laps_offsets_by_phase() {
    assert_eq!(max_laps(&frac(3, 50), &frac(11, 20), &frac(13, 20)), 2);
}
