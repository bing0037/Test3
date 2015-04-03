#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 34
#define MAX 100000
typedef struct {
	char  str[1000];
	int len;
	int offset;
} StringReader;

int** get ();                      
void getdist(char ch[],int** dist);
int getCityCode (char* cityName);
char* getCityName (int code);
void getData (int** dist);
int main (void){
	
	int** dist;
	char ch[10];
	dist= get ();				//得到文件数据
	
	printf("请输入起点城市：");
	scanf("%s",ch);
	getdist(ch,dist);			//得到遍历数据	
	return 0;
	
}


void getdist(char ch[],int** dist)
{
	int s[M],dingwei[M];
    int n,number,u;
    int i,j,k,min,distance=0;
	
	getData (dist);
	
	system("cls");

		n=getCityCode(ch);
		
    
	u=1;	
   number=n;

for(i=0;i<M;i++)
s[i]=0;
	for(j=0;j<M;j++)
	{
		for(i=0;i<M;i++)
		  {
        
			dingwei[i]=dist[number][i];
		  }
		  s[number]=1;        
      printf("%s->",getCityName(number));
											
			min=MAX;												
			for(k=0;k<M;k++)					
			{
			  if(s[k]==0&&min>dingwei[k])   
			  {
				min=dingwei[k];
				number=k;
			  }
			  if(u==M)
				  min=dingwei[n];
			 
			}
			u++;
							
			
			distance+=min;
			
			 
			
	}
	
	 printf("%s",getCityName(n));
	 printf("\n距离为:%d\n",distance);

}

char city[40][10];
int cityNum = 0;
FILE* file = fopen ("distance.txt","r");
StringReader sr ;
char buf[20];


int getLine (FILE* file,char* str){
	static int c;
	int count = 0;
	int ifeof = 0;
	if (c == EOF){
		return -1;
	}
	while ((c=fgetc(file)) != EOF){
		if (c == '\n'){
			str[count] = '\0';
			return 1;
		}
		
		str[count++] = c;
	}
	str[count] = '\0';
	return 1;
}

int getToken (StringReader* sr,char* buf){
	int in = 0;
	char ch;
	int c = sr->offset;
	int k = 0;
	if (c == sr->len){
		return -1;
	}
    for (;c<sr->len;++c,sr->offset++){
		    ch=sr->str[c];
			if (ch == '\t'||ch == ' '){
				if (in == 1){
					buf[k] = '\0';
					return 1;
				}		
			}
			else {
				if (in == 0){
					in = 1;
				}
				buf[k++] = ch;
			}
	}
	buf[k] = '\0';
	return 1;
}

void initStringReader (StringReader* sr){
	sr->len = strlen (sr->str);
	sr->offset = 0;
}

char* getCityName (int code){
	return city[code];
}

int getCityCode (char* cityName){
	for (int i = 0;i<cityNum;++i){
		if (strcmp(cityName,city[i]) == 0)
			return i;
	}
	return -1;
}

void getData (int** dist){
	while ((getLine (file,sr.str))!=-1){
		initStringReader (&sr);
		getToken (&sr,buf);
		int code = getCityCode (buf);
		for (int i=0;i<cityNum;++i){
			getToken(&sr,buf);
			dist[i][code] = atoi(buf);
		}
	}
}

int** get(){
	getLine (file,sr.str);
	initStringReader (&sr);
	int i;
	int count = 0;
	while ((i = getToken (&sr,buf))!=-1){
		cityNum ++;
		int len = strlen (buf);
		for (int a=0;a<len;++a){
			city[count][a] = buf[a];
		}
		city[count][a] = '\0';
		++count;
	}
	int** dist =(int** )malloc ((sizeof (int*))*cityNum);
	for (i=0;i<cityNum;++i){
		dist[i] = (int*)malloc ((sizeof (int))*cityNum);
	}
	getData (dist);

	return dist;
	
}



