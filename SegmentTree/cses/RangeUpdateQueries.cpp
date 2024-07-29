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
  ll accum; // sum of the range
  ll l; //Left range
  ll r; //Right range
  SegTreeNode* left;
  SegTreeNode* right;

  SegTreeNode(ll l1,ll r1){
    this->l = l1;
    this->r = r1;
    left = nullptr;
    right = nullptr;
    accum = 0;
  }
  ~SegTreeNode(){
    left = nullptr;
    right = nullptr;
  }
  /*
  */
};

class SegTree{
  SegTreeNode* root;
public:
  SegTree(ll l, ll r,vl & arr){
    root = new SegTreeNode(l,r);
    build(l,r,arr,root);
  }
  ll query(ll index){
    ll ans = 0;
    query(index,root,ans);
    return ans;
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
  /*
  */
  void update_range(ll l, ll r, ll value){
    update(l,r,value,root);
  }
private:
  void update(ll l,ll r,ll value, SegTreeNode* node){
    if(l <= node->l &&  node->r <= r){
      node->accum+=value;
      return;
    }

    if(!((node->l <= l && l <= node->r) || (node->l <= r && r <= node->r))){
      return;
    }
    update(l,r,value,node->left);
    update(l,r,value,node->right); 
  }
  void build(ll l, ll r, vl & arr, SegTreeNode* node){
    if(l == r){
      return;
    }
    ll mid = (r+l)/2;
    node->left = new SegTreeNode(l,mid);
    node->right = new SegTreeNode(mid+1,r);
    build(l,mid,arr,node->left);
    build(mid+1,r,arr,node->right);
  }
  void query(ll index, SegTreeNode* node,ll & sum){
    //Covers me
    if(node->l == node->r){
      if(node->l == index)
        sum+=node->accum;
      return;
    }
    if(node->l<= index && index <= node->r)
      sum+=node->accum;
    //Disjoint
    if(!((node->l <= index && index <= node->r))){
      return;
    }
    //Ask children
    query(index,node->left,sum);
    query(index,node->right,sum); 
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
      ll mode;
      cin >> mode;
      if(mode == 1){
        ll l,r,value;
        cin >> l >> r >> value;
        l--;
        r--;
        sg.update_range(l, r, value);
      }else{
        ll index;
        cin >> index;
        index--;
        cout << arr[index]+sg.query(index)<<'\n';
      }
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


