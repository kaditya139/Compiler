#include<stdio.h>
#include<string.h>

int isEqual(int*,int*);
int isNullable(char[][2],int[][2],int,int);
int main(){
    char str[50];
    scanf("%s",str);
    int size=strlen(str);
    char table[size][2];
	int index[size][2];
    int i,j;
    table[size-1][0]='L';index[size-1][0]=size-1;index[size-1][1]=-1;table[size-1][1]='.';
    table[size-2][0]='R';index[size-2][0]=size-2;index[size-2][1]=size-1;table[size-2][1]='#';
    for(i=size-3;i>=0;i--){
        if(((int)str[i])>96 && ((int)str[i])<123){
            if(str[i+1]!='*'){
				if(i!=0){
		            if(str[i+3]!='*'){
		                table[i][0]='L';index[i][0]=i;index[i][1]=i+2;table[i][1]=str[i-1];
		            }
		            else{
		                table[i][0]='L';index[i][0]=i;index[i][1]=i+3;table[i][1]=str[i-1];
		            }
	                table[i-1][0]='R';index[i-1][0]=i-1;index[i-1][1]=i;table[i-1][1]=str[i];
				}
				else{
					if(str[i+3]!='*'){
		                table[i][0]='L';index[i][0]=i;index[i][1]=i+2;table[i][1]=str[i];
		            }
		            else{
		                table[i][0]='L';index[i][0]=i;index[i][1]=i+3;table[i][1]=str[i];
		            }
				}
            }
            else{
                table[i+1][0]='L';index[i+1][0]=i+1;index[i+1][1]=i+3;table[i+1][1]=str[i-1];
				if(i!=0){
	                table[i][0]='R';index[i][0]=i;index[i][1]=i+1;table[i][1]=str[i+1];
    	            table[i-1][0]='L';index[i-1][0]=i-1;index[i-1][1]=i;table[i-1][1]=str[i];
				}
				else{
					table[i+1][0]='L';index[i+1][0]=i+1;index[i+1][1]=i+3;table[i+1][1]=str[i+1];
					table[i][0]='L';index[i][0]=i;index[i][1]=i+1;table[i][1]=str[i];
				}
            }
        }
    }
	for(i=0;i<size;i++)
        printf("%d\t%d\t%c\t%c\n",index[i][0],index[i][1],table[i][0],table[i][1]);

	int first[size][11],last[size][11];
	for(i=0;i<size;i++){
		for(j=0;j<11;j++)
			first[i][j]=last[i][j]=0;
	}
	
	int count=0;
	for(i=0;i<size;i++){
		if((((int)table[i][1])>96 && ((int)table[i][1])<123) || table[i][1]=='#'){
			first[i][first[i][10]++]=last[i][last[i][10]++]=++count;
		}
	}
	for(i=0;i<size;i++){
		if(table[i][1]=='*' || table[i][1]=='|' || table[i][1]=='.'){
			if(table[i][1]=='*'){
				for(j=0;j<size;j++){
					if(index[j][1]==i){
						int k;
						for(k=0;k<11;k++){
							first[i][k]=first[j][k];
							last[i][k]=last[j][k];
						}
						break;
					}
				}
			}
			if(table[i][1]=='|'){
				for(j=0;j<size;j++){
					if(index[j][1]==i && table[j][0]=='L'){
						int k;
						for(k=0;k<11;k++){
							first[i][k]=first[j][k];
							last[i][k]=last[j][k];
						}
					}
				}
				for(j=0;j<size;j++){
					if(index[j][1]==i && table[j][0]=='R'){
						int k=0;
						while(first[j][k]!=0){
							first[i][first[i][10]++]=first[j][k];
							k++;
						}
						k=0;
						while(last[j][k]!=0){
							last[i][last[i][10]++]=last[j][k];
							k++;
						}
					}
				}
			}
			if(table[i][1]=='.'){
				int p= isNullable(table,index,i,size);
				//printf("Nullable %d\n",p);
				if(p){
					for(j=0;j<size;j++){
						if(index[j][1]==i && table[j][0]=='L'){
							int k;
							for(k=0;k<11;k++){
								first[i][k]=first[j][k];
								last[i][k]=last[j][k];
							}
						}
					}
					for(j=0;j<size;j++){
						if(index[j][1]==i && table[j][0]=='R'){
							int k=0;
							while(first[j][k]!=0){
								first[i][first[i][10]++]=first[j][k];
								k++;
							}
							k=0;
							while(last[j][k]!=0){
								last[i][last[i][10]++]=last[j][k];
								k++;
							}
						}
					}
				}
				else{
					for(j=0;j<size;j++){
						if(index[j][1]==i && table[j][0]=='L'){
							int k;
							for(k=0;k<11;k++){
								first[i][k]=first[j][k];
							}
							break;
						}
					}
					for(j=0;j<size;j++){
						if(index[j][1]==i && table[j][0]=='R'){
							int k;
							for(k=0;k<11;k++){
								last[i][k]=last[j][k];
							}
							break;
						}
					}
				}
			}
		}
	}


	/*for(i=0;i<size;i++){
		for(j=0;j<11;j++)
			printf("%d  ",first[i][j]);
		printf("\t");
		for(j=0;j<11;j++)
			printf("%d  ",last[i][j]);
		printf("\n");
	}*/
	int follow[6][11];
	for(i=0;i<6;i++){
		for(j=0;j<11;j++)
			follow[i][j]=0;
	}
	for(i=0;i<size;i++){
		if(table[i][1]=='*'){
			int pos1=0,pos2;
			while(last[i][pos1]!=0){
				pos2=0;
				while(first[i][pos2]!=0){
					int k,l=first[i][pos2++],flag=0;
					for(k=0;k<follow[last[i][pos1]-1][9];k++){
						if(follow[last[i][pos1]-1][k]==l){
							flag=1;break;
						}
					}
					if(flag==0)
						follow[last[i][pos1]-1][follow[last[i][pos1]-1][10]++]=l;
				}
				pos1++;
			}
		}
	}
	for(i=0;i<size;i++){
		if(table[i][1]=='.'){
			int pos3=i,pos4,pos5,pos6,pos7;
			for(j=0;j<size;j++){
				if(index[j][1]==pos3 && table[j][0]=='L'){
					pos4=j;break;
				}
			}
			for(j=0;j<size;j++){
				if(index[j][1]==pos3 && table[j][0]=='R'){
					pos5=j;break;
				}
			}
			pos6=0;
			while(last[pos4][pos6]!=0){
				pos7=0;
				while(first[pos5][pos7]!=0){
					int k,l=first[pos5][pos7++],flag=0;
					for(k=0;k<follow[last[pos4][pos6]-1][9];k++){
						if(follow[last[pos4][pos6]-1][k]==l){
							flag=1;break;
						}
					}
					if(flag==0)
						follow[last[pos4][pos6]-1][follow[last[pos4][pos6]-1][10]++]=l;
				}
				pos6++;
			}
		}
	}
	printf("\n");
	for(i=0;i<6;i++){
		for(j=0;j<11;j++)
			printf("%d  ",follow[i][j]);
		printf("\n");
	}
	int arr[26];
	count=0;
	for(i=0;i<26;i++)
		arr[i]=0;
	for(i=0;i<size;i++){
		if(((int)str[i])>96 && ((int)str[i])<123)
			arr[((int)str[i])-97]=1;
	}
	for(i=0;i<26;i++)
		count+=arr[i];
	int index1[count][11];
	for(i=0;i<count;i++){
		for(j=0;j<11;j++)
			index1[i][j]=0;
	}
	char table1[count][1];
	for(i=0;i<count;i++)
		table1[i][0]=(char)(97+i);
	int count1=0;
	for(i=0;i<size;i++){
		if(((int)str[i])>96 && ((int)str[i])<123){
			index1[((int)str[i])-97][index1[((int)str[i])-97][10]++]=++count1;
		}
	}
	/*for(i=0;i<count;i++){
		printf("%c\t",table1[i][0]);
		for(j=0;j<11;j++)
			printf("%d  ",index1[i][j]);
		printf("\n");
	}*/

	int dfaTable[20][10];
	for(i=0;i<20;i++){
		for(j=0;j<10;j++)
			dfaTable[i][j]=-1;
	}
	for(i=0;i<10;i++)
		dfaTable[0][i]=first[size-1][i];
	int pos1=1;
	for(i=0;i<=pos1;i++){
		for(j=0;j<count;j++){
			int k,l,x=1,temp[10],s=0,flag1=0;
			for(k=0;k<10;k++)
				temp[k]=0;	
			for(k=0;k<10;k++){
				if(dfaTable[i][k]==0)
					break;
				for(l=0;l<10;l++){
					if(index1[j][l]==0)
						break;
					if(dfaTable[i][k]==index1[j][l]){
						flag1=1;
						int p,q,r;
						int m=dfaTable[i][k];
						for(p=0;p<follow[m-1][10];p++){
							int flag=0;
							q=follow[m-1][p];
							for(r=0;r<10;r++){
								if(temp[r]==q){
									flag=1;break;
								}
							}
							if(flag==0)
								temp[s++]=q;
						}
					}
				}
			}
			if(flag1==1){
				int p,flag=0;
				for(k=0;k<20;k++){
					p=isEqual(temp,dfaTable[k]);
					if(p){
						flag=1;break;
					}
				}
				if(flag==1)
					printf("move (s%d, %c) -> s%d\n",i,table1[j][0],k);
				else{
					for(k=0;k<10;k++){
						dfaTable[pos1][k]=temp[k];
					}
					printf("move (s%d, %c) -> s%d\n",i,table1[j][0],pos1);
					pos1++;
				}
			}
		}
	}

	for(i=0;i<pos1;i++){
		for(j=0;j<10;j++)
			printf("%d  ",dfaTable[i][j]);
		printf("\n");
	}
}

int isNullable(char table[][2], int index[][2], int i, int size){
	int j,k;
	for(j=0;j<size;j++){
		if(index[j][1]==i && table[j][1]=='*'){
			return 1;
		}
		if(index[j][1]==i && table[j][1]=='|'){
			i=j;j=0;
		}
	}
	return 0;
}	

int isEqual(int arr1[10],int arr2[10]){
	int i,j;
	for(i=0;i<10;i++){
		int flag=0;
		for(j=0;j<10;j++){
			if(arr1[i]==arr2[j]){
				flag=1;break;
			}
		}
		if(flag==0)
			return 0;
	}
	for(i=0;i<10;i++){
		int flag=0;
		for(j=0;j<10;j++){
			if(arr2[i]==arr1[j]){
				flag=1;break;
			}
		}
		if(flag==0)
			return 0;
	}
	return 1;
}
