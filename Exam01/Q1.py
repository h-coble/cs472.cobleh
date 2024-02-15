def insertion_sort(A:list)->list:           #O(n^2)
    for i in range(1, len(A)):              #n times
        j = i
        while j > 0 and A[j-1] > A[j]:      #another n times
            A[j-1] , A[j] = A[j], A[j-1]
            j-=1
    return A

#binary search and binary insertion sort resources found online
#https://www.geeksforgeeks.org/binary-insertion-sort/
#I'm not very pythonic, but I didn't want to deal with C++ template functions

def  binary_search(A:list, target, start, end) -> int: #O(logN)
    if start == end:
        if A[start] > target:
            return start
        else:
            return start+1
    if start > end:
        return start
    mid = (start + end)//2
    if A[mid] < target:
        return binary_search(A,target, mid+1,end)
    elif A[mid] < target :
        return binary_search(A,target, mid-1, end)
    else:
        return mid

def binary_insertion_sort(A:list)->list:        #O(logN) - see note below function
    for i in range(1,len(A)):                   #n times
        j = binary_search(A, A[i],0,i-1)        #has O(logN)
        A = A[:j] + [A[i]] + A[j:i] + A[i+1:]
    return A

#Summation of (logN) = log(N*N1*N2...Nn) -> log(N) because
#log(a) + log(b) = log(ab). This is of order log(n), 
#which is a better time complexity than O(n^2)


ex = [0,2,3,1,4,8,7,9,5,6]
print(ex)
ex = insertion_sort(ex)
print(ex)
ex = [0,2,3,1,4,8,7,9,5,6]
print(ex)
ex = binary_insertion_sort(ex)
print(ex)