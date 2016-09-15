#include <queue>
#include <vector>
#include <functional>
#include <stdio.h>
#include<cassert>

#define mp make_pair

using namespace std;

typedef pair<int, int> ii;

int inf = 1e9;

vector<int>& djikstra(vector<vector<ii> >& vec, int start, int dest) {
	//int inf = 1e9;
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
	return *dist;

}

void testOneNodeGraph() {
	//Test case with 1 node, expected value: 0, since start node is the same as destination
	vector<vector<ii> > AL(1, vector<ii>());
	vector<int> res = djikstra(AL, 0, 0);
	assert(res.size() == 1);
	assert(res[0] == 0);
}

void testNormalGraph() {
	/*Test case with "normal" directed graph. 5 nodes and 6 edges. Path between node 0 and 3 has an expected minimum path of 8.
	0
	(3)/ \(5)
	/   \
	▼	   ▼
	1-(1)-► 2
	/ \
	(4)/   \(6)
	▼     ▼
	3 ◄-(1)-4
	*/
	vector<vector<ii> > AL(5, vector<ii>());
	AL[0].push_back(mp(1, 3));
	AL[0].push_back(mp(2, 5));
	AL[1].push_back(mp(2, 1));
	AL[2].push_back(mp(3, 4));
	AL[2].push_back(mp(4, 6));
	AL[4].push_back(mp(3, 1));
	vector<int> res = djikstra(AL, 0, 3);
	assert(res.size() == 5);
	assert(res[0] == 0);
	assert(res[3] == 8);
}

void testConnectedComponentGraph() {
	/*Test case with 2 connected components, path between them shouldn't exist. Expected result of: inf value.
	0				3
	/ \			   / ▲
	(3)/   \(2)     (2)/   \(1)
	▼     ▼		 ▼     \
	1◄-(2)-2		 4-(3)-►5
	*/
	vector<vector<ii> > AL(6, vector<ii>());
	AL[0].push_back(mp(1, 3));
	AL[0].push_back(mp(2, 2));
	AL[2].push_back(mp(1, 2));
	AL[3].push_back(mp(4, 2));
	AL[4].push_back(mp(5, 3));
	AL[5].push_back(mp(3, 1));
	vector<int> res = djikstra(AL, 0, 3);
	assert(res.size() == 6);
	assert(res[0] == 0);
	assert(res[3] == inf);
}



int main() {
	testOneNodeGraph();
	testNormalGraph();
	testConnectedComponentGraph();
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
	printf("%d\n", (djikstra(AL, start, dest))[dest]);

}

