use super::*;
use crate::basic::{test::frac};

#[test]
fn optimize_some_lifespan() {
    let (travel_time, lifespan) = optimize(frac(0,1),frac(1,2),2,frac(1,1),|_, _, _| {
        Some(1)
    });
    assert_eq!(frac(1,2),travel_time);
    assert_eq!(frac(1,1),lifespan);

    let (travel_time, lifespan) = optimize(frac(0,1),frac(1,2),2,frac(1,1),|_, _, _| {
        Some(2)
    });
    assert_eq!(frac(1,2),travel_time);
    assert_eq!(frac(3,2),lifespan);
}

#[test]
fn optimize_passes_params_to_lap_fn() {
    let (travel_time, lifespan) = optimize(frac(1,1),frac(3,2),3,frac(1,1),|phase, travel_time, on_ratio| {
        if *phase == frac(1,1) && *on_ratio == frac(3,2) && *travel_time == frac(2,3) {
            Some(3)
        } else {
            Some(0)
        }
    });
    assert_eq!(frac(2,3),travel_time);
    assert_eq!(frac(8,3),lifespan);
}

#[test]
fn optimize_granulates_up_to_max_travel_time() {
    let (travel_time, lifespan) = optimize(frac(0,1),frac(1,2),2,frac(2,1),|_, _, _| {
        Some(2)
    });
    assert_eq!(frac(1,1),travel_time);
    assert_eq!(frac(3,1),lifespan);

    let (travel_time, lifespan) = optimize(frac(0,1),frac(1,2),3,frac(2,1),|_, _, _| {
        Some(3)
    });
    assert_eq!(frac(4,3),travel_time);
    assert_eq!(frac(16,3),lifespan);
}

#[test]
fn optimize_handles_none() {
    let (travel_time, lifespan) = optimize(frac(0,1),frac(1,2),2,frac(1,1),|_, _, _| {
        None
    });
    assert_eq!(frac(1,2),travel_time);
    assert_eq!(frac(1,0),lifespan);
}