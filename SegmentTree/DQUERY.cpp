#include <bits/stdc++.h>
#define MAXN 1000002
#define MAXQ 200002
using namespace std;

int arr[MAXN];
int block;
int ans[MAXQ];

struct Query{
	int l, r, idx;
};

bool mo_comapare(Query x, Query y){
	if(x.l/block != y.l/block){
		return x.l/block < y.l/block;
	}
	return x.r < y.r;
}

void init(){
	memset(arr, 0, MAXN*sizeof(int));
}

void queryProcess(int a[], int n, Query q[], int m){
	block = (int)sqrt(n);

	sort(q, q+m, mo_comapare);
	// for(int i=0; i<m; i++){
	// 	cout << q[i].l << " " << q[i].r << " " << q[i].idx<< endl;
	// }
	int unq_ele = 0;
	int currL=0, currR=-1;
	for(int i=0; i<m; i++){
		int L = q[i].l, R = q[i].r;
		//Removing Elements from previous range
		while(currL < L){
			arr[a[currL]]--;
			if(arr[a[currL]] == 0){
				unq_ele--;
			}
			currL++;
		}
		//Adding elements for current range in previous range
		while(currL > L){
			currL--;
			if(arr[a[currL]] == 0){
				unq_ele++;
			}
			arr[a[currL]]++;
		}
		while(currR < R){
			currR++;
			if(arr[a[currR]] == 0){
				unq_ele++;
			}
			arr[a[currR]]++;
		}
		while(currR > R){
			arr[a[currR]]--;
			if(arr[a[currR]] == 0){
				unq_ele--;
			}
			currR--;
		}

		ans[q[i].idx] = unq_ele;
	}
}

int main(){
	init();
	int n;
	int a[n];
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		scanf("%d", (a+i));
	}
	int m, L, R;
	scanf("%d", &m);
	Query qu[m];
	for(int i=0; i<m; i++){
		scanf("%d%d", &L, &R);
		qu[i].l = L-1;
		qu[i].r = R-1;
		qu[i].idx = i;
	}
	queryProcess(a, n, qu, m);
	for(int i=0; i<m; i++){
		printf("%d\n", ans[i]);
	}
	return 0;
}