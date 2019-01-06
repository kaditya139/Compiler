#include<stdio.h>
#include<string.h>

void firstSearch(char[][20],char[][20],char,int,int);
void firstSearchEps(char[][20],char[][20],char,int,int);
void followSearch(char[][20],char[][20],char[][20],char,int);
void parsingTable(char[][20],char[][20],char[][20],char[][200]);

int main() {
    char str[500];
    scanf("%[^\n]*c",str);
    int size = strlen(str);
    int i, j, k, l, m = 0, count;
    char input[20][20], first[20][20], follow[20][20], table[20][200];
    for (i=0; i<20; i++) {
        for (j=0; j<20; j++) {
            input[i][j] = first[i][j] = follow[i][j] = '\0';
        }
    }
    for (i=0; i<20; i++) {
	for (j=0; j<200; j++) {
    	    table[i][j] = '\0';
	}
    }
    j=3; l=0; count=0;
    for (i=0; i<size; i++) {
        if (str[i] == '/') {
            input[l][0] = str[m];
            input[l][1] = '-';
	    input[l][2] = '>';
            int x = 3;
            for (k=j; k<i; k++) {
                input[l][x++] = str[k];
            }
            count++; l++; i++; j=i;
        }
        if (((int)str[i]) == 32) {
            input[l][0] = str[m]; input[l][1] = '-'; input[l][2] = '>';
            int x = 3;
            for (k=j; k<i; k++)
                input[l][x++] = str[k];
            l++; count++; i++; j=i+3; m=i;
        }
    }
    printf("\n");
    for (i=0; i<count; i++)
        printf("%s\n", input[i]);
    printf("\n");
    int arr[56];
    for (i=0; i<56; i++)
        arr[i] = 0;
    for (i=0; i<size; i++) {
        if (((int)str[i]) > 64 && ((int)str[i]) < 91)
            arr[((int)str[i])-64] = 1;
        if (((int)str[i]) > 96 && ((int)str[i]) < 123)
            arr[((int)str[i])-70] = 1;
        if (str[i] == '+')
            arr[52] = 1;
        if (str[i] == '*')
            arr[53]=1;
	if (str[i] == '(')
            arr[54] = 1;
        if (str[i] == ')')
            arr[55] = 1;
    }
    int nnt = 0;
    for (i=0; i<26; i++)
        nnt+=arr[i];
    int symbol = 0;
    for (i=0; i<56; i++)
        symbol+=arr[i];
    int nt = symbol - nnt;
    k = 0;
    for (i=0; i<26; i++) {
        if (arr[i] == 1) {
            first[k][0] = follow[k][0] = table[k+1][0] = ((char)(i+64));
            k++;
        }
    }
    int f = 10;
    for (i=26; i<52; i++) {
	if (arr[i] == 1) {
	    table[0][f] = ((char)(i+70));
       	    f+=10;
	}
    }
    if (arr[52] == 1) {
	table[0][f] = '+';
	f+=10;
    }
    if (arr[53] == 1){
        table[0][f] = '*';
	f+=10;
    }
    if (arr[54] == 1) {
        table[0][f] = '(';
	f+=10;
    }
    if (arr[55] == 1) {
        table[0][f] = ')';
	f+=10;
    }
    table[0][f] = '$';

    for (i=0; i<nnt; i++) {
        char a = first[i][0];
        firstSearch(input, first, a, 1, i);
    }
    for (i=0; i<20; i++) {
	if (input[i][3] == '@') {
	    for (j=0; j<20; j++) {
		if (first[j][0] == input[i][0]) {
		    int k = 0;
		    while (first[j][k] != '\0')
			k++;
		    first[j][k] = '@';
		}
	    }
	}
    }
    for (i=0; i<nnt; i++) {
        char a = first[i][0];
        firstSearchEps(input, first, a, nnt, i);
    }
    for (i=0; i<k; i++)
	printf("%s\n", first[i]);
    printf("\n");

    for (i=0; i<nnt; i++) {
        char a = follow[i][0];
        followSearch(input, first, follow, a, i);
    }
    for (i=0; i<k; i++)
	printf("%s\n", follow[i]);
    printf("\n");
    count = 0;
    parsingTable(input, first, follow, table);
    for (i=0; i<=k; i++)
	printf("%s\n", table[i]);
    printf("\n");
}

void firstSearch(char input[][20], char first[][20], char a, int k, int i){
    int j;
    for (j=0; j<20; j++) {
	if (input[j][0] == '\0')
	    break;
        if (input[j][0] == a) {
            if ((((int)input[j][3]) <= 64 || ((int)input[j][3]) >= 91) && input[j][3] != '@') {
                first[i][k++] = input[j][3];
	    }
            else {
                char b = input[j][3];
                firstSearch(input, first, b, k, i);
            }
        }
    }
}

void firstSearchEps(char input[][20], char first[][20], char a, int nnt, int i) {
    int j, flag = 0;
    for (j=0; j<20; j++) {
        if (input[j][0] == '\0')
	    break;
        char c = input[j][0];
        flag = 0;
        if (input[j][0] == a) {
	    if (((int)input[j][3]) > 64 && ((int)input[j][3]) < 91) {
	        char b = input[j][3];
	        int k, m;
		    for (k=0; k<20; k++) {
		        int l = 1; flag = 0;
		        if (first[k][0] == b) {
			    while (first[k][l] != '\0') {
			        if (first[k][l++] == '@') {
				    flag = 1;
				    break;
			        }
			    }
			    if (flag == 1) {
			        for (m=0; m<20; m++) {
				    if (first[m][0] == c) {
				        int n = 1, flag1 = 0;
				        while (first[m][n] != '\0')
					    n++;
				        char d = input[j][4];
				        if (((int)d) <= 64 || ((int)d) >= 91) {
					    int x, flag2 = 0;
					    for (x=1; x<=n; x++) {
					        if (d == first[m][x]) {
						    flag2 = 1; break;
					        }
					    }
					    if (flag2 == 0)
					        first[m][n++] = d;
				        }
			    	    else {
				    	int x, y;
					    for (x=0; x<20; x++) {
					    if (first[x][0] == d) {
					        int p = 1, q = 1;
					        while (first[x][p] != '\0') {
						    int flag3 = 0;
						    for (y=0; y<=n; y++) {
						        if (first[c][y] == first[x][p]) {
							    flag3 = 1;
							    break;
						        }
						    }
						    p++;
						    if (flag3 == 0)
						        first[c][n++] = first[x][p++];
					        }
					    }
				        }
				    }
			        }
			    }
		        }
		    }		
	        }
	    }
        }
    }
}

void followSearch(char input[][20], char first[][20], char follow[][20], char a, int i){
    char b = input[0][0];
    int j, k = 3, l = 1, m = 1, n, z, y, flag = 0;
    if (input[0][0] == a)
	follow[i][l++] = '$';
	for (j=0; j<20; j++) {
	k = 3;
	if (input[j][0] == '\0')
	    break;
	while (input[j][k] != '\0') {
	    flag = 0;
	    if (input[j][k] == a) {
		if (input[j][k+1] != '\0') {
		    if (((int)input[j][k+1]) <= 64 || ((int)input[j][k+1]) >= 91)
			follow[i][l++] = input[j][k+1];
			else {
                	    char c = input[j][k+1];
                	    for (z=0; z<20; z++) {
				if (first[z][0] == c) {
				    while (first[z][m] != '\0') {
					if (first[z][m] != '@') {
					    follow[i][l++] = first[z][m++];
					}
					else {
					    flag = 1;
					    m++;
					}
				    }
				}
			    }		
            		}
			if (flag == 1) {
			    char c = input[j][0];
			    for (z=0; z<20; z++) {
				if (follow[z][0] == c) {
				    int q = 1;
				    while (follow[z][q] != '\0') {
					follow[i][l++] = follow[z][q++];
				    }
				}
			    }
			}
		    }
		    else {
			char c = input[j][0];
			for (n=0; n<20; n++) {
			if (follow[n][0] == '\0')
			    break;
			if (follow[n][0] == c) {
			    int p = 1;
			    while (follow[n][p] != '\0') {
				int q, flag = 0;
				for (q=0; q<=l; q++) {
				    if (follow[i][q] == follow[n][p]) {
					flag = 1; break;
				    }
				}
				if (flag == 0)
			            follow[i][l++] = follow[n][p++];
				else
				    p++;
			    }
			}
		    }
		}
	    }
	    k++;
	}
    }
}

void parsingTable(char input[][20], char first[][20], char follow[][20], char table[][200]) {
    char first1[10], follow1[10];
    int i, j, k, l, d = 0, e = 1, f = 0, g = 1;
    for (k=0; k<20; k++) {
	for (i=0; i<10; i++)
	    first1[i] = '\0';
	d = 0; e = 1;
        if (input[k][0] == '\0')
	    break;
	if (((int)input[k][3]) <= 64 || ((int)input[k][3]) >= 91) {
	    first1[d++] = input[k][3];
	}
    	else {
            char b = input[k][3];
	    for (j=0; j<20; j++) {
		if (first[j][0] == '\0')
		    break;
		if (first[j][0] == b) {
	    	    while (first[j][e] != '\0') {
			first1[d++] = first[j][e++];
		    }
		}
	    }
	}
	d = 0;
	while (first1[d] != '\0') {
	    char b = first1[d];
	    char c = input[k][0];
	    e = 0;
	    for (i=10; i<100; i+=10) {
		if (table[0][i] == b) {
		    while (input[k][e] != '\0') {
			for (l=1; l<20; l++) {
			    if (table[l][0] == c) {
			        table[l][i+e] = input[k][e];
				e++;
			    }
			}
		    }
		}
	    }
	    d++;
	}
    }
    for (k=0; k<20; k++) {
	for (i=0; i<10; i++)
	    follow1[i] = '\0';
	f = 0; g = 1;
	int m = 1;
	if (input[k][0] == '\0')
	    break;
	if (input[k][3] == '@') {
	    char x = input[k][0];
	    for (i=0; i<20; i++) {
	        if (follow[i][0] == x) {
		    while (follow[i][g] != '\0') {
		        follow1[f++] = follow[i][g++];
		    }
		    break;
		}
	    }
	    f = 0;
	    while (follow1[f] != '\0') {
	        char b = follow1[f];
		char c = input[k][0];
		g = 0;
		for (i=10; i<100; i+=10) {
		    if(table[0][i] == b) {
			while (input[k][g] != '\0') {
			    for (l=1; l<20; l++) {
				if (table[l][0] == c) {
				    table[l][i+g] = input[k][g];
				    g++;
				}
			    }
			}
		    }
		}
		f++;
	    }
	}
    }
    for (i=0; i<20; i++) {
        for (j=0; j<100; j++) {
  	    if (table[i][j] == '\0')
	        table[i][j] = (char)32;
	}
    }
}
