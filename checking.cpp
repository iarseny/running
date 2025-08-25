#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

bool can = true;

const int N = 15;
const ll INF = 1e18;
int color[N];

vector<int> g[N];

void dfs(int v, int col) {
    color[v] = col;

    for (auto u : g[v]) {
        if (color[u] == col) {
            can = false;
            return;
        }

        if (color[u] == 0) {
            dfs(u, 3 - col);
        }
    }
}

void clear() {
    can = true;
    for (int i = 0; i < N; i++) {
        g[i].clear();
        color[i] = 0;
    }
}

ll correct_solve(ll n, vector<ll> p, vector<ll> q) {
    clear();
    vector<pair<ll, pll>> edges;
    for (int i = 1; i <= n; i++) {
        edges.push_back({i, {0, p[i - 1]}});
    }

    for (int i = 1; i <= n; i++) {
        if (i == n) {
            edges.push_back({i, {1, q[i - 1]}});
        } else {
            edges.push_back({i, {i + 1, q[i - 1]}});
        }
    }

    ll ans = INF;

    for (int i = 0; i < (1 << (int)edges.size()); i++) {
        clear();
        ll sum = 0;
        for (int j = 0; j < (int)edges.size(); j++) {
            if (i & (1 << j)) {
                sum += edges[j].second.second;
            } else {
                g[edges[j].first].push_back(edges[j].second.first);
                g[edges[j].second.first].push_back(edges[j].first);
            }
        }

        for (int j = 0; j <= n; j++) {
            if (color[j] == 0) {
                dfs(j, 1);
            }
        }

        if (can) {
            ans = min(ans, sum);
        }
    }

    return ans;
}

ll solve(int n, vector<ll> pp, vector<ll> qq) {
    vector<ll> p(n + 1);
    for (int i = 1; i <= n; i++) {
        p[i] = pp[i - 1];
    }

    vector<ll> q(n + 1);
    for (int i = 1; i <= n; i++) {
        q[i] = qq[i - 1];
    }

    if (n % 2 != 0) {

        ll ans = INF;

        for (int i = 1; i <= n; i++) {
            vector<int> nums;
            for (int j = i; j >= 1; j--) {
                nums.push_back(j);
            }

            for (int j = n; j >= i + 1; j--) {
                nums.push_back(j);
            }

            vector<vector<ll>> dp(n + 1, vector<ll>(3, INF));
            dp[1][0] = p[nums.front()];
            dp[1][1] = 0;
            for (int j = 1; j < n; j++) {
                dp[j + 1][0] = min(dp[j + 1][0], dp[j][0] + p[nums[j]]);
                dp[j + 1][0] = min(dp[j + 1][0], dp[j][1] + q[nums[j]] + p[nums[j]]);
                dp[j + 1][0] = min(dp[j + 1][0], dp[j][2] + q[nums[j]] + p[nums[j]]);

                dp[j + 1][1] = min(dp[j + 1][1], dp[j][1] + p[nums[j]]);
                dp[j + 1][2] = min(dp[j + 1][2], dp[j][2] + p[nums[j]]);

                if ((j + 1) % 2 == 0) {
                    dp[j + 1][2] = min(dp[j + 1][2], dp[j][0] + q[nums[j]]);
                    dp[j + 1][2] = min(dp[j + 1][2], dp[j][1] + q[nums[j]]);
                    dp[j + 1][2] = min(dp[j + 1][2], dp[j][2] + q[nums[j]]);
                    dp[j + 1][2] = min(dp[j + 1][2], dp[j][2]);
                    dp[j + 1][2] = min(dp[j + 1][2], dp[j][0]);
                } else {
                    dp[j + 1][1] = min(dp[j + 1][1], dp[j][0] + q[nums[j]]);
                    dp[j + 1][1] = min(dp[j + 1][1], dp[j][1] + q[nums[j]]);
                    dp[j + 1][1] = min(dp[j + 1][1], dp[j][2] + q[nums[j]]);
                    dp[j + 1][1] = min(dp[j + 1][1], dp[j][1]);
                    dp[j + 1][1] = min(dp[j + 1][1], dp[j][0]);
                }
            }

            ll res = INF;
            res = min(res, dp[n][0]);
            res = min(res, dp[n][1]);
            res = min(res, dp[n][2]);

            ans = min(ans, res + q[i]);
        }

        return ans;
    }

    ll sum_chet = 0;
    ll sum_nechet = 0;

    for (int i = 1; i <= n; i++) {
        if (i % 2 != 0) {
            sum_nechet += p[i];
        } else {
            sum_chet += p[i];
        }
    }

    ll ans = INF;

    for (int i = 1; i <= n; i++) {
        vector<int> nums;
        for (int j = i; j >= 1; j--) {
            nums.push_back(j);
        }

        for (int j = n; j >= i + 1; j--) {
            nums.push_back(j);
        }

        vector<vector<ll>> dp(n + 1, vector<ll>(3, INF));
        dp[1][0] = p[nums.front()];
        dp[1][1] = 0;
        for (int j = 1; j < n; j++) {
            dp[j + 1][0] = min(dp[j + 1][0], dp[j][0] + p[nums[j]]);
            dp[j + 1][0] = min(dp[j + 1][0], dp[j][1] + q[nums[j]] + p[nums[j]]);
            dp[j + 1][0] = min(dp[j + 1][0], dp[j][2] + q[nums[j]] + p[nums[j]]);

            dp[j + 1][1] = min(dp[j + 1][1], dp[j][1] + p[nums[j]]);
            dp[j + 1][2] = min(dp[j + 1][2], dp[j][2] + p[nums[j]]);

            if ((j + 1) % 2 == 0) {
                dp[j + 1][2] = min(dp[j + 1][2], dp[j][0] + q[nums[j]]);
                dp[j + 1][2] = min(dp[j + 1][2], dp[j][1] + q[nums[j]]);
                dp[j + 1][2] = min(dp[j + 1][2], dp[j][2] + q[nums[j]]);
                dp[j + 1][2] = min(dp[j + 1][2], dp[j][2]);
                dp[j + 1][2] = min(dp[j + 1][2], dp[j][0]);
            } else {
                dp[j + 1][1] = min(dp[j + 1][1], dp[j][0] + q[nums[j]]);
                dp[j + 1][1] = min(dp[j + 1][1], dp[j][1] + q[nums[j]]);
                dp[j + 1][1] = min(dp[j + 1][1], dp[j][2] + q[nums[j]]);
                dp[j + 1][1] = min(dp[j + 1][1], dp[j][1]);
                dp[j + 1][1] = min(dp[j + 1][1], dp[j][0]);
            }
        }

        ll res = INF;
        res = min(res, dp[n][0]);
        res = min(res, dp[n][1]);
        res = min(res, dp[n][2]);

        ans = min(ans, res + q[i]);
    }

    return min(ans, min(sum_chet, sum_nechet));
}

int main() {
    ios_base::sync_with_stdio(false);
    cout.tie(0);
    cin.tie(0);

    srand(time(NULL));

    while (true) {
        int n = rand() % 15 + 3;

        vector<ll> p(n);
        for (int i = 0; i < n; i++) {
            p[i] = rand() % 55 + 1;
        }

        vector<ll> q(n);
        for (int i = 0; i < n; i++) {
            q[i] = rand() % 55 + 1;
        }

        // if (n % 2 != 0) continue;

        if (correct_solve(n, p, q) != solve(n, p, q)) {
            cout << n << endl;
            for (auto i : p) {
                cout << i << ' ';
            }
            cout << endl;
            for (auto i : q) {
                cout << i << ' ';
            }

            cout << endl << endl;

            cout << correct_solve(n, p, q) << ' ' << solve(n, p, q) << endl;

            break;
        }

    }

    return 0;
}