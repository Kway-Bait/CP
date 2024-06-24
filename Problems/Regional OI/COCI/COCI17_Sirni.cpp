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

    bool merge(int a, int b){
        a = find_parent(a);
        b = find_parent(b);
        parent[a] = b;
        return (a != b);
    }
};

int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    // ifstream cin();
    // ofstream cout();
    
    int n;
    cin >> n;

    vector<int> p(n);

    for(int i = 0; i < n; i++){
        cin >> p[i];
    }

    sort(p.begin(), p.end());

    const int P = p.back() + 5;

    vector<int> nearest(P, -1);
    for(int i = 0; i < n; i++) nearest[p[i]] = i;
    for(int i = P-2; i >= 0; i--){
        if(nearest[i] == -1) nearest[i] = nearest[i+1];
    }

    vector<vector<pair<int, int>>> edge(P, vector<pair<int, int>>()); // Use Bucket Sort
    for(int i = 0; i < n; i++){
        if(i+1 < n && p[i] == p[i+1]) continue;
        if(nearest[p[i]+1] == -1) break;

        int remainder = p[nearest[p[i]+1]] % p[i];
        edge[remainder].PB(MP(i, nearest[p[i]+1]));

        for(int cur = p[i]*2; cur < P; cur += p[i]){
            if(nearest[cur] == -1) break;
            remainder = p[nearest[cur]] % p[i];
            edge[remainder].PB(MP(i, nearest[cur]));
        }
    }
    
    DSU dsu(n);

    ll int ans = 0;
    for(int remainder = 0; remainder < P; remainder++){
        for(pair<int, int> p : edge[remainder]){
            if(dsu.merge(p.f, p.s)){
                ans += remainder;
            }
        }
    }

    cout << ans << endl;
}