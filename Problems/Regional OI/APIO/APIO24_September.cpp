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

struct DSU {
    vector<int> parent;

    DSU(int n){
        parent = vector<int>(n+1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find_parent(int p){
        return (parent[p] == p)? p : parent[p] = find_parent(parent[p]);
    }

    void merge_range(int a, int b){
        if(a > b) swap(a, b);
        for(int i = a; i < b; i++){
            if(!merge(i, b)){
                // This segment has been unified
                break;
            }
        }

        for(int i = b-1; i >= a; i--){
            if(!merge(i, b)){
                // This segment has been unified also
                break;
            }
        }
    }

    bool merge(int a, int b){
        a = find_parent(a);
        b = find_parent(b);
        if(a > b) swap(a, b);
        parent[a] = b;
        return (a != b);
    }
};

vector<vector<int>> adj;
vector<bool> vis_parent, vis;

void init(int n){
    adj = vector<vector<int>>(n, vector<int>());
    vis_parent = vector<bool>(n, false);
    vis = vector<bool>(n, false);
}

int get_max_index(int cur, int prev, vector<int> &index){
    if(vis[cur]) return -1;
    vis[cur] = true;

    int max_index = index[cur];
    for(int child : adj[cur]){
        if(child == prev) continue;
        int next = get_max_index(child, cur, index);
        max_index = max(max_index, next);
    }

    return max_index;
}

// Two rules:
// 1: If a parent falls, all of its children fell
// 2: If same leaf appear in different index by different record, the range will be in same day

int solve(int n, int m, vector<int> to, vector<vector<int>> v){
    init(n);
    
    // Fill adjacency list
    for(int i = 1; i < n; i++){
        adj[i].PB(to[i]);
        adj[to[i]].PB(i);
    }

    DSU dsu(n);

    vis = vector<bool>(n, false);
    vector<vector<int>> ind(m);
    for(int i = 0; i < m; i++){
        // Process index
        vector<int> index(n);
        for(int j = 0; j < n-1; j++){
            index[v[i][j]] = j;
        }

        ind[i] = index;
        
        // Construct segment here
        queue<int> included;
        for(int j = 0; j < n-1; j++){
            if(vis[v[i][j]]) continue;

            int last_max_index = j;
            included.push(v[i][j]);
            while(!included.empty()){
                int cur = included.front();
                included.pop();

                if(vis[cur]) continue;

                int max_index = get_max_index(cur, to[cur], index);
                for(int k = last_max_index+1; k <= max_index; k++){
                    if(!vis[v[i][k]]) included.push(v[i][k]);
                }
                
                last_max_index = max(last_max_index, max_index);
            }

            dsu.merge_range(j, last_max_index);
        }
    }

    // Merge union with index of same leaf (Must be same day in the range)
    for(int i = 1; i < n; i++){
        int mn = n, mx = -1;
        for(int j = 0; j < m; j++){
            mn = min(mn, ind[j][i]);
            mx = max(mx, ind[j][i]);
        }

        dsu.merge_range(mn, mx);
    }

    int cnt = 0;
    for(int i = 0; i < n-1;){
        int par = dsu.find_parent(i);
        if(vis_parent[par]) continue;
        vis_parent[par] = true;
        cnt++;

        i = par + 1;
    }

    return cnt;
}