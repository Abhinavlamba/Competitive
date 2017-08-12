#include <bits/stdc++.h>
#define MAXN 100005
#define ll long long
using namespace std;

ll int a[MAXN];
int tree[4*MAXN];

void buildTree(int node, int lo, int hi){
	if(lo == hi){
		tree[node] = lo;
		return;
	}
	int mid = lo+(hi-lo)/2;
	buildTree(2*node+1, lo, mid);
	buildTree(2*node+2, mid+1, hi);
	int l_m = tree[2*node+1], r_m = tree[2*node+2];
	tree[node] = a[l_m]<a[r_m]?l_m:r_m;
}

int query(int node, int lo, int hi, int l, int r){
	if(l<=lo && r>=hi){
		return tree[node];
	}
	int mid = lo+(hi-lo)/2;
	if(r<=mid){
		return query(2*node+1, lo, mid, l, r);
	}
	else if(l>mid){
		return query(2*node+2, mid+1, hi, l, r);
	}
	int l_idx = query(2*node+1, lo, mid, l, r);
	int r_idx = query(2*node+2, mid+1, hi, l, r);
	return a[l_idx]<a[r_idx]?l_idx:r_idx;
}

ll int maxRegArea(int node, int lo, int hi, int l, int r){
	if(l > r){
		return LLONG_MIN;
	}
	if(l == r){
		return a[l];
	}
	int m = query(node, lo, hi, l, r);
	ll int max_left = maxRegArea(node, lo, hi, l, m-1);
	ll int max_right = maxRegArea(node, lo, hi, m+1, r);
	ll int max_val = max(max(max_right, max_left), (r-l+1)*a[m]);
	return max_val;
}

int main(){
	int n;
	scanf("%d", &n);
	while(n!=0){
		for(int i=0; i<n; i++){
			scanf("%lld", (a+i));
		}
		buildTree(0, 0, n-1);
		printf("%lld\n", maxRegArea(0, 0, n-1, 0, n-1));
		scanf("%d", &n);
	}
}