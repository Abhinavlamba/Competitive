#include <bits/stdc++.h>
#define MAXN 30005
using namespace std;

struct no{
	int open, close;
};

int a[MAXN];
no tree[4*MAXN];

void buildTree(int node, int lo, int hi){
	if(lo == hi){
		if(a[lo] == -1){
			tree[node] = (no){0, 1};
		}
		else{
			tree[node] = (no){1, 0};
		}
		return;
	}
	int mid = lo+(hi-lo)/2;
	buildTree(2*node+1, lo, mid);
	buildTree(2*node+2, mid+1, hi);
	tree[node].open = max(tree[2*node+1].open, tree[2*node+1].open + tree[2*node+2].open - tree[2*node+1].close);
	tree[node].close = max(tree[2*node+2].close, tree[2*node+2].close + tree[2*node+1].close - tree[2*node+2].open);
}

void update(int node, int lo, int hi, int idx){
	if(lo == hi && lo == idx){
		a[lo]*=-1;
		if(a[lo] == -1){
			tree[node] = (no){0, 1};
		}
		else{
			tree[node] = (no){1, 0};
		}
		return;
	}
	int mid = lo + (hi-lo)/2;
	if(idx <= mid){
		update(2*node+1, lo, mid, idx);
	}
	else{
		update(2*node+2, mid+1, hi, idx);
	}
	tree[node].open = max(tree[2*node+1].open, tree[2*node+1].open + tree[2*node+2].open - tree[2*node+1].close);
	tree[node].close = max(tree[2*node+2].close, tree[2*node+2].close + tree[2*node+1].close - tree[2*node+2].open);
}

int main(){
	int t=10, n;
	while(t--){
		scanf("%d", &n);
		char s[MAXN];
		scanf("%s", s);
		for(int i=0; i<n; i++){
			if(s[i] == '('){
				a[i] = -1;
			}
			else{
				a[i] = 1;
			}
		}
		buildTree(0, 0, n-1);
		int m, x;
		scanf("%d", &m);
		printf("Test %d:\n", 10-t);
		for(int i=0; i<m; i++){
			scanf("%d", &x);
			if(x == 0){
				// query
				if(tree[0].open == 0 && tree[0].close == 0){
					printf("YES\n");
				}
				else{
					printf("NO\n");
				}
			}
			else{
				//update
				update(0, 0, n-1, x-1);
			}
		}
	}
}