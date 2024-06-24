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

struct BIT{
    int sz;
    vector<int> tree;

    BIT(int n) : sz(n+1), tree(n, 0) {};

    void add(int pos, int val){
        for(; pos < sz; pos += pos&-pos) tree[pos] += val;
    }

    int query(int pos){
        int temp = 0;
        for(; pos >= 1; pos -= pos&-pos) temp += tree[pos];
        return temp;
    }
};

ll int count_swaps(vector<int> v){
    int n = v.size();
    vector<queue<int>> pos(2*N, queue<int>());
    for(int i = 0; i < n; i++){
        pos[v[i] + N].push(i);
    }

    BIT bit(2*N);
    vector<bool> vis(n, false);

    ll int move = 0;
    for(int i = 0; i < n; i++){
        if(vis[i]) continue;
        int target = pos[N-v[i]].front();
        pos[N+v[i]].pop();
        pos[N-v[i]].pop();

        int ori_offset = bit.query(i);
        int tar_offset = bit.query(target);
        int offset = tar_offset - ori_offset;

        move += (target - i - 1) - offset;
        if(v[i] > 0) move++;

        bit.add(target, 1);
        vis[target] = true;
    }

    return move;
}

// int main(){
    
//     ios::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     // ifstream cin();
//     // ofstream cout();
    
//     ll int temp;
//     // temp = count_swaps({2, 1, -1, -2});
//     // temp = count_swaps({-2, 2, 2, -2, -2, 2});

//     cout << temp << endl;
    
// }