#include "RangeModule_Point.h"
#include "RangeModule_Seg.h"
void Print_Point(RangeModule_Point* h,int l,int r) {// 打印 [l,r] 上每一个点的信息
    cout<<"[ "<<l<<" , "<<r<<" ] : \n";
    for(int i = l;i <= r;i ++) {
        cout<<h->getQ(i)<<" ";
    }
    cout<<"\n";
}
void Test_RangeModule_Point() {// 测试 RangeModule_Point 模块 无需输入
    RangeModule_Point* h = new RangeModule_Point(1,8);
    cout<<"Initial seg : [1,8,2] : \n\n";
    h->add(1,8,2);
    Print_Point(h,1,8);
    cout<<"The current max-length : "<<h->getMaxRLen()<<"\n";
    cout<<"\n\n";

    cout<<"change pos_1 -> 3 : \n\n";
    cout<<"Before change : \n";
    Print_Point(h,1,8);
    h->update(1,3);
    cout<<"After change : \n";
    Print_Point(h,1,8);
    cout<<"The current max-length : "<<h->getMaxRLen()<<"\n";
    cout<<"\n\n";

    cout<<"change pos_5 -> 1 : \n\n";
    cout<<"Before change : \n";
    Print_Point(h,1,8);
    h->update(5,1);
    cout<<"After change : \n";
    Print_Point(h,1,8);
    cout<<"The current max-length : "<<h->getMaxRLen()<<"\n";
    cout<<"\n\n";
}
void Help(RangeModule_Seg* h,int op,int l,int r) {// 帮助测试 RangeModule_Seq 模块
    if(op == 1) {
        cout<<"Add [ "<<l<<" , "<<r<<" ] : \n"; h->add(l,r); h->Print_Seq();
        h->Print_Len();
        cout<<" ----------- \n\n";
    } else if(op == 2) {
        cout<<"Erase [ "<<l<<" , "<<r<<" ] : \n"; h->erase(l,r); h->Print_Seq();
        h->Print_Len();
        cout<<" ----------- \n\n";
    } else {
        cout<<"query [ "<<l<<" , "<<r<<" ] : \n"; 
        if(h->query(l,r)) cout<<" YES\n ";
        else cout<<" NO\n ";
        cout<<" ----------- \n\n";
    }
}
void Test_RangeModule_Seq() {// 测试 RangeModule_Seq 模块
    RangeModule_Seg* h = new RangeModule_Seg(true);
    int op,l,r,n;
    cin >> n;
    for(int i = 0;i < n;i ++) {
        cin >> op >> l >> r;
        Help(h,op,l,r);// 输入数据在 data.txt 中
    }
}
int main() {
    // Test_RangeModule_Point();
    Test_RangeModule_Seq();
    return 0;
}