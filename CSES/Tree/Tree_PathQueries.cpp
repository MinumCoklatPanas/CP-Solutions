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

vector< ll > adj[MAXN];
ll in[MAXN];
ll out[MAXN];
ll sum[MAXN];
ll BIT[MAXN];
ll val[MAXN];
ll cur = 1;
ll n,q;

void dfs(ll node,ll prv)
{
	in[node] = cur++;
	sum[node] = sum[prv] + val[node];
	for (ll next : adj[node]) if (next != prv)
	{	
		dfs(next,node);
	}
	out[node] = cur - 1;
}

void upd(ll x,ll val)
{
	for ( ; x <= n ; x += (x & -x))
		BIT[x] += val;
}

ll query(ll x) 
{
	ll ret = 0;
	for ( ; x ; x -= (x & -x))
		ret += BIT[x];
	return ret;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> q;
	for (ll i = 1 ; i <= n ; i++)
		cin >> val[i];
	for (ll i = 1 ; i < n ; i++)
	{
		ll a,b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	} 
	dfs(1,0);
	for (ll i = 1 ; i <= n ; i++)
	{
		upd(in[i],sum[i]);
		upd(in[i] + 1,-sum[i]);
	}
	while (q--)
	{
		ll ask;
		cin >> ask;
		if (ask == 1)
		{
			ll node,x;
			cin >> node >> x;
			ll delta = x - val[node];
			upd(in[node],delta);
			upd(out[node] + 1,-delta);
			val[node] = x;
		}
		else
		{
			ll node;
			cin >> node;
			cout << query(in[node]) << endl;
		}
	}
}