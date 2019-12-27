#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int INF = 1e9;
const ll INFF = 1e18;
const int MOD = 1e9 + 7;
const double PI = acos(-1.0);
const double INFD = 1E9;
const double EPS = 1e-9;
const int MAXN = 2e5 + 10;

vector< int > adj[MAXN];
int dist[4][MAXN];
int n;

void bfs(int kode,int root)
{
	for (int i = 1 ; i <= n ; i++)
	{
		dist[kode][i] = INF;
	}
	queue< pair<int,int> > q;
	q.push({root,0});
	dist[kode][root] = 0;
	while (!q.empty())
	{
		pair<int,int> cur = q.front();
		q.pop();
		int node = cur.first;
		int step = cur.second;
		for (int next : adj[node])
		{
			if (dist[kode][next] > step + 1)
			{
				dist[kode][next] = step + 1;
				q.push({next,step + 1});
			}
		}
	}
}

int findFurthest(int kode,int root)
{
	bfs(kode,root);
	int ret = -1;
	int mx = 0;
	for (int i = 1 ; i <= n ; i++)
	{
		if (dist[kode][i] >= mx)
		{
			mx = dist[kode][i];
			ret = i;
		}
	}
	return ret;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1 ; i < n ; i++)
	{
		int a,b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	int furthest1 = findFurthest(0,1);
	int furthest2 = findFurthest(1,furthest1);
	bfs(2,furthest1);
	bfs(3,furthest2);
	for (int i = 1 ; i <= n ; i++)
	{
		int ans = max(dist[2][i],dist[3][i]);
		if (i == n)
			cout << ans << endl;
		else
			cout << ans << " ";
	}
}