#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;

int tree[4*MAXN], lazy[4*MAXN], a[MAXN];

void init(){
	memset(lazy, 0, 4*MAXN*sizeof(int));
	memset(a, 0, MAXN*sizeof(int));
}

void buildTree(int node, int lo, int hi){
	if(lo == hi){
		tree[node] = 0;
		return;
	}
	int mid = lo+(hi-lo)/2;
	buildTree(2*node+1, lo, mid);
	buildTree(2*node+2, mid+1, hi);
	tree[node] = 0;
}

void update(int node, int lo, int hi, int us, int ue){
	if(lazy[node] != 0){
		if(lazy[node]%2 == 1){
			tree[node] = (hi-lo+1) - tree[node];
		}
		if(lo != hi){
			lazy[2*node+1] += lazy[node];
			lazy[2*node+2] += lazy[node];
		}
		lazy[node] = 0;
	}
	if(lo > hi || lo > ue || hi < us){
		return;
	}
	if(us <= lo && ue >=hi){
		tree[node] = (hi-lo+1) - tree[node];
		if(lo != hi){
			lazy[2*node+1]++;
			lazy[2*node+2]++;
		}
		return;
	}

	int mid = lo+(hi-lo)/2;
	update(2*node+1, lo, mid, us, ue);
	update(2*node+2, mid+1, hi, us, ue);
	tree[node] = tree[2*node+1] + tree[2*node+2];
}

int query(int node, int lo, int hi, int qs, int qe){
	if(lazy[node] != 0){
		if(lazy[node]%2 == 1){
			tree[node] = (hi-lo+1) - tree[node];
		}
		if(lo != hi){
			lazy[2*node+1] += lazy[node];
			lazy[2*node+2] += lazy[node];
		}
		lazy[node] = 0;
	}

	if(qs <= lo && qe >= hi){
		return tree[node];
	}
	int mid = lo+(hi-lo)/2;
	if(qe <= mid){
		return query(2*node+1, lo, mid, qs, qe);
	}
	else if(qs > mid){
		return query(2*node+2, mid+1, hi, qs, qe);
	}
	return query(2*node+1, lo, mid, qs, qe)+query(2*node+2, mid+1, hi, qs, qe);
}

int main(){
	init();
	int n, m;
	scanf("%d%d", &n, &m);
	buildTree(0, 0, n-1);
	int ty, x, y;
	for(int i=0; i<m; i++){
		// for(int i=0; i<10; i++){
		// 	cout << tree[i] << " ";
		// }
		// cout << endl;
		scanf("%d%d%d", &ty, &x, &y);
		if(ty == 0){
			//update
			update(0, 0, n-1, x-1, y-1);
		}
		else if(ty == 1){
			//query
			printf("%d\n", query(0, 0, n-1, x-1, y-1));
		}
	}
	return 0;
}