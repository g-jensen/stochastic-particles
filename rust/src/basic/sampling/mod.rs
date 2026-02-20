#[cfg(test)]
mod test;

use fraction::Fraction;

pub fn sample_phase(
    granularity: u64,
    callback: &mut impl FnMut(Fraction),
) {
    each_unit_fraction(granularity, 0, &mut |phase| {
        callback(phase)
    });
}

pub fn sample_on_ratio(
    granularity: u64,
    callback: &mut impl FnMut(Fraction),
) {
    each_unit_fraction(granularity, 1, &mut |on_ratio| {
        callback(on_ratio)
    });
}

pub fn sample(
    granularity: u64,
    max_travel_time: Fraction,
    callback: &mut impl FnMut(Fraction, Fraction, Fraction),
) {
    each_unit_fraction(granularity, 0, &mut |phase| {
        sample_travel_times_for_phase(granularity, max_travel_time, phase, callback);
    });
}

fn each_unit_fraction(granularity: u64, start: u64, body: &mut impl FnMut(Fraction)) {
    for i in start..granularity {
        body(Fraction::new(i, granularity));
    }
}

fn sample_travel_times_for_phase(
    granularity: u64,
    max_travel_time: Fraction,
    phase: Fraction,
    callback: &mut impl FnMut(Fraction, Fraction, Fraction),
) {
    let step = max_travel_time / granularity;
    each_unit_fraction(granularity, 1, &mut |on_ratio| {
        for tt_i in 1..granularity {
            let travel_time = step * tt_i;
            callback(phase, travel_time, on_ratio);
        }
    });
    
}