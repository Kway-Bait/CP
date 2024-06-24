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


int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    // ifstream cin();
    // ofstream cout();
    
    ll int n, k, m;
    cin >> n >> k >> m;

    vector<ll> p(n);

    for(int i = 0; i < n; i++){
        cin >> p[i];
    }

    vector<int> to(n);
    int l = 0, r = k;
    for(int i = 0; i < n; i++){
        while(r+1 < n && p[r+1] - p[i] < p[i] - p[l]){
            r++, l++;
        }

        if(p[i] - p[l] >= p[r] - p[i]){
            to[i] = l;
        }else {
            to[i] = r;
        }
    }

    vector<int> ans(n), nxt(n), new_nxt(n);
    iota(ans.begin(), ans.end(), 0);
    for(int i = 0; i < n; i++) nxt[i] = to[i]; // First step

    for(int i = 0; i < 60; i++){
        if((m >> i) & 1) {
            for(int j = 0; j < n; j++){
                ans[j] = nxt[ans[j]];
            }
        }

        for(int j = 0; j < n; j++){
            new_nxt[j] = nxt[nxt[j]];
        }

        nxt = new_nxt;
    }

    for(int i = 0; i < n; i++){
        cout << ans[i] + 1 << ' ';
    }
}