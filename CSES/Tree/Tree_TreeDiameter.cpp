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
int dist[200010];
int n;

void bfs(int root) {
	for (int i = 1 ; i <= n ; i++)
		dist[i] = INF;
	dist[root] = 0;
	queue< pair<int,int> > q;
	q.push({root,0});
	while (!q.empty()) {
		pair<int,int> tmp = q.front();
		q.pop();
		int cur = tmp.first;
		int step = tmp.second;
		for (int i = 0 ; i < adj[cur].size() ; i++) {
			int nxt = adj[cur][i];
			if (dist[nxt] > step + 1) {
				dist[nxt] = step + 1;
				q.push({nxt,dist[nxt]});
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1 ; i < n ; i++) {
		int a,b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	bfs(1);
	int furthestNode = 1;
	int maxDist = 0;
	for (int i = 1 ; i <= n ; i++) if (dist[i] > maxDist) {
		maxDist = dist[i];
		furthestNode = i;
	}
	bfs(furthestNode);
	maxDist = 0;
	for (int i = 1 ; i <= n ; i++)
		maxDist = max(maxDist,dist[i]);
	cout << maxDist << endl;
}	