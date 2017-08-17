#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;

struct no{
	int sum1, sum2, sum0;
};

no tree[4*MAXN];
int lazy[4*MAXN];

void init(){
	memset(lazy, 0, 4*MAXN*sizeof(int));
}

void buildTree(int node, int lo, int hi){
	if(lo == hi){
		tree[node].sum0 = 1;
		tree[node].sum1 = tree[node].sum2 = 0;
		return;
	}
	int mid = lo + (hi-lo)/2;
	buildTree(2*node+1, lo, mid);
	buildTree(2*node+2, mid+1, hi);
	tree[node].sum1 = tree[node].sum2 = 0;
	tree[node].sum0 = tree[2*node+1].sum0 + tree[2*node+2].sum0;
}

void update(int node, int lo, int hi, int us, int ue){
	int a, b, c;
	if(lazy[node] != 0){
		a = tree[node].sum0; b = tree[node].sum1; c = tree[node].sum2;
		if(lazy[node]%3 == 1){
			tree[node].sum0 = c; tree[node].sum1 = a; tree[node].sum2 = b;
		}
		else if(lazy[node]%3 == 2){
			tree[node].sum0 = b; tree[node].sum1 = c; tree[node].sum2 = a;
		}
		if(lo != hi){
			lazy[2*node+1] += lazy[node];
			lazy[2*node+2] += lazy[node];
		}
		lazy[node] = 0;
	}

	if(lo > hi || ue < lo || us > hi){
		return;
	}
	if(us <= lo && ue >= hi){
		a = tree[node].sum0; b = tree[node].sum1; c = tree[node].sum2;
		tree[node].sum0 = c; tree[node].sum1 = a; tree[node].sum2 = b;
		if(lo != hi){
			lazy[2*node+1]++;
			lazy[2*node+2]++;
		}
		return;
	}
	int mid = lo+(hi-lo)/2;
	update(2*node+1, lo, mid, us, ue);
	update(2*node+2, mid+1, hi, us, ue);
	no left = tree[2*node+1], right = tree[2*node+2];
	tree[node].sum0 = left.sum0 + right.sum0;
	tree[node].sum1 = left.sum1 + right.sum1;
	tree[node].sum2 = left.sum2 + right.sum2;
}

int query(int node, int lo, int hi, int qs, int qe){
	int a, b, c;
	if(lazy[node] != 0){
		a = tree[node].sum0; b = tree[node].sum1; c = tree[node].sum2;
		if(lazy[node]%3 == 1){
			tree[node].sum0 = c; tree[node].sum1 = a; tree[node].sum2 = b;
		}
		else if(lazy[node]%3 == 2){
			tree[node].sum0 = b; tree[node].sum1 = c; tree[node].sum2 = a;
		}
		if(lo != hi){
			lazy[2*node+1] += lazy[node];
			lazy[2*node+2] += lazy[node];
		}
		lazy[node] = 0;
	}

	if(qs <= lo && qe >= hi){
		return tree[node].sum0;
	}
	int mid = lo+(hi-lo)/2;
	if(qe <= mid){
		return query(2*node+1, lo, mid, qs, qe);
	}
	else if(qs > mid){
		return query(2*node+2, mid+1, hi, qs, qe);
	}
	return query(2*node+1, lo, mid, qs, qe) + query(2*node+2, mid+1, hi, qs, qe);
}

int main(){
	init();
	int n, m;
	scanf("%d%d", &n, &m);
	buildTree(0, 0, n-1);
	int ty, x, y;
	for(int i=0; i<m; i++){
		scanf("%d%d%d", &ty, &x, &y);
		if(ty == 0){
			//update
			update(0, 0, n-1, x, y);
		}
		else if(ty == 1){
			//query
			printf("%d\n", query(0, 0, n-1, x, y));
		}
	}
	return 0;
}