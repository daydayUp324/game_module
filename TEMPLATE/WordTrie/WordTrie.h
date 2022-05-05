#include <bits/stdc++.h>
using namespace std;
#define WTSZ 26
#define BASE 'a'
class WordTrie
{
    /**
     * @author : daydayuppp
     * 
     * 1. 使用时需要设置 WTSZ 表示 不同 "字符" 的个数。 默认为 26
     * 2. 使用时需要设置 BASE 表示 基底字符。默认为 'a'
     * 
     * 使用范围 :
     * 
     * 1. 插入某一个单词
     * 2. 删除某一个单词
     * 3. 查询某一个单词(个数) 或者 前缀
     * 4. 查询某一个单词是能用当前数据结构中的单词组成
     */
private:
    int cnt;// 某一个节点 被多少个 word 所共用
    bool end;// 某一个节点 是否是一个 word 的结束
    WordTrie* next[WTSZ];
public:
    void add(string& w) {// 加入单词 w
        WordTrie* root = this;
        for(auto& c : w) {
            int next = c - BASE;
            if(!root->next[next]) root->next[next] = new WordTrie(); 
            root = root->next[next];
            root->cnt ++;
        }
        root->end = true;
    }
    bool helpErase(WordTrie* root,string& w,int curp) {
        if(curp == w.size() - 1) {
            if(root->end) {
                root->cnt --;
                if(!root->cnt) root = nullptr;
                return true;
            }
            return false;
        }
        int next = w[curp] - BASE;
        if(!root->next[next]) return false;
        root = root->next[next];
        if(!helpErase(root,w,curp + 1)) return false;
        root->cnt --;
        if(!root->cnt) root = nullptr;
        return true;
    }
    void erase(string& w) {// 删除单词 w 递归删除 helpErase() 将空节点置空
        WordTrie* root = this;
        helpErase(root,w,0);
    }
    int query(string& w) {// 查询 单词 w 的个数
        WordTrie* root = this;
        for(auto& c : w) {
            int next = c - BASE;
            if(!root->next[next]) return 0; 
            root = root->next[next];
        }
        if(root->end) return root->cnt;
        return 0;// 如果不是一个单词的结束
    }
    // Attention : 此时是当前的单词能重复使用 且 没有重复的单词
    // 如果有重复的单词,且不能重复使用的话,需要 bool end -> int end 并且在回溯的时候 主要 end 的更新
    bool helpJudge(WordTrie* root,vector<bool>& vi,string& w,int curp) {
        if(curp == w.size()) return root->end;
        int o = w[curp] - BASE;
        if(!vi[curp] && root->end) {
            if(this->next[o] && helpJudge(this->next[o],vi,w,curp + 1)) {
                return true;
            } 
            vi[curp] = true;
        }
        if(root->next[o] && helpJudge(root->next[o],vi,w,curp + 1)) return true;
        return false;
    }
    bool judgeCompose(string& w) {// 判断 单词 w 是否能被当前的单词所组成
        WordTrie* root = this;
        vector<bool> vi((int) w.size(),false);
        return helpJudge(root,vi,w,0);
    }
    bool startsWith(string& prefix) {// 查询是否有一个单词有前缀 prefix
        WordTrie* root = this;
        for(auto& c : prefix) {
            int next = c - BASE;
            if(!root->next[next]) return false; 
            root = root->next[next];
        }
        return true;
    }
    WordTrie() {
        this->cnt = 0 , this->end = false;
        for(int i = 0;i < WTSZ;i ++) this->next[i] = nullptr;
    };
};