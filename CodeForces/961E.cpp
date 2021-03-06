//#define NOSTDCPP
//#define Cpp11
//#define Linux_System
#ifndef NOSTDCPP

#include <bits/stdc++.h>

#else

#include <algorithm>
#include <bitset>
#include <cassert>
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

using namespace std;

typedef long long ll;
typedef vector <int> vi;
typedef set <int> si;
typedef pair <int, int> pii;
typedef long double ld;

const int MOD = 1e9 + 7;
const int maxn = 300009;
const int maxm = 300009;
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

inline void out_number(ll x)
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

int n, data[maxn];
ll tree[maxn];

priority_queue <pii, vector <pii>, greater <pii> > pq;

int lowbit(int x){return x & -x;}

void update(ll x, int p)
{
	for(int i = p; i <= n; i += lowbit(i))
		tree[i] += x;
}

ll query(int p)
{
	ll ans = 0;
	for(int i = p; i; i -= lowbit(i))
		ans += tree[i];
	return ans;
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll ans = 0;
	int f = 1, t = 1;
	cin >> n;
	for(int i = 1; i <= n; i ++)
		cin >> data[i]; 
	update(1, 1);
	pq.push(make_pair(data[1], 1));
	for(int y = 2; y <= n; y ++)
	{
		while(! pq.empty() && pq.top().fi < y)
			update(-1, pq.top().se), pq.pop();
		ans += query(min(data[y], y - 1));
		update(1, y);
		pq.push(make_pair(data[y], y));
	}
	cout << ans << endl;
	return 0;
}
/*
5
1 2 3 4 5
3
8 12 7
3
3 2 1
*/ 
