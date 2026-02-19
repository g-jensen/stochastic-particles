#[cfg(test)]
mod test;

use fraction::Fraction;

#[derive(Debug, PartialEq)]
pub struct ValidationError {
    pub phase: Fraction,
    pub travel_time: Fraction,
    pub on_ratio: Fraction,
    pub simulation_result: Option<u64>,
    pub theory_result: Option<u64>,
}

pub fn validate(
    inputs: &[(Fraction, Fraction, Fraction)],
    theory_fn: impl Fn(&Fraction, &Fraction, &Fraction) -> Option<u64>,
    simulation_fn: impl Fn(&Fraction, &Fraction, &Fraction, u64) -> Option<u64>,
    max_laps: u64,
) -> Result<(), ValidationError> {
    for (phase, travel_time, on_ratio) in inputs {
        let simulation_result = simulation_fn(phase, travel_time, on_ratio, max_laps);
        let theory_result = theory_fn(phase, travel_time, on_ratio);
        if simulation_result != theory_result {
            return Err(ValidationError {
                phase: phase.clone(),
                travel_time: travel_time.clone(),
                on_ratio: on_ratio.clone(),
                simulation_result,
                theory_result,
            });
        }
    }
    Ok(())
}
