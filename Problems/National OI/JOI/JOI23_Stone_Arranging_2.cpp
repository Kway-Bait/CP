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

struct DSU {
    vector<int> parent;

    DSU(int n){
        parent = vector<int>(n);
        iota(parent.begin(), parent.end(), 0);
    }

    int find_parent(int p){
        return (parent[p] == p)? p : parent[p] = find_parent(parent[p]);
    }

    int merge(int a, int b){
        a = find_parent(a);
        b = find_parent(b);
        if(a > b) swap(a, b);
        return parent[a] = b;
    }
};

int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    // ifstream cin();
    // ofstream cout();
    
    int n;
    cin >> n;

    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    // Coordinate compression
    map<int, int> idx;
    set<int> temp;
    for(int i = 0; i < n; i++) temp.insert(a[i]);

    int ind = 0;
    for(int i : temp){
        idx[i] = ind++;
    }

    // Solve
    DSU dsu(n);
    vector<stack<int>> v(N, stack<int>());
    for(int i = 0; i < n; i++){
        int cur = idx[a[i]];
        while(!v[cur].empty()){
            int prev = v[cur].top();
            v[cur].pop();

            if(dsu.find_parent(prev) == prev){
                int temp = prev;
                while(temp != i){
                    temp = dsu.merge(temp, temp+1);
                }
                break;
            }
        }

        v[cur].push(i);
    }

    // Output
    for(int i = 0; i < n; i++){
        cout << a[dsu.find_parent(i)] << endl;
    }
}