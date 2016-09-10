#include <bits/stdc++.h>

using namespace std;

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

class UnionFind {
private: vi p, rank;
public:
	UnionFind(int N) {
		rank.assign(N, 0);
		p.assign(N, 0);
		for (int i = 0; i < N; i++) p[i] = i;
	}
	
	int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
	bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
	void unionSet(int i, int j) {
		if (!isSameSet(i,j)){
			int x = findSet(i); int y = findSet(j);
			if (rank[x] > rank[y]) p[y] = x;
			else {
				p[x] = y;
				if (rank[x] == rank[y]) rank[y]++;
			}
		}
	} 
};

int main(int argc, char** argv){
	int N = 10;
	UnionFind uf(N);
	for (int i = 0; i < N; i++)
		assert(uf.findSet(i) == i);
	uf.unionSet(1,2);
	uf.unionSet(3,4);

	assert(uf.isSameSet(1,2));
	assert(uf.isSameSet(3,4));

	uf.unionSet(2,3);

	assert(uf.isSameSet(1,2) && uf.isSameSet(2,3) && uf.isSameSet(3,4) && uf.isSameSet(1,4));
	return 0;
}