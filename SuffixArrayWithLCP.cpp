#include <bits/stdc++.h>

using namespace std;


class SA{
	struct entry{
	int nr[2];
	int p;
	};
public:
	vector<int> lcp;
	vector<int> sa;
	SA(const string& str) : s(str){
		s += "$";
		buildSA(s);
	}

	//OPTIONAL!
	pair<int,int> stringMatching(const string& P){
		int M = P.size();
		int N = s.size();
		int lo = 0, hi = N-1, mid = lo;
		while(lo < hi){
			mid = (lo + hi) / 2;
			if(s.substr(sa[mid],M) >= P){
				hi = mid;
			}
			else{
				lo = mid + 1;
			}
		}
		if(s.substr(sa[lo],M) != P) return pair<int,int>(-1,-1);
		pair<int,int> ans;
		ans.first = lo;
		lo = 0; hi = N; mid = lo;
		while(lo < hi){
			mid = (lo + hi) / 2;
			if (s.substr(sa[mid],M) > P){
				hi = mid;
			} 
			else{
				lo = mid + 1;
			}
		}
		if(hi >= N || s.substr(sa[hi],M) != P) hi--;
		ans.second = hi;
		return ans;
	}
private:
	vector<entry> L;
	vector<vector<int> >P;
	vector<int> rank;
	string s;
	static int cmp(struct entry a, struct entry b){
		return a.nr[0]==b.nr[0] ?(a.nr[1]<b.nr[1] ?1: 0): (a.nr[0]<b.nr[0] ?1: 0);
	}

	void buildLCP(const string& str){
		int N = str.size(),k = 0;
		lcp = vector<int>(N,0);
		rank = vector<int>(N,0);

		for(int i = 0; i < N; i++) rank[sa[i]] = i;

		for(int i = 0; i< N; i++, k?k--:0){
			if(rank[i]==N-1) {k=0; continue;}
	        int j=sa[rank[i]+1];
	        while(i+k<N && j+k<N && str[i+k]==str[j+k]) k++;
	        lcp[rank[i]]=k;
		}
	}

	void buildSA(const string& str){
		int N = str.size();
		P = vector<vector<int> >((int)log2(N) + 2,vector<int>(N,0));
		L = vector<entry>(N);
		sa = vector<int>(N,0);
		for(int i = 0 ; i < N; i++){
			P[0][i] = (int)(str[i]-'a');
		}
		for(int stp =1, cnt = 1; cnt < N; stp++, cnt *=2){
			for(int i = 0 ; i < N; i++){
				L[i].nr[0]=P[stp- 1][i];
	            L[i].nr[1]=i +cnt <N? P[stp -1][i+ cnt]:-1;
	            L[i].p= i;
			}
			sort(L.begin(),L.end(),cmp);
			for(int i = 0 ; i < N; i++){
				P[stp][L[i].p] = i > 0 && L[i].nr[0] == L[i - 1].nr[0] && L[i].nr[1] == L[i - 1].nr[1] ?
				P[stp][L[i - 1].p] : i;
			}
		}
		for(int i = 0 ; i < N; i++){
			sa[i] = L[i].p;
		}
		
		buildLCP(str);

	}
};


string LCSubstring(const string& str1, const string& str2){
	int N = str1.size();
	int M = str2.size();
	string comp = str1 + "#" + str2;
	SA sa(comp);
	string res = "";
	for(int i = 0 ; i < sa.lcp.size()-1;i++){
		if( ( (sa.sa[i] < N && sa.sa[i+1] >= N+1) || (sa.sa[i] >= N+1 && sa.sa[i+1] < N) ) 
			&& sa.lcp[i] > res.size() ) {
			res = comp.substr(sa.sa[i],sa.lcp[i]);
		}
	}
	return res;
}

string LRSubstring(const string& str){
	SA sa(str);
	int res = -1;
	int idx = -1;
	for(int i = 0 ; i < sa.lcp.size()-1; i++){
		if(sa.lcp[i] > res){
			res = sa.lcp[i];
			idx = sa.sa[i];
		}
	}
	return str.substr(idx,res);
}


int main(){
	ios::sync_with_stdio(0);
	int T;
	cin >> T;
	while(T--){
		string word;
		cin >> word;
		word += "#";
		string found = LRSubstring(word);
		if(found.empty()){
			cout << "No repetitions found!" << endl;
			continue;
		}
		SA sa(word);
		pair<int,int> bounds = sa.stringMatching(found);
		cout << found << " " << (bounds.second - bounds.first + 1) << endl;
	}
	return 0;
}
