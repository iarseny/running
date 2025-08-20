
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <random>
#include <numeric>
#include <time.h>

using namespace std;

const int N = 1e5 + 1;
const int K = 1e4;

vector<int> g[N + 5];
int a[N + 5];
int rs = 1;

set<int> dfs(int v, int pr = -1) {
    set<int> know{a[v]};
    for (auto u : g[v]) {
        if (u == pr) continue;

        set<int> tmp = dfs(u, v);
        for (auto j : tmp) {
            know.insert(__gcd(j, a[v]));
        }
    }

    rs = max(rs, (int)know.size());
    return know;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout.tie(0);
    cin.tie(0);

    mt19937 mt(time(NULL));

    double ans = 0;

    for (int i = 0; i < K; i++) {
        vector<int> p(N - 1);
        for (int j = 0; j < N - 1; j++) {
            p[j] = ((mt() % (j + 1)) + 1);
        }

        for (int j = 0; j <= N; j++) {
            a[j] = 0;
            g[j].clear();
        }

        rs = 1;

        for (int j = 1; j <= N; j++) {
            a[j] = (mt() % (N - 1)) + 1;
        }

        for (int j = 0; j < N - 1; j++) {
            g[j + 2].push_back(p[j]);
            g[p[j]].push_back(j + 2);
        }

        dfs(1);

        // ans = max(ans, rs);
    }

    cout << endl;

    cout << ans;
}