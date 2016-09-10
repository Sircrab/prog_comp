#include <bits/stdc++.h>

using namespace std;

class SegmentTree {
public:
  static const int inf = 1e9;
  SegmentTree(const vector<int>& init_array) {
    arr = init_array;  
    n = (int)arr.size(); 
    tree.assign(4 * n + 10, 0);
    lazy.assign(4 * n + 10, 0);
    build_tree(1, 0, n - 1);
  }

  void update(int i, int j, int val) {
    update_tree(1, 0, n - 1, i, j, val);
  }

  int query(int i, int j) {
    return query_tree(1, 0, n - 1, i, j);
  }

private:
  vector<int> arr;
  vector<int> tree;
  vector<int> lazy;
  int n;

  void build_tree(int node, int a, int b) {
      if(a > b) return; // Out of range
      if(a == b) { // Leaf node
          tree[node] = arr[a]; // Init value
      return;
    }
    build_tree(node*2, a, (a+b)/2); // Init left child
    build_tree(node*2+1, 1+(a+b)/2, b); // Init right child
    tree[node] = max(tree[node*2], tree[node*2+1]); // Init root value
    // cambiar here
  }

  /**
   * Increment elements within range [i, j] with value value
   */
  void update_tree(int node, int a, int b, int i, int j, int value) {
      if(lazy[node] != 0) { // This node needs to be updated
        tree[node] += lazy[node]; // Update it

        if(a != b) {
          lazy[node*2] += lazy[node]; // Mark child as lazy
          lazy[node*2+1] += lazy[node]; // Mark child as lazy
        }
          lazy[node] = 0; // Reset it
      }
    
      if(a > b || a > j || b < i) // Current segment is not within range [i, j]
        return;
      
      if(a >= i && b <= j) { // Segment is fully within range
          tree[node] += value;

      if(a != b) { // Not leaf node
        lazy[node*2] += value;
        lazy[node*2+1] += value;
      }
      return;
    }

    update_tree(node*2, a, (a+b)/2, i, j, value); // Updating left child
    update_tree(1+node*2, 1+(a+b)/2, b, i, j, value); // Updating right child

    tree[node] = max(tree[node*2], tree[node*2+1]); // Updating root with max value
    // cambiar here
  }
  
  /**
   * Query tree to get max element value within range [i, j]
   */
  int query_tree(int node, int a, int b, int i, int j) {
    
    if(a > b || a > j || b < i) return -inf; // Out of range
    // cambiar here

    if(lazy[node] != 0) { // This node needs to be updated
      tree[node] += lazy[node]; // Update it

      if(a != b) {
        lazy[node*2] += lazy[node]; // Mark child as lazy
        lazy[node*2+1] += lazy[node]; // Mark child as lazy
      }

      lazy[node] = 0; // Reset it
    }

    if(a >= i && b <= j) // Current segment is totally within range [i, j]
      return tree[node];

    int q1 = query_tree(node*2, a, (a+b)/2, i, j); // Query left child
    int q2 = query_tree(1+node*2, 1+(a+b)/2, b, i, j); // Query right child

    int res = max(q1, q2); // cambiar here 
    
    return res;
  }
  
};

int main(int argc, char** argv) {
  vector<int> arr;
  for (int i = 0; i < 10; i++)
    arr.push_back(i);
  SegmentTree st(arr); 
  
  assert(st.query(0, 3) == 3);
  assert(st.query(0, 0) == 0);
  assert(st.query(3, 6) == 6);
  assert(st.query(9, 9) == 9);
  assert(st.query(0, 9) == 9);

  st.update(3, 6, 10);
  assert(st.query(0, 3) == 13);
  assert(st.query(0, 0) == 0);
  assert(st.query(3, 6) == 16);
  assert(st.query(9, 9) == 9);
  assert(st.query(0, 9) == 16);

  st.update(9, 9, 5);
  assert(st.query(9, 9) == 14);
  return 0;
}






