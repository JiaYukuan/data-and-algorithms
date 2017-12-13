#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int x;
    int y;
}Point;
Point *point;

typedef struct node{
    struct node *left;
    struct node *right;
    Point* point; //point=NULL represents it's not a leaf
    int dimension; //0 represents x, 1 represents y
    int divide_val;
    int point_num;
}Node;

int Abs(int a){
    return a>0?a:-a;
}

int Max(int a,int b){
    return a>b?a:b;
}

void QSort(int *point_sub,int first,int last,int dimension){
    if(first>last)return;
    int i=first,j=last,key=point_sub[first];
    if(dimension){ 
        while(i<j){
            while(i<j&&point[point_sub[j]].y>=point[key].y)j--;
            point_sub[i]=point_sub[j];
            while(i<j&&point[point_sub[i]].y<=point[key].y)i++;
            point_sub[j]=point_sub[i];
        }
    }
    else{
        while(i<j){
            while(i<j&&point[point_sub[j]].x>=point[key].x)j--;
            point_sub[i]=point_sub[j];
            while(i<j&&point[point_sub[i]].x<=point[key].x)i++;
            point_sub[j]=point_sub[i];
        }
    }
    point_sub[i]=key;
    QSort(point_sub,first,i-1,dimension);
    QSort(point_sub,i+1,last,dimension);
}

Node* TreeConstruct(int *point_sub,int point_num,int dimension)
{   
    if(point_num==0)return NULL;
    else if(point_num==1){
        Node *leaf=(Node*)malloc(sizeof(Node));
        leaf->left=NULL;
        leaf->right=NULL;
        leaf->point=(Point*)malloc(sizeof(Point));
        leaf->point->x=point[point_sub[0]].x;
        leaf->point->y=point[point_sub[0]].y;
        leaf->dimension=dimension;
        if(dimension)leaf->divide_val=point[point_sub[0]].y;
        else leaf->divide_val=point[point_sub[0]].x;
        leaf->point_num=point_num;
        return leaf;
    }
    else{
        int *point_coordinate=(int*)malloc(point_num*sizeof(int));
        QSort(point_sub,0,point_num-1,dimension);
        Node *branch=(Node*)malloc(sizeof(Node));
        branch->point=NULL;
        branch->dimension=dimension;
        if(dimension)branch->divide_val=point[point_sub[point_num/2-1]].y;
        else branch->divide_val=point[point_sub[point_num/2-1]].x;
        branch->point_num=point_num;
        int point_num_left=point_num/2,point_num_right=point_num-point_num_left;
        int *point_sub_left=(int*)malloc(point_num_left*sizeof(int));
        int *point_sub_right=(int*)malloc(point_num_right*sizeof(int));
        for(int i=0;i<point_num_left;i++)point_sub_left[i]=point_sub[i];
        for(int i=0;i<point_num_right;i++)point_sub_right[i]=point_sub[point_num_left+i];
        branch->left=TreeConstruct(point_sub_left,point_num_left,!dimension);
        branch->right=TreeConstruct(point_sub_right,point_num_right,!dimension);
        free(point_sub_left);
        free(point_sub_right);
        return branch;
    }
}

void Free(Node* head){
    if(head->point!=NULL)free(head->point);
    if(head->left!=NULL)Free(head->left);
    if(head->right!=NULL)Free(head->right);
    free(head);
}

void Search(int* num,Point aim,int aim_distance,Node* head)
{
    if(head->point!=NULL){
        if(Max(Abs(aim.x-head->point->x),Abs(aim.y-head->point->y))<=aim_distance)(*num)++;
    }
    else{
        if(head->dimension)
            if(aim.y<=head->divide_val){
                Search(num,aim,aim_distance,head->left);
                if(Abs(aim.y-head->divide_val)<=aim_distance)Search(num,aim,aim_distance,head->right);
            }
            else{
                Search(num,aim,aim_distance,head->right);
                if(Abs(aim.y-head->divide_val)<=aim_distance)Search(num,aim,aim_distance,head->left);
            }
        else 
            if(aim.x<=head->divide_val){
                Search(num,aim,aim_distance,head->left);
                if(Abs(aim.x-head->divide_val)<=aim_distance)Search(num,aim,aim_distance,head->right);
            }
            else{
                Search(num,aim,aim_distance,head->right);
                if(Abs(aim.x-head->divide_val)<=aim_distance)Search(num,aim,aim_distance,head->left);
            }
    }
}

int main()
{
    int point_num,aim_num;
    scanf("%d %d",&point_num,&aim_num);
    point=(Point*)malloc(point_num*sizeof(Point));
    for(int i=0;i<point_num;i++)scanf("%d%d",&(point[i].x),&(point[i].y));
    Point *aim=(Point*)malloc(aim_num*sizeof(Point));
    int *aim_distance=(int*)malloc(aim_num*sizeof(int));
    for(int i=0;i<aim_num;i++)scanf("%d%d%d",&(aim[i].x),&(aim[i].y),aim_distance+i);
    int *point_sub=(int*)malloc(sizeof(int)*point_num);
    for(int i=0;i<point_num;i++)point_sub[i]=i;
    Node *parent=TreeConstruct(point_sub,point_num,0);
    free(point);
    point=NULL;
    free(point_sub);
    point_sub=NULL;
    for(int i=0;i<aim_num;i++){
        int num=0;
        Search(&num,aim[i],aim_distance[i],parent);
        printf("%d\n",num);
    }
    //free the memory
    free(aim);
    aim=NULL;
    Free(parent);
    return 0;
}
