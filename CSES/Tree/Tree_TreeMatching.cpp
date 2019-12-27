#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int INF = 1e9;
const ll INFF = 1e18;
const int MAXN = 510;
const int MOD = 1e9 + 7;
const double PI = acos(-1.0);
const double INFD = 1E9;
const double EPS = 1e-9;

vector< int > adj[200010];
int dp[200010][2]; //[node][ambil]

int rec(int node,int prv) {
	int ret1 = 0;
	int ret2 = 0;
	for (int i = 0 ; i < adj[node].size() ; i++) {
		int nxt = adj[node][i];
		if (nxt == prv) continue;
		ret2 += rec(nxt,node);
	}
	for (int i = 0 ; i < adj[node].size() ; i++) {
		int nxt = adj[node][i];
		if (nxt == prv) continue;
		int rem = ret2 - max(dp[nxt][0],dp[nxt][1]);
		ret1 = max(ret1,rem + 1 + dp[nxt][0]);
	}
	dp[node][0] = ret2;
	dp[node][1] = ret1;
	return max(ret1,ret2);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for (int i = 1 ; i < n ; i++) {
		int a,b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	int ans = rec(1,-1);
	cout << ans << endl;
}