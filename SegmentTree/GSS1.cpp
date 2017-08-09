#include <bits/stdc++.h>
#define MAXN 50010
#define ll long long 

using namespace std;

struct no{
	ll int max, total, prefix, suffix;
};

ll int arr[MAXN];
no tree[4*MAXN];

void buildTree(int node, int lo, int hi){
	if(lo == hi){
		tree[node] = ((no){arr[lo], arr[lo], arr[lo], arr[lo]});
	}
	else{
		int mid = lo + (hi-lo)/2;
		buildTree(2*node+1, lo, mid);
		buildTree(2*node+2, mid+1, hi);
		no left=tree[2*node+1], right=tree[2*node+2];
		tree[node].max = max(max(left.max, right.max), left.suffix+right.prefix);
		tree[node].suffix = max(right.suffix, right.total+left.suffix);
		tree[node].prefix = max(left.prefix, left.total+right.prefix);
		tree[node].total = left.total + right.total;
	}
}

no query(int node, int lo, int hi, int qs, int qe){
	if(qs <= lo && hi <= qe){
		return tree[node];
	}
	int mid = lo + (hi-lo)/2;
	if(qe <= mid){
		return query(2*node+1, lo, mid, qs, qe);
	}
	if(qs > mid){
		return query(2*node+2, mid+1, hi, qs, qe);
	}
	no left = query(2*node+1, lo, mid, qs, qe);
	no right = query(2*node+2, mid+1, hi, qs, qe);
	no result;
	result.max = max(max(left.max, right.max), left.suffix+right.prefix);
	result.prefix = max(left.prefix, left.total+right.prefix);
	result.suffix = max(right.suffix, right.total+left.suffix);
	result.total = left.total+right.total;
	return result;
}

int main(){
	int n;
	cin >> n;
	for(int i=0; i<n; i++){
		scanf("%lld", (arr+i));
	}
	buildTree(0, 0, n-1);
	int m;
	cin >> m;
	for(int i=0; i<m; i++){
		int x,y;
		scanf("%d%d", &x, &y);
		printf("%lld\n", query(0, 0, n-1, x-1, y-1).max);
	}
}