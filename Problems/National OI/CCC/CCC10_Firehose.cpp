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

const int N = 1e3 + 5;
const int M = 1e9 + 7; 
const int inf = 0x3f3f3f3f;
const ll int INF = 1e18;

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
    
    int n, k, h[N];
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> h[i];
    }
    
    sort(h, h+n);

    cin >> k;

    int ans = bin(0, 1e6, [&](int x){
        for(int i = 0; i < n; i++){
            // For each house as the starting house
            int cnt = 0, cur = -inf;
            for(int j = 0; j < n; j++){
                int house = h[(i+j)%n];
                if(i+j >= n) house += 1e6;
                if(cur + x >= house) continue;
                else {
                    cur = house + x;
                    cnt++;
                }
            }
            
            if(cnt <= k) return true;
        }

        return false;
    });
    
    cout << ans << endl;
}