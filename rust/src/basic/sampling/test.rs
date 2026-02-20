use super::*;
use crate::basic::test::frac;

#[test]
fn sample_does_not_call_callback_for_granularity_1() {
    let mut calls: Vec<(Fraction, Fraction, Fraction)> = Vec::new();
    sample(1, frac(1, 1), &mut |phase, travel_time, on_ratio| {
        calls.push((phase, travel_time, on_ratio));
    });
    assert_eq!(calls, vec![]);
}

#[test]
fn sample_produces_4_combinations_for_granularity_2() {
    let mut calls: Vec<(Fraction, Fraction, Fraction)> = Vec::new();
    sample(2, frac(1, 1), &mut |phase, travel_time, on_ratio| {
        calls.push((phase, travel_time, on_ratio));
    });
    assert_eq!(
        calls,
        vec![
            (frac(0, 2), frac(1, 2), frac(1, 2)),
            (frac(1, 2), frac(1, 2), frac(1, 2)),
        ]
    );
}

#[test]
fn sample_produces_12_combinations_for_granularity_3() {
    let mut calls: Vec<(Fraction, Fraction, Fraction)> = Vec::new();
    sample(3, frac(1, 1), &mut |phase, travel_time, on_ratio| {
        calls.push((phase, travel_time, on_ratio));
    });
    assert_eq!(
        calls,
        vec![
            (frac(0, 3), frac(1, 3), frac(1, 3)),
            (frac(0, 3), frac(2, 3), frac(1, 3)),
            (frac(0, 3), frac(1, 3), frac(2, 3)),
            (frac(0, 3), frac(2, 3), frac(2, 3)),
            
            (frac(1, 3), frac(1, 3), frac(1, 3)),
            (frac(1, 3), frac(2, 3), frac(1, 3)),
            (frac(1, 3), frac(1, 3), frac(2, 3)),
            (frac(1, 3), frac(2, 3), frac(2, 3)),

            (frac(2, 3), frac(1, 3), frac(1, 3)),
            (frac(2, 3), frac(2, 3), frac(1, 3)),
            (frac(2, 3), frac(1, 3), frac(2, 3)),
            (frac(2, 3), frac(2, 3), frac(2, 3)),
        ]
    );
}

#[test]
fn sample_travel_time_has_granularity_minus_one_steps() {
    let mut calls: Vec<(Fraction, Fraction, Fraction)> = Vec::new();
    sample(2, frac(3, 2), &mut |phase, travel_time, on_ratio| {
        calls.push((phase, travel_time, on_ratio));
    });
    assert_eq!(
        calls,
        vec![
            (frac(0, 2), frac(3, 4), frac(1, 2)),
            (frac(1, 2), frac(3, 4), frac(1, 2)),
        ]
    );
}
