"""
miller-rabin prime test

Test if n is prime with error probability less than 2^(−𝑠).

"""

import random
from exponentiation import exp

Prime = 0
Composite = 1


def miller_rabin(n, s):
    if n == 2:
        return Prime
    elif n % 2 == 0:
        return Composite

    for _ in range(s):
        a = random.randint(1, n-1)
        if test(a, n) == True:
            return Composite

    return Prime

def test(a, n):
    t, u = 0, n-1
    while (u % 2 == 0):
        t += 1                  #t >= 1, u is odd, n=1 = 2^t * u
        u //= 2                 #initialization
    x = exp(a, u, n)           #initializing x0 = a^u mod n

    for _ in range(t-1):        #for i = 1 to t
        x_prev = x              #xi-1
        x = exp(x_prev, 2, n)   #xi = (xi-1)^2 mod n
        if x == 1 and x_prev != 1 and x_prev != (n-1):      #NSR test
            return True

    if x != 1:                  #Fermat test
        return True
    return False


if __name__ == "__main__":

    primes = [7879, 7883, 7901, 7907, 7919, 7927, 7933, 7937, 7949, 7951,
              7963, 7993, 8009, 8011, 8017, 8039, 8053, 8059, 8069, 8081,
              8087, 8089, 8093, 8101, 8111, 8117, 8123, 8147, 8161, 8167]

    for p in primes:
        result = miller_rabin(p, 20)
        if result == Prime:
            print("Prime")
        elif result == Composite:
            print("Composite")
        else:
            print("Undefined")
