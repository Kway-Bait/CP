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

const int N = 5e5 + 5;
const int M = 1e9 + 7; 
const int inf = 0x3f3f3f3f;
const ll int INF = 1e18;

int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    // ifstream cin();
    // ofstream cout();
    
    int n;
    cin >> n;

    vector<pair<ll, ll>> v;
    for(int i = 0; i < n; i++){
        ll int a, b;
        cin >> a >> b;
        v.PB(MP(a, b));
    }

    sort(v.begin(), v.end());
    for(int i = 0; i < n; i++) v[i].s -= v[i].f;
    for(int i = 1; i < n; i++) v[i].s += v[i-1].f;

    ll int mx = v[0].s + v[0].f, cur = v[0].s + v[0].f;
    for(int i = 1; i < n; i++){
        cur = max(cur + v[i].s, v[i].s + v[i].f - v[i-1].f);
        mx = max(mx, cur);
    }

    cout << mx << endl;
}