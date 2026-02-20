use super::*;
use crate::basic::test::frac;

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
fn lap_count_counts_consecutive_passing_laps() {
    assert_eq!(
        lap_count(&frac(0, 1), &frac(3, 10), &frac(1, 2), 100),
        Some(1)
    );
}

#[test]
fn lap_count_zero_when_phase_beyond_on_ratio() {
    assert_eq!(
        lap_count(&frac(3, 5), &frac(3, 10), &frac(1, 2), 100),
        Some(0)
    );
}

#[test]
fn lap_count_offsets_by_phase() {
    assert_eq!(
        lap_count(&frac(3, 50), &frac(11, 20), &frac(13, 20), 100),
        Some(2)
    );
}

#[test]
fn lap_count_none_if_max_laps_exceeded() {
    assert_eq!(
        lap_count(&frac(3, 50), &frac(11, 20), &frac(13, 20), 1),
        None
    );
}

#[test]
fn lap_count_none_if_infinite_laps() {
    assert_eq!(lap_count(&frac(0, 1), &frac(1, 2), &frac(7, 10), 100), None);
}
