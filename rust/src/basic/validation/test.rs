use super::*;
use crate::basic::test::frac;

#[test]
fn validate_returns_ok_when_both_functions_agree() {
    let inputs = vec![(frac(1, 4), frac(1, 2), frac(1, 3))];
    let result = validate(
        &inputs,
        |_phase, _travel_time, _on_ratio| Some(1),
        |_phase, _travel_time, _on_ratio, _max_laps| Some(1),
        100,
    );
    assert_eq!(result, Ok(()));
}

#[test]
fn validate_returns_err_when_functions_disagree() {
    let inputs = vec![(frac(1, 4), frac(1, 2), frac(1, 3))];
    let result = validate(
        &inputs,
        |_phase, _travel_time, _on_ratio| Some(2),
        |_phase, _travel_time, _on_ratio, _max_laps| Some(1),
        100,
    );
    assert_eq!(
        result,
        Err(ValidationError {
            phase: frac(1, 4),
            travel_time: frac(1, 2),
            on_ratio: frac(1, 3),
            simulation_result: Some(1),
            theory_result: Some(2),
        })
    );
}

#[test]
fn validate_passes_max_laps_to_simulation_fn() {
    let inputs = vec![(frac(1, 4), frac(1, 2), frac(1, 3))];
    let result = validate(
        &inputs,
        |_phase, _travel_time, _on_ratio| None,
        |_phase, _travel_time, _on_ratio, max_laps| {
            if max_laps == 0 {
                None
            } else {
                Some(max_laps)
            }
        },
        0,
    );
    assert_eq!(result, Ok(()));
}
