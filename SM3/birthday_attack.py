import random
import string
import math
import time
V = [0x7380166F, 0x4914B2B9, 0x172442D7, 0xDA8A0600,
      0xA96F30BC, 0x163138AA, 0xE38DEE4D, 0xB0FB0E4E]


def ll(s, l):
    l = l % 32
    return (((s << l) & 0xFFFFFFFF) | ((s & 0xFFFFFFFF) >> (32 - l)))


def FF(s1, s2, s3, i):
    if i >= 0 and i <= 15:
        return s1 ^ s2 ^ s3
    else:
        return ((s1 & s2) | (s1 & s3) | (s2 & s3))


def GG(s1, s2, s3, i):
    if i >= 0 and i <= 15:
        return s1 ^ s2 ^ s3
    else:
        return ((s1 & s2) | (~s1 & s3))


def P0(s):
    return s ^ ll(s, 9) ^ ll(s, 17)


def P1(s):
    return s ^ ll(s, 15) ^ ll(s, 23)


def T(i):
    if i >= 0 and i <= 15:
        return 0x79cc4519
    else:
        return 0x7a879d8a


def padding(message):
    m = bin(int(message, 16))[2:]
    if len(m) != len(message) * 4:
        m = '0' * (len(message) * 4 - len(m)) + m
    l = len(m)
    l_bin = '0' * (64 - len(bin(l)[2:])) + bin(l)[2:]
    m = m + '1'
    m = m + '0' * (448 - len(m) % 512) + l_bin
    m = hex(int(m, 2))[2:]
    return m


def block(m):
    n = len(m) / 128
    M = []
    for i in range(int(n)):
        M.append(m[0 + 128 * i:128 + 128 * i])
    return M


def extension(M, n):
    W = []
    W1 = []
    for j in range(16):
        W.append(int(M[n][0 + 8 * j:8 + 8 * j], 16))
    for j in range(16, 68):
        W.append(P1(W[j - 16] ^ W[j - 9] ^ ll(W[j - 3], 15)) ^ ll(W[j - 13], 7) ^ W[j - 6])
    for j in range(64):
        W1.append(W[j] ^ W[j + 4])
    s1 = ''
    s2 = ''
    for x in W:
        s1 += (hex(x)[2:] + ' ')
    for x in W1:
        s2 += (hex(x)[2:] + ' ')
    return W, W1


def compress(V, M, i):
    A, B, C, D, E, F, G, H = V[i]
    W, W1 = extension(M, i)
    for j in range(64):
        SS1 = ll((ll(A, 12) + E + ll(T(j), j % 32)) % (2 ** 32), 7)
        SS2 = SS1 ^ ll(A, 12)
        TT1 = (FF(A, B, C, j) + D + SS2 + W1[j]) % (2 ** 32)
        TT2 = (GG(E, F, G, j) + H + SS1 + W[j]) % (2 ** 32)
        D = C
        C = ll(B, 9)
        B = A
        A = TT1
        H = G
        G = ll(F, 19)
        F = E
        E = P0(TT2)

    a, b, c, d, e, f, g, h = V[i]
    V1 = [a ^ A, b ^ B, c ^ C, d ^ D, e ^ E, f ^ F, g ^ G, h ^ H]
    return V1


def SM3_encryption(M):
    n = len(M)
    V = []
    V.append(V)
    for i in range(n):
        V.append(compress(V, M, i))
    return V[n]



def rand_get(n):
    rn = []
    while len(rn) < n:
        i = random.randint(0, pow(2,64))
        if i not in rn:
            rn.append(i)
    return rn

def brithday_attack():
    random_value = []
    r = rand_get(pow(2,16))
    for i in range(pow(2,16)):
        m = padding(str(r[i]))
        M = block(m)
        Mn = SM3_encryption(M)
        tmp=""
        for k in Mn:
            tmp += hex(k)[2:]
        random_value.append(tmp[:7])



print("Collsion:")
start = time.time()
brithday_attack()
end = time.time()
print("Time:%.3fs"%(end-start))