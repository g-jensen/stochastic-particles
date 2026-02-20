#[cfg(test)]
mod test;

use fraction::Fraction;

pub fn sample(
    granularity: u64,
    max_travel_time: Fraction,
    callback: &mut impl FnMut(Fraction, Fraction, Fraction),
) {
    each_unit_fraction(granularity, &mut |phase| {
        sample_travel_times_for_phase(granularity, max_travel_time, phase, callback);
    });
}

fn sample_travel_times_for_phase(
    granularity: u64,
    max_travel_time: Fraction,
    phase: Fraction,
    callback: &mut impl FnMut(Fraction, Fraction, Fraction),
) {
    let step = Fraction::new(1u64, granularity);
    for tt_i in 1u64.. {
        let travel_time = step * Fraction::from(tt_i);
        if travel_time > max_travel_time {
            break;
        }
        each_unit_fraction(granularity, &mut |on_ratio| {
            callback(phase, travel_time, on_ratio);
        });
    }
}

fn each_unit_fraction(granularity: u64, body: &mut impl FnMut(Fraction)) {
    for i in 0..granularity {
        body(Fraction::new(i, granularity));
    }
}
