#[cfg(test)]
mod test;

use fraction::Fraction;

fn fractional_part(f: Fraction) -> Fraction {
    f - f.floor()
}

fn should_lap_forever(phase: &Fraction, q: u64, on_ratio: &Fraction) -> bool {
    (phase + Fraction::new(q - 1,q)).le(on_ratio)
}

fn mod_inverse(p: i64, q: i64) -> i64 {
    let (mut old_r, mut r) = (p, q);
    let (mut old_s, mut s) = (1, 0);
    let (mut old_t, mut t) = (0, 1);

    while r != 0 {
        let quot = old_r / r;
        (old_r, r) = (r, old_r - quot * r);
        (old_s, s) = (s, old_s - quot * s);
        (old_t, t) = (t, old_t - quot * t);
    }

    ((old_s % q) + q) % q
}

#[allow(dead_code)]
fn slow_lap_count(phase: &Fraction, travel_time: &Fraction, on_ratio: &Fraction) -> Option<u64> {
    let p: u64 = *travel_time.numer().unwrap();
    let q: u64 = *travel_time.denom().unwrap();
    if should_lap_forever(phase, q, on_ratio) {
        return None;
    }
    let p_inv: u64 = mod_inverse(p as i64, q as i64).try_into().unwrap();

    (0..q)
        .filter(|k| fractional_part(phase + Fraction::new(*k, q)) > *on_ratio)
        .map(|k| (k * p_inv) % q)
        .map(|n| if n == 0 {q} else {n})
        .min()
        .and_then(|n| Some(n-1))
}

pub fn lap_count(phase: &Fraction, travel_time: &Fraction, on_ratio: &Fraction) -> Option<u64> {
    let p: u64 = *travel_time.numer().unwrap();
    let q: u64 = *travel_time.denom().unwrap();
    if should_lap_forever(phase, q, on_ratio) {
        return None;
    }
    
    let mut m = 0;
    for n in 1..=q {
        m = (m+p) % q;
        if fractional_part(phase + Fraction::new(m,q)).gt(on_ratio) {
            return Some(n-1);
        }
    }
    return None;
}
