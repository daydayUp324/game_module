#

参考链接：[最小表示法](https://oi-wiki.org/string/minimal-string/)

## 最小表示法

`最小表示法` 是用于解决__字符串__最小表示问题的方法。

循环同构：

当 `字符串 S` 中可以选定一个位置 $i$ 满足：

$$S[i:n) + S[0:i) = T, S.length = n$$

则称 $S$ 与 $T$ 循环同构

__最小表示__

字符串 $S$ 的最小表示为与 $T$ 循环同构的所有字符串中字典序最小的字符串



### 朴素的思想

枚举每一个 $i$ 来进行判断：我们每次比较 $i$ 和 $j$ 开始的循环同构，把当前比较到的位置记作 $k$，每次遇到不一样的字符时便把大的跳过，最后剩下的就是最优解。

**CODE**

```cpp
string Minimal_string(string& s) {
    int i = 0, j = 1, k = 0, n = s.size();
    while (k < n && i < n && j < n) {
        if (s[(i + k) % n] == s[(j + k) % n]) {
            k ++;
        } else {
            if (s[(i + k) % n] > s[(j + k) % n]) i ++;
            else j ++;
            k = 0;
            if (i == j) j ++;
        }
    }
    return s.substr(i) + s.substr(0, i);
}
```

**时间复杂度：** $O(n^2)$，最坏情况下会达到 $O(n^2)$

### 最小表示法

算法核心：

同样我们按照朴素的算法来思考应该如何优化：设 $i$，$j$ 满足 $i < j$，当遍历到 $k$ 使之对应位置的字符不同，不妨设 $S[i + k] > S[j + k]$ (此时为了方便不进行取模)。那么对于 $l \in [i, i + k]$ 开头的任意字符串一定不会是最优的解。

证明：因为此时一定满足 $S[i:i + k - 1] == S[j:j + k - 1]$ 那么对于任意的以 $l = i + a, a \in [0,k]$ 开头的一定比存在 $p = j + a$ 开头的字符串比它更优。

即此时我们可以直接跳到 $i + k + 1$ 开头的字符串来进行比较即可。这样，我们就完成了对于上文暴力朴素算法的优化。

**CODE**

```cpp
string Minimal_string(string& s) {
    int i = 0, j = 1, k = 0, n = s.size();
    while (k < n && i < n && j < n) {
        if (s[(i + k) % n] == s[(j + k) % n]) {
            k ++;
        } else {
            if (s[(i + k) % n] > s[(j + k) % n]) i += k + 1;
            else j += k + 1;
            k = 0;
            if (i == j) j ++;
        }
    }
    return s.substr(i) + s.substr(0, i);
}
```

**时间复杂度：** $O(n)$

