#include <iostream>
#include <NTL/ZZ.h>
#include<NTL/tools.h>
using namespace NTL;
using namespace std;
int main()
{
    ZZ q;
    cin >> q;
    PrimeSeq s;
    long p;
    p = s.next();
    while (p != 0 && p <= q)
    {
        if (q % p == 0)
        {
            cout << p << "\n";
            q = q / p;
        }
        p = s.next();
    }
}