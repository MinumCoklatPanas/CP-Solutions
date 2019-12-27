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

int spa[20][MAXN];
int n,q;

void precom() {
	for (int i = 1 ; i <= LOG ; i++)
		for (int j = 1 ; j <= n ; j++) 
			if (spa[i - 1][j] != -1) {
				// cout << "yo\n";
				spa[i][j] = spa[i - 1][spa[i - 1][j]];
			}
}

int walk(int node,int k) {
	for (int i = 0 ; i <= LOG ; i++) if (k & (1 << i)) {
		node = spa[i][node];
		if (node == -1) break;
	}
	return node;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> q;
	memset(spa,-1,sizeof(spa));
	for (int i = 2 ; i <= n ; i++)
		cin >> spa[0][i];
	precom();
	while (q--) {
		int node,k;
		cin >> node >> k;
		cout << walk(node,k) << endl;
	}
}