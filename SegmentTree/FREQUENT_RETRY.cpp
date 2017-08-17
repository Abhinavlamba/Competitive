#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;

struct no{
	int prefix, suffix, max;
};

int a[MAXN];
no tree[4*MAXN];

void buildTree(int node, int lo, int hi){
	if(lo == hi){
		tree[node] = (no){1, 1, 1};
		return;
	}
	int mid = lo+(hi-lo)/2;
	buildTree(2*node+1, lo, mid);
	buildTree(2*node+2, mid+1, hi);
	no left = tree[2*node+1], right = tree[2*node+2];
	if(a[lo] == a[mid+1]){
		tree[node].prefix = left.prefix+right.prefix;
	}
	else{
		tree[node].prefix = left.prefix;
	}
	if(a[hi] == a[mid]){
		tree[node].suffix = right.suffix+left.suffix;
	}
	else{
		tree[node].suffix = right.suffix;
	}
	if(a[mid] == a[mid+1]){
		tree[node].max = max(max(left.max, right.max), left.suffix+right.prefix);
	}
	else{
		tree[node].max = max(left.max, right.max);
	}
}

no query(int node, int lo, int hi, int qs, int qe){
	if(qs <= lo && qe >= hi){
		return tree[node];
	}
	int mid = lo+(hi-lo)/2;
	if(qe<=mid){
		return query(2*node+1, lo, mid, qs, qe);
	}
	else if(qs>mid){
		return query(2*node+2, mid+1, hi, qs, qe);
	}
	no left = query(2*node+1, lo, mid, qs, qe);
	no right = query(2*node+2, mid+1, hi, qs, qe);
	no result;
	if(a[lo] == a[mid+1]){
		result.prefix = left.prefix+right.prefix;
	}
	else{
		result.prefix = left.prefix;
	}
	if(a[hi] == a[mid]){
		result.suffix = right.suffix+left.suffix;
	}
	else{
		result.suffix = right.suffix;
	}
	if(a[mid] == a[mid+1]){
		result.max = max(max(left.max, right.max), left.suffix+right.prefix);
	}
	else{
		result.max = max(left.max, right.max);
	}
	return  result;
}

int main(){
	int n,q;
	scanf("%d", &n);
	while(n!=0){
		scanf("%d", &q);
		for(int i=0; i<n; i++){
			scanf("%d", (a+i));
		}
		buildTree(0, 0, n-1);
		int x, y;
		for(int i=0; i<q; i++){
			scanf("%d%d", &x, &y);
			printf("%d\n", query(0, 0, n-1, x-1, y-1).max);
		}
		scanf("%d", &n);
	}
}