#include<bits/stdc++.h>
#include <vector>

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
  ll sum; // sum of the range
  ll y1;
  ll x1;
  ll y2;
  ll x2;
  SegTreeNode* c1;
  SegTreeNode* c2;
  SegTreeNode* c3;
  SegTreeNode* c4;


  SegTreeNode(ll _y1,ll _x1,ll _y2, ll _x2){
    this->y1 = _y1;
    this->x1 = _x1;
    this->y2 = _y2;
    this->x2 = _x2;
    c1 = nullptr;
    c2 = nullptr;
    c3 = nullptr;
    c4 = nullptr;
    sum = 0;
  }
  ~SegTreeNode(){
    c1 = nullptr;
    c2 = nullptr;
    c3 = nullptr;
    c4 = nullptr;
  }
};

class SegTree{
  SegTreeNode* root;
public:
  SegTree(ll y1,ll x1,ll y2,ll x2,vector<vector<char>> & forest){
    root = new SegTreeNode(y1,x1,y2,x2);
    build(y1,x1,y2,x2,forest,root);
  }
  ll query(ll y1,ll x1, ll y2,ll x2){
    return query(y1,x1,y2,x2, root);
  }
  ~SegTree(){
    killNodes(root);
  }
  void killNodes(SegTreeNode* node){
    if(node!= nullptr){
      killNodes(node->c1);
      killNodes(node->c2);
      killNodes(node->c3);
      killNodes(node->c4);
      delete node;
    }
  }
private:
  void build(ll y1,ll x1, ll y2, ll x2, vector<vector<char>> & forest, SegTreeNode* node){
    if(y1 == y2 && x1 == x2){
      node->sum = forest[y1][x1] == '*';
      return;
    }
    ll midy = (y2+y1)/2;
    ll midx = (x2+x1)/2;
    ll temp_sum = 0;

    if(midy+1 <= y2 && midx+1 <= x2){
      node->c1 = new SegTreeNode(midy+1,midx+1,y2  ,x2);
      build(midy+1,midx+1,y2,x2,forest,node->c1);
      temp_sum += node->c1->sum;
    }

    if(midy+1<=y2){
      node->c2 = new SegTreeNode(midy+1,x1    ,y2  ,midx);
      build(midy+1,x1,y2,midx,forest,node->c2);
      temp_sum += node->c2->sum;
    }

    node->c3 = new SegTreeNode(y1    ,x1    ,midy,midx);
    build(y1,x1,midy,midx,forest,node->c3);
    temp_sum += node->c3->sum;

    if(midx+1 <=x2){
      node->c4 = new SegTreeNode(y1    ,midx+1,midy,x2);
      build(y1,midx+1,midy,x2,forest,node->c4);
      temp_sum += node->c4->sum;
    }
    node->sum = temp_sum;
  }
  ll query(ll y1,ll x1, ll y2, ll x2, SegTreeNode* node){
    if(node == nullptr)
      return 0;
    //Covers me
    if(x1 <= node->x1 && node->y1 >= y1 && x2>=node->x2 && y2>=node->y2){
      //cout << node->y1+1 << ' ' << node->x1+1 << ' ' << node->y2+1 << ' ' << node->x2+1 << ' ' << node->sum << '\n';
      return node->sum;
    }
    //Disjoint
    /*
    if(!((node->x1 <= x1 && x1 <= node->x2 && node->y1 <= y1 && y1 <= node->y2) ||
          (node->x1 <= x1 && x1 <= node->x2 && node->y1 <= y2 && y2 <= node->y2) || 
          (node->x1 <= x2 && x2 <= node->x2 && node->y1 <= y1 && y1 <= node->y2) ||
          (node->x1 <= x2 && x2 <= node->x2 && node->y1 <= y2 && y2 <= node->y2) ||

          (x1 <= node->x2 && node->x2 <= x2 && y1 <= node->y2 && node->y2 <= y2) ||
          (x1 <= node->x1 && node->x1 <= x2 && y1 <= node->y2 && node->y2 <= y2) ||
          (x1 <= node->x2 && node->x2 <= x2 && y1 <= node->y1 && node->y1 <= y2) ||
          (x1 <= node->x1 && node->x1 <= x2 && y1 <= node->y1 && node->y1 <= y2)
          )){
      return 0;
    }
    */
    /*
    */
    //Ask children
    return query(y1,x1,y2,x2,node->c1)+query(y1,x1,y2,x2,node->c2)+query(y1,x1,y2,x2,node->c3)+query(y1,x1,y2,x2,node->c4); 
  }

};

void solve(){
    //code
    ll n,q;
    cin >> n >> q;
    vector<vector<char>> forest(n,vector<char>(n));
    for(ll i = 0; i < n;i++){
      for(ll j = 0; j < n;j++){
        cin >> forest[i][j];
      }
    }
    SegTree sg = SegTree(0, 0,n-1,n-1, forest);
    while(q--){
      ll y1,x1,y2,x2;
      cin >> y1 >> x1 >> y2 >>x2;
      y1--;
      x1--;
      y2--;
      x2--;
      cout << sg.query(y1,x1,y2,x2) << '\n';
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


