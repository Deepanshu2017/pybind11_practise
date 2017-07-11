import numba

@numba.jit
def sum_plus_5(lst):
    return sum(lst) + 5

if __name__ == '__main__':
    print(sum_plus_5([1, 2, 3, 4]))
