#

## 下一个排列 (next-permutation)


### 利用字典序的性质来求解下一个排列

以求下一个排列为例 (字符串版) 

有 `字符串 s` , 我们需要找到它的下一个排列(如果存在)  那么我们需要从后往前找到第一个 `逆序` 的位置使得  `s[p]  s[p + 1]` , 那么此时 `swap(s[p],s[j])` , `j 满足  j  p , s[j]  s[p] , j 尽可能大` , 然后翻转 `s[p+1]` 即可。

比如  `s = acbdcb` , 那么第一个位置是 `s[2]` , `j == 4` , 那么先 `swap(s[2],s[4]) - accdbb` 然后翻转 `- accbbd`

```cpp
 [31. 下一个排列](httpsleetcode.cnproblemsnext-permutation)
templatetypename T
bool My_nextpermutation(T& s,int l,int r) {  s[lr] 区间的下一个排列
    r ++;
    for(int i = r - 2;i = l;i --) {
        if(s[i]  s[i + 1]) {  找到了
            int j = i + 1;
            while(j + 1  r && s[j + 1]  s[i]) j ++;
            swap(s[i],s[j]);
            reverse(s.begin() + i + 1,s.begin() + r);
            return true;
        }
    }
    reverse(s.begin() + l,s.begin() + r);
    return false; 没有下一个排列
}
```


### C++  next_permutation()

`C++` 自带的求 下一个 `字典序` 的库函数  `next_permutation`

```cpp


函数原型 
#include algorithm

bool next_permutation(iterator start,iterator end)

当当前序列不存在下一个排列时，函数返回false (此时整个序列为最小值)，否则返回true


nums = {1,2,3}
next_permutation(nums.begin(),nums.end());
 nums = {1,3,2}
```

### C++  prev_permutation()

`C++` 自带的求 上一个 `字典序` 的库函数  `prev_permutation`

```cpp


函数原型 
#include algorithm

bool prev_permutation(iterator start,iterator end)

当当前序列不存在上一个排列时，函数返回false (此时整个序列为最大值)，否则返回true


nums = {3,2,1}
prev_permutation(nums.begin(),nums.end());
 nums = {3,1,2}
```
