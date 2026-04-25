use super::*;
use crate::basic::test::frac;

#[test]
fn optimize_single_sample_returns_it() {
    let result = optimize(
        frac(1, 4),
        frac(1, 2),
        2,
        frac(1, 1),
        |_phase, _travel_time, _on_ratio| Some(3),
    );
    assert_eq!(result, (frac(1, 2), Some(3)));
}

#[test]
fn optimize_picks_largest_lap_count() {
    let result = optimize(
        frac(1, 4),
        frac(1, 2),
        4,
        frac(1, 1),
        |_phase, travel_time, _on_ratio| {
            if *travel_time == frac(1, 4) {
                Some(5)
            } else if *travel_time == frac(1, 2) {
                Some(10)
            } else {
                Some(2)
            }
        },
    );
    assert_eq!(result, (frac(1, 2), Some(10)));
}

#[test]
fn optimize_picks_none_as_infinite_laps() {
    let result = optimize(
        frac(1, 4),
        frac(1, 2),
        4,
        frac(1, 1),
        |_phase, travel_time, _on_ratio| {
            if *travel_time == frac(1, 4) {
                Some(100)
            } else if *travel_time == frac(1, 2) {
                None
            } else {
                Some(5)
            }
        },
    );
    assert_eq!(result, (frac(1, 2), None));
}

#[test]
fn optimize_forwards_phase_and_on_ratio_to_lap_fn() {
    let result = optimize(
        frac(3, 7),
        frac(5, 9),
        3,
        frac(1, 1),
        |phase, travel_time, on_ratio| {
            if *phase == frac(3, 7) && *on_ratio == frac(5, 9) && *travel_time == frac(2, 3) {
                Some(20)
            } else {
                Some(0)
            }
        },
    );
    assert_eq!(result, (frac(2, 3), Some(20)));
}

#[test]
fn optimize_tie_prefers_last_travel_time() {
    let result = optimize(
        frac(1, 4),
        frac(1, 2),
        4,
        frac(1, 1),
        |_phase, _travel_time, _on_ratio| Some(5),
    );
    assert_eq!(result, (frac(3, 4), Some(5)));
}

#[test]
fn optimize_samples_up_to_max_travel_time() {
    let result = optimize(
        frac(1, 4),
        frac(1, 2),
        3,
        frac(2, 1),
        |_phase, travel_time, _on_ratio| {
            if *travel_time == frac(4, 3) {
                Some(7)
            } else {
                Some(1)
            }
        },
    );
    assert_eq!(result, (frac(4, 3), Some(7)));
}
