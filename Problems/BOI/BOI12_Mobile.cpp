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

const int N = 1e5 + 5;
const int M = 1e9 + 7; 
const int inf = 0x3f3f3f3f;
const ll int INF = 1e18;

double bin(double l, double r, function<bool(double)> f){
    while(r - l > 1e-3){
        double mid = (r + l)/2;
        if(f(mid)){
            r = mid;
        }else {
            l = mid;
        }
    }
    return l;
}

int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    // ifstream cin();
    // ofstream cout();
    
    vector<pair<double, double>> v;
    int n;
    double L;
    cin >> n >> L;
    for(int i = 0; i < n; i++){
        double x, y;
        cin >> x >> y;
        v.PB(MP(x, y));
    }

    double ans = bin(0, 1.5e9, [&](double d){
        double cur = 0;
        for(int i = 0; i < n; i++){
            double dis = sqrt(d*d - v[i].s * v[i].s);
            double left = v[i].f - dis, right = v[i].f + dis;
            if(left <= cur) cur = max(cur, right);
        }

        return (cur >= L);
    });
    
    cout << fixed << setprecision(4);
    cout << ans << endl;
}