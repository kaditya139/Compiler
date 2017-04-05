#include<stdio.h>
#include<string.h>

void tableConstructor(char[][20], char[][20]);
void stateConstructor(char[][20], char[][20], char[][20], int, int);
void stateConstructorRec(char[][20], char[][20], char[][20], int, int);
int isStateEqual(char[][20], char[][20]);
int isEqual(char[], char[]);
void fillState(char[][20], char[][20]);
void fillTable(int, int, char, char[][200]);
void fillTableReduce(int, int, char[][200], char[][20], char[]);
void fillReduce(int, int, char[][200]);
int isEqualReduce(char[], char[]);
void swap(char*,char*);

int main(){
	int i,j,k,l,m=0,count;
    char str[500];
    scanf("%[^\n]*c",str);
    int size=strlen(str);
    char input[20][20];
    for(i=0;i<20;i++){
        for(j=0;j<20;j++){
            input[i][j]='\0';
        }
    }
	printf("\n");
    j=3;l=1;count=0;
    for(i=0;i<size;i++){
        if(str[i]=='/'){
            input[l][0]=str[m];
            input[l][1]='-';input[l][2]='>';input[l][3]='.';
            int x=4;
            for(k=j;k<i;k++){
                input[l][x++]=str[k];
            }
            count++;l++;i++;j=i;
        }
        if(((int)str[i])==32){
            input[l][0]=str[m];
            input[l][1]='-';input[l][2]='>';input[l][3]='.';
            int x=4;
            for(k=j;k<i;k++)
                input[l][x++]=str[k];
            l++;count++;i++;j=i+3;m=i;
        }
    }
	char z=input[1][0];
	input[0][0]='Z';input[0][1]='-';input[0][2]='>';input[0][3]='.';input[0][4]=z;
	char production[20][20];
	for(i=1;i<20;i++){
		for(j=0;j<20;j++){
			production[i-1][j]=input[i][j];
		}
		for(j=4;j<20;j++){
			production[i-1][j-1]=production[i-1][j];
		}
	}

	char store[20][20][20];
	int sCount=0;
	i=0;j=0;
	while(input[i][0]!='\0'){
		j=0;
		while(input[i][j]!='\0'){
			store[0][i][j]=input[i][j];
			j++;
		}
		i++;
	}
	int arr[56];
    for(i=0;i<56;i++)
        arr[i]=0;
    for(i=0;i<size;i++){
        if(((int)str[i])>64 && ((int)str[i])<91)
			arr[((int)str[i])-64]=1;
        if(((int)str[i])>96 && ((int)str[i])<123)
			arr[((int)str[i])-70]=1;
        if(str[i]=='+')		arr[52]=1;
        if(str[i]=='*')		arr[53]=1;
		if(str[i]=='(')		arr[54]=1;
        if(str[i]==')')		arr[55]=1;
    }
	int ns=0;
	for(i=0;i<56;i++)
		ns+=arr[i];

	char symbol[ns];
	for(i=0;i<ns;i++)
		symbol[i]='\0';
	char table[20][200];
	for(i=0;i<20;i++){
		for(j=0;j<200;j++)
			table[i][j]='\0';
	}
	for(i=0;i<20;i++){
		int div=i/10,rem=i%10;
		table[i+1][0]=(char)(div+48);
		table[i+1][1]=(char)(rem+48);
	}
	k=1;
	int f=10;k=0;
	for(i=26;i<52;i++){
		if(arr[i]==1){
			table[0][f]=symbol[k++]=((char)(i+70));
			f+=10;
		}
	}
	if(arr[52]==1){
        table[0][f]=symbol[k++]='+';
		f+=10;
	}
    if(arr[53]==1){
        table[0][f]=symbol[k++]='*';
		f+=10;
	}
    if(arr[54]==1){
        table[0][f]=symbol[k++]='(';
		f+=10;
	}
    if(arr[55]==1){
        table[0][f]=symbol[k++]=')';
		f+=10;
	}
	table[0][f]='$';
	f+=10;
	for(i=0;i<26;i++){
		if(arr[i]==1){
			table[0][f]=symbol[k++]=((char)(i+64));
			f+=10;
		}
	}
	int limit=f-10;
	int null=0;
	for(i=0;i<=sCount;i++){
		char temp[20][20],extract[20][20];
		for(k=0;k<20;k++){
			for(l=0;l<20;l++)
				temp[k][l]=extract[k][l]='\0';
		}
		for(k=0;k<20;k++){
			for(l=0;l<20;l++){
				extract[k][l]=store[i][k][l];
			}
		}
		char searchArray[20];
		null=0;
		for(j=0;j<20;j++){
			searchArray[j]=extract[0][j];
		}
		if(extract[0][3]==production[0][0] && extract[0][4]=='.' && extract[0][5]=='\0')
			fillReduce((i+1),limit,table);

		for(j=0;j<ns;j++){
			for(k=0;k<20;k++){
				for(l=0;l<20;l++)
					temp[k][l]='\0';
			}
			char a=symbol[j];
			stateConstructor(temp,extract,input,a,0);
			if(temp[0][0]!='\0')
				null++;
			int flag=0;
			for(k=0;k<sCount;k++){
				if(isStateEqual(temp,store[k])){
					flag=1;break;
				}
				else if(temp[0][0]=='\0'){
					flag=2;break;
				}
				else{
					flag=0;
				}
			}
			if(flag==1){
				fillTable((i+1),k,a,table);
			}
			if(flag==0){
				sCount++;
				fillState(store[sCount],temp);
				fillTable((i+1),sCount,a,table);
			}
		}
		if(null==0){
			if(searchArray[3]==production[0][0])
				fillReduce((i+1),limit,table);
			else
				fillTableReduce((i+1),limit,table,production,searchArray);
		}
	}

	i=0;j=0;k=0;
	store[0][0][0]='Z';store[0][0][1]='-';
	store[3][0][0]='Z';store[3][0][1]='-';
	for(i=0;i<=sCount;i++){
		printf("Printing State number %d\n",i);
		j=0;
		while(store[i][j][0]!='\0'){
			printf("%s\t",store[i][j]);
			j++;
		}
		printf("\n");
	}

	for(i=0;i<20;i++){
		for(j=0;j<100;j++){
			if(table[i][j]=='\0')
				table[i][j]=(char)32;
		}
	}
	for(i=0;i<=sCount+1;i++)
		printf("%s\n",table[i]);

	return 0;
}

void stateConstructor(char temp[][20], char extract[][20], char input[][20], int search, int line){
	int i,j,k=0;
	for(i=0;i<20;i++){
		j=4;
		while(extract[i][j]!='\0'){
			if(extract[i][j]==search && extract[i][j-1]=='.'){
				k=0;
				while(extract[i][k]!='\0'){
					temp[line][k]=extract[i][k];
					k++;
				}
				swap(&temp[line][j],&temp[line][j-1]);
				line++;
				break;
			}
			j++;
		}
		if((int)extract[i][j+1]>64 && (int)extract[i][j+1]<91){
			char a=extract[i][j+1];
			stateConstructorRec(temp, extract, input, a, line);
		}
	}
}

void stateConstructorRec(char temp[][20], char extract[][20], char input[][20], int search, int line){
	int i,j,k,l;
	for(i=0;i<20;i++){
		if(input[i][0]=='\0')
			break;
		if(input[i][0]==search){
			j=0;
			while(input[i][j]!='\0'){
				temp[line][j]=input[i][j];
				j++;
			}
			line++;
			if(((int)input[i][4]>64 && (int)input[i][4]<91) && input[i][0]!=input[i][4]){
				char a=input[i][4];
				stateConstructorRec(temp, extract, input, a, line);
			}
		}
	}
}

int isStateEqual(char temp[][20], char store[][20]){
	int i,j;
	for(i=0;i<20;i++){
		int flag=0;
		for(j=0;j<20;j++){
			if(isEqual(temp[i],store[j])){
				flag=1;break;
			}
		}
		if(flag==0)
			return 0;
	}
	for(i=0;i<20;i++){
		int flag=0;
		for(j=0;j<20;j++){
			if(isEqual(store[i],temp[j])){
				flag=1;
			}
		}
		if(flag==0)
			return 0;
	}
	return 1;
}

int isEqual(char arr1[10],char arr2[10]){
	int i,j;
	for(i=0;i<10;i++){
		if(arr1[i]=='\0' && arr2[i]=='\0')
			break;
		if(arr1[i]!=arr2[i])
			return 0;
	}
	return 1;
}

void fillState(char store[][20], char temp[][20]){
	int i=0,j=0;
	while(temp[i][0]!='\0'){
		j=0;
		while(temp[i][j]!='\0'){
			store[i][j]=temp[i][j];
			j++;
		}
		i++;
	}
}

void fillTable(int row, int state, char search, char table[][200]){
	int i=10;
	int div=state/10,rem=state%10;
	for(i=10;i<200;i+=10){
		if(table[0][i]==search){
			break;
		}
	}
	if((int)search >64 && (int)search<91)
		table[row][i]='g';
	else
		table[row][i]='s';
	table[row][i+1]=(char)(div+48);table[row][i+2]=(char)(rem+48);
}

void fillTableReduce(int row, int limit, char table[][200], char production[][20], char searchArray[]){
	int i,j;
	for(j=0;j<20;j++){
		if(isEqualReduce(production[j],searchArray)){
			break;
		}
	}
	j++;
	int div=j/10,rem=j%10;
	for(i=10;i<=limit;i+=10){
		if((int)table[0][i]<65 || (int)table[0][i]>90){
			table[row][i]='r';table[row][i+1]=(char)(div+48);table[row][i+2]=(char)(rem+48);
		}
	}
}

void fillReduce(int row, int limit, char table[][200]){
	int i;
	for(i=0;i<=limit;i+=10){
		if(table[0][i]=='$'){
			table[row][i]='a';table[row][i+1]='c';table[row][i+2]='c';break;
		}
	}
}

int isEqualReduce(char arr1[10],char arr2[10]){
	int i,j;
	for(i=0;i<10;i++){
		if(arr1[i]=='\0' && arr2[i]=='\0')
			break;
		if(arr1[i]!=arr2[i]){
			if((arr1[i]=='.' && arr1[i+1]=='\0') || (arr2[i]=='.' && arr2[i+1]=='\0'));
			else
				return 0;
		}
	}
	return 1;
}

	

void swap(char *a, char *b){
	char temp=*a;
	*a=*b;
	*b=temp;
}


//	E->E+T/T T->T*F/F F->(E)/i
//	S->AA A->aA/b
//	0-0		1-5		2-4		3-1		4-3		5-2		6-8		7-6		8-7		9-11		10-9		11-10
