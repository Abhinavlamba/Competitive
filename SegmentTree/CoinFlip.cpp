#include <bits/stdc++.h>

using namespace std;

int main(){
	int t,g;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &g);
		int i,n,q;
		while(g--){
			scanf("%d%d%d", &i, &n, &q);
			if(n%2 == 0){
				printf("%d\n", n/2);
			}
			else{
				if(i == q){
					printf("%d\n", n/2);
				}
				else{
					printf("%d\n", n/2+1);
				}
			}
		}
	}
}