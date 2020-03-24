#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

int n, a, b;
ll w, pw[200001], dp[200001][2][2];
vector<pair<int, ll>> graph[200001];

void dfs(int node, int par) {
    if (graph[node].size() == 1 && par != -1) return;

    ll tot = 0, best_mid = INT_MIN, best_unuse_mid = INT_MIN, best_unuse_mid2 = INT_MIN,
       best_unuse_nomid = INT_MIN, best_unuse_nomid2 = INT_MIN;

    int best_unuse_mid_child, best_unuse_mid_child2, best_unuse_nomid_child,
        best_unuse_nomid_child2;

    for (int i = 0; i < graph[node].size(); i++) {
        if (graph[node][i].first != par) {
            int child = graph[node][i].first;
            ll edge = graph[node][i].second;

            pw[child] = edge;

            dfs(child, node);
            
            ll normsc = max(dp[child][0][0], dp[child][1][0]);
            tot += normsc;
            ll midsc = max(dp[child][0][1], dp[child][1][1]) - normsc;

            if (midsc > best_mid) best_mid = midsc;

            ll unuse_midsc = dp[child][0][1] + edge - normsc;

            if (unuse_midsc > best_unuse_mid) {
                best_unuse_mid2 = best_unuse_mid;
                best_unuse_mid_child2 = best_unuse_mid_child;
                best_unuse_mid = unuse_midsc;
                best_unuse_mid_child = child;
            } else if (unuse_midsc > best_unuse_mid2) {
                best_unuse_mid2 = unuse_midsc;
                best_unuse_mid_child2 = child;
            }

            ll unuse_nomidsc = dp[child][0][0] + edge - normsc;
            
            if (unuse_nomidsc > best_unuse_nomid) {
                best_unuse_nomid2 = best_unuse_nomid;
                best_unuse_nomid_child2 = best_unuse_nomid_child;
                best_unuse_nomid = unuse_nomidsc;
                best_unuse_nomid_child = child;
            } else if (unuse_nomidsc > best_unuse_nomid2) {
                best_unuse_nomid2 = unuse_nomidsc;
                best_unuse_nomid_child2 = child;
            }
        }
    }

    dp[node][0][0] = tot;
    dp[node][0][1] = tot + max(0LL, best_mid);
    dp[node][0][1] = max(dp[node][0][1], tot + best_unuse_nomid + best_unuse_nomid2);

    if (best_unuse_mid_child != best_unuse_nomid_child) {
        dp[node][0][1] = max(dp[node][0][1], tot + best_unuse_nomid + best_unuse_mid);
    } else {
        dp[node][0][1] = max(dp[node][0][1], tot + best_unuse_nomid2 + best_unuse_mid);
        dp[node][0][1] = max(dp[node][0][1], tot + best_unuse_nomid + best_unuse_mid2);
    }

    dp[node][1][0] = tot + pw[node] + best_unuse_nomid;
    dp[node][1][1] = tot + pw[node] + best_unuse_mid;
}

int main() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b >> w;
        graph[a].push_back({b, w});
        graph[b].push_back({a, w});
    }
    dfs(1, -1);

    cout << max(dp[1][0][1], dp[1][0][0]) << '\n';
    return 0;
}