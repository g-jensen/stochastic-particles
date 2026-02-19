#[cfg(test)]
mod test;

use fraction::Fraction;
use fraction::One;

pub fn should_lap_forever(phase: &Fraction, travel_time: &Fraction, on_ratio: &Fraction) -> bool {
    let q = Fraction::from(*travel_time.denom().unwrap());
    let one = Fraction::one();
    (phase + (((q * (one - *phase)).ceil() - one) / q)).le(on_ratio)
}