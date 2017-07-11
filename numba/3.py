from numba import jit, int32, float32

@jit(["int64(int64, int64)", "float64(float64, float64)"], nopython=True, nogil=True, parallel=True)
def sum_plus_5(a, b):
    return a + b + 5

if __name__ == '__main__':
    print(sum_plus_5(2 ** 30, 5))
    print(sum_plus_5(10, 10))
    print(sum_plus_5(2 ** 31, 2 ** 31 + 1))
    print(sum_plus_5(21.58, 42.01))
