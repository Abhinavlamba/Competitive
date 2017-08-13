#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;

struct no{
	int ans;
	pair<int, int> max1, max2;
};

int a[MAXN];
no tree[4*MAXN];

void buildTree(int node, int lo, int hi){
	if(lo == hi){
		tree[node].max1.second = a[lo];
		tree[node].max2.second = tree[node].max2.first = -1;
		tree[node].max1.first = lo;
		tree[node].ans = a[lo]-1;
		return;
	}
	int mid = lo+(hi-lo)/2;
	buildTree(2*node+1, lo, mid);
	buildTree(2*node+2, mid+1, hi);
	if(tree[2*node+1].max1.second >= tree[2*node+2].max1.second){
		tree[node].max1 = tree[2*node+1].max1;
		if(tree[2*node+2].max1.second >= tree[2*node+1].max2.second){
			tree[node].max2 = tree[2*node+2].max1;
		}
		else{
			tree[node].max2 = tree[2*node+1].max2;
		}
	}
	else{
		tree[node].max1 = tree[2*node+2].max1;
		if(tree[2*node+1].max1.second >= tree[2*node+2].max2.second){
			tree[node].max2 = tree[2*node+1].max1;
		}
		else{
			tree[node].max2 = tree[2*node+2].max2;
		}
	}
	tree[node].ans = tree[node].max1.second + tree[node].max2.second;
}

no query(int node, int lo, int hi, int qs, int qe){
	if(qs<=lo && qe>=hi){
		return tree[node];
	}
	int mid = lo+(hi-lo)/2;
	if(qe <= mid){
		return query(2*node+1, lo, mid, qs, qe);
	}
	else if(qs > mid){
		return query(2*node+2, mid+1, hi, qs, qe);
	}
	no left = query(2*node+1, lo, mid, qs, qe);
	no right = query(2*node+2, mid+1, hi, qs, qe);
	no result;
	if(left.max1.second >= right.max1.second){
		result.max1 = left.max1;
		if(right.max1.second >= left.max2.second){
			result.max2 = right.max1;
		}
		else{
			result.max2 = left.max2;
		}
	}
	else{
		result.max1 = right.max1;
		if(left.max1.second >= right.max2.second){
			result.max2 = left.max1;
		}
		else{
			result.max2 = right.max2;
		}
	}
	result.ans = result.max1.second+result.max2.second;
	return result;
}

void update(int node, int lo, int hi, int idx, int val){
	if(lo == hi && idx == lo){
		a[idx] = val;
		tree[node].max1.second = a[lo];
		tree[node].max2.second = tree[node].max2.first = -1;
		tree[node].max1.first = lo;
		tree[node].ans = a[lo]-1;
		return;
	}
	int mid = lo + (hi-lo)/2;
	if(idx <= mid){
		update(2*node+1, lo, mid, idx, val);
	}
	else{
		update(2*node+2, mid+1, hi, idx, val);
	}

	if(tree[2*node+1].max1.second >= tree[2*node+2].max1.second){
		tree[node].max1 = tree[2*node+1].max1;
		if(tree[2*node+2].max1.second >= tree[2*node+1].max2.second){
			tree[node].max2 = tree[2*node+2].max1;
		}
		else{
			tree[node].max2 = tree[2*node+1].max2;
		}
	}
	else{
		tree[node].max1 = tree[2*node+2].max1;
		if(tree[2*node+1].max1.second >= tree[2*node+2].max2.second){
			tree[node].max2 = tree[2*node+1].max1;
		}
		else{
			tree[node].max2 = tree[2*node+2].max2;
		}
	}
	tree[node].ans = tree[node].max1.second + tree[node].max2.second;
}

int main(){
	int n,q;
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		scanf("%d", (a+i));
	}
	buildTree(0, 0, n-1);
	scanf("%d", &q);
	char ty;
	int x, y;
	for(int i=0; i<q; i++){
		cin >> ty >> x >> y;
		if(ty == 'Q'){
			//Query
			printf("%d\n", query(0, 0, n-1, x-1, y-1).ans);
		}
		else if(ty == 'U'){
			//update
			update(0, 0, n-1, x-1, y);
		}
	}
}