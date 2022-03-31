#include <bits/stdc++.h>
using namespace std;
/**
 * @author : daydayUppp
 * @brief  : 
 * 主要参考 : [C++ STL: map自定义键值类型](https://blog.csdn.net/y109y/article/details/82901710)
 * 
 * 首先给出官方定义 :
    template < class Key,                                   //map::key_tpe
           class T,                                     //map::mapped_type
           class Compare = less<Key>,                   //map::key_compare
           class Alloc = allocator<pair<const Key, T>>  //map::allocator_type
           > class map;
 * 所以需要重载 map 中添加的数据类型的 == 和 比较函数 less<Key>
 * 方法一 : 重载 operator < () 操作符 (最为方便)
 * 方法二 : 利用std::function。它是一种通用、多态、类型安全的函数封装
 * 方法三 : 重载 operator() 的类
 * 方法四 : 模板定制 直接给出 less<Node> 的定义
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
    // 方法一 : 重载 operator < () 操作符
    // bool operator <(const Node& A) const {// 按照字典序排序
    //     if(a == A.a) return b == A.b ? b < A.b : c < A.c;
    //     return a < A.a;
    // }
};
// 方法二 : 构建函数实例
// map<Node,int,decltype(&mp_cmp)> mp(mp_cmp);
bool mp_cmp(const Node& A,const Node& B) {
    if(A.a == B.a) return A.b == B.b ? A.c < B.c : A.b < B.b;
    return A.a < B.a;
}
// 方法三 : 重载 operator() 的类
// map<Node,int,MyCmp> mp;
struct MyCmp {
    bool operator () (const Node& A,const Node& B) const {
        if(A.a == B.a) return A.b == B.b ? A.c < B.c : A.b < B.b;
        return A.a < B.a;
    }
};
// 方法四 : 模板定制 直接给出 less<Node> 的定义
namespace std {
    template <>
        class less<Node>{
            public :
                bool operator () (const Node& A,const Node& B) const {
                    if(A.a == B.a) return A.b == B.b ? A.c < B.c : A.b < B.b;
                    return A.a < B.a;
                }
        };
};

int main() {
    int n;
    cin >> n;
    int a,b,c;
    // 方法一 : 
    // map<Node,int> mp;
    // 方法二 :
    // map<Node,int,decltype(&mp_cmp)> mp(mp_cmp);
    // 方法三 : 
    // map<Node,int,MyCmp> mp;
    // 方法四 :
    map<Node,int> mp;
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