#include <string>
#include <vector>
#include <cassert>

using namespace std;

//CHANGE THESE IF SOMETHING FAILS
const long long primeBase = 257;
const long long primeMod = 1000000007;

//Rolling hashing function
long long Hash(string& str) {
	long long sum = 0;
	for (int i = 0; i < str.size(); i++) {
		sum = sum * primeBase + str[i];
		sum %= primeMod;
	}
	return sum;
}

/*Rabin Karp substring match function based in rolling hashing
Input: A pattern string (pattern) and a main string (str) to search the pattern in.
Output: A vector of ints which contain the starting indexes of all occurences of the pattern in the main string. The vector is ordered by order of occurence.
*/
vector<int>& rabinKarp(string pattern, string str) {
	int strLen = str.size();
	int patLen = pattern.size();
	vector<int>& res = *new vector<int>();
	if (strLen < patLen)
		return res;
	long long targetHash = Hash(pattern);
	long long curHash = Hash(str.substr(0,patLen));
	long long power = 1;
	for (int i = 0; i < patLen; i++)
		power = (power * primeBase) % primeMod;
	for (int i = 0; i < strLen - patLen; i++) {
		if (targetHash == curHash)
			res.push_back(i);
		//Update Hash
		curHash = (curHash * primeBase) + str[i + patLen];
		curHash %= primeMod;
		curHash -= power*str[i] % primeMod;
		curHash = curHash < 0 ? curHash + primeMod : curHash;
	}
	if (targetHash == curHash)
		res.push_back(strLen-patLen);
	return res;

}

//Test with empty main string as an input, expected output is an empty vector.
void testEmptyString() {
	vector<int> myRes = rabinKarp("a pattern", "");
	assert(myRes.size() == 0);
}

//Test where the main string is shorter than the pattern string, expected output is an empty vector.
void testShortString() {
	vector<int> myRes = rabinKarp("Roll that", "Hash");
	assert(myRes.size() == 0);
}

//Test where the pattern string is the same as the main string, expected output is a vector with a single element: 0
void testSameString() {
	vector<int> myRes = rabinKarp("Same", "Same");
	assert(myRes.size() == 1);
	assert(myRes[0] == 0);
}

//Test where the pattern string doesn't appear in the main string, expected output is an empty vector.
void testNoOccurence() {
	vector<int> myRes = rabinKarp("Find me", "I won't find you");
	assert(myRes.size() == 0);
}

//Test where the pattern string appears several times in the main string, expected output is number of occurences with correct indexes.
void testOccurences() {
	vector<int> myRes = rabinKarp("word", "This phrase will contain the word: word. Not WORD or wOrD, simply word.");
	assert(myRes.size() == 3);
	assert(myRes[0] == 29);
	assert(myRes[1] == 35);
	assert(myRes[2] == 66);
}


int main() {
	testEmptyString();
	testShortString();
	testSameString();
	testNoOccurence();
	testOccurences();
	//Example of Use
	vector<int> myRes = rabinKarp("hola", "holamenesholaquetalhola");
	for (int i = 0; i < myRes.size(); i++) {
		printf("%d ", myRes[i]);
	}
	printf("\n");
}



