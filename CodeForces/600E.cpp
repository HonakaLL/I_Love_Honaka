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
const int maxn = 500009;
const int maxm = maxn << 1;
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

int n, m, A[maxn], hsh[maxn];
ll C, ans[maxn], AnsMax;

struct edge
{
	int to, next;
}edg[maxm];
int fir[maxn], edg_cnt;
void addedge(int f, int t)
{
	edg[++ edg_cnt].to = t;
	edg[edg_cnt].next  = fir[f];
	fir[f] = edg_cnt;
}

int father[maxn], size[maxn], son[maxn];
bool vis[maxn];
void dfs1(int u, int fa)
{
	father[u] = fa;
	size[u] = 1;
	for(int i = fir[u], v; i; i = edg[i].next)
	{
		v = edg[i].to;
		if(v != fa)
		{
			dfs1(v, u);
			size[u] += size[v];
			if(! son[u] || size[son[u]] < size[v])
				son[u] = v;
		}
	}
}

void cal(int u, int val)
{
	//统计子树的结果 
	hsh[A[u]] += val;
	if(val > 0 && hsh[A[u]] == AnsMax) C += A[u];
	if(val > 0 && hsh[A[u]] > AnsMax) C = A[u], AnsMax = hsh[A[u]];
	for(int i = fir[u], v; i; i = edg[i].next)
	{
		v = edg[i].to;
		if(v != father[u] && ! vis[v]) //这里的判断条件是避免重复判断 
			cal(v, val);
	}
}

void dfs2(int u, bool preferred_son)
{
	//先遍历轻儿子 
	for(int i = fir[u], v; i; i = edg[i].next)
	{
		v = edg[i].to;
		if(v != father[u] && v != son[u])
			dfs2(v, false);
	}
	//再遍历重儿子 
	if(son[u]) dfs2(son[u], true), vis[son[u]] = true;
	cal(u, 1);
	ans[u] = C;
	if(son[u]) vis[son[u]] = false;
	//如果是轻儿子，要擦除结果 
	if(! preferred_son) cal(u, -1), C = AnsMax = 0;
}

int main()
{
	edg_cnt = 0;
	scanf("%d", &n);
	for(register int i = 1; i <= n; ++ i) scanf("%d", A + i);
	for(register int i = 1, f, t; i < n; ++ i)
	{
		scanf("%d %d", &f, &t);
		addedge(f, t);
		addedge(t, f);
	}
	dfs1(1, -1);
	dfs2(1, false);
	for(int i = 1; i <= n; ++ i) printf("%I64d ", ans[i]);
	puts("");
	return 0;
}

