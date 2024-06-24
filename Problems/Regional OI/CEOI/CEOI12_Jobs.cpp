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

const int N = 1e6 + 5;
const int M = 1e9 + 7; 
const int inf = 0x3f3f3f3f;
const ll int INF = 1e18;

int bin(int l, int r, function<bool(int)> f){
    while(l < r){
        int mid = l + (r - l)/2;
        if(f(mid)){
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return l;
}

int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    // ifstream cin();
    // ofstream cout();
    
    vector<pair<int, int>> v;
    int n, d, m, a;
    cin >> n >> d >> m;
    for(int i = 0; i < m; i++){
        cin >> a;
        v.PB(MP(a, i+1));
    }
    
    sort(v.begin(), v.end());

    vector<vector<int>> ans;
    int mac = bin(1, m, [&](int x){
        vector<vector<int>> cur_ans;
        bool valid = true;
        int tot = 0;
        for(int day = 1, i = 0; day <= n && i < m; day++){
            int cnt = 0;
            vector<int> cur;
            while(i < m && cnt < x && v[i].f <= day){
                if(day - d > v[i].f) valid = false;
                cur.PB(v[i].s);
                cnt++;
                i++;
            }
            tot += cur.size();
            cur_ans.PB(cur);
        }

        if(valid && tot == m) ans = cur_ans;
        return (valid && tot == m);
    });
    
    cout << mac << endl;
    for(int i = 0; i < n; i++){
        if(i < (int)ans.size()){
            for(int j : ans[i]){
                cout << j << ' ';
            }
        }
        cout << 0 << endl;
    }
}