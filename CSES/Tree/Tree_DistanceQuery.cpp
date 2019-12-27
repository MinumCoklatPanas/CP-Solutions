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

vector<int> adj[MAXN];
int depth[MAXN];
int spa[20][MAXN];
int n,q;

void dfs(int node,int deep,int prv) {
	spa[0][node] = prv;
	depth[node] = deep;
	for (int next : adj[node]) {
		if (next != prv) {
			dfs(next,deep + 1,node);
		}
	}
}

void precom() {
	for (int i = 1 ; i <= LOG ; i++) 
		for (int j = 1 ; j <= n ; j++)
			if (spa[i - 1][j] != -1)
				spa[i][j] = spa[i - 1][spa[i - 1][j]];
	// cout << spa[0][3] << endl;
}

int query(int a,int b) {
	if (depth[a] < depth[b])
		swap(a,b);
	// cout << a << " " << b << endl;
	int ret = 0;
	for (int i = LOG ; i >= 0 ; i--) if (depth[a] - (1 << i) >= depth[b]) {
		a = spa[i][a];
		// cout << i << " " << a << endl;
		ret += (1 << i);
	}
	// cout << a << " " << b << endl;
	if (a == b) return ret;
	// cout << "yo\n";
	for (int i = LOG ; i >= 0 ; i--) if (spa[i][a] != -1 && spa[i][a] != spa[i][b]) {
		a = spa[i][a];
		b = spa[i][b];
		ret += (1 << (i + 1));
	}
	return ret + 2;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	memset(spa,-1,sizeof(spa));
	// int n,q;
	cin >> n >> q;
	for (int i = 1 ; i < n ; i++) {
		int a,b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs(1,0,-1);
	precom();
	while (q--) {
		int a,b;
		cin >> a >> b;
		cout << query(a,b) << endl;
	}
}