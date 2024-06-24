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

const int N = 1e4 + 5;
const int M = 1e9 + 7; 
const int inf = 0x3f3f3f3f;
const ll int INF = 1e18;

struct DSU {
    vector<int> parent;

    DSU(int n){
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

    bool same(int a, int b){
        a = find_parent(a);
        b = find_parent(b);
        return (a == b);
    }
};

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
    
    using Edge = tuple<int, int, int, int>;
    vector<Edge> edge;
    int n, m, k;
    cin >> n >> m >> k;
    for(int i = 0; i < m; i++){
        int a, b, c;
        cin >> a >> b >> c;
        edge.PB({c, a, b, i});
    }
    
    sort(edge.rbegin(), edge.rend());

    vector<DSU> dsu(k+1, DSU(n+1));
    vector<int> ans(m, 0);

    for(auto [w, a, b, id] : edge){
        int ind = bin(1, k, [&](int x){
            return !dsu[x].same(a, b);
        });
        if(dsu[ind].merge(a, b)) ans[id] = ind;
    }

    for(int i = 0; i < m; i++){
        cout << ans[i] << endl;
    }
}