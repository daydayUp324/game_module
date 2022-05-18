# 

## 动态开点线段树应用

### [2276. 统计区间中的整数数目](https://leetcode.cn/problems/count-integers-in-intervals/)

**题目描述 :**

[![OovL7V.png](https://s1.ax1x.com/2022/05/18/OovL7V.png)](https://imgtu.com/i/OovL7V)

[![OoxPn1.png](https://s1.ax1x.com/2022/05/18/OoxPn1.png)](https://imgtu.com/i/OoxPn1)

**思路分析 :**

因为整个区间有 `[1:1e9]` 的大小 , 所以直接开 `线段树` 肯定是不行的。可以看到 , 其实最后的区间段最多只有 `1e5` 的级别 , 所以我们可以进行 `动态开点` 的方式来进行处理。

**代码参考 :**

见 `./DST_Problem/LC2276_统计区间中的整数数目.h`

---

### [2271. 毯子覆盖的最多白色砖块数](https://leetcode.cn/problems/maximum-white-tiles-covered-by-a-carpet/)

**题目描述 :**

[![OTd9BD.png](https://s1.ax1x.com/2022/05/18/OTd9BD.png)](https://imgtu.com/i/OTd9BD)

[![OTdFNd.png](https://s1.ax1x.com/2022/05/18/OTdFNd.png)](https://imgtu.com/i/OTdFNd)

**思路分析 :**

首先把每一段区间都给到初始区间 `[1:1e9]` 中 , 然后从每一段区间的 `左端点` 贪心的往后选取即可。用 `query(l,r)` 即可。

**代码参考 :**

见 `./DST_Problem/LC2271_毯子覆盖的最多白色砖块数.h`

---

### [2251. 花期内花的数目](https://leetcode.cn/problems/number-of-flowers-in-full-bloom/)

**题目描述 :**

[![OTjMlj.png](https://s1.ax1x.com/2022/05/18/OTjMlj.png)](https://imgtu.com/i/OTjMlj)

[![OTjQ6s.png](https://s1.ax1x.com/2022/05/18/OTjQ6s.png)](https://imgtu.com/i/OTjQ6s)

**思路分析 :**

本质其实是一个 `区间更新` 问题 , 就是对于 `[l:r]` 中会有花开 , 那么 `[l:r]` 中的全部数量 `+1` 即可 , 最终求得每一个人所在的日期的花开的数量

1. 用 `动态开点线段树` 可以解决
2. 用 `差分数组` 也可以解决

**代码参考 :**

见 `./DST_Problem/LC2251_花期内花的数目.h`

---

### [计算右侧小于当前元素的个数](https://leetcode.cn/problems/count-of-smaller-numbers-after-self/)

**题目描述 :**

[![OTzoH1.png](https://s1.ax1x.com/2022/05/18/OTzoH1.png)](https://imgtu.com/i/OTzoH1)

[![OTzHN6.png](https://s1.ax1x.com/2022/05/18/OTzHN6.png)](https://imgtu.com/i/OTzHN6)

**思路分析 :**

直接从后面往前 , 每次对 `[nums[i] + 1e4,nums[i] + 1e4]` 区间 `+ 1` 即可

1. 用 `动态开点线段树` 可以解决
2. 用 `树状数组` 也可以解决

**代码参考 :**

见 `./DST_Problem/LC315_计算右侧小于当前元素的个数.h`

---

### [699. 掉落的方块](https://leetcode-cn.com/problems/falling-squares/)

**题目描述 :**

![image.png](https://i.bmp.ovh/imgs/2022/04/04/fb76b0fba6bb9215.png)

[![qqElwQ.png](https://s1.ax1x.com/2022/04/04/qqElwQ.png)](https://imgtu.com/i/qqElwQ)

**思路分析 :**

题目等价于我们每次把 `[l,r]` 的区间更新为 `max{arr[l:r]} + height`。然后返回 `[1:1e9]` 区间中的最大值即可。

**代码参考 :**

见 `./DST_Problem/LC315_掉落的方块.h`
