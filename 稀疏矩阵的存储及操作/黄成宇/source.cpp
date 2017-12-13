#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct DataStruct{
	int row;
	int col;
	int data;
	struct DataStruct *hor_next;
	struct DataStruct *ver_next;
}Data;

typedef struct {
	int num_row;
	int num_col;
	int num_data;
	Data **row_first,**col_first;
}SparseMatrix;

void SparseMatrixInit(SparseMatrix* matrix){matrix->row_first=matrix->col_first=NULL;}
void SparseMatrixClear(SparseMatrix* matrix) {
	Data *head, *prev;
	for (int i = 0; i < matrix->num_row; i++) {
		head=matrix->row_first[i];
		prev=NULL;
		while(head!=NULL){
			prev=head;
			head=head->hor_next;
			free(prev);
		}
		free(head);
	}
	for(int i=0;i<matrix->num_row;i++)matrix->row_first[i]=NULL;
	for(int i=0;i<matrix->num_col;i++)matrix->col_first[i]=NULL;
}

void SparseMatrixInsert(SparseMatrix* matrix,int row,int col,int data){
	Data *tmp=(Data*)malloc(sizeof(Data));
	tmp->row=row;
	tmp->col=col;
	tmp->data=data;
	tmp->hor_next=tmp->ver_next=NULL;
	if(matrix->row_first[row]==NULL){
		matrix->row_first[row]=tmp;
	}
	else{
		Data *head=matrix->row_first[row],*prev=NULL;
		while(TRUE){
			if(col<head->col){
				if(prev==NULL){
					matrix->row_first[row]=tmp;
					tmp->hor_next=head;
				}
				else{
					prev->hor_next=tmp;
					tmp->hor_next=head;
				}
				break;
			}
			if(head->hor_next==NULL){
				head->hor_next=tmp;
				break;
			}
			else{
				prev=head;
				head=head->hor_next;
			}
		}
	}
	if(matrix->col_first[col]==NULL){
		matrix->col_first[col]=tmp;
	}
	else{
		Data *head=matrix->col_first[col],*prev=NULL;
		while(TRUE){
			if(row<head->row){
				if(prev==NULL){
					matrix->col_first[col]=tmp;
					tmp->ver_next=head;
				}
				else{
					prev->ver_next=tmp;
					tmp->ver_next=head;
				}
				break;
			}
			if(head->ver_next==NULL){
				head->ver_next=tmp;
				break;
			}
			else{
				prev=head;
				head=head->ver_next;
			}
		}
	}
}

void SparseMatrixRead(SparseMatrix* matrix){
	scanf("%d%d%d",&matrix->num_row,&matrix->num_col,&matrix->num_data);
	matrix->row_first=(Data**)malloc(matrix->num_row*sizeof(Data*));
	for(int i=0;i<matrix->num_row;i++)matrix->row_first[i]=NULL;
	matrix->col_first=(Data**)malloc(matrix->num_col*sizeof(Data*));
	for(int i=0;i<matrix->num_col;i++)matrix->col_first[i]=NULL;
	int row,col,data,NUM=matrix->num_data;
	for(int i=0;i<NUM;i++){
		scanf("%d%d%d",&row,&col,&data);
		if(data)SparseMatrixInsert(matrix,row,col,data);
		else matrix->num_data--;
	}
}

void SparseMatrixPrintT(SparseMatrix* matrix){
	Data* head;
	for(int i=0;i<matrix->num_col;i++){
		head=matrix->col_first[i];
		while(head!=NULL){
			printf("%d %d %d\n",head->col,head->row,head->data);
			head=head->ver_next;
		}
	}
}

void SparseMatrixPrintAPlusAT(SparseMatrix* matrix){
	Data *head_hor,*head_ver;
	int data;
	for(int i=0;i<matrix->num_row;i++){
		head_hor=matrix->row_first[i];
		head_ver=matrix->col_first[i];
		for(int j=0;j<matrix->num_col;j++){
			data=0;
			if(head_hor!=NULL&&head_hor->col==j){
				data+=head_hor->data;
				head_hor=head_hor->hor_next;
			}
			if(head_ver!=NULL&&head_ver->row==j){
				data+=head_ver->data;
				head_ver=head_ver->ver_next;
			}
			if(data){
				printf("%d %d %d\n",i,j,data);
			}
		}
	}
}

void SparseMatrixPrintAMultiAT(SparseMatrix* matrix){
	Data *head_i,*head_j;
	int data;
	for(int i=0;i<matrix->num_row;i++)
		for(int j=0;j<matrix->num_col;j++){
			data=0;
			head_i=matrix->row_first[i];
			head_j=matrix->row_first[j];
			if(head_i!=NULL&&head_j!=NULL){
				while(TRUE){
					while(head_j->col<head_i->col){
						if(head_j->hor_next==NULL)break;
						else head_j=head_j->hor_next;
					}
					if(head_i->col==head_j->col)data+=head_i->data*head_j->data;
					if(head_i->hor_next==NULL)break;
					else head_i=head_i->hor_next;
				}
				if(data)printf("%d %d %d\n",i,j,data);
			}
		}
}

int main(){
	SparseMatrix matrix;
	SparseMatrixInit(&matrix);
	SparseMatrixRead(&matrix);
	SparseMatrixPrintT(&matrix);
	SparseMatrixPrintAPlusAT(&matrix);
	SparseMatrixPrintAMultiAT(&matrix);
	SparseMatrixClear(&matrix);
	return 0;
}
