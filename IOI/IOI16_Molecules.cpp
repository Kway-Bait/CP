#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cstring>
#include <string>
#include <cmath>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
 
using namespace std;
#define ll long long
#define ull unsigned long long
#define f first
#define s second
#define PF push_front
#define PB push_back
#define MP make_pair
#define max(a, b) ((a > b)? a : b)
#define min(a, b) ((a < b)? a : b)
#define max3(a, b, c) max(max(a, b), c)
#define min3(a, b, c) min(min(a, b), c)
 
const int N = 2e5 + 5;
const int M = 1e9 + 7; 
const int inf = 0x3f3f3f3f;
const ll int INF = 1e18;
 
vector<int> find_subset(int l, int u, vector<int> w){
    int n = w.size();
    vector<pair<int, int>> v;
    for(int i = 0; i < n; i++){
        v.PB(MP(w[i], i));
    }
 
    sort(v.begin(), v.end());
 
    ll int pre = 0, suf = 0, sz = -1;
    for(int i = 0; i < n; i++){
        pre += v[i].f;
        suf += v[n-i-1].f;
        if(pre <= u && suf >= l){
            sz = i;
            break;
        }
    }
    
    vector<int> ans;
    if(sz == -1) return ans;
    
    pre = suf = 0;
    for(int i = 0; i <= sz; i++){
        pre += v[i].f;
    }
 
    for(int i = 0; i <= sz; i++){
        if(pre + suf >= l && pre + suf <= u) break;
        pre -= v[sz-i].f;
        suf += v[n-i-1].f;
    }
 
    for(ll int i = 0, temp = 0; temp < pre; temp += v[i].f, i++) ans.PB(v[i].s);
    for(ll int i = 0, temp = 0; temp < suf; temp += v[n-i-1].f, i++) ans.PB(v[n-i-1].s);
 
    return ans;
}