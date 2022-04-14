#include <bits/stdc++.h>
using namespace std;
const int N = 5e4 + 7;
int n,m,a,b;
int Log2[N];
int w[N];
int maxST[N][18];
int minST[N][18];
int main() {
    cin >> n >> m;
    for(int i = 0;i < n;i ++) {
        scanf("%d",&maxST[i][0]);
        minST[i][0] = maxST[i][0];
    }
    Log2[1] = 0;
    for(int i = 2;i < n;i ++) Log2[i] = Log2[i / 2] + 1;
    for(int i = 1;i < 18;i ++) {
        for(int j = 0;j + (1 << i) <= n;j ++) {
            maxST[j][i] = max(
                maxST[j][i-1] , maxST[j + (1 << (i - 1))][i-1]
            );
            minST[j][i] = min(
                minST[j][i-1] , minST[j + (1 << (i - 1))][i-1]
            );
        }
    }
    while(m --) {
        scanf("%d %d",&a,&b);
        a -- , b --;
        int s = Log2[b - a + 1];
        int o1,o2;
        o1 = max(maxST[a][s],maxST[b - (1 << s) + 1][s]);
        o2 = min(minST[a][s],minST[b - (1 << s) + 1][s]);
        printf("%d\n",\
            o1 - o2
        );
    }
    return 0;
}