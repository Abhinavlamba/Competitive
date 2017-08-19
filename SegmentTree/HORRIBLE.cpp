#include <bits/stdc++.h>
#define MAXN 100005
#define ll long long
using namespace std;

ll int a[MAXN], lazy[4*MAXN], tree[4*MAXN];

void init(){
	memset(a, 0, MAXN*sizeof(long long  int));
	memset(lazy, 0, 4*MAXN*sizeof(long long int));
}

void buildTree(long long int node, long long int lo, long long int hi){
	if(lo == hi){
		tree[node] = 0;
		return;
	}
	long long int mid = lo + (hi-lo)/2;
	buildTree(2*node+1, lo, mid);
	buildTree(2*node+2, mid+1, hi);
	tree[node] = 0;
}

void update(long long int node, long long int lo, long long int hi, long long int us, long long int ue, long long int val){
	if(lazy[node]!=0){
		tree[node] += (hi-lo+1)*lazy[node];
		if(lo != hi){
			lazy[2*node+1] += lazy[node];
			lazy[2*node+2] += lazy[node];
		}
		lazy[node] = 0;
	}
	if(lo > hi || lo > ue || hi < us){
		return;
	}
	if(us <= lo && ue >= hi){
		tree[node] += (hi-lo+1)*val;
		if(lo != hi){
			lazy[2*node+1] += val;
			lazy[2*node+2] += val;
		}
		return;
	}
	long long int mid = lo+(hi-lo)/2;
	update(2*node+1, lo, mid, us, ue, val);
	update(2*node+2, mid+1, hi, us, ue, val);
	tree[node] = tree[2*node+1] + tree[2*node+2];
}

long long int query(long long int node, long long int lo , long long int hi, long long int qs, long long int qe){
	if(lazy[node]!=0){
		tree[node] += (hi-lo+1)*lazy[node];
		if(lo != hi){
			lazy[2*node+1] += lazy[node];
			lazy[2*node+2] += lazy[node];
		}
		lazy[node] = 0;
	}

	if(qs <= lo && qe >= hi){
		return tree[node];
	}
	long long int mid = lo+(hi-lo)/2;
	if(qe <= mid){
		return query(2*node+1, lo, mid, qs, qe);
	}
	else if(qs > mid){
		return query(2*node+2, mid+1, hi, qs, qe);
	}
	return query(2*node+1, lo, mid, qs, qe) + query(2*node+2, mid+1, hi, qs, qe);
}

int main(){
	long long int t, n, c;
	scanf("%lld", &t);
	while(t--){
		init();
		scanf("%lld%lld", &n, &c);
		buildTree(0, 0, n-1);
		long long int ty, x, y, v;
		for(long long int i=0; i<c; i++){
			scanf("%lld", &ty);
			if(ty == 0){
				//update
				scanf("%lld%lld%lld", &x, &y, &v);
				update(0, 0, n-1, x-1, y-1, v);
			}
			else{
				//query
				scanf("%lld%lld", &x, &y);
				printf("%lld\n", query(0, 0, n-1, x-1, y-1));
			}
		}
	}
}