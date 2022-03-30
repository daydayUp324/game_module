#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using PII = pair<int,pair<int,int>>;
const int N = 2e5 + 7;
const int INF = 0x3f3f3f3f;
int gcd(int a,int b) {return b == 0 ? a : gcd(b,a % b);}
const int dir[8][2] = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,-1},{-1,1}};
int n,m;
