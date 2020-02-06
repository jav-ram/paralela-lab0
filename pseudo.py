import math

def my_max(array):
    greater = -float('inf')
    for item in array:
        if item > greater:
            greater = item
    return greater


def my_paralel_max(array, P):
    global_max = -float('inf')
    n = len(array)/P
    for p in range(len(P)):
        local_max = launch_thread(array[n*p:n*(p+1) - 1])
        global_max = local_max if local_max > global_max else global_max
    return global_max

