#include <bits/stdc++.h>
using namespace std;
/**
 * @author : daydayUppp
 * @brief  : 
 * 主要参考 : [C++ STL：unordered_map 自定义键值类型](https://blog.csdn.net/y109y/article/details/82669620)
 * 
 * 首先给出官方定义 :
 * template<class Key,
    class Ty,
    class Hash = std::hash<Key>,
    class Pred = std::equal_to<Key>,
    class Alloc = std::allocator<std::pair<const Key, Ty> > >
    class unordered_map;
    > class unordered_map
 * 
 * 所以需要重载 unordered_map 中添加的数据类型的 == (第四个参数需要) 和 哈希函数
 * 注意哈希值是可以重复的 , 因为有冲突的可能 , 但是当冲突比较多的时候会影响性能
 */
const int N = 1e5;
struct Node {
    int a,b,c;
    // 两个构造函数
    Node(int a_,int b_,int c_) : a(a_) , b(b_) , c(c_) {}
    Node() {}
    bool operator == (const Node& A) const {
        return a == A.a && b == A.b && c == A.c;
    }
};

// 方法一 : 重载operator()的类
// unordered_map<Node,int,hash_mp> mp;
struct hash_mp {
    long long operator()(const Node& A) const {
        long long val = (long long) A.a * N * N + A.b * N + A.c;
        return val;
    }
};

// 方法二 : 构建函数实例
// 1. unordered_map<Node,int,decltype(&ump_hash)> mp(100,ump_hash);
// 2. unordered_map<Node,int,function<long long( const Node& p )>> mp(100, ump_hash);
long long ump_hash(const Node& A) {
    long long val = (long long) A.a * N * N + A.b * N + A.c;
    return val;
}
// 方法三 : 模板定制 不过要确保自己的hash function不会影响std空间里的其他类
// unordered_map<Node,int> mp;
namespace std {
    template <>
        class hash<Node>{
            public :
                long long operator()(const Node &A ) const
                {
                    return (long long) A.a * N * N + A.b * N + A.c;
                }
        };
};

int main() {
    int n;
    cin >> n;
    int a,b,c;
    // 方法一 : 
    // unordered_map<Node,int,hash_mp> mp;
    // 方法二 :
    // unordered_map<Node,int,decltype(&ump_hash)> mp(100,ump_hash);
    // unordered_map<Node,int,function<long long( const Node& p )>> mp(100, ump_hash);
    // 方法三 : 
    unordered_map<Node,int> mp;
    for(int i = 0;i < n;i ++) {
        cin >> a >> b >> c;
        cout<<"Insert : "<<a<<" , "<<b<<" , "<<c<<"\n";
        mp[Node(a,b,c)] ++;
    }
    cin >> n;
    cout<<"\n";
    for(auto it = mp.begin();it != mp.end();it ++) {
        cout<<it->first.a<<" , "<<it->first.b<<" , "<<it->first.c<<"\n";
    }
    cout<<"\n";
    for(int i = 0;i < n;i ++) {
        cin >> a >> b >> c;
        cout<<"Query : "<<a<<" , "<<b<<" , "<<c<<"\n";
        if(mp.count(Node(a,b,c))) cout<<"Exist. cnt : "<<mp[Node(a,b,c)]<<"\n";
        else cout<<"Not Exist.\n";
    }
    return 0;
}