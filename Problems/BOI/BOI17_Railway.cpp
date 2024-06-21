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

vector<vector<int>> adj(N, vector<int>()), par(19, vector<int>(N));
vector<int> to(N), tin(N), tout(N);
map<pair<int, int>, int> ind;

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
    return (tin[anc] <= tin[child] && tout[anc] >= tout[child]);
}

int get_lca(int a, int b){
    if(isAncestor(b, a)) return b;
    int lca = a, cur = b;
    for(int i = 18; i >= 0; i--){
        int next_cur = par[i][cur];
        if(isAncestor(next_cur, a)){
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
    
    int n, m, k;
    cin >> n >> m >> k;
    for(int i = 1; i <= n-1; i++){
        int a, b;
        cin >> a >> b;

        ind[MP(a, b)] = i;
        ind[MP(b, a)] = i;

        adj[a].PB(b);
        adj[b].PB(a);
    }

    to[1] = 1;
    dfs(1, -1);

    BIT bit(n*2);

    for(int i = 1; i <= n; i++) par[0][i] = to[i];
    for(int i = 1; i < 19; i++){
        for(int j = 1; j <= n; j++){
            par[i][j] = par[i-1][par[i-1][j]];
        }
    }

    for(int i = 0; i < m; i++){
        int num;
        cin >> num;
        vector<int> query(num);
        for(int j = 0; j < num; j++) cin >> query[j];
        sort(query.begin(), query.end(), [](int &a, int &b){return tin[a] < tin[b];});
        query.PB(query[0]);

        for(int j = 0; j < num; j++){
            int lca = get_lca(query[j], query[j+1]);
            bit.add(tin[query[j]], 1);
            bit.add(tin[query[j+1]], 1);
            bit.add(tin[lca], -2);
        }
    }

    vector<int> ans;
    for(int i = 2; i <= n; i++){
        if(bit.sum(tout[i]) - bit.sum(tin[i]-1) >= 2*k){
            ans.PB(ind[MP(i, to[i])]);
        }
    }

    sort(ans.begin(), ans.end());

    cout << ans.size() << endl;
    for(int i : ans) cout << i << ' ';
    
}