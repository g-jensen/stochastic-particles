#[cfg(test)]
mod test;

use std::panic::{catch_unwind, AssertUnwindSafe};

use fraction::Fraction;

#[derive(Debug, PartialEq)]
pub struct ValidationError {
    pub phase: Fraction,
    pub travel_time: Fraction,
    pub on_ratio: Fraction,
    pub simulation_result: Result<Option<u64>, String>,
    pub theory_result: Result<Option<u64>, String>,
}

fn panic_to_string(err: Box<dyn std::any::Any + Send>) -> String {
    if let Some(s) = err.downcast_ref::<&str>() {
        s.to_string()
    } else if let Some(s) = err.downcast_ref::<String>() {
        s.clone()
    } else {
        "unknown panic".to_string()
    }
}

pub fn validate(
    phase: &Fraction,
    travel_time: &Fraction,
    on_ratio: &Fraction,
    theory_fn: impl Fn(&Fraction, &Fraction, &Fraction) -> Option<u64>,
    simulation_fn: impl Fn(&Fraction, &Fraction, &Fraction, u64) -> Option<u64>,
    max_laps: u64,
) -> Result<(), ValidationError> {
    let simulation_result = catch_unwind(AssertUnwindSafe(|| {
        simulation_fn(phase, travel_time, on_ratio, max_laps)
    }))
    .map_err(panic_to_string);

    let theory_result = catch_unwind(AssertUnwindSafe(|| theory_fn(phase, travel_time, on_ratio)))
        .map_err(panic_to_string);

    let is_match = matches!((&simulation_result, &theory_result), (Ok(s), Ok(t)) if s == t);

    if !is_match {
        return Err(ValidationError {
            phase: phase.clone(),
            travel_time: travel_time.clone(),
            on_ratio: on_ratio.clone(),
            simulation_result,
            theory_result,
        });
    }
    Ok(())
}
