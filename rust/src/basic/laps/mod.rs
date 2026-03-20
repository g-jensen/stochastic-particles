#[cfg(test)]
mod test;

use fraction::Fraction;

use crate::basic::sampling::sample_travel_time;

fn gte_laps(candidate: Option<u64>, current: Option<u64>) -> bool {
    match (candidate, current) {
        (None, _) => true,
        (_, None) => false,
        (Some(a), Some(b)) => a >= b,
    }
}

pub fn optimize(
    phase: Fraction,
    on_ratio: Fraction,
    granularity: u64,
    max_travel_time: Fraction,
    lap_fn: impl Fn(&Fraction, &Fraction, &Fraction) -> Option<u64>,
) -> (Fraction, Option<u64>) {
    let mut best: Option<(Fraction, Option<u64>)> = None;
    sample_travel_time(max_travel_time, granularity, &mut |travel_time| {
        let laps = lap_fn(&phase, &travel_time, &on_ratio);
        let dominated = best
            .as_ref()
            .map_or(true, |current| gte_laps(laps, current.1));
        if dominated {
            best = Some((travel_time, laps));
        }
    });
    best.unwrap_or_default()
}
