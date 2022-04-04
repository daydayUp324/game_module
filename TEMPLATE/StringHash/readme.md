#

## 字符串哈希

```cpp
/**
 * @author : daydayUppp
 * StringHash : 
 * 用 PII 的双哈希来减小冲突的可能 , hash<int>() 用于产生一个哈希值
 * 
 * 算法 :
 * 1. 首先产生两个随机数 Base1 , Base2 作为基底 , Base1 , Base2 都用随机数生成
 * 2. hash(s[i:j]) = {h1,h2}
 *      - h1 = (index = i->j) sum{ s[index] * Base1^(j - index) } % MOD1
 *      - h2 = (index = i->j) sum{ s[index] * Base2^(j - index) } % MOD2
 * 3. 所以预处理 : 
 *      - pow1[i] = (Base1 ^ i) % MOD1 , pow2[i] = (Base2 ^ i) % MOD2
 *      - pre1[i] = hash( s[0:i] ) : Base1 , pre2[i] = hash( s[0:i] ) : Base2
 * 4. 那么计算 对于 Base1 来说 :
 *      hash( s[i : j] ) : Base1 : 
 *      - 1. i == 0 : return pre1[j];
 *      - 2. return pre1[j] - pre1[i - 1] * pow1[j + 1 - i];
 * 5. 计算 对于 Base2 来说同理可得
 * 
 * 注意 : 减法时的负数问题
 */
```
