#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int INF = 1e9;
const ll INFF = 1e18;
const int MAXN = 2e5 + 10;
const int MOD = 1e9 + 7;
const double PI = acos(-1.0);
const double INFD = 1E9;
const double EPS = 1e-9;
const int BLK = 450;

struct MO
{
	int l;
	int r;
	int ix;
};

vector< int > adj[MAXN];
int in[MAXN];
int out[MAXN];
int val[MAXN];
int pos[MAXN];
unordered_map<int,int> frek;
int cur = 1;
vector< MO > query;
int ans[MAXN];
int cnt = 0;

bool cmp(MO a,MO b)
{
	if (a.l / BLK != b.l / BLK) return (a.l / BLK < b.l / BLK);
	return a.r < b.r;
}

void dfs(int node,int prv)
{
	pos[cur] = node;
	in[node] = cur++;
	for (int next : adj[node]) if (next != prv)
	{
		dfs(next,node);
	}
	out[node] = cur - 1;
	query.push_back({in[node],out[node],node});
}

void add(int x)
{
	frek[x]++;
	if (frek[x] == 1)
		++cnt;
}

void rem(int x)
{
	frek[x]--;
	if (frek[x] == 0)
		--cnt;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for (int i = 1 ; i <= n ; i++)
		cin >> val[i];
	for (int i = 1 ; i < n ; i++)
	{
		int a,b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs(1,-1);
	sort(query.begin(),query.end(),cmp);
	int curL = 1;
	int curR = 1;
	// ++curR;
	for (int i = 0 ; i < n ; i++)
	{
		int L = query[i].l;
		int R = query[i].r;
		int ix = query[i].ix;
		while (curL > L)
		{
			add(val[pos[curL - 1]]);
			--curL;
		}
		while (curR <= R)
		{
			add(val[pos[curR]]);
			++curR;
		}
		while (curL < L)
		{
			rem(val[pos[curL]]);
			++curL;
		}
		while (curR > R + 1)
		{
			rem(val[pos[curR - 1]]);
			--curR;
		}
		ans[ix] = cnt;
	}
	for (int i = 1 ; i <= n ; i++)
	{
		if (i == n)
			cout << ans[i] << endl;
		else
			cout << ans[i] << " ";
	}
}