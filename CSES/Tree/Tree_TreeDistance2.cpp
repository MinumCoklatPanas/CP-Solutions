#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e9;
const ll INFF = 1e18;
const ll MAXN = 510;
const ll MOD = 1e9 + 7;
const double PI = acos(-1.0);
const double INFD = 1E9;
const double EPS = 1e-9;

const ll N = 200005;
ll centroid = -1;
ll n;
vector< ll > adj[N];
ll subtreeSum[N];
ll subtreeSize[N];
ll ans[N];
ll tot = 0;

void dfs1(ll curNode,ll depth,ll prv) {
    subtreeSize[curNode] = 1;
    subtreeSum[curNode] = 0;
    // cout << curNode << endl;
    for (ll next : adj[curNode]) {
      if (next == prv) continue;
      dfs1(next,depth + 1,curNode);
      subtreeSize[curNode] += subtreeSize[next];
      subtreeSum[curNode] += subtreeSum[next] + subtreeSize[next];
    }
}

void dfs2(ll curNode,ll prv) {
  ans[curNode] = subtreeSum[curNode]; 
  if (prv != -1) {
    ans[curNode] = n + ans[prv] - 2 * subtreeSize[curNode];
  }
  for (ll next : adj[curNode]) {
    if (next == prv) continue;
    dfs2(next,curNode);
  }
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (ll i = 1 ; i < n ; i++) {
    ll a,b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  dfs1(1,0,-1);
  dfs2(1,-1);
  for (ll i = 1 ; i <= n ; i++) {
    if (i == n)
      cout << ans[i] << endl;
    else
      cout << ans[i] << " ";
  }
}