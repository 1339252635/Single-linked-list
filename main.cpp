#include<stdio.h>
#include<stdlib.h>
#include<string.h>
    typedef struct  XscjNode{
        char NO[20];
        char Name[20];
        char Mtel[20];
        char Email[20];
        char BornAddr[10];
        float AScore;
        float BScore;
        struct  XscjNode *next;
}XscjList,*XscjLink;
void Build(XscjLink &T){
    T=(XscjLink )malloc(sizeof(XscjList));
    T->next=NULL;
    XscjLink y,p;
    y=T;
     FILE *fp;
     char a[25];
     printf("请输入要打开的文件:\n");
     scanf("%s",a);
    fp=fopen(a,"r");
     if((fp=fopen(a,"r"))==NULL)
    {
        printf("The file can not be opened.\n");
        exit(0);
        }
    while(!feof(fp)){
        p=(struct XscjNode*)malloc(sizeof(XscjList));
        p->next=y->next;
        y->next=p;
        y=p;
        fscanf(fp,"%s %s %s %s %s %f %f", p->NO, p->Name, p->Mtel,p->Email,p->BornAddr, &p->AScore, &p->BScore);
        //printf("%s %s %s %s %s %f %f\n", p->NO, p->Name, p->Mtel, p->Email, p-> BornAddr, p->AScore, p->BScore);//测试题目二
        }
    fclose(fp);
}
void Update(XscjLink T, char *Name, float *ScoreA){
    XscjLink p;
    p=T->next;
    while(p){
    if(strcmp(p->Name,Name)==0)
        p->AScore=*ScoreA;
    p=p->next;
    }

}
void OutPut(XscjLink T){
    XscjLink p;
    p=T->next;
    while(p){
      printf("%s %s %s %s %s %f %f\n", p->NO, p->Name, p->Mtel, p->Email, p-> BornAddr, p->AScore, p->BScore);
      p=p->next;
    }
}
void Insert(XscjLink T, char *Name, char *No){
     XscjLink q,x,y,h,p,r,m;
     h=(XscjLink )malloc(sizeof(XscjList));
     h->next=NULL;
     p=(XscjLink )malloc(sizeof(XscjList));
     p->next=NULL;
     strcpy(p->NO,No);
     strcpy(p->Name,Name);
     q=T->next;
     x=h;y=p;
     h->next=p;
     while(q){
            r=q->next;
        if(strcmp(q->NO,p->NO)<=0){
            x->next=q;
            q->next=p;
            x=x->next;
        }
        else{
            y->next=q;
            y=y->next;
            y->next=NULL;
        }
        q=r;
     }
     m=h->next;
     T->next=m;
     h->next=NULL;
     free(h);
     printf("插入后的名单：\n");
}
void Sort(XscjLink T){
    XscjLink q,p,h,m,n,x,y;
    p=T->next;
    m=p,h=p,q=T;
    n=p->next;
    p->next=NULL;
    p=n;
    while(p){
            n=p->next;
        if(p->BScore>=m->BScore){
            m->next=p;
            p->next=NULL;
            m=m->next;
        }
        if(p->BScore<h->BScore){
            q->next=p;
            p->next=h;
            h=p;
        }
        if(p->BScore>h->BScore&&p->BScore<m->BScore){
            for(x=h->next,y=h;x!=NULL;y=y->next,x=x->next){
                if(p->BScore<x->BScore){
                    y->next=p;
                    p->next=x;
                }
            }
        }
        p=n;
    }
}
void Merge(XscjLink &T1, XscjLink &T2){
    Build(T1);
    Sort(T1);
    Build(T2);
    Sort(T2);
	printf("\n");
XscjLink p1,p2,q1,q2;
p1=T1->next;
p2=T2->next;
T1->next=NULL;
while(p1&&p2){

    if(p1->BScore<p2->BScore){
        q1=p1->next;
        p1->next=T1->next;
        T1->next=p1;
        p1=q1;
    }
	else if((p1->BScore==p2->BScore)&&(strcmp(p1->NO,p2->NO)==0)){
	   p2=p2->next;
    }
     else{
       q2=p2->next;
       p2->next=T1->next;
       T1->next=p2;
       p2=q2;
    }
}
while(p1){
    q1=p1->next;
    p1->next=T1->next;
    T1->next=p1;
    p1=q1;
}
while(p2){
    q2=p2->next;
    p2->next=T1->next;
    T1->next=p2;
    p2=q2;
}
OutPut(T1);
}
int Count(XscjLink T){
	XscjLink p;
	int num=0;
	p=T->next;
	while(p){
		if(strcmp(p->BornAddr,"广州")==0){
			num++;
		}
		p=p->next;
	}
	printf("该名单里籍贯是广州的人数为：");
	printf("%d\n",num);
	return 0;
}
void MoveK(XscjLink T, int k){
	XscjLink p,q,m,n,t;
	int i=0;
	m=T->next;
	n=T;
	p=T->next;
	q=T->next;
	t=T;
	while(p){
		if(i>=k){
		q=q->next;
		n=n->next;
		}
		p=p->next;
		t=t->next;
		i++;
	}
	T->next=q;
	n->next=NULL;
	t->next=m;
}
void ReverseN(XscjLink T){
    XscjLink p,q,t,m,n;
	p=T->next;
	q=T->next;
	while(p->next){
        p=p->next;
        if(p->next){
                p=p->next;
                q=q->next;
        }
	}
    t=q->next;
    m=t->next;
    n=m;
    q->next=p;
t->next=NULL;
    while(n){
        n=n->next;
        m->next=t;
        t=m;
        m=n;
    }
}
int main(){
    XscjLink T,x;
    int i,k;
    printf("请输入要执行的函数序号:\n1：构建学生成绩链表\n2：将姓名为Name的学生的A分成绩改为score\n3：输出学生成绩信息\n4：插入学号为NO，姓名为Name学生信息，将链表中学号小于NO的结点放到该结点前面，大于NO的结点放到后面\n5：将学生按照B分成绩非递减排序\n6：将两个按B分非递减排序的学生成绩单合并为一个按B分非递增排序，去掉相同结点\n7：统计籍贯是广州的学生人数\n8：将学生成绩单倒数第k个结点后的所有结点移到头结点后面\n9：将学生成绩链表正中间结点之后的全部结点倒置\n0：结束程序\n");
	for(int j;j<100;j++){
		scanf("%d",&i);
    switch(i){
    case 0:
		exit(0);
    case 1:
        Build(T);
        break;
    case 2:
        float q;char p[20];
        Build(T);
        printf("请分别输入要更改AScore学生的姓名和分数(以空格分隔)：\n");
        scanf("%s %f",p,&q);
        Update(T,p,&q);
        x=T->next;
             OutPut(T);
        break;
	case 3:
		Build(T);
		OutPut(T);
		break;
    case 4:
        char m[20];char n[20];
        Build(T);
        printf("请输入要插入学生的学号和姓名：\n");
        scanf("%s %s",m,n);
        Insert(T,n,m);
        OutPut(T);
        break;
    case 5:
        Build(T);
        Sort(T);
        OutPut(T);
        break;
    case 6:
        XscjLink T1,T2;
        Merge(T1,T2);
        break;
    case 7:
        Build(T);
        Count(T);
        break;
    case 8:
        Build(T);
        printf("请输入k值：\n");
        scanf("%d",&k);
        MoveK(T,k);
        OutPut(T);
        break;
    case 9:
        Build(T);
        ReverseN(T);
        OutPut(T);
        break;
    }
	}
	return 0;
}
