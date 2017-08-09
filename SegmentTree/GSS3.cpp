#include <bits/stdc++.h>
#define MAXN 50010
#define ll long long

using namespace std;

struct node{
	ll int max, prefix, suffix, total;
};

ll int arr[MAXN];
node tree[4*MAXN];

void build(int nod, int lo, int hi){
	if(lo == hi){
		tree[nod] = (node){arr[lo], arr[lo], arr[lo], arr[lo]};
		return;
	}

	int mid = lo+(hi-lo)/2;
	build(2*nod+1, lo, mid);
	build(2*nod+2, mid+1, hi);
	node left = tree[2*nod+1], right = tree[2*nod+2];
	tree[nod].max = max(max(left.max, right.max), left.suffix+right.prefix);
	tree[nod].prefix = max(left.prefix, left.total+right.prefix);
	tree[nod].suffix = max(right.suffix, right.total+left.suffix);
	tree[nod].total = left.total + right.total;
}

node query(int nod, int lo, int hi, int qs, int qe){
	if(qs <= lo && hi <= qe){
		return tree[nod];
	}
	int mid = lo+(hi-lo)/2;
	if(qe <= mid){
		return query(2*nod+1, lo, mid, qs, qe);
	}
	if(qs > mid){
		return query(2*nod+2, mid+1, hi, qs, qe);
	}
	node left = query(2*nod+1, lo, mid, qs, qe);
	node right = query(2*nod+2, mid+1, hi, qs, qe);
	node result;
	result.max = max(max(left.max, right.max), left.suffix+right.prefix);
	result.prefix = max(left.prefix, left.total+right.prefix);
	result.suffix = max(right.suffix, right.total+left.suffix);
	result.total = left.total+right.total;
	return result;
}

void update(int nod, int lo, int hi, int i, int val){
	if(lo == hi && lo == i){
		arr[i] = val;
		tree[nod] = (node){val, val, val, val};
		return;
	}
	int mid = lo+(hi-lo)/2;
	if(i <= mid){
		update(2*nod+1, lo, mid, i, val);
	}
	else if(i > mid){
		update(2*nod+2, mid+1, hi, i, val);
	}

	node left = tree[2*nod+1], right = tree[2*nod+2];
	tree[nod].max = max(max(left.max, right.max), left.suffix+right.prefix);
	tree[nod].prefix = max(left.prefix, left.total+right.prefix);
	tree[nod].suffix = max(right.suffix, right.total+left.suffix);
	tree[nod].total = left.total + right.total; 
}

int main(){
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		scanf("%lld", (arr+i));
	}
	build(0, 0, n-1);
	int m;
	scanf("%d", &m);
	int ty, x, y;
	for(int i=0; i<m; i++){
		scanf("%d%d%d", &ty, &x, &y);
		if(ty == 0){
			//modify or update
			update(0, 0, n-1, x-1, y);
		}
		else if(ty == 1){
			//query
			printf("%lld\n",query(0, 0, n-1, x-1, y-1).max);
		}
	}
	return 0;
}