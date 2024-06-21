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

const int N = 8e2 + 5;
const int M = 1e9 + 7; 
const int inf = 0x3f3f3f3f;
const ll int INF = 1e18;

const int xMove[4] = {0, 1, 0, -1};
const int yMove[4] = {1, 0, -1, 0};

int bin(int l, int r, function<bool(int)> f){
    while(l < r){
        int mid = l + (r - l + 1)/2;
        if(f(mid)){
            l = mid;
        }else {
            r = mid - 1;
        }
    }
    return r;
}

int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    // ifstream cin();
    // ofstream cout();
    
    pair<int, int> ini;
    char c[N][N];
    int n, step;
    cin >> n >> step;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> c[i][j];
            if(c[i][j] == 'M') ini = MP(i, j);
        }
    }

    queue<pair<int, int>> bee;
    bool vis_bee[N][N]{false};
    int stepBee[N][N]{0};
    memset(stepBee, inf, sizeof(stepBee));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(c[i][j] == 'H'){
                bee.push(MP(i, j));
                vis_bee[i][j] = true;
                stepBee[i][j] = 0;
            }
        }
    }

    while(!bee.empty()){
        auto [x, y] = bee.front();
        bee.pop();

        for(int i = 0; i < 4; i++){
            int new_x = x + xMove[i];
            int new_y = y + yMove[i];
            if(new_x < 0 || new_x >= n || new_y < 0 || new_y >= n) continue;
            if(c[new_x][new_y] == 'T' || c[new_x][new_y] == 'D') continue;
            if(vis_bee[new_x][new_y]) continue;

            vis_bee[new_x][new_y] = true;
            stepBee[new_x][new_y] = stepBee[x][y] + 1;
            bee.push(MP(new_x, new_y));
        }
    }
    
    bool vis_bear[N][N]{false};
    int stepBear[N][N]{0};
    int ans = bin(-1, N*N, [&](int time_offset){
        // Initialize
        memset(vis_bear, false, sizeof(vis_bear));
        memset(stepBear, 0, sizeof(stepBear));

        queue<pair<int, int>> bear;
        bear.push(ini);
        vis_bear[ini.f][ini.s] = true;
        if(time_offset >= stepBee[ini.f][ini.s]) return false;

        while(!bear.empty()){
            auto [x, y] = bear.front();
            bear.pop();

            if(c[x][y] == 'D') return true;

            int cur_time = (stepBear[x][y] + 1)/step + time_offset;

            for(int i = 0; i < 4; i++){
                int new_x = x + xMove[i];
                int new_y = y + yMove[i];
                if(new_x < 0 || new_x >= n || new_y < 0 || new_y >= n) continue;
                if(c[new_x][new_y] == 'T' || vis_bear[new_x][new_y]) continue;
                if(cur_time >= stepBee[new_x][new_y]) continue;

                vis_bear[new_x][new_y] = true;
                stepBear[new_x][new_y] = stepBear[x][y] + 1;

                bear.push(MP(new_x, new_y));
            }
        }

        return false;
    });

    cout << ans << endl;
}