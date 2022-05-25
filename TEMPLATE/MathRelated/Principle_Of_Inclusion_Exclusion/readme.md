#

## 容斥原理 (Principle_Of_Inclusion_Exclusion)

**参考链接 :** 
**[容斥原理 (OI Wiki)](https://oi-wiki.org/math/combinatorics/inclusion-exclusion-principle/)**

**定义 :**

> 在计数时，必须注意没有重复，没有遗漏。为了使重叠部分不被重复计算，人们研究出一种新的计数方法，这种方法的基本思想是：先不考虑重叠的情况，把包含于某内容中的所有对象的数目先计算出来，然后再把计数时重复计算的数目排斥出去，使得计算的结果既无遗漏又无重复，这种计数的方法称为容斥原理。—— **百度百科**
> 
> 其实就是一种集合的运算

主要有两种表现形式 :

![XCVzaF.png](https://s1.ax1x.com/2022/05/24/XCVzaF.png)

![XCZkKx.png](https://s1.ax1x.com/2022/05/24/XCZkKx.png)

**基本计算思路 :**

> 要计算几个集合并集的大小，我们要先将所有单个集合的大小计算出来，然后减去所有两个集合相交的部分，再加回所有三个集合相交的部分，再减去所有四个集合相交的部分.........依此类推，一直计算到所有集合相交的部分。（可以理解为就是先把所有单个集合全加一遍然后再去重）
> 
> 正确性证明可见 : **[容斥原理 (OI Wiki)](https://oi-wiki.org/math/combinatorics/inclusion-exclusion-principle/)**

---

### Application

具体见 `./Application/Application_x.md`

1. **不定方程非负整数解计数**
2. **错位排列计数**
3. **最大公约数为 k 的数对个数**
4. **推导欧拉函数**
5. **DAG计数(了解即可)**
