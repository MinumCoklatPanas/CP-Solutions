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

vector<int> child[200010];
int sz[200010];

int cnt(int node) {
	int ret = 0;
	for (int i = 0 ; i < child[node].size() ; i++) {
		ret += cnt(child[node][i]);
	}
	return sz[node] = ret + 1;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for (int i = 2 ; i <= n ; i++) {
		int ta;
		cin >> ta;
		child[ta].push_back(i);
	}
	cnt(1);
	for (int i = 1 ; i <= n ; i++) {
		if (i == n)
			cout << sz[i] - 1 << endl;
		else
			cout << sz[i] - 1 << " ";
	}
}