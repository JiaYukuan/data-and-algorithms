#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define MAX_LENGTH 1000
#define MAX(a,b) (((a)>(b))?(a):(b))  //use macro to define a MAX operate

typedef struct
{
	char num[MAX_LENGTH];	//use char type to store a number
	int length;
}LongNumber;

void LongNumberRead(LongNumber *pointer_num){
	pointer_num->length=0;
	char num_tmp;
	while(TRUE){
		num_tmp=getchar();
		if(num_tmp>47&&num_tmp<58)pointer_num->num[pointer_num->length++]=num_tmp;
		else break;
	}
}

void LongNumberPrint(LongNumber pointer_num){
	for(int i=0;i<pointer_num.length;i++)putchar(pointer_num.num[i]);
}

void LongNumberInverted(LongNumber num_input,LongNumber *num_inverted_point){
	num_inverted_point->length=num_input.length;
	for(int i=0;i<num_input.length;i++){
		num_inverted_point->num[i]=num_input.num[num_input.length-i-1];
	}
}

LongNumber LongNumberPlus(LongNumber A,LongNumber B){
	int max_length=MAX(A.length,B.length);
	LongNumber num_result;
	num_result.length=max_length;	//temporarily assume no carry at the highest number
	int carry_bit=0,num_tmp;
	for(int i=0;i<max_length;i++){
		//below judge to avoid array out of bound
		if(A.length-i>0&&B.length-i>0)num_tmp=A.num[A.length-1-i]-48+B.num[B.length-1-i]-48+carry_bit;
		else if(A.length-i>0)num_tmp=A.num[A.length-1-i]-48+carry_bit;
		else num_tmp=B.num[B.length-1-i]-48+carry_bit;
		//below deal with carry bit
		if(num_tmp<10){
			num_result.num[max_length-1-i]=num_tmp+48;
			carry_bit=0;
		}
		else{
			num_result.num[max_length-1-i]=num_tmp+48-10;
			carry_bit=1;
		}
	}
	//deal with carry at the highest number
	if(carry_bit){
		for(int i=max_length;i>0;i--)num_result.num[i]=num_result.num[i-1];
		num_result.length++;
		num_result.num[0]=49;
	}
	return num_result;
}


int main(){
	LongNumber A,B;
	LongNumberRead(&A);
	LongNumberRead(&B);
	LongNumberPrint(LongNumberPlus(A,B));
	return 0;
}
