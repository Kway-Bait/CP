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

struct DSU{
    vector<int> parent;

    DSU(int n) {
        parent = vector<int>(n);
        iota(parent.begin(), parent.end(), 0);
    }

    int find_parent(int p){
        return (parent[p] == p)? p : parent[p] = find_parent(parent[p]);
    }

    bool merge(int a, int b){
        a = find_parent(a);
        b = find_parent(b);
        parent[a] = b;
        return (a != b);
    }
};

ll int plan_roller_coaster(vector<int> s, vector<int> t){
    s.PB(inf);
    t.PB(1);
    int n = s.size();
    // Coordinate Compression
    set<int> coor;
    for(int i = 0; i < n; i++){
        coor.insert(s[i]);
        coor.insert(t[i]);
    }

    map<int, int> mp;
    vector<int> val;
    int ind = 0;
    for(int i : coor){
        mp[i] = ind++;
        val.PB(i);
    }

    // Initial connect
    DSU dsu(ind);
    vector<int> entry(ind, 0);
    for(int i = 0; i < n; i++){
        entry[mp[s[i]]]++;
        entry[mp[t[i]]]--;
        dsu.merge(mp[s[i]], mp[t[i]]);
    }

    vector<int> balance(ind, 0);
    for(int i = 0, cur = 0; i < ind; i++){
        cur += entry[i];
        balance[i] = cur;
    }

    // Add positive edges
    ll int cost = 0;
    for(int i = 0; i < ind-1; i++){
        if(!balance[i]) continue;
        cost += max(0, 1ll * balance[i] * (val[i+1] - val[i]));
        dsu.merge(i, i+1);
        balance[i] = 0;
    }

    // Connect unconnected component
    using Edge = tuple<int, int, int>; 
    vector<Edge> edge;
    for(int i = 0; i < ind-1; i++){
        edge.PB({val[i+1] - val[i], i, i+1});
    }

    sort(edge.begin(), edge.end());

    for(auto [w, i, j] : edge){
        if(dsu.merge(i, j)){
            cost += w;
        }
    }

    return cost;
}

// int main(){
    
//     ios::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     // ifstream cin();
//     // ofstream cout();
    
//     ll int temp;
//     // temp = plan_roller_coaster({1, 4, 5, 6}, {7, 3, 8, 6});
//     // temp = plan_roller_coaster({1, 3, 5, 7}, {2, 4, 6, 8});
//     cout << temp << endl;
// }