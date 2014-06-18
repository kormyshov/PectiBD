#include "header.h"

using namespace std;

void print_string(const char *s, int cnt){

	int i;
	for(i=0; s[i] && i<cnt; ++i){
		printf("%c", s[i]);
		if(s[i] == -48 || s[i] == -47) if(s[i+1] != -47 && s[i+1] != -48)++cnt;
		if(s[i] == -30) cnt += 2;
	}
	for(; i<cnt; ++i) printf(" ");
}

int DMcost(char c1, char c2){

	if(c1 == c2) return 0;
	if((c1 >= '0' && c1 <= '9') || (c2 >= '0' && c2 <= '9')) return 5;
	return 1;
}

int DMdistance(const char *s1, const char *s2){

	int n = strlen(s1);
	int m = strlen(s2);

	int **mm = new int*[n+1];
	for(int i=0; i<=n; ++i){
		mm[i] = new int[m+1];
		for(int j=0; j<=m; ++j){
			if(!i || !j){
				mm[i][j] = i+j;
				continue ;
			}
			mm[i][j] = mm[i-1][j] + 2;
			mm[i][j] = min(mm[i][j], mm[i][j-1] + 2);
			mm[i][j] = min(mm[i][j], mm[i-1][j-1] + DMcost(s1[i-1], s2[j-1]));
		}
	}
	return mm[n][m];
}

