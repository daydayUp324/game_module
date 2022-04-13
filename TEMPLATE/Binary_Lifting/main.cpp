#include <bits/stdc++.h>
#include "LCA.h"
using namespace std;
void readn() {
    int n,m,root,a,b,x,y;
    cin >> n >> m >> root;
    vector<vector<int>> g;
    g.resize(n + 1);
    for(int i = 0;i < n - 1;i ++) {
        scanf("%d %d",&x,&y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    LCA *h = new LCA(g,root);
    // 查询
    while(m --) {
        scanf("%d %d",&a,&b);
        printf("%d\n",h->calLCA(a,b));
    }
}
int main() {
    readn();
    return 0;
}
