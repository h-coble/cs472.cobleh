from math import sqrt, pow
def closest_pair(P:list[tuple], F):
    first_flag = True
    for pair in P[:-1]:
        for j in P[P.index(pair)+1:]:
            if first_flag:
                mindist = F(pair,j)
                first_flag = False
            elif F(pair,j) < mindist:
                mindist = F(pair,j)
    return mindist

def euc_dist(p1:tuple[float,float], p2:tuple[float,float]) -> float:
    return sqrt(pow(p1[0] - p2[0],2) + pow(p1[1] - p2[1],2))

def hamming_distance(p1:tuple[int,int], p2:tuple[int,int]):
    a = (p1[0] ^ p2[0])
    b = (p1[1] ^ p2[1])
    return countSetBits(a) + countSetBits(b)

#https://www.geeksforgeeks.org/count-set-bits-in-an-integer/
def  countSetBits(n):
    count = 0
    while (n):
        count += n & 1
        n >>= 1
    return count

A = [(0,0), (1,1), (1,2),(0,1)]
print(closest_pair(A,euc_dist))
print(closest_pair(A, hamming_distance))