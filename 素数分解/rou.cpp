#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll pr;
ll pmod(ll a, ll b, ll p) { return (a * b - (ll)((long double)a / p * b) * p + p) % p; } //普通的快速乘会T
ll gmod(ll a, ll b, ll p)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            res = pmod(res, a, p);
        a = pmod(a, a, p);
        b >>= 1;
    }
    return res;
}
inline ll gcd(ll a, ll b)
{ 
    if (!a)
        return b;
    if (!b)
        return a;
    int t = __builtin_ctzll(a | b);
    a >>= __builtin_ctzll(a);
    do
    {
        b >>= __builtin_ctzll(b);
        if (a > b)
        {
            ll t = b;
            b = a, a = t;
        }
        b -= a;
    } while (b);
    return a << t;
}
bool Miller_Rabin(ll n)
{
    if (n == 46856248255981ll || n < 2)
        return false; 
    if (n == 2 || n == 3 || n == 7 || n == 61 || n == 24251)
        return true;
    if (!(n & 1) || !(n % 3) || !(n % 61) || !(n % 24251))
        return false;
    ll m = n - 1, k = 0;
    while (!(m & 1))
        k++, m >>= 1;
    for (int i = 1; i <= 20; ++i) 
    {
        ll a = rand() % (n - 1) + 1, x = gmod(a, m, n), y;
        for (int j = 1; j <= k; ++j)
        {
            y = pmod(x, x, n);
            if (y == 1 && x != 1 && x != n - 1)
                return 0;
            x = y;
        }
        if (y != 1)
            return 0;
    }
    return 1;
}
ll Pollard_Rho(ll x)
{
    ll n = 0, m = 0, t = 1, q = 1, c = rand() % (x - 1) + 1;
    for (ll k = 2;; k <<= 1, m = n, q = 1)
    {
        for (ll i = 1; i <= k; ++i)
        {
            n = (pmod(n, n, x) + c) % x;
            q = pmod(q, abs(m - n), x);
        }
        t = gcd(x, q);
        if (t > 1)
            return t;
    }
}
map<long long, int> m;
void fid(ll n)
{
    if (n == 1)
        return;
    if (Miller_Rabin(n))
    {
        pr = max(pr, n);
        m[n]++;
        return;
    }
    ll p = n;
    while (p >= n)
        p = Pollard_Rho(p);
    fid(p);
    fid(n / p);
}
void printx(ll ptr)
{
	         string t = "0123456789ABCDEF"; 
            string s;
	        ll x,num;
	        num=ptr;
            while(num != 0)
			{
		      x = num % 16; 
		        s = t[x] + s;
		        num = num / 16;
	         }
	         if(s == "")
			 {
		      cout << 0; 
	          }
			  else{
			  	//s[0] = '0';
		        cout << s;
	           }
              
}
int main()
{
    int T;
    ll n;
    scanf("%d", &T);
    while (T--)
    {
        m.clear();
        scanf("%lld", &n);
        pr = 0;
        auto begin1 = std::chrono::high_resolution_clock::now();
        fid(n);
        if (pr == n)
            puts("Prime");
        else
        {
            //printf("%lld\n", pr);
            
            for (map<long long, int>::iterator c = m.begin(); c != m.end();)
            {
                //printf("%d", c->second);
                printx(c->first);
                //printx(c->second);
                if ((++c) != m.end())
                    printf(" * ");
            }
            printf("\n");
        }
        auto end1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::ratio<1, 1000>> diff1 = end1 - begin1;
        std::cout << diff1.count() << " ms\n";
    }
    return 0;
}

