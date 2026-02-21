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

pub fn sample_travel_time(
    max_travel_time: Fraction,
    granularity: u64,
    callback: &mut impl FnMut(Fraction),
) {
    let mut step = max_travel_time / granularity;
    for _ in 1..granularity {
        callback(step);
        step += step;
    }
}

pub fn sample(
    granularity: u64,
    max_travel_time: Fraction,
    callback: &mut impl FnMut(Fraction, Fraction, Fraction),
) {
    sample_phase(granularity, &mut |phase| {
        sample_on_ratio(granularity, &mut |on_ratio| {
            sample_travel_time(max_travel_time, granularity, &mut |travel_time| {
                callback(phase, travel_time, on_ratio);
            });
        });
    });
}

fn each_unit_fraction(granularity: u64, start: u64, body: &mut impl FnMut(Fraction)) {
    for i in start..granularity {
        body(Fraction::new(i, granularity));
    }
}