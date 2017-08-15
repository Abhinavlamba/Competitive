#include <bits/stdc++.h>
#define MAXN 100005
#define ll long long 
using namespace std;

ll int a[MAXN];
ll int tree[4*MAXN];

void buildSegTree(int node, int lo, int hi){
	if(lo == hi){
		tree[node] = a[lo];
		return;
	}
	int mid = lo + (hi-lo)/2;
	buildSegTree(2*node+1, lo, mid);
	buildSegTree(2*node+2, mid+1, hi);
	tree[node] = tree[2*node+1]+tree[2*node+2];
}

void update(int node, int lo, int hi, int us, int ue){
	if(us > hi || ue < lo){
		return;
	}
	if(tree[node] == (hi-lo+1)){
		return;
	}
	if(lo == hi){
		a[lo] = sqrt(a[lo]);
		tree[node] = a[lo];
		return;
	}
	int mid = lo + (hi-lo)/2;
	if(ue <= mid){
		update(2*node+1, lo, mid, us, ue);
	}
	else if(us > mid){
		update(2*node+2, mid+1, hi, us, ue);
	}
	else{
		update(2*node+1, lo, mid, us, ue);
		update(2*node+2, mid+1, hi, us, ue);
	}
	tree[node] = tree[2*node+1] + tree[2*node+2];
}

ll int query(int node, int lo, int hi, int qs, int qe){
	if(qs <= lo && qe>=hi){
		return tree[node];
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
	int n,m;
	int count = 1;
	while(scanf("%d", &n)!=EOF){
		for(int i=0; i<n; i++){
			scanf("%lld", (a+i));
		}
		buildSegTree(0, 0, n-1);
		scanf("%d", &m);
		int t, x, y;
		printf("Case #%d:\n", count++);
		for(int i=0; i<m; i++){
			scanf("%d%d%d", &t, &x, &y);
			int temp;
			if(x > y){
				temp = y;
				y = x;
				x = temp;
			}
			if(t==0){
				//update
				update(0, 0, n-1, x-1, y-1);
				// for(int j=x-1; j<=y-1; j++){
				// 	if(a[j] == 1){
				// 		continue;
				// 	}
				// 	update(0, 0, n-1, j);
				// }
			}
			else if(t==1){
				//query
				printf("%lld\n", query(0, 0, n-1, x-1, y-1));
			}
		}
		printf("\n");
	}
	return 0;
}