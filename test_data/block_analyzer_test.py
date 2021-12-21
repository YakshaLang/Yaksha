def function_a():
    def function_a1():
        a = 1  # comment goes here
        b = 2  # next empty new lines should be ignored

        c = 3

    def function_a2():
        d = 3


def function_b():
    e = 1  # next empty new line should be ignored

    f = 2


BANANA = [1,  # ah I see
          2, 3,  # OK
          4, 5]  # More
