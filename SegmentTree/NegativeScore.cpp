#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;

int arr[MAXN];
int tree[4*MAXN];

void buildTree(int node, int lo, int hi){
	if(lo == hi){
		tree[node] = arr[lo];
		return;
	}
	int mid=lo+(hi-lo)/2;
	buildTree(2*node+1, lo, mid);
	buildTree(2*node+2, mid+1, hi);
	tree[node] = min(tree[2*node+1], tree[2*node+2]);
}

int query(int node, int lo, int hi, int a, int b){
	if(a<=lo && b>=hi){
		return tree[node];
	}
	int mid = lo+(hi-lo)/2;
	if(b<=mid){
		return query(2*node+1, lo, mid, a, b);
	}
	else if(a>mid){
		return query(2*node+2, mid+1, hi, a, b);
	}
	return min(query(2*node+1, lo, mid, a, b), query(2*node+2, mid+1, hi, a, b));
}

int main(){
	int t;
	scanf("%d", &t);
	int count=1;
	while(t--){
		int n,q;
		scanf("%d%d", &n, &q);
		for(int i=0; i<n; i++){
			scanf("%d", (arr+i));
		}
		buildTree(0, 0, n-1);
		int x,y;
		printf("Scenario #%d:\n", count++);
		for(int i=0; i<q; i++){
			scanf("%d%d", &x, &y);
			printf("%d\n", query(0, 0, n-1, x-1, y-1));
		}
	}
}