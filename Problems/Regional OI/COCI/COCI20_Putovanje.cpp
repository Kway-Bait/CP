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

    BIT(int n) : sz(n+1), tree(n+1, 0) {};

    void add(int pos, int val){
        for(; pos < sz; pos += pos&-pos) tree[pos] += val;
    }

    int sum(int pos){
        int ans = 0;
        for(; pos >= 1; pos -= pos&-pos) ans += tree[pos];
        return ans;
    }
};

vector<vector<pair<int, int>>> adj(N, vector<pair<int, int>>());
vector<vector<int>> par(20, vector<int>(N));
vector<pair<int, int>> ticket(N);
vector<int> to(N), to_edge(N), tin(N), tout(N);

int timer = 1;
void dfs(int cur, int prev){
    tin[cur] = timer++;
    for(auto [child, edge_id] : adj[cur]){
        if(child == prev) continue;

        to[child] = cur;
        to_edge[child] = edge_id;

        dfs(child, cur);
    }
    tout[cur] = timer++;
}

bool isAncestor(int anc, int child){
    return (tin[anc] <= tin[child] && tout[anc] >= tout[child]);
}

int get_lca(int a, int b){
    if(isAncestor(a, b)) return a;
    int lca = b, cur = a;
    for(int i = 19; i >= 0; i--){
        int next_cur = par[i][cur];
        if(isAncestor(next_cur, b)){
            lca = next_cur;
        }else {
            cur = next_cur;
        }
    }
    return lca;
}

int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    // ifstream cin();
    // ofstream cout();
    
    int n;
    cin >> n;
    for(int i = 1; i <= n-1; i++){
        int a, b, c1, c2;
        cin >> a >> b >> c1 >> c2;
        adj[a].PB(MP(b, i));
        adj[b].PB(MP(a, i));
        ticket[i] = MP(c1, c2);
    }

    to[1] = 1;
    to_edge[1] = -1;
    dfs(1, -1);
    
    BIT bit(n*2);

    for(int i = 1; i <= n; i++) par[0][i] = to[i];
    for(int i = 1; i < 20; i++){
        for(int j = 1; j <= n; j++){
            par[i][j] = par[i-1][par[i-1][j]];
        }
    }

    for(int i = 1; i < n; i++){
        int lca = get_lca(i, i+1);
        bit.add(tin[i], 1);
        bit.add(tin[i+1], 1);
        bit.add(tin[lca], -2);
    }

    // Check for each edge, its number of passing
    ll ans = 0;
    for(int i = 2; i <= n; i++){
        int cur = bit.sum(tout[i]) - bit.sum(tin[i] - 1), ind = to_edge[i];
        ans += min(1ll * ticket[ind].f * cur, ticket[ind].s);
    }

    cout << ans << endl;

}