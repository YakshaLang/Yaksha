"""
This is a test
"""
from yaksha import *  # YAKSHA-PRAGMA-IGNORE


@device
def vector_add(a: Global[List[f32]], b: Global[List[f32]], c: Global[List[f32]], count: u32) -> None:
    i: i32 = get_global_id(0)
    h: i32 = 0x123AaBbCcDdEefF4567890
    b2: i32 = 0b101010
    o: i32 = 0o12345670
    n: i32 = 1000
    f0: f32 = 1.2
    f1: f32 = 1.
    f2: f32 = .1
    f3: f32 = .1e1
    f4: f32 = 1e1
    f5: f32 = 1.e1
    f6: f32 = 112312.123123e1123123
    if i < count:
        c[i] = a[i] + b[i]
