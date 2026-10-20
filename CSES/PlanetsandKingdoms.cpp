#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define umap unordered_map
#define uset unordered_set
void setIO(const string& name = "") {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if (!name.empty()) {
        freopen((name + ".in").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    }
}

vector<vector<ll>> UnweightedGraph;
vector<vector<pair<ll,ll>>> WeightedGraph;
vector<ll> dist;
vector<bool> visited;
vector<ll> LowLink;
ll n,m;


auto dijkstra(ll start) {
    dist.assign(n, LLONG_MAX);
    priority_queue<pair<ll, ll>,vector<pair<ll,ll>>,greater<>> pq;
    dist[start] = 0;
    pq.emplace(0, start);
    while (!pq.empty()) {
        auto [u,d] = pq.top();
        pq.pop();

        if (dist[u] < d) {
            continue;
        }

        for (auto [v,w] : WeightedGraph[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }
    }

}

auto tarjan() {
    vector<ll> ids(n, -1);
    vector<bool> onStack(n, false);
    vector<ll>groups(n,-1);
    stack<ll> S;
    ll id = 0, sccCount = 0;

    LowLink.assign(n, -1);

    function<void(ll)> dfs = [&](ll u) {
        S.push(u);
        onStack[u] = true;
        ids[u] = LowLink[u] = id++;

        for (const ll v : UnweightedGraph[u]) {
            if (ids[v] == -1) {
                dfs(v);
                LowLink[u] = min(LowLink[u], LowLink[v]);
            } else if (onStack[v]) {
                LowLink[u] = min(LowLink[u], ids[v]);
            }
        }

        if (LowLink[u] == ids[u]) {
            sccCount++;
            while (true) {
                const ll w = S.top();
                groups[w] = sccCount;
                S.pop();
                onStack[w] = false;
                if (w == u) break;
            }
        }
    };

    for (ll i = 0; i < n; i++) {
        if (ids[i] == -1) dfs(i);
    }
    cout<<sccCount<<endl;
    for (auto i : groups) {
        cout<<i<<" ";
    }
    return sccCount;
}

int main() {
    setIO();
    cin >> n >> m;
    UnweightedGraph.resize(n);
    for (ll i = 0; i < m; i++) {
        ll v, u;
        cin >> v >> u;
        v--;
        u--;
        UnweightedGraph[v].emplace_back(u);
    }
    tarjan();

    return 0;
}
