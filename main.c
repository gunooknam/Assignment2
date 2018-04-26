#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

struct stat stat1, stat2;
struct tm time1, time2;
int errno=1;

void filestat1(void);
void filestat2(void);
void filetime1(void);
void filetime2(void);
void sizecmp(void);
void blockcmp(void);
void datecmp(void);
void timecmp(void);
void errorcheck();

int main(void)
{
	filestat1();
	filestat2();
	errorcheck();
	filetime1();
	filetime2();
	sizecmp();
	blockcmp();
	datecmp();
	timecmp();
}

//파일 존재하지 않을 경우 예외처리를 출력
void errorcheck(){
	switch(errno){
		case 2:
			perror("text1 ");
			exit(0);
		case 4: 
			perror("text2 ");
			exit(0);
		case 8: 
			perror("text1 and text2 ");
			exit(0);
	}
}

//파일 1의 정보를 가져오는 함수 작성
void filestat1(void)
{
	if(stat("text1", &stat1)){
		errno=errno<<1;
	}
	/*
	else{
		printf("size : %d \n", (int)stat1.st_size);
		printf("size : %d \n", (int)stat1.st_block);
	}
	*/ 


}
//파일 2의 정보를 가져오는 함수 작성
void filestat2(void)
{
	if(stat("text2", &stat2)){
		errno=errno<<2;
	}
}


//파일 1의 시간 정보를 가져오는 함수 작성
void filetime1(void)
{
	time1=*localtime(&stat1.st_mtime);// stat구조체의 st_mtime:파일의 마지막 수정시간
	 
}

//파일 2의 시간 정보를 가져오는 함수 작성
void filetime2(void)
{
	time2=*localtime(&stat2.st_mtime);// stat구조체의 st_mtime:파일의 마지막 수정시간
}

//두 개의 파일 크기를 비교하는 함수 작성
void sizecmp(void)
{
	printf("size compare\n");
	if ( stat1.st_size > stat2.st_size ) 
		printf("text1 is bigger\n\n");
	else if (stat1.st_size < stat2.st_size ) 
		printf("text2 is bigger\n\n");
	else 
		printf("sizes are equal\n\n");
}

//두 개의 파일 블락 수를 비교하는 함수 작성
void blockcmp(void)
{
	printf("block compare\n");
	if (stat1.st_blocks > stat2.st_blocks) 
		printf("text1 is bigger\n\n");
	else if(stat1.st_blocks < stat2.st_blocks) 
		printf("text2 is bigger\n\n");
	else
		printf("sizes are equal\n\n");
}

//두 개의 파일 수정 날짜를 비교하는 함수 작성
void datecmp(void)
{
	printf("date compare\n");  
	if(time1.tm_mon+1 > time2.tm_mon+1)
		printf("text2 is early\n\n");
	else if(time1.tm_mon+1 < time2.tm_mon+1)
		printf("text1 is early\n\n");
	else {
		(time1.tm_mday > time2.tm_mday)? printf("text2 is early\n\n"): ( (time1.tm_mday <time2.tm_mday)? printf("text1 is early\n\n"):printf("same date\n\n") );  
	}
}

//두 개의 파일 수정 시간을 비교하는 함수 작성
void timecmp(void)
{
	printf("time compare\n");
	if(time1.tm_hour > time2.tm_hour)
		printf("text2 is early\n\n");
	else if((int)time1.tm_hour < (int)time2.tm_hour)
		printf("text1 is early\n\n");    
	else {
		(time1.tm_min > time2.tm_min)? printf("text2 is early\n\n"): ( (time1.tm_min <time2.tm_min)? printf("text1 is early\n\n"):printf("same time\n\n") );  
	}  
}
