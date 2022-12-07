#

## 分块思想

参考于 [IO分块](https://oi-wiki.org/ds/decompose/)

其实，分块是一种思想，而不是一种数据结构。分块的基本思想是，通过对原数据的适当划分，并在划分后的每一个块上预处理部分信息，从而较一般的暴力算法取得更优的时间复杂度。分块的时间复杂度主要取决于分块的块长，一般可以通过均值不等式求出某个问题下的最优块长，以及相应的时间复杂度。分块是一种很灵活的思想，相较于树状数组和线段树，分块的优点是通用性更好，可以维护很多树状数组和线段树无法维护的信息。当然，分块的缺点是渐进意义的复杂度，相较于线段树和树状数组不够好。不过在大多数问题上，分块仍然是解决这些问题的一个不错选择。

### CODE

**模板代码：**`./decompose.h`
**例题：**`./Problems/LC2286以组为单位订音乐会的门票.h`