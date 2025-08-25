#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const ll INF = 1e18;
const int N = 2e5 + 5;

ll pref[N][3];

int n;

int nxt(int pos) {
    return (pos % n) + 1;
}

vector<ll> p, q;

ll solve() {
    ll ans = INF;
    
    for (int i = n; i <= n; i++) {
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
            for (int b = 0; b < 3; b++) {
                dp[j + 1][b] = min(dp[j + 1][b], dp[j][b] + p[nums[j]]);
            }
            
            dp[j + 1][0] = min(dp[j + 1][0], dp[j][1] + q[nums[j]] + p[nums[j]]);
            dp[j + 1][0] = min(dp[j + 1][0], dp[j][2] + q[nums[j]] + p[nums[j]]);
            
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

int main() {
    ios_base::sync_with_stdio(false);
    cout.tie(0);
    cin.tie(0);
    
    cin >> n;
    
    p.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    
    q.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> q[i];
    }
    
    if (n % 2 != 0) {
        
        cout << solve();
        
        return 0;
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

    cout << min(solve(), min(sum_chet, sum_nechet));

    return 0;
}
