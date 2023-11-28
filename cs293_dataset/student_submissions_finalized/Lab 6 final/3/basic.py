def binarySearch(arr, val):
    l = 0
    r = len(arr) - 1
    while l < r:
        m = l + (r - l) // 2
        if arr[m] > val:
            r = m
        elif arr[m] < val:
            l = m
        else:
            return m
    return -1