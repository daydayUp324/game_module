#

## 组合数

设 `C[i][j]` 来表示 在 `j` 件物品中挑选出 `i` 件物品的方案数 , `j >= i` , `组合数公式` :

$C[i][j] = \frac{j!}{i! * (j - i)!}$

> 这个思考方式是从 `排列组合` 的角度来进行考虑的 , 从 `j` 件物品中选择 `i` 件物品 , 假设需要考虑顺序 : 那么第一件的选择方案数是 : $j$ , 第二件的选择方案数是 : $j - 1$ , ... , 那么此时可供选择的方案数为 : $sum = j*(j - 1)*...*(j - i + 1)=A_j^i$ , 又因为 `组合` 是不分 __排列顺序__ 的 , 所以 $C_j^i=\frac{A_j^i}{i!}=\frac{j!}{i!*(j - i)!}$

---

但是因为 `阶乘` 往往比较大 , 所以一般需要带有 `MOD` , 而通过 `组合数公式` 来进行求解时 , 取模操作对除法是不能直接进行取模的 , 需要先求 `i!` 的逆元就比较繁琐。现在给出 时间复杂度在 $O(n * m)$ 的 **递推式** 求解 `C[n][m]` 组合数的方法 :

$C[i][j] = C[i-1][j-1] + C[i][j-1]$

> 这个思考方向是来判断 `j` 个物品中的一个物品 **是否取** 来进行递归求解的 : 因为一个物品只有 **取和不取** 两种方案 , 而加法的操作对于 __取模__ 操作是可以直接相加求解的。

### 组合数代码参考

```cpp
void cal_com(vector<vector<int>>& C) {
    for(int i = 1;i < C.size();i ++) {
        C[0][i] = C[i][i] = 1;
        for(int j = 1;j < i - 1;j ++) {
            C[j][i] = ((long long)C[j - 1][i - 1] + C[j][i - 1]) % MOD;
        }
    }
}
```

### 小球放盒问题

__参考链接 :__ [放球问题_百度百科](https://baike.baidu.com/item/%E6%94%BE%E7%90%83%E9%97%AE%E9%A2%98/12740706)

`小球` n 个 , `盒子` m 个

1. 小球相同 , 盒子不同 , 不允许空盒 , $n \ge m > 0$ 。 我们可以想成将 n 个小球分成 m 堆 , 那么就是在 n 个小球中 n - 1 个空隙中选择 m - 1 个空隙进行放置 , 此时的放置方案数为 :
   > $C(m - 1,n - 1)$
2. 小球相同 , 盒子不同 , 允许空盒。__参考题目 :__ [生成乘积数组的方案数](https://leetcode-cn.com/problems/count-ways-to-make-array-with-product/) 。那么我们可以换一个角度思考 : 假定不允许空盒 , 即最后每一个盒子都至少放置了一个小球 ,那么原问题就转换为了 n + m 个 `小球` , m 个 `盒子` 的不允许空盒的情况。那么按照 `情况1` 的结论 此时的放置方案数为 :
   > $C(m - 1,n + m - 1)$
