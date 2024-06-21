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
#define PF push_front
#define PB push_back
#define MP make_pair
#define max(a, b) ((a > b)? a : b)
#define min(a, b) ((a < b)? a : b)
#define max3(a, b, c) max(max(a, b), c)
#define min3(a, b, c) min(min(a, b), c)

const int N = 2e2 + 5;
const int TOWN = 250 + 5;
const int M = 1e9 + 7; 
const int inf = 0x3f3f3f3f;
const ll int INF = 1e18;


int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    // ifstream cin();
    // ofstream cout();
    
    vector<vector<int>> region, adj(N, vector<int>());
    vector<bool> is_member(TOWN, false);

    int n, m, l;
    cin >> n >> m >> l;
    for(int i = 0; i < l; i++){
        int member;
        cin >> member;
        is_member[member] = true;
    }

    map<pair<int, int>, int> connector;
    for(int i = 0; i < n; i++){
        int sz;
        cin >> sz;
        region.PB(vector<int>());
        for(int j = 0; j < sz; j++){
            int a; cin >> a;
            region[i].PB(a);
        }

        for(int j = 0; j < sz; j++){
            pair<int, int> cur = {min(region[i][j], region[i][(j+1)%sz]), max(region[i][j], region[i][(j+1)%sz])};
            if(connector[cur] == 0){
                connector[cur] = i+1;
            }else {
                int neighbour = connector[cur] - 1;
                adj[neighbour].PB(i);
                adj[i].PB(neighbour);
            }
        }
    }

    // for(int i = 0; i < n; i++){
    //     cout << "At: " << i << " adj to: ";
    //     for(int j : adj[i]) cout << j << ' ';
    //     cout << endl;
    // }

    // BFS from all region and find optimal
    int ans = inf, ans_region = -1;
    bool vis_member[TOWN]{false}, vis[N]{false};
    for(int i = 0; i < n; i++){
        memset(vis_member, false, sizeof(vis_member));
        memset(vis, false, sizeof(vis));

        int cnt = 0;

        queue<pair<int, int>> q;
        q.push(MP(i, 0));
        vis[i] = true;

        while(!q.empty()){
            auto [cur, step] = q.front();
            q.pop();

            for(int town : region[cur]){
                if(is_member[town] && !vis_member[town]){
                    vis_member[town] = true;
                    cnt += step;
                }
            }

            for(int neigh : adj[cur]){
                if(vis[neigh]) continue;
                vis[neigh] = true;
                q.push(MP(neigh, step + 1));
            }
        }

        if(cnt < ans){
            ans = cnt;
            ans_region = i+1;
        }
    }
    
    cout << ans << endl << ans_region << endl;
}