#include <bits/stdc++.h>
#define MAXN 100004
#define ll long long
using namespace std;

struct no
{
	ll int total, sum, prefix, suffix;
};

ll int a[MAXN];
no tree[4*MAXN];

void buildTree(int node, int lo, int hi){
	if(lo == hi){
		tree[node] = (no){a[lo], a[lo], a[lo], a[lo]};
		return;
	}
	int mid = lo+(hi-lo)/2;
	buildTree(2*node+1, lo, mid);
	buildTree(2*node+2, mid+1, hi);
	no left = tree[2*node+1], right = tree[2*node+2];
	tree[node].prefix = max(left.prefix, left.total+right.prefix);
	tree[node].suffix = max(right.suffix, right.total+left.suffix);
	tree[node].sum = max(max(left.sum, right.sum), left.suffix+right.prefix);
	tree[node].total = left.total+right.total;
	return;
}

no query(int node, int lo, int hi, int qs, int qe){
	if(lo > hi || qs > qe){
		return (no){0, 0, 0, 0};
	}
	if(qs <= lo && qe >= hi){
		return tree[node];
	}
	int mid = lo+(hi-lo)/2;
	if(qe<=mid){
		return query(2*node+1, lo, mid, qs, qe);
	}
	else if(qs > mid){
		return query(2*node+2, mid+1, hi, qs, qe);
	}
	no left = query(2*node+1, lo, mid, qs, qe);
	no right = query(2*node+2, mid+1, hi, qs, qe);
	no result;
	result.prefix = max(left.prefix, left.total+right.prefix);
	result.suffix = max(right.suffix, right.total+left.suffix);
	result.sum = max(max(left.sum, right.sum), left.suffix+right.prefix);
	result.total = left.total+right.total;
	return result;
}

int main(){
	int t, n, m;
	cin >> t;
	while(t--){
		cin >> n;
		for(int i=0; i<n; i++){
			cin >> a[i];
		}
		buildTree(0, 0, n-1);
		cin >> m;
		int x1, y1, x2, y2;
		for(int i=0; i<m; i++){
			cin >> x1 >> y1 >> x2 >> y2;
			if(y1 < x2){
				// Non-Overlapping
				ll int bestleft = query(0, 0, n-1, x1-1, y1-1).suffix;
				ll int total = query(0, 0, n-1, y1, x2-2).total;
				ll int bestright = query(0, 0, n-1, x2-1, y2-1).prefix;
				cout << bestleft+total+bestright << endl;
			}
			else{
				//Overlapping
				ll int first = query(0, 0, n-1, x1-1, x2-2).suffix + query(0, 0, n-1, x2-1, y2-1).prefix;
				ll int second = query(0, 0, n-1, x1-1, y1-1).suffix+query(0, 0, n-1, y1, y2-1).prefix;
				ll int third = query(0, 0, n-1, x2-1, y1-1).sum;
				cout << max(max(first, second),third) << endl;
			}
		}
	}
}