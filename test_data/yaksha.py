"""
This is a stub for Yaksha
"""
import typing as _hidden_typing  # noqa
from functools import wraps as _hidden_wraps  # noqa

# Primitive Types
""" Signed integer of size 8 (cl_char) """
i8 = int
""" Unsigned integer of size 8 (cl_uchar) """
u8 = int

""" Signed integer of size 16 (cl_short) """
i16 = int
""" Unsigned integer of size 16 (cl_ushort) """
u16 = int

""" Signed integer of size 32 (cl_int) """
i32 = int
""" Unsigned integer of size 32 (cl_uint) """
u32 = int

""" Signed integer of size 64 (cl_long) """
i64 = int
""" Unsigned integer of size 64 (cl_ulong) """
u64 = int

""" Float of size 16 (cl_half) """
f16 = float
""" Float of size 32 (cl_float) """
f32 = float
""" Float of size 64 (cl_double) """
f64 = float


@_hidden_typing._SpecialForm  # noqa
def Global(self, parameters):  # noqa
    """
    Mark as global
    """
    arg = _hidden_typing._type_check(parameters, f"{self} requires a single type.")  # noqa
    return arg


"""List, same as cl_float*, etc"""
List = _hidden_typing.List

"""
Array, same as cl_float[5], etc
---
Usage:
    my_vec = Array[i32, 4]
"""
Array = _hidden_typing.Annotated


def get_global_id(arg_: int) -> int:
    pass


# decorator @host for code that runs in host
def host(x: _hidden_typing.Callable) -> _hidden_typing.Callable:
    return _hidden_wraps(x)


# decorator @device for code that runs in OpenCL device
def device(x: _hidden_typing.Callable) -> _hidden_typing.Callable:
    return _hidden_wraps(x)
