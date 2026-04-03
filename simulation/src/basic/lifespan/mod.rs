use fraction::{ConstZero, Fraction, Sign};

use crate::basic::sampling::sample_travel_time;

#[cfg(test)]
mod test;

fn lifespan_from_lap_count(lap_count: Option<u64>, travel_time: Fraction) -> Fraction {
    lap_count
        .and_then(|laps| Some(travel_time*(laps+1)))
        .unwrap_or(Fraction::Infinity(Sign::Plus))
}

pub fn optimize(
    phase: Fraction, 
    on_ratio: Fraction, 
    granularity: u64,
    max_travel_time: Fraction, 
    lap_fn: impl Fn(&Fraction,&Fraction,&Fraction) -> Option<u64>
) -> (Fraction, Fraction) {
    let (mut  optimal_travel_time, mut optimal_lifespan) = (Fraction::ZERO,Fraction::ZERO);
    sample_travel_time(max_travel_time, granularity, &mut |travel_time| {
        let lap_count_opt = lap_fn(&phase, &travel_time, &on_ratio);
        let lifespan = lifespan_from_lap_count(lap_count_opt,travel_time);
        if lifespan >= optimal_lifespan {
            (optimal_travel_time,optimal_lifespan) = (travel_time,lifespan);
        }
    });
    (optimal_travel_time,optimal_lifespan)
}