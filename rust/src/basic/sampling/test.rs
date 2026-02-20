use super::*;
use crate::basic::test::frac;

#[test]
fn sample_calls_callback_for_granularity_1() {
    let mut calls: Vec<(Fraction, Fraction, Fraction)> = Vec::new();
    sample(1, frac(1, 1), &mut |phase, travel_time, on_ratio| {
        calls.push((phase, travel_time, on_ratio));
    });
    assert_eq!(calls, vec![(frac(0, 1), frac(1, 1), frac(0, 1))]);
}

#[test]
fn sample_produces_8_combinations_for_granularity_2() {
    let mut calls: Vec<(Fraction, Fraction, Fraction)> = Vec::new();
    sample(2, frac(1, 1), &mut |phase, travel_time, on_ratio| {
        calls.push((phase, travel_time, on_ratio));
    });
    assert_eq!(
        calls,
        vec![
            (frac(0, 2), frac(1, 2), frac(0, 2)),
            (frac(0, 2), frac(1, 2), frac(1, 2)),
            (frac(0, 2), frac(2, 2), frac(0, 2)),
            (frac(0, 2), frac(2, 2), frac(1, 2)),
            (frac(1, 2), frac(1, 2), frac(0, 2)),
            (frac(1, 2), frac(1, 2), frac(1, 2)),
            (frac(1, 2), frac(2, 2), frac(0, 2)),
            (frac(1, 2), frac(2, 2), frac(1, 2)),
        ]
    );
}

#[test]
fn sample_includes_travel_times_beyond_granularity_steps() {
    let mut calls: Vec<(Fraction, Fraction, Fraction)> = Vec::new();
    sample(2, frac(3, 2), &mut |phase, travel_time, on_ratio| {
        calls.push((phase, travel_time, on_ratio));
    });
    assert_eq!(
        calls,
        vec![
            (frac(0, 2), frac(1, 2), frac(0, 2)),
            (frac(0, 2), frac(1, 2), frac(1, 2)),
            (frac(0, 2), frac(2, 2), frac(0, 2)),
            (frac(0, 2), frac(2, 2), frac(1, 2)),
            (frac(0, 2), frac(3, 2), frac(0, 2)),
            (frac(0, 2), frac(3, 2), frac(1, 2)),
            (frac(1, 2), frac(1, 2), frac(0, 2)),
            (frac(1, 2), frac(1, 2), frac(1, 2)),
            (frac(1, 2), frac(2, 2), frac(0, 2)),
            (frac(1, 2), frac(2, 2), frac(1, 2)),
            (frac(1, 2), frac(3, 2), frac(0, 2)),
            (frac(1, 2), frac(3, 2), frac(1, 2)),
        ]
    );
}
