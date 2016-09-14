#include <queue>
#include <vector>
#include <functional>
#include <stdio.h>

#define mp make_pair

using namespace std;

typedef pair<int, int> ii;

vector<int>* djikstra(vector<vector<ii> >& vec, int start, int dest) {
	int inf = 1e9;
	priority_queue<ii, vector<ii >, greater<ii> > pq;
	int N = vec.size();
	pq.push(mp(0,start));
	vector<int>* dist = new vector<int>(N, inf);
	(*dist)[start] = 0;

	while (!pq.empty()) {
		ii front = pq.top(); pq.pop();
		int d = front.first; int u = front.second;
		if (d > (*dist)[u])continue;
		for (int j = 0; j < (int)vec[u].size(); j++) {
			ii v = vec[u][j];
			if ((*dist)[u] + v.second < (*dist)[v.first]) {
				(*dist)[v.first] = (*dist)[u] + v.second;
				pq.push(mp((*dist)[v.first], v.first));
			}
		}
	}
	return dist;

}



int main() {
	int V, E;
	scanf("%d %d", &V, &E);
	vector<vector<ii> > AL(V, vector<ii>());
	for (int i = 0; i < E; i++) {
		int to, from, weight;
		scanf("%d %d %d", &to, &from, &weight);
		AL[to].push_back(mp(from, weight));
	}
	int start, dest;
	scanf("%d %d", &start, &dest);
	printf("%d\n", (*djikstra(AL, start, dest))[dest]);

}