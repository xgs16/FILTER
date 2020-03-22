#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER_LEN 24

char ucBufferA[BUFFER_LEN]={0};
char ucBufferB[BUFFER_LEN] = {0};
char str1[BUFFER_LEN] ={0};
char str2[BUFFER_LEN] ={0};

void assgnment(long lSite,int ch);
int filter_ch(int src,char des);
int check_openflow();
int copy_src_to_des(FILE *src,FILE *des);


int main(int argc,char *argv[])
{
	int iTmp;
	long lSite = 0;
	long lCurSiteSrc = 0;
	long lNewCurSiteSrc = 0;
	int i=0;

	
	FILE *fpsrc = NULL;
	fpsrc = fopen("C:\\Users\\Administrator\\Desktop\\handshake.txt","r+");
	if(fpsrc == NULL)
	{
		printf("txt invalid\r\n");
		exit(1);
	}
	
	FILE *fpdes = NULL;
	fpdes = fopen("des.txt","w+");
	if(fpdes == NULL)
	{
		printf("txt creat failed\r\n");
		exit(1);
	}
	
	lCurSiteSrc = ftell(fpsrc); 
	
	while((iTmp = fgetc(fpsrc))!= EOF)
	{
		
	//	printf("iTmp:%c\r\n",iTmp);
		if((iTmp != '\n'))
		{
			assgnment(lSite,iTmp);
			lSite++;	
								
		}
		else
		{
			lNewCurSiteSrc = ftell(fpsrc);
		
			if(1)
			if(0 == check_openflow())
			{
			//	printf("fseek lSite:%ld\r\n",lSite);
				if(0 ==fseek(fpsrc,lCurSiteSrc-lNewCurSiteSrc,SEEK_CUR))
				{
				//	printf("fseek \r\n");
					if(0 == copy_src_to_des(fpsrc,fpdes))
					{
					//	printf("copy_src_to_des \r\n");
						return -1;	
					}
				
				}
				
			}
		
	//		printf("fseek lSite:%ld\r\n",lSite);
			lSite = 0;
			lCurSiteSrc = ftell(fpsrc); 
		//	printf("fseek iCurSiteSrc:%ld\r\n",lCurSiteSrc);
		}

	}
	printf("finsh\r\n");
	fclose(fpsrc);
	fclose(fpdes);
	return 0;
}

void assgnment(long lSite,int ch)
{
	int i =0;
	switch(lSite)
	{
		case 6:
			ucBufferA[0] = ch;
			ucBufferB[0] = ch;
		break;
		case 7:
			ucBufferA[1] = ch;
			ucBufferB[1] = ch;
		break;
		case 108:
			ucBufferA[2] = ch;
		break;
		case 109:
			ucBufferA[3] = ch;
		break;
		case 111:
			ucBufferA[4] = ch;
		break;
		case 112:
			ucBufferA[5] = ch;
		break;
		case 114:
			ucBufferB[2] = ch;
		break;
		case 115:
			ucBufferB[3] = ch;
		break;
		case 117:
			ucBufferB[4] = ch;
		break;
		case 119:
			ucBufferB[5] = ch;
		break;
		case 144:
			ucBufferA[6] = ch;
			ucBufferB[6] = ch;
		break;
		case 145:
			ucBufferA[7] = ch;
			ucBufferB[7] = ch;
		break;
		case 147:
			ucBufferA[8] = ch;
			ucBufferB[8] = ch;
		break;
		case 148:
			ucBufferA[9] = ch;
			ucBufferB[9] = ch;
			for(i=0;i<10;i++)
			{
				sprintf(str1+i,"%c",ucBufferA[i]);
				sprintf(str2+i,"%c",ucBufferA[i]);
				ucBufferA[i] = '0';
				ucBufferB[i] = '0';
			}
			sprintf(str1+10,"\0");
			sprintf(str1+10,"\0");
		break;
		default:
		break;
	}
}

int check_openflow()
{
	char str[BUFFER_LEN] = "1419e95018";
	printf("str1:%s,str2:%s\r\n",str1,str2);
	if((0 == !strcmp(str,str1))&&( 0 == !strcmp(str,str2)))
	{
		return -1;
	}
	else
	{
		printf("str1:%s,str2:%s\r\n",str1,str2);
		memset(str1,0,sizeof(str1));
		memset(str2,0,sizeof(str2));	
		return 0;
	}
//	printf("ucBufferA:%s,ucBufferB:%s\r\n",ucBufferA,ucBufferB);
	
}

int copy_src_to_des(FILE *src,FILE *des)
{
	int iSrc ;
	int iDes ;
	int state = 0;
	int iCount =0;
	int iCtr = 0;
	
	while((iSrc = fgetc(src)) != '\n')
	{

		if(iCtr< 6)
		{
			iCtr++;
		}
		else
		{
			if((iSrc == '|') || (iSrc == '+') || (iSrc == '-'))
			{
				iSrc = ' ';
			}
		
			state = fputc(iSrc,des);
			printf("state:%d\r\n",state);
			iCount++;
			if(EOF == state)
			{
				printf("end\r\n");
				return 1;
			}	
			fflush(des);
		}
	}
	fputc('\n',des);
	iCtr = 0;
	fflush(des);
	iCount++;
	return iCount;
}

int filter_ch(int src,char des)
{
	int iTmp = (char)src;

	if((iTmp == '|') || (iTmp == '+') || (iTmp == '-'))
	{
		des = (int)' ';
	}
	else
	{
		des = src;
	}
	return 0;
}


