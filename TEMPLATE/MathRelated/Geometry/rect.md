#

## 矩阵相关

> 给出一个矩阵 `rect` 的 `左下角 (lx,ly)` 和 `右下角 (rx,ry)`
> 1. 计算矩阵的面积
> 2. 计算两个矩阵的相交面积和矩阵

---

### CODE

具体看 `./Rect.h`

---

### Application

**[1761. 阻挡广告牌](https://www.acwing.com/problem/content/1763/)**

```cpp
#include<bits/stdc++.h>
#incldue "Rect.h"
using namespace std;
int main() {
    Rect h[3];
    for(int i = 0;i < 3;i ++) {
        cin >> h[i].lx >> h[i].ry >> h[i].rx >> h[i].ly;
    }
    cout<<h[0].area() - h[0].Join(h[2]).area() + h[1].area() - h[1].Join(h[2]).area()<<"\n";
    return 0;
}
```

**[2032. 过度种植](https://www.acwing.com/problem/content/2034/)**

需要用到 `容斥原理` 来进行处理。

```cpp
#include<bits/stdc++.h>
#incldue "Rect.h"
using namespace std;
Rect h[20];
int n;
int res;
void dfs(int p,int num,Rect cur) {
    if(!cur.area()) return ;
    if(num & 1) {
        res += cur.area();
    } else {
        res -= cur.area();
    }
    for(int i = p;i < n;i ++) {
        dfs(i + 1,num + 1,cur.Join(h[i]));
    }
}
int main() {
    cin >> n;
    for(int i = 0;i < n;i ++) {
        cin >> h[i].lx >> h[i].ly >> h[i].rx >> h[i].ry;
    }
    res = 0;
    for(int i = 0;i < n;i ++) {
        dfs(i + 1,1,h[i]);
    }
    cout<<res<<"\n";
    return 0;
}
```
