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
const int LOG = 19;

//HLD
vector< int > adj[MAXN];
int parent[MAXN];
int depth[MAXN];
int heavy[MAXN];
int head[MAXN];
int pos[MAXN];
int spa[20][MAXN];
int curPos;
int n,q;

int dfs(int u,int par)
{
	parent[u] = par;
	int ret = 1;
	int mx = -1;
	for (int i = 0 ; i < adj[u].size() ; i++) if (adj[u][i] != parent[u])
	{
		depth[adj[u][i]] = depth[u] + 1;
		int sz = dfs(adj[u][i],u);
		ret += sz;
		if (sz > mx)
		{
			mx = sz;
			heavy[u] = adj[u][i];
		}
	}
	return ret;
}

void decompose(int node,int h)
{
	head[node] = h;
	pos[node] = curPos++;
	if (heavy[node] != -1)
		decompose(heavy[node],h);
	for (int i = 0 ; i < adj[node].size() ; i++)
		{	
			if (adj[node][i] != parent[node]
				&& adj[node][i] != heavy[node])
			{
				decompose(adj[node][i],adj[node][i]);
			}
		}
}

void precom() 
{
	for (int i = 1 ; i <= n ; i++)
		spa[0][i] = parent[i];
	for (int i = 1 ; i <= LOG ; i++)
		for (int j = 1 ; j <= n ; j++)
			spa[i][j] = spa[i - 1][spa[i - 1][j]];
}

void makeHLD() 
{
	memset(heavy,-1,sizeof(heavy));
	dfs(1,-1);
	curPos = 1;
	decompose(1,1);
	memset(spa,-1,sizeof(spa));
	precom();
}
//End of HLD

//Query
int ans[MAXN];

int get_LCA(int u,int v)
{
	if (depth[u] < depth[v])
		swap(u,v);
	for (int i = LOG ; i >= 0 ; i--) if (depth[u] - (1 << i) >= depth[v])
	{
		u = spa[i][u];
	}
	if (u == v) return u;
	for (int i = LOG ; i >= 0 ; i--) if (spa[i][u] != -1 && spa[i][u] != spa[i][v])
	{
		u = spa[i][u];
		v = spa[i][v];
	}
	return parent[u];
}

void updateValue(int l,int r,int val) 
{
	ans[r + 1] -= val;
	ans[l] += val;
}

void walk(int u,int v) 
{
	while (head[u] != head[v])
	{
		updateValue(pos[head[u]],pos[u],1);
		u = parent[head[u]];
	}
	updateValue(pos[v],pos[u],1);
	return;
}

int updatePath(int u,int v)
{
	int LCA = get_LCA(u,v);
	walk(u,LCA);
	walk(v,LCA);
	updateValue(pos[LCA],pos[LCA],-1);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> q;
	for (int i = 1 ; i < n ; i++)
	{
		int a,b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	makeHLD();
	while (q--) 
	{
		int u,v;
		cin >> u >> v;
		updatePath(u,v);
	}
	for (int i = 1 ; i <= n ; i++)
		ans[i] += ans[i - 1];
	for (int i = 1 ; i <= n ; i++) 
	{
		if (i == n)
			cout << ans[pos[i]] << endl;
		else
			cout << ans[pos[i]] << " ";
	}
}