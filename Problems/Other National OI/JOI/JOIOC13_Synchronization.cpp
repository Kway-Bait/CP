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

struct BIT {
    int sz;
    vector<int> tree;

    BIT(int n) : sz(n+2), tree(n+2, 0) {};

    void add(int pos, int val){
        while(pos < sz){
            tree[pos] += val;
            pos += pos&-pos;
        }
    }

    int sum(int pos){
        int ans = 0;
        while(pos >= 1){
            ans += tree[pos];
            pos -= pos&-pos;
        }
        return ans;
    }
};

vector<vector<int>> adj(N, vector<int>()), par(20, vector<int>(N));
vector<int> to(N), tin(N), tout(N); // For LCA and Binary Lifting
vector<int> info(N, 1), last_sync(N, 0);

vector<pair<int, int>> edge;
bool active[N]{false};

int timer = 1;
void dfs(int cur, int prev){
    tin[cur] = timer++;
    for(int child : adj[cur]){
        if(child == prev) continue;
        to[child] = cur;
        dfs(child, cur);
    }

    tout[cur] = timer++;
}

bool isAncestor(int anc, int child){
    return (tin[anc] < tin[child] && tout[anc] > tout[child]);
}

int find_root(BIT &bit, int child){
    int cur = child, at = bit.sum(tin[child]);
    for(int i = 19; i >= 0; i--){
        int next_cur = par[i][cur];
        if(at - bit.sum(tin[next_cur]) == 0){
            cur = next_cur;
        }
    }
    return cur;
}

int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    // ifstream cin();
    // ofstream cout();
    
    int n, m, q;
    cin >> n >> m >> q;

    edge = vector<pair<int, int>>(n);

    for(int i = 1; i <= n-1; i++){
        int a, b;
        cin >> a >> b;

        edge[i] = MP(a, b);

        adj[a].PB(b);
        adj[b].PB(a);
    }

    to[1] = 1;
    dfs(1, -1);

    BIT bit(n*2);
    
    for(int i = 1; i <= n; i++){
        bit.add(tin[i], 1);
        bit.add(tout[i], -1);
    }

    for(int i = 1; i <= n; i++) par[0][i] = to[i];
    for(int i = 1; i < 20; i++){
        for(int j = 1; j <= n; j++){
            par[i][j] = par[i-1][par[i-1][j]];
        }
    }

    while(m--){
        int x;
        cin >> x;

        auto [u, v] = edge[x];
        if(isAncestor(v, u)) swap(u, v);
        
        if(!active[x]){
            // Activate
            bit.add(tin[v], -1);
            bit.add(tout[v], 1);

            int root = find_root(bit, v);
            info[root] += info[v] - last_sync[v];
        }else {
            // Deactivate
            bit.add(tin[v], 1);
            bit.add(tout[v], -1);

            int root = find_root(bit, u);
            info[v] = info[root];
            last_sync[v] = info[root];
        }

        active[x] = !active[x];
    }

    while(q--){
        int x;
        cin >> x;
        cout << info[find_root(bit, x)] << endl;
    }
    
}