#[cfg(test)]
mod test;

use fraction::Fraction;
use fraction::One;

pub fn should_lap_forever(phase: &Fraction, travel_time: &Fraction, on_ratio: &Fraction) -> bool {
    let q = Fraction::from(*travel_time.denom().unwrap());
    let one = Fraction::one();
    (phase + (((q * (one - *phase)).ceil() - one) / q)).le(on_ratio)
}

fn mod_inverse(p: i64, q: i64) -> i64 {
    let (mut old_r, mut r) = (p,q);
    let (mut old_s, mut s) = (1,0);
    let (mut old_t, mut t) = (0,1);

    while r != 0 {
        let quot = old_r / r;
        (old_r, r) = (r, old_r - quot * r);
        (old_s, s) = (s, old_s - quot * s);
        (old_t, t) = (t, old_t - quot * t);
    };

    ((old_s % q) + q) % q
}

// assumes !should_lap_forever
pub fn lap_count(phase: &Fraction, travel_time: &Fraction, on_ratio: &Fraction) -> u64 {
    let p: u64 = (*travel_time.numer().unwrap()).try_into().unwrap();
    let q: u64 = (*travel_time.denom().unwrap()).try_into().unwrap();
    let p_inv: u64 = mod_inverse(p as i64, q as i64).try_into().unwrap();
    let one = Fraction::one();
    (0..q)
    .filter(|k| ((phase + Fraction::new(*k, q)) % one) > *on_ratio)
    .map(|k| (k * p_inv) % q)
    .min().unwrap()-1
}