#

## 对于 unordered_map 的 hash 定制

参考链接 : [Blowing up unordered_map, and how to stop getting hacked on it](https://codeforces.com/blog/entry/62393)

```cpp
using ULL = unsigned long long;
ULL mix (ULL o) {
    o += 0x9e3779b97f4a7c15;
    o = (o ^ (o >> 30)) * 0xbf58476d1ce4e5b9;
    o = (o ^ (o >> 27)) * 0x94d049bb133111eb;
    return o ^ (o >> 31);
}
```
