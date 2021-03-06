//#define NOSTDCPP
//#define Cpp11
//#define Linux_System
#ifndef NOSTDCPP

#include <bits/stdc++.h>

#else

#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <complex>
#include <cstring>
#include <cstdio>
#include <deque>
#include <exception>
#include <functional>
#include <iomanip>
#include <iostream>
#include <istream>
#include <iterator>
#include <list>
#include <map>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#endif

# ifdef Linux_System
# define getchar getchar_unlocked
# define putchar putchar_unlocked
# endif

# define RESET(_) memset(_, 0, sizeof(_))
# define RESET_(_, val) memset(_, val, sizeof(_))
# define fi first
# define se second
# define pb push_back
# define midf(x, y) ((x + y) >> 1)
# define DXA(_) ((_ << 1))
# define DXB(_) ((_ << 1) | 1)

# define next __Chtholly__
# define x1 __Mercury__
# define y1 __bbtl04__
# define index __ikooo__

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector <int> vi;
typedef set <int> si;
typedef pair <int, int> pii;
typedef long double ld;

const int MOD = 1e9 + 7;
const int maxn = 100009;
const int maxm = 300009;
const ll inf = 1e18;
const double pi = acos(-1.0);
const double eps = 1e-6;

ll myrand(ll mod){return ((ll)rand() << 32 ^ (ll)rand() << 16 ^ rand()) % mod;}

template <class T>
inline bool scan_d(T & ret)
{
	char c;
	int sgn;
	if(c = getchar(), c == EOF)return false;
	while(c != '-' && (c < '0' || c > '9'))c = getchar();
	sgn = (c == '-') ? -1 : 1;
	ret = (c == '-') ? 0 : (c - '0');
	while(c = getchar(), c >= '0' && c <= '9')
		ret = ret * 10 + (c - '0');
	ret *= sgn;
	return true;
}
#ifdef Cpp11
template <class T, class ... Args>
inline bool scan_d(T & ret, Args & ... args)
{
	scan_d(ret);
	scan_d(args...);
}
#define cin.tie(0); cin.tie(nullptr);
#define cout.tie(0); cout.tie(nullptr);
#endif
inline bool scan_ch(char &ch)
{
	if(ch = getchar(), ch == EOF)return false;
	while(ch == ' ' || ch == '\n')ch = getchar();
	return true;
}

template <class T>
inline void out_number(T x)
{
	if(x < 0)
	{
		putchar('-');
		out_number(- x);
		return ;
	}
	if(x > 9)out_number(x / 10);
	putchar(x % 10 + '0');
}

int n, ans, L, R, mid;
int A[maxn], giftL[maxn], giftR[maxn];

bool ok(int x)
{
	int p = A[1], q = x - A[1];
	giftL[1] = A[1], giftR[1] = 0;
	for(int i = 2; i <= n; ++ i)
	{
		if(i % 2 == 0)
		{
			giftL[i] = min(A[i], p - giftL[i - 1]);
			giftR[i] = A[i] - giftL[i];
		}
		else 
		{
			giftR[i] = min(A[i], q - giftR[i - 1]);
			giftL[i] = A[i] - giftR[i];
		}
	}
	/*
	printf("X = %d: \n", x);
	for(int i = 1; i <= n; ++ i)
		printf("giftL[i] = %d, giftR[i] = %d\n", giftL[i], giftR[i]);
		*/
	return giftL[n] == 0;
}

int main()
{
	while(scanf("%d", &n) && n)
	{
		L = 0, R = 0;
		for(int i = 1; i <= n; ++ i) scanf("%d", A + i);
		if(n == 1) {printf("%d\n", A[1]); continue;}
		for(int i = 1; i <= n; ++ i) L = max(L, A[i] + A[(i == n) ? 1 : i + 1]), R = max(R, A[i] * 3);
		ans = L;
		if(n & 1)
		{
			while(L <= R)
			{
				mid = midf(L, R);
				if(ok(mid))
				{
					ans = mid;
					R = mid - 1;
				}
				else L = mid + 1;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

/*
3
4 2 2
5 
2 2 2 2 2
5
1 1 1 1 1
0
*/ 
