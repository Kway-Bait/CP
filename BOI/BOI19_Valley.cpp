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

const int N = 1e5 + 5;
const int M = 1e9 + 7; 
const int inf = 0x3f3f3f3f;
const ll int INF = 1e18;

vector<vector<pair<int, ll>>> adj(N, vector<pair<int, ll>>()), par(20, vector<pair<int, ll>>(N));
vector<pair<int, int>> edge;
vector<int> depth(N), tin(N), sz(N, 1), to(N);
vector<ll> path(N), dp(N);
vector<bool> isShop(N, false);

int entry = 1;
void dfs(int cur, int prev = -1){
    tin[cur] = entry++;
    dp[cur] = (isShop[cur])? path[cur] : INF;
    for(auto [child, weight] : adj[cur]){
        if(child == prev) continue;

        depth[child] = depth[cur] + 1;
        path[child] = path[cur] + weight;
        to[child] = cur;

        dfs(child, cur);

        if(dp[child] != INF) dp[cur] = min(dp[cur], dp[child] + 2*path[child]);
        sz[cur] += sz[child];
    }
    if(dp[cur] != INF) dp[cur] -= 2*path[cur];
}

bool isAncestor(int child, int anc){
    return (tin[anc] <= tin[child] && tin[anc] + sz[anc] > tin[child]);
}

int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    // ifstream cin();
    // ofstream cout();
    
    int n, s, q, e;
    cin >> n >> s >> q >> e;
    for(int i = 0; i < n-1; i++){
        int a, b, w;
        cin >> a >> b >> w;
        edge.PB(MP(a, b));
        adj[a].PB(MP(b, w));
        adj[b].PB(MP(a, w));
    }

    for(int i = 0; i < s; i++) {
        int shop;
        cin >> shop;
        isShop[shop] = true;
    }
    
    // let lca(u, v) = w, 
    // dis(u, v) = path[u] - path[w] + path[v] - path[w]
    // let v be the closest shop to w in subtree with root w
    // dp[w] = path[v] - 2*path[w];
    // Transition: dp[w] = min(dp[i] + 2*path[i]) - 2*path[w];

    // Find all dp[i], such that answer for R is path[R] + min(dp[i])

    to[e] = e;
    path[e] = 0;
    dfs(e);

    for(int i = 1; i <= n; i++) par[0][i] = MP(to[i], min(dp[i], dp[to[i]]));
    for(int i = 1; i < 20; i++){
        for(int j = 1; j <= n; j++){
            par[i][j] = par[i-1][par[i-1][j].f];
            par[i][j].s = min(par[i][j].s, par[i-1][j].s);
        }
    }

    while(q--){
        int block, start;
        cin >> block >> start;

        auto [x, y] = edge[block-1];
        if(depth[x] > depth[y]) swap(x, y);

        if(isAncestor(start, y)){
            int dis = depth[start] - depth[y];
            ll mn = dp[start];

            int cur = start;
            for(int i = 0; i < 20; i++){
                if((dis >> i) & 1){
                    mn = min(mn, par[i][cur].s);
                    cur = par[i][cur].f;
                }
            }
            
            if(mn == INF){
                cout << "oo" << endl;
            }else {
                cout << path[start] + mn << endl;
            }
        }else {
            cout << "escaped" << endl;
        }
    }
}