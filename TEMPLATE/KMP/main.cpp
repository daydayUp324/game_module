#include "KMP.h"
int main() {
    string s,p;
    cin >> s >> p;
    KMP h(p);
    int pos = h.Match_s(s);
    if(pos == -1) cout<<"Not Match.\n";
    else cout<<"Match successful.\n"<<s.substr(pos,p.size())<<"\n";
    return 0;
}