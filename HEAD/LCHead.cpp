#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using PII = pair<int,int>;
#define VALID (nx >= 0 && nx < n && ny >= 0 && ny < m)
#define x first
#define y second
#define SQR(x)     ((x)*(x))
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
int exp_pow(int a,int b) {int res = 1; while(b) {if(b&1) res = (LL) a * res % MOD;b >>= 1;a = (LL) a * a % MOD;}return res;}
int exp_mul(int a,int b) {int res = 0; while(b) {if(b&1) res = ((LL) res + a) % MOD;b >>= 1;a = (LL) a * 2 % MOD;}return res;}
int gcd(int a,int b) {return b == 0 ? a : gcd(b,a % b);}
const int dir[8][2] = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,-1},{-1,1}};
const char oe[10] = {'a','e','i','o','u','A','E','I','O','U'};
const double EPS = 1e-6;
const int N = 1e5 + 7;
int n,m,a,b;
int w[N];


