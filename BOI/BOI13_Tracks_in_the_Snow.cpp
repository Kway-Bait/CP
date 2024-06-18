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
#define PB push_back
#define MP make_pair
#define max(a, b) ((a > b)? a : b)
#define min(a, b) ((a < b)? a : b)

const int N = 4e3 + 5;
const int M = 1e9 + 7; 
const int INF = 0x3f3f3f3f;

const int xMove[4] = {0, 1, 0, -1};
const int yMove[4] = {1, 0, -1, 0};

int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    // ifstream cin();
    // ofstream cout();
    
    char meadow[N][N];
    int h, w;
    cin >> h >> w;
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            cin >> meadow[i][j];
        }
    }

    deque<pair<int, int>> q;
    int depth[N][N]{0}, ans = 0;

    q.push_front(MP(0, 0));
    depth[0][0] = 1;

    while(!q.empty()){
        auto [x, y] = q.front();
        q.pop_front();

        ans = max(ans, depth[x][y]);

        for(int i = 0; i < 4; i++){
            int new_x = x + xMove[i];
            int new_y = y + yMove[i];
            if(new_x < 0 || new_x >= h || new_y < 0 || new_y >= w) continue;
            if(meadow[new_x][new_y] == '.') continue;
            if(depth[new_x][new_y] != 0) continue;

            if(meadow[x][y] == meadow[new_x][new_y]){
                depth[new_x][new_y] = depth[x][y];
                q.push_front(MP(new_x, new_y));
            }else {
                depth[new_x][new_y] = depth[x][y] + 1;
                q.push_back(MP(new_x, new_y));
            }
        }
    }

    cout << ans << endl;
    
}