
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <random>
#include <numeric>
#include <time.h>
#include <unordered_map>

using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pil = pair<int, ll>;
using pli = pair<ll, int>;

const int N = 1e5 + 1;
const int K = 1e4;
const ll MOD = 1e9 + 7;

vector<int> g[N + 5];
int a[N + 5];
ll ans = 0;

// {sum_of_length, cnt_length}
unordered_map<int, pll> dfs(int v, int pr = -1) {
    unordered_map<int, pll> know;
    for (auto u : g[v]) {
        if (u == pr) continue;

        unordered_map<int, pll> tmp = dfs(u, v);

        for (auto j : tmp) {
            for (auto k : know) {
                ans = (ans + (__gcd((ll)k.first, (ll)j.first) * (((k.second.first) * j.second.second) + (((j.second.first + j.second.second) % MOD) * k.second.second) % MOD))) % MOD % MOD;
            }
        }

        for (auto j : tmp) {
            know[__gcd(j.first, a[v])].first += (j.second.first + j.second.second);
            know[__gcd(j.first, a[v])].second += j.second.second;
        }
    }

    // if (v == 2) {
    //     cout << ans << endl;
    //     for (auto j : know) {
    //         cout << j.first << ' ' << j.second.first << ' ' << j.second.second << endl;
    //     }
    // }

    for (auto i : know) {
        ans = (ans + (i.first * i.second.first) % MOD) % MOD;
    }

    know[a[v]].first++;
    know[a[v]].second++;

    // if (v == 2) {
    //     for (auto i : know) {
    //         cout << i.first << ' ' << i.second.first << ' ' << i.second.second << endl;
    //     }
    // }


    /*
    if (v == 2) {
        for (auto i : know) {
            cout << i.first << ' ' << i.second.first << ' ' << i.second.second << endl;
        }
    }

    */

    // cout << v << ' ' << ans << endl;

    // rs = max(rs, (int)know.size());

    return know;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout.tie(0);
    cin.tie(0);

    /*
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
    */

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1);

    cout << ans;
}