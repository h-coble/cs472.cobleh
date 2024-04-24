#include <iostream>


bool isComposite(const int n)
{
    for (int i = 2; i <= n/2; i++)
    {
        if(n%i == 0)
            return true;
    }
    return false;
}

/*
    O(log2(n))
    The number of bits needed to represent n is log2n (= x).
    Given from the question (thank you Dr. Lewis), the number in test is
    the number of bits in n's binary expansion. This means O(2^x), or O(log2(n)), and not O(n).

    Because O is exponential, we cannot solve this problem in polynomial time, 
    which would contradict the definition of complexity class P. Therefore, the 
    problem is not of complexity class P.
*/

int main()
{
    if (isComposite(97))
        std::cout << "97 is composite.\n";
    else
        std::cout << "97 isn't composite.\n";
    if(isComposite(187))
        std::cout << "187 is composite.\n";
    else
        std::cout << "187 isn't composite.\n";
    
    return 0;
}