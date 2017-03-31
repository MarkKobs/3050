#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTable.h"

#define FRIEND_SIZE 1024

typedef struct person
{
    char name[100];

    char Friend[FRIEND_SIZE][100];

    int NumFriend;

} Person;

typedef struct relationship
{
    char Relation[100];
} Relationship;

static void free_Relationship(void* Relation)
{
    free(Relation);
}

static void free_Person(void* Per)
{
    free(Per);
}

static void showfriend(Person* p)
{
    int i = 0;
    for(i = 0;i < p->NumFriend ;i++)
        printf("%s ",p->Friend[i]);

}



int main()
{
    HashTable* ht = hash_table_new();
    if (NULL == ht) {
        return -1;
    }


    char q;
    char b[200];
    char c[100];
    char d[200];
    char e[200];
    char f[200];
    char g[200];

    while(1) {
        scanf("%c",&q);
        switch(q) {
        case 'P' :
            scanf("%30s",&b);
            strcat(b," +");

            Person* per = (Person*)malloc(sizeof(Person));
            strcpy(per->name,b);

            hash_table_put2(ht, per->name, per, free_Person);
            break;
        case 'F' :
            scanf("%30s",&b);
            scanf("%30s",&c);
            strcpy(f,b);
            strcat(f," +");
            Person* per3 = (Person*)hash_table_get(ht, f);
            strcpy(per3->Friend[per3->NumFriend],c);
            per3->NumFriend++;
            strcpy(g,c);
            strcat(g," +");
            Person * per4 = (Person*)hash_table_get(ht, g);
            strcpy(per4->Friend[per4->NumFriend],b);
            per4->NumFriend++;
            strcpy(d,b);
            strcpy(e,c);
            strcat(b," ");
            strcat(b,c);
            strcat(e," ");
            strcat(e,d);

            Person * per1 = (Person*)malloc(sizeof(Person));
            strcpy(per1->name,b);
            hash_table_put2(ht, per1->name, per1, free_Person);

            Person * per2 = (Person*)malloc(sizeof(Person));
            strcpy(per2->name,e);
            hash_table_put2(ht, per2->name, per2, free_Person);

            break ;

        case 'U':
            scanf("%30s",&b);
            scanf("%30s",&c);
            strcpy(d,b);
            strcpy(e,c);
            strcat(b," ");
            strcat(b,c);
            strcat(e," ");
            strcat(e,d);


            hash_table_rm(ht, b);
            hash_table_rm(ht, e);

            break;
        case 'L':
            scanf("%30s",&b);
            strcat(b," +");

            Person * perL = (Person*)hash_table_get(ht, b);
            showfriend(perL);

            break;
        case 'Q':
            scanf("%30s",&b);
            scanf("%30s",&c);
            strcat(b," ");
            strcat(b,c);

            if(NULL == (Person*)hash_table_get(ht, b)) 
            {
                printf("No\n");
            }else {
                printf("Yes\n");
            }
            break;
        case 'X' :

            hash_table_delete(ht);
            exit(0);

            break;


        }
    }
    // 向哈希表中加入多个学生结构体
    /*  for (int i = 0; i < 100; i++) {
        struct Student * stu = (struct Student*)malloc(sizeof(struct Student));
        stu->age = 18 + rand()%5;
        stu->score = 50.0f + rand() % 100;
        sprintf(stu->name, "同学%d", i);
        hash_table_put2(ht, stu->name, stu, free_student);
        }

    // 根据学生姓名查找学生结构
    for (int i = 0; i < 100; i++) {
    char name[32];
    sprintf(name, "同学%d", i);
    struct Student * stu = (struct Student*)hash_table_get(ht, name);
    show_student(stu);
    }
    */
    // 销毁哈希表实例
    return 0;
}
