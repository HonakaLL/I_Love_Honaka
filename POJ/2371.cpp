#define NOSTDCPP
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

using namespace std;

typedef long long ll;
typedef vector <int> vi;
typedef set <int> si;
typedef long double ld;

const int MOD = 1e9 + 7;
const int maxn = 5009;
const int maxm = 300009;
const double pi = acos(-1.0);
const double eps = 1e-6;

int data[maxn];

int ans(int x)
{
	int tmp = 0;
	for(int i = 1; i <= maxn - 1; i ++)
	{
		tmp += data[i];
		if(tmp >= x)
			return i;
	}
}

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, q, t;
	scanf("%d", &n);
	RESET(data);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &t), data[t] ++;
	scanf("\n###\n");
	scanf("%d", &q);
	for(int i = 1;i <= q;i ++)
	{
		scanf("%d", &t);
		printf("%d\n", ans(t));
	}
	return 0;
}

