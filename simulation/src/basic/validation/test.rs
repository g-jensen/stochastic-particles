use super::*;
use crate::basic::test::frac;

#[test]
fn validate_returns_ok_when_both_functions_agree() {
    let result = validate(
        &frac(1, 4),
        &frac(1, 2),
        &frac(1, 3),
        |_phase, _travel_time, _on_ratio| Some(1),
        |_phase, _travel_time, _on_ratio, _max_laps| Some(1),
        100,
    );
    assert_eq!(result, Ok(()));
}

#[test]
fn validate_returns_err_when_functions_disagree() {
    let result = validate(
        &frac(1, 4),
        &frac(1, 2),
        &frac(1, 3),
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
            simulation_result: Ok(Some(1)),
            theory_result: Ok(Some(2)),
        })
    );
}

#[test]
fn validate_returns_err_when_theory_fn_panics() {
    let result = validate(
        &frac(1, 4),
        &frac(1, 2),
        &frac(1, 3),
        |_phase, _travel_time, _on_ratio| panic!("overflow"),
        |_phase, _travel_time, _on_ratio, _max_laps| Some(1),
        100,
    );
    assert_eq!(
        result,
        Err(ValidationError {
            phase: frac(1, 4),
            travel_time: frac(1, 2),
            on_ratio: frac(1, 3),
            simulation_result: Ok(Some(1)),
            theory_result: Err("overflow".to_string()),
        })
    );
}

#[test]
fn validate_passes_max_laps_to_simulation_fn() {
    let result = validate(
        &frac(1, 4),
        &frac(1, 2),
        &frac(1, 3),
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
