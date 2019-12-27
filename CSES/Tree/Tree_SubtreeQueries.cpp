#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e9;
const ll INFF = 1e18;
const ll MAXN = 2e5 + 10;
const ll MOD = 1e9 + 7;
const double PI = acos(-1.0);
const double INFD = 1E9;
const double EPS = 1e-9;

vector<ll> adj[MAXN];
ll in[MAXN];
ll out[MAXN];
ll BIT[MAXN];
ll tab[MAXN];
ll n,q,cur = 1;

void upd(ll x,ll val) {
	for ( ; x <= n ; x += (x & -x))
		BIT[x] += val;
}

ll query(ll x) {
	ll ret = 0;
	for ( ; x ; x -= (x & -x))
		ret += BIT[x];
	return ret;
}

void dfs(ll node,ll prv) {
	in[node] = cur;
	upd(cur,tab[node]);
	++cur;
	for (ll next : adj[node]) {
		if (next != prv) {
			dfs(next,node);
		}
	}
	out[node] = cur - 1;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> q;
	for (ll i = 1 ; i <= n ; i++)
		cin >> tab[i];
	for (ll i = 1 ; i < n ; i++) {
		ll a,b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs(1,-1);
	while (q--) {
		ll ask;
		cin >> ask;
		if (ask == 1) {
			ll node,x;
			cin >> node >> x;
			upd(in[node],-tab[node]);
			tab[node] = x;
			upd(in[node],tab[node]);
		}
		else {
			ll ta;
			cin >> ta;
			ll ans = query(out[ta]) - query(in[ta] - 1);
			cout << ans << endl;
		}
	}
}