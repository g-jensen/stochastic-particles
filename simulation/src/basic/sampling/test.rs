use super::*;
use crate::basic::test::frac;

#[test]
fn sample_phase_produces_1_combinations_for_granularity_1() {
    let mut calls: Vec<Fraction> = Vec::new();
    sample_phase(1, &mut |phase| {
        calls.push(phase);
    });
    assert_eq!(calls, vec![frac(0,1)]);
}

#[test]
fn sample_phase_produces_2_combinations_for_granularity_2() {
    let mut calls: Vec<Fraction> = Vec::new();
    sample_phase(2, &mut |phase| {
        calls.push(phase);
    });
    assert_eq!(calls, vec![frac(0,2), frac(1,2)]);
}

#[test]
fn sample_phase_produces_3_combinations_for_granularity_3() {
    let mut calls: Vec<Fraction> = Vec::new();
    sample_phase(3, &mut |phase| {
        calls.push(phase);
    });
    assert_eq!(calls, vec![frac(0,3), frac(1,3), frac(2,3)]);
}

#[test]
fn sample_on_ratio_produces_0_combinations_for_granularity_1() {
    let mut calls: Vec<Fraction> = Vec::new();
    sample_on_ratio(1, &mut |phase| {
        calls.push(phase);
    });
    assert_eq!(calls, vec![]);
}

#[test]
fn sample_on_ratio_produces_1_combinations_for_granularity_2() {
    let mut calls: Vec<Fraction> = Vec::new();
    sample_on_ratio(2, &mut |phase| {
        calls.push(phase);
    });
    assert_eq!(calls, vec![frac(1,2)]);
}

#[test]
fn sample_on_ratio_produces_2_combinations_for_granularity_3() {
    let mut calls: Vec<Fraction> = Vec::new();
    sample_on_ratio(3, &mut |phase| {
        calls.push(phase);
    });
    assert_eq!(calls, vec![frac(1,3), frac(2,3)]);
}

#[test]
fn sample_travel_time_behaves_like_ratio_with_max_1() {
    let one = frac(1,1);
    let mut calls: Vec<Fraction> = Vec::new();
    sample_travel_time(one, 1, &mut |phase| {
        calls.push(phase);
    });
    assert_eq!(calls, vec![]);

    let mut calls: Vec<Fraction> = Vec::new();
    sample_travel_time(one, 2, &mut |phase| {
        calls.push(phase);
    });
    assert_eq!(calls, vec![frac(1,2)]);

    let mut calls: Vec<Fraction> = Vec::new();
    sample_travel_time(one, 3, &mut |phase| {
        calls.push(phase);
    });
    assert_eq!(calls, vec![frac(1,3), frac(2,3)]);
}

#[test]
fn sample_travel_time_granulates_up_to_max() {
    let mut calls: Vec<Fraction> = Vec::new();
    sample_travel_time(frac(2,1), 2, &mut |phase| {
        calls.push(phase);
    });
    assert_eq!(calls, vec![frac(1,1)]);

    let mut calls: Vec<Fraction> = Vec::new();
    sample_travel_time(frac(3,1), 2, &mut |phase| {
        calls.push(phase);
    });
    assert_eq!(calls, vec![frac(3,2)]);

    let mut calls: Vec<Fraction> = Vec::new();
    sample_travel_time(frac(1,1), 3, &mut |phase| {
        calls.push(phase);
    });
    assert_eq!(calls, vec![frac(1,3), frac(2,3)]);

    let mut calls: Vec<Fraction> = Vec::new();
    sample_travel_time(frac(3,1), 3, &mut |phase| {
        calls.push(phase);
    });
    assert_eq!(calls, vec![frac(1,1), frac(2,1)]);
}

#[test]
fn sample_does_not_call_callback_for_granularity_1() {
    let mut calls: Vec<(Fraction, Fraction, Fraction)> = Vec::new();
    sample_all(1, frac(1, 1), &mut |phase, travel_time, on_ratio| {
        calls.push((phase, travel_time, on_ratio));
    });
    assert_eq!(calls, vec![]);
}

#[test]
fn sample_produces_4_combinations_for_granularity_2() {
    let mut calls: Vec<(Fraction, Fraction, Fraction)> = Vec::new();
    sample_all(2, frac(1, 1), &mut |phase, travel_time, on_ratio| {
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
    sample_all(3, frac(1, 1), &mut |phase, travel_time, on_ratio| {
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
    sample_all(2, frac(3, 2), &mut |phase, travel_time, on_ratio| {
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
