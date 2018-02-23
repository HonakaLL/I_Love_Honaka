#define NOSTDCPP
//#define Cpp11
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
#include <fstream>
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

typedef struct
{
	ll lsum, rsum, sum, lazy;
}node;

node tree[maxn];
int n, m;

void pushup(int p, int l, int r)
{
	if(l < r)
	{
		tree[p].lsum = tree[DXA(p)].lsum;
		tree[p].rsum = tree[DXB(p)].rsum;
		int mid = midf(l, r);
		if(tree[p].lsum == mid - l + 1) //p ������������
			tree[p].lsum += tree[DXB(p)].lsum;
		if(tree[p].rsum == r - mid) //p �����Һ�������
			tree[p].rsum += tree[DXA(p)].rsum;
		tree[p].sum = max(max(tree[DXA(p)].sum, tree[DXB(p)].sum), 
		                  tree[DXA(p)].rsum + tree[DXB(p)].lsum);
		//sum ֵ���������������䳤��:
		//����ӵ�sumֵ���Ҷ��ӵ�sumֵ ������ӵ�rsumֵ+�Ҷ��ӵ�lsumֵ
	}
}

void pushdown(int p, int l, int r)
{
	//-1 ��ʾ������
	if(~ tree[p].lazy)
	{
		int mid = midf(l, r);
		tree[DXA(p)].lazy = tree[DXB(p)].lazy = tree[p].lazy;
		tree[DXA(p)].sum = tree[DXA(p)].lsum = tree[DXA(p)].rsum 
		= tree[p].lazy * (mid - l + 1);
		//������������ס��/��ס�˵ĳ���Ϊ mid - l + 1 
		tree[DXB(p)].sum = tree[DXB(p)].lsum = tree[DXB(p)].rsum 
		= tree[p].lazy * (r - mid);
		//������������ס��/��ס�˵ĳ���Ϊ r - mid
		tree[p].lazy = -1;
	}
}

void pre(int l, int r, int p)
{
	tree[p].lazy = -1;
	if(l == r)
	{
		tree[p].sum = tree[p].lsum = tree[p].rsum = 1;
		// Ĭ����û��ס�˵� 
		return ;
	}
	int mid = midf(l, r);
	pre(l, mid, DXA(p));
	pre(mid + 1, r, DXB(p));
	pushup(p, l, r);
}

void update(int l, int r, int nl, int nr, int val, int p)
//update ����: val = 0 ��ʾ [l, r] �Ѿ�ס�ˣ�val = 1 ��ʾ [l, r] û��ס�� 
{
	if(l <= nl && nr <= r)
	{
		tree[p].lazy = val;
		tree[p].sum = tree[p].rsum = tree[p].lsum = val * (nr - nl + 1);
		//һ��Ҫ���� tree[p] ���ӵ���Ϣ�� 
		return ;
	}
	pushdown(p, nl, nr);
	int mid = midf(nl, nr);
	if(l <= mid)update(l, r, nl, mid, val, DXA(p));
	if(mid < r) update(l, r, mid + 1, nr, val, DXB(p));
	pushup(p, nl, nr);
}

ll query(int nl, int nr, int rq, int p)
{
	if(nl == nr) //�߽�������nl == nr ���ݹ鵽����һ������һ������������ 
		return nl;
	pushdown(p, nl, nr);
	int mid = midf(nl, nr);
	if(tree[DXA(p)].sum >= rq) // [l, mid] ���ܺͱ���Ҫ�Ĵ� 
		return query(nl, mid, rq, DXA(p));
	else if(tree[DXA(p)].rsum + tree[DXB(p)].lsum >= rq) 
	// ��Խ [l, mid] (mid, r] ��һ�η���Ҫ����������� 
		return mid - tree[DXA(p)].rsum + 1;
	else 
	// (mid, r] ����һ�η���Ҫ����������� 
		return query(mid + 1, nr, rq, DXB(p));
}

int main()
{
	int f, t, type;
	scan_d(n);
	scan_d(m);
	pre(1, n, 1);
	while(m --)
	{
		scan_d(type);
		switch(type)
		{
			case 1:
				scan_d(f);
				if(tree[1].sum < f) //�������䳤��С�� f 
				{
					puts("0");
					continue;
				}
				t = query(1, n, f, 1);
				out_number(t);
				puts("");
				update(t, t + f - 1, 1, n, 0, 1);
				break;
			case 2:
				scan_d(f);
				scan_d(t);
				update(f, f + t - 1, 1, n, 1, 1);
				break;
			default:
				assert(type == 1 || type == 2);
		}
	}
	return 0;
}

/*
10 4
1 10
2 1 3
2 5 2
1 5
*/

