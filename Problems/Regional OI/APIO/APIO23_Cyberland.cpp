#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <functional>
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
#define PB push_back
#define MP make_pair
#define max(a, b) ((a > b)? a : b)
#define min(a, b) ((a < b)? a : b)

const int N = 1e5 + 5;
const int M = 1e9 + 7; 
const int inf = 0x3f3f3f3f;
const double INF = 1e18;

// Make variable global 
vector<vector<pair<int, int>>> adj(N, vector<pair<int, int>>());
vector<int> canUse(N, false);

void init(int n){
    adj.clear();
    adj.resize(n, vector<pair<int, int>>());
    for(int i = 0; i < n; i++) canUse[i] = false;
}

void dfs(int cur, int h){
    if(cur == h) return;
    canUse[cur] = true;
    for(pair<int, int> p : adj[cur]){
        if(!canUse[p.f]) dfs(p.f, h);
    }
    
}

double solve(int n, int m, int k, int h, vector<int> x, vector<int> y, vector<int> c, vector<int> arr){
    init(n);
    for(int i = 0; i < m; i++){
        adj[x[i]].PB(MP(y[i], c[i]));
        adj[y[i]].PB(MP(x[i], c[i]));
    }

    dfs(0, h);
    arr[0] = 0;
    k = min(k, 69);

    vector<double> half(k+1, 1);
    for(int i = 1; i <= k; i++){
        half[i] = half[i-1]/2;
    }

    using node = tuple<double, int, int>;
    priority_queue<node, vector<node>, greater<node>> pq;
    vector<vector<double>> dis(n, vector<double>(k+1, 1e18));
    
    auto query = [&](int id, int use, double time){
        if(dis[id][use] > time){
            dis[id][use] = time;
            pq.push((node)make_tuple(time, use, id));
        }
    };

    query(h, k, 0);
    while(!pq.empty()){
        auto [time, use, id] = pq.top();
        pq.pop();
        
        if(dis[id][use] < time) continue;
        if(arr[id] == 0) return time;
        
        for(pair<int, int> p : adj[id]){
            if(!canUse[p.f]) continue;
            // Didnt use ability
            query(p.f, use, time + (double)p.s * half[k - use]);

            // Use ability
            if(arr[id] == 2 && use > 0) query(p.f, use-1, time + (double)p.s * half[k - use + 1]);
        }
    }

    return -1;
}