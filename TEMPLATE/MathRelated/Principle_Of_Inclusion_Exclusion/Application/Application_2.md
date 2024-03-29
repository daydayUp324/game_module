#

## 错位排序计数

> 错位排列计数
> 对于 1~n 的排列 P 如果满足 $P_i \neq i$ ，则称 P 是 n 的错位排列。求 n 的错位排列数。

那么同样按照上述的分析过程来进行分析 :

1. 首先全集 `U` : `1-n 全部的排列 方案数为 n!`
2. 然后 `Si` : `Pi != i` 的排列方案
3. 那么需要求的是 `S1 ∩ ... ∩ Sn` , 进行 `补集` 转化 : `S1 ∩ ... ∩ Sn` = `U` - `~S1 ∪ ... ∪ ~Sn`
4. `~Si` : `Pi == i` 的排列方案 , 那么同样用 `容斥原理` 来解决即可。

[![XFwnXR.png](https://s1.ax1x.com/2022/05/25/XFwnXR.png)](https://imgtu.com/i/XFwnXR)
