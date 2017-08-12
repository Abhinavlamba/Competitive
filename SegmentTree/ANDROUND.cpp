#include <bits/stdc++.h>
#define MAXN 60012
#define ll long long
using namespace std;

ll int a[MAXN];
ll int tree[4*MAXN];

void buildTree(int node, int lo, int hi){
	if(lo == hi){
		tree[node] = a[lo];
		return;
	}
	int mid = lo+(hi-lo)/2;
	buildTree(2*node+1, lo, mid);
	buildTree(2*node+2, mid+1, hi);
	tree[node] = tree[2*node+1]&tree[2*node+2];
}

ll int query(int node, int lo, int hi, int qs, int qe){
	if(qs <= lo && qe >= hi){
		return tree[node];
	}
	int mid = lo+(hi-lo)/2;
	if(qe <= mid){
		return query(2*node+1, lo, mid, qs, qe);
	}
	if(qs > mid){
		return query(2*node+2, mid+1, hi, qs, qe);
	}
	return query(2*node+1, lo, mid, qs, qe)&query(2*node+2, mid+1, hi, qs, qe);
}

int main(){
	int t;
	scanf("%d", &t);
	ll int n,k;
	while(t--){
		scanf("%lld%lld", &n, &k);
		for(int i=0; i<n; i++){
			scanf("%lld", (a+i));
		}
		for(int i=0; i<n; i++){
			a[n+i] = a[2*n+i] = a[i];
		}
		buildTree(0, 0, 3*n-1);
		for(int i=n; i<2*n; i++){
			if(2*k+1 >= n){
				printf("%lld ", query(0, 0, 3*n-1, 0, n-1));
			}
			else{
				printf("%lld ", query(0, 0, 3*n-1, i-k, i+k));
			}
		}
		printf("\n");
	}
	return 0;
}