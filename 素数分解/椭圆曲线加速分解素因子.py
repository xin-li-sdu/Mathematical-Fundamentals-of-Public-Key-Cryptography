from random import randint
from math import gcd
def modular_inv(a, m):
    def egcd(a, b):
        if a == 0:
            return (b, 0, 1)
        else:
            g, y, x = egcd(b % a, a)
            return (g, x - (b // a) * y, y)

    g, x, y = egcd(a, m)
    if g != 1:
        return None, None, g
    else:
        return x % m, None, g


def EulerSieve(n):
    vis = [True] * (n + 1)
    primes = []
    for i in range(2, n + 1):
        if vis[i]:
            primes.append(i)
        for j in primes:
            if i * j > n:
                break
            vis[i * j] = False
            if i % j == 0:
                break
    return primes
def exgcd(a,b):
    if b == 0:
        return 1, 0, a
    q, r = divmod(a, b)
    x, y, d = exgcd(b, r)
    return y, x - q * y, d

def elliptic_add(p, q, a, b, m):
    if p[2] == 0: 
        return q
    if q[2] == 0: 
        return p
    if p[0] == q[0]:
        if (p[1] + q[1]) % m == 0:
            return 0, 1, 0
        num = (3 * p[0] * p[0] + a) % m
        denom = (2 * p[1]) % m
    else:
        num = (q[1] - p[1]) % m
        denom = (q[0] - p[0]) % m
    inv, _, g = modular_inv(denom, m)
    if g > 1:
        return 0, 0, denom  
    z = (num * inv * num * inv - p[0] - q[0]) % m
    return z, (num * inv * (p[0] - z) - p[1]) % m, 1
def elliptic_mul(k, p, a, b, m):
    res = (0, 1, 0)
    while k > 0:
        if p[2] > 1:
            return p
        if k % 2 == 1:
            res = elliptic_add(p, res, a, b, m)
        k = k // 2
        p = elliptic_add(p, p, a, b, m)
    return res
def lenstra(n, limit):
    g = n
    while g == n:
        q = randint(0, n - 1), randint(0, n - 1), 1
        a = randint(0, n - 1)
        b = (q[1] * q[1] - q[0] * q[0] * q[0] - a * q[0]) % n
        g = gcd(4 * a * a * a + 27 * b * b, n) 
    if g > 1:
        return g
    primes=EulerSieve(limit)
    for p in primes:
        pp = p
        while pp < limit:
            q = elliptic_mul(p, q, a, b, n)
            if q[2] > 1:
                return gcd(q[2], n)
            pp = p * pp
    return False
def main():
    n=9982123112
    #B=7000
    B=721
    curve_count=200
    for i in range(curve_count):
        res=lenstra(n, B)
        if res != False:
            print(res)
            break
if __name__ == '__main__':
    main()
