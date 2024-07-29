#include<bits/stdc++.h>

using namespace std;

//Typedef...

typedef long long ll;
typedef vector<int> vi;
typedef vector<long long> vl;
typedef pair<int,int> pi;
typedef pair<long long,long long> pl;
typedef vector<pair<int,int>> vpi;
typedef vector<pair<long long,long long>> vpl;

//

//Macros

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

//Functions

const ll mod = 1000000007;
const ll INF = 1e18;

ll binpow(ll a, ll b) {
    a %= mod;
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

struct SegTreeNode;

struct SegTreeNode{
  ll minimum; // minimum of the range
  ll l; //Left range
  ll r; //Right range
  SegTreeNode* left;
  SegTreeNode* right;

  SegTreeNode(ll l1,ll r1){
    this->l = l1;
    this->r = r1;
    left = nullptr;
    right = nullptr;
    minimum = INF;
  }
  ~SegTreeNode(){
    left = nullptr;
    right = nullptr;
  }
};

class SegTree{
  SegTreeNode* root;
public:
  SegTree(ll l, ll r,vl & arr){
    root = new SegTreeNode(l,r);
    build(l,r,arr,root);
  }
  ll query(ll l, ll r){
    return query(l, r, root);
  }
  ~SegTree(){
    killNodes(root);
  }
  void killNodes(SegTreeNode* node){
    if(node!= nullptr){
      killNodes(node->left);
      killNodes(node->right);
      delete node;
    }
  }
private:
  void build(ll l, ll r, vl & arr, SegTreeNode* node){
    if(l == r){
      node->minimum = arr[l];
      return;
    }
    ll mid = (r+l)/2;
    node->left = new SegTreeNode(l,mid);
    node->right = new SegTreeNode(mid+1,r);
    build(l,mid,arr,node->left);
    build(mid+1,r,arr,node->right);
    node->minimum = min(node->left->minimum, node->right->minimum);
  }
  ll query(ll l, ll r, SegTreeNode* node){
    //Covers me
    if(l <= node->l && node->r <= r)
      return node->minimum;
    //Disjoint
    if(!((node->l <= l && l <= node->r) || (node->l <= r && r <= node->r))){
      return INF;
    }
    //Ask children
    return min(query(l,r,node->left),query(l,r,node->right)); 
  }

};

void solve(){
    //code
    ll n,q;
    cin >> n >> q;
    vl arr(n);
    for(ll i = 0; i < n;i++){
      cin >> arr[i];
    }
    SegTree sg = SegTree(0, n-1, arr);
    while(q--){
      ll l,r;
      cin >> l >> r;
      l--;
      r--;
      cout << sg.query(l,r) << '\n';
    }
    /*
    */
}
int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int tt = 1;
    while(tt--) solve();
    return 0;
}


