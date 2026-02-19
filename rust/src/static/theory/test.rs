use super::*;
use crate::r#static::test::frac;

#[test]
fn should_lap_forever_table() {
    let cases = [
        (frac(0, 1),   frac(1, 2),    frac(1, 2),    true),
        (frac(0, 1),   frac(2, 4),    frac(2, 4),    true),
        (frac(1, 10),  frac(1, 2),    frac(1, 2),    false),
        (frac(0, 1),   frac(7, 10),   frac(1, 2),    false),
        (frac(0, 1),   frac(1, 2),    frac(7, 10),   true),
        (frac(6, 100), frac(55, 100), frac(65, 100), false),
        (frac(0, 1),   frac(1, 2),    frac(65, 100), true),
        (frac(1, 10),  frac(3, 2),    frac(1, 2),    false),
        (frac(0, 1),   frac(3, 2),    frac(1, 2),    true),
    ];

    for (phase, travel_time, on_ratio, expected) in cases {
        assert_eq!(should_lap_forever(&phase, &travel_time, &on_ratio),
        expected,
        "phase={phase}, travel_time={travel_time}, on_ratio={on_ratio}");
    }
}
