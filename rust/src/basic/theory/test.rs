use super::*;
use crate::basic::test::frac;

#[test]
fn lap_count_table() {
    let cases = [
        (frac(0, 1),   frac(1, 2),    frac(1, 2),    None),
        (frac(0, 1),   frac(2, 4),    frac(2, 4),    None),
        (frac(0, 1),   frac(1, 2),    frac(7, 10),   None),
        (frac(0, 1),   frac(1, 2),    frac(65, 100), None),
        (frac(0, 1),   frac(3, 2),    frac(1, 2),    None),
        (frac(1, 10),  frac(1, 2),    frac(1, 2),    Some(0)),
        (frac(0, 1),   frac(7, 10),   frac(1, 2),    Some(0)),
        (frac(1, 10),  frac(3, 2),    frac(1, 2),    Some(0)),
        (frac(1, 5),   frac(1, 10),   frac(1, 10),   Some(0)),
        (frac(0, 1),   frac(3, 10),   frac(1, 2),    Some(1)),
        (frac(1, 5),   frac(4, 5),    frac(1, 10),   Some(1)),
        (frac(1, 2),   frac(1, 2),    frac(1, 10),   Some(1)),
        (frac(0, 1),   frac(1, 4),    frac(1, 2),    Some(2)),
        (frac(6, 100), frac(55, 100), frac(65, 100), Some(2)),
        (frac(1, 2),   frac(55, 100), frac(65, 100), Some(3)),
    ];

    for (phase, travel_time, on_ratio, expected) in cases {
        assert_eq!(
            expected,
            lap_count(&phase, &travel_time, &on_ratio),
            "phase={phase}, travel_time={travel_time}, on_ratio={on_ratio}"
        );
    }
}
