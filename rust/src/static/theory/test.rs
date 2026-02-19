use super::*;
use crate::r#static::test::frac;

#[test]
fn should_lap_forever_table() {
    assert_eq!(
        should_lap_forever(&frac(0u64, 1u64), 0, &frac(1, 1), &frac(1, 2)),
        true
    );
}
