#[cfg(test)]
mod test;

use fraction::{Fraction};

use crate::basic::sampling::sample_travel_time;

fn gt_laps(candidate: Option<u64>, current: Option<u64>) -> bool {
    match (candidate, current) {
        (None, _) => true,
        (_, None) => false,
        (Some(a), Some(b)) => a > b,
    }
}

pub fn optimize(
    phase: Fraction,
    on_ratio: Fraction,
    granularity: u64,
    max_travel_time: Fraction,
    lap_fn: impl Fn(&Fraction, &Fraction, &Fraction) -> Option<u64>,
) -> (Vec<Fraction>, Option<u64>) {
    let mut best: (Vec<Fraction>, Option<u64>) = (vec![],Some(0));
    sample_travel_time(max_travel_time, granularity, &mut |travel_time| {
        let laps = lap_fn(&phase, &travel_time, &on_ratio);
        if laps == best.1 {
            best.0.push(travel_time);
        }
        if gt_laps(laps, best.1) {
            best = (vec![travel_time], laps);
        }
    });
    best
}
