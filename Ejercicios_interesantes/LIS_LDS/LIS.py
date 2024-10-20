def LIS(s):
    L = [1] * len(s)
    for k in range(1, len(L)):
        subproblemas = [L[i] for i in range(k) if s[i] < s[k]]
        L[k] = 1 + max(subproblemas, default=0)
    print(L)
    return max(L, default=0)

s = [7,8,1,2,4,6,3,5]
print(LIS(s))
