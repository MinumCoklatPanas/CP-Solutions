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

vector< int > child[MAXN];
int spa[20][MAXN];
int depth[MAXN];
int n,q;

void dfs(int node,int deep) {
	depth[node] = deep;
	for (int next : child[node]) {
		dfs(next,deep + 1);
	}
}

void precom() {
	for (int i = 1 ; i <= LOG ; i++)
		for (int j = 1 ; j <= n ; j++) 
			if (spa[i - 1][j] != -1) {
				// cout << "yo\n";
				spa[i][j] = spa[i - 1][spa[i - 1][j]];
			}
}

int query(int a,int b) {
	if (depth[a] < depth[b])
		swap(a,b);
	for (int i = LOG ; i >= 0 ; i--) if (depth[a] - (1 << i) >= depth[b])
		a = spa[i][a];
	if (a == b) return a;
	for (int i = LOG ; i >= 0 ; i--) if (spa[i][a] != -1 && spa[i][a] != spa[i][b]) {
		a = spa[i][a];
		b = spa[i][b];
	}
	return spa[0][a];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> q;
	memset(spa,-1,sizeof(spa));
	for (int i = 2 ; i <= n ; i++) {
		cin >> spa[0][i];
		child[spa[0][i]].push_back(i);
	}
	dfs(1,0);
	precom();
	while (q--) {
		int a,b;
		cin >> a >> b;
		cout << query(a,b) << endl;
	}
}