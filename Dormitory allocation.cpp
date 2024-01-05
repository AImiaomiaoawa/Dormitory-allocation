#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
 
#define N sizeof(struct DORMITORY)
struct DORMITORY {
     int no;  //房间号
     char id[15];      //学号
     char name[10];    //姓名
     char sex[10];     //性别 
     struct DORMITORY* next;//指针域
 };

typedef struct DORMITORY* dormitory;

char set[16][15];//学号集合，避免重复
dormitory head;     //链表头节点，不用来保存住宿记录，方便建立链表（头插法） 

void menu();           //主菜单
void menu_query();  //信息查询菜单 
void direction();    //使用说明    
void checkIn();        //入住      
void checkOut();       //退房      
void print();        //打印全部信息 
void findAll();        //查看全部信息
void findById();       //按学号查询 
void findByName();     //按姓名查询 
void findByno();      //按宿舍号查询
void findBysex();     //按性别查询 
void del(dormitory node);    //删除一条住宿记录 
void destroy();                //销毁链表       
int repeated(char id[15]);     //判断学号是否重复 
dormitory create();         //创建一条住宿记录 

int main() {
    head = (dormitory)malloc(N);
     head->no = 16; 
     head->id[0] = '4';
     head->id[1] = '4';
    head->id[2] = '4';
      head->id[3] = '4';
    head->next = NULL;
    menu();
      return 0;
 }
 
 void menu() { //主菜单
     char t;
    int flag = 1;
    while(flag) {
        system("cls");
        printf("+--------------------+\n");
        printf("|    宿舍管理系统    |\n");
        printf("+--------------------+\n");
        printf("|  【1】入住 管理    |\n");
        printf("|                    |\n");
        printf("|  【2】退房 管理    |\n");
        printf("|                    |\n");
        printf("|  【3】信息 查询    |\n");
        printf("|                    |\n");
        printf("|  【4】使用 说明    |\n");
        printf("|                    |\n");
        printf("|  【5】退出 系统    |\n");
        printf("+--------------------+\n");
        t=getch();  
        switch(t) {
		             case '1':
                checkIn();     //入住管理
			                 break;
            case '2':
                checkOut();     //退房管理
                break;
            case '3':
                menu_query();//信息查询
                break;
            case '4':
                direction(); //使用说明 
                break;
            case '5':
                printf("\n感谢您的使用，再见");
                destroy(); 
                flag = 0;    
                break;
            default:
                break;
        }
    }
 }
 
void menu_query() { //查询菜单
    char t;
    int flag = 1;
    while(flag) {
        system("cls"); 
        printf("+---------------------+\n");
        printf("|      信息 查询      |\n");
        printf("+---------------------+\n");
        printf("|  【1】全体  查询    |\n");
        printf("|                     |\n");
        printf("|  【2】学号  查询    |\n");
        printf("|                     |\n");
        printf("|  【3】姓名  查询    |\n");
        printf("|                     |\n");
        printf("|  【4】房间号查询    |\n");
        printf("|                     |\n");
        printf("|  【5】性别  查询    |\n");
        printf("+---------------------+\n");
        t=getch();  
        switch(t) {
            case '1':
                findAll();     //查询全部
                break;
            case '2':
                findById();     //按学号查询
                break;
            case '3':
                findByName();//按姓名查询
                break;
            case '4':
                findByno(); //按宿舍号查询
                break;
			case '5':
                findBysex(); //按询
                break;
            case 27:
                flag = 0;     //返回主菜单
                break;
            default:         //屏蔽其他输入
                break;
        }
    }
}

int repeated(char id[15]){ //检查学号是否已经存在 
    int i;
    for(i = 0; i < 16; ++i){
        if(!strcmp(id, set[i]))//如果学号已经存在，返回1
            return 1;
    }
    return 0;
}

dormitory create() { //创建一条入住信息
    dormitory record = (dormitory)malloc(N);//申请空间 
    //输入学号
    printf("请输入学号：\n");
    scanf("%s", record->id); 
    //判重  
    if(repeated(record->id))
        return NULL;
    strcpy(set[16 - head->no], record->id);//将不重复的学号记录在set数组 
    //输入姓名
    printf("请输入姓名：\n");  
    scanf("%s", record->name);
    //输入性别 
    printf("请输入性别：\n");  
    scanf("%s", record->sex);
    //确定要分配的房间号 
    if(head->id[0] > '0') {
        record->no = 101;
        head->id[0] -= 1; 
    } else if(head->id[1] > '0') {
        record->no = 102;
        head->id[1] -= 1;
    } else if(head->id[2] > '0') {
        record->no = 201;
        head->id[2] -= 1;
    } else {
        record->no = 202;
        head->id[3] -= 1;
    }
     //指针指向 
     record->next = NULL; 
     return record;
 }
 
 void del(dormitory node){ //删除一条住宿记录
     int no = node->no, i = 0;
     dormitory m = node->next;
     dormitory p = head->next;
     //set数组保留的对应学号删除
     for(i = 0; i < 16; ++i){
         if(!strcmp(node->id, set[i])){//找到学号，置空 
             strcpy(set[i], "\0");
             break; 
         }
     }
     //把对应的房间数修改
     if(no == 101)
         head->id[0] += 1;
     else if(no == 102)
         head->id[1] += 1;
     else if(no == 201)
         head->id[2] += 1;
     else
         head->id[3] += 1;
     //删除结点，释放空间 
     if(m != NULL){ 
        
         node->no = m->no;
         strcpy(node->id, m->id);
         strcpy(node->name, m->name);
         node->next = m->next;
         free(m);
     }else{
         m = head;
         for(; p != NULL; m = p, p = p->next)
             if(!strcmp(p->id, node->id))
                 break;
         m->next = NULL;
         free(p);
     }
 } 
 
 void destroy(){
     dormitory p = NULL;
     dormitory q = head;
     while(q != NULL) {
         p = q;        
         q = q->next;
         free(p);   
     }
 } 
 
 void checkIn() { 
     char t;
     while(head->no > 0) {
         system("cls");       
         dormitory node = create();
         if(node != NULL){ 
             head->no -= 1;             
             node->next = head->next; 
             head->next = node;            
         }else{ 
             printf("学号已存在，请重新进行添加操作！");
             break;
         }
         printf("\n+--------------------+");
         printf("\n|    是否继续添加    |");
         printf("\n+--------------------+");
         printf("\n|【1】是      【2】否|");
         printf("\n+--------------------+");
         t = getch();
         if(t == '1')
             continue;
         else
             break;
     }
     if(head->no == 0)
         printf("\n宿舍房间人数已满，无法继续入住！");
     printf("\n即将返回主菜单……"); 
     Sleep(1500);    
 }
 
 void checkOut() { 
     char id[15];
     int flag = 0; 
     dormitory p = head->next;
     system("cls"); 
     print(); 
     printf("请输入要进行此操作的学生学号(如果是误触，请输入esc确认返回)：\n");
     scanf("%s", id);
     if(!strcmp(id, "esc\0")){
         p =NULL;
         flag = 1; 
     } 
     for(; p != NULL; p = p->next){
         if(!strcmp(p->id, id)){
             del(p);      
             head->no += 1;
             printf("退房办理成功！"); 
             flag = 1;
         }
     } 
     if(!flag)
         printf("学号不存在！");
     printf("\n即将返回主菜单……"); 
     Sleep(1500); 
 }
 
 void direction() { 
     char t; 
     while(1){
         system("cls"); 
         printf("+------------------------------------------+\n");
         printf("|              使  用  说  明              |\n");
         printf("+------------------------------------------+\n");
         printf("| 1. 每个操作都有对应的'【】'按键提示      |\n");
         printf("|                                          |\n");
         printf("| 2. 如无特殊提示，按'ESC'键返回上一个菜单 |\n");
         printf("|                                          |\n");
         printf("| 3. 预祝您使用愉快！\n");
         printf("+------------------------------------------+\n");
         t = getch();
         if(t == 27)
             break;
     } 
 }
  
 void print() { //输出全部 
     int i = 0; 
     dormitory p = head->next;
     system("cls"); 
     printf("+-----------------------------------+\n"); 
     printf("|            住宿信息(全)           |\n");
     printf("+-----------------------------------+\n");
     printf("| 宿舍号 |    学号    | 姓名 | 性别 |\n");
     printf("+-----------------------------------+\n");
     for(; p != NULL; p = p->next, ++i) 
     printf("|  %4d  | %11s | %6s | %2s  |\n", p->no, p->id, p->name,p->sex);
     printf("+-----------------------------------+\n");
     printf("|            共有%2d条信息           |\n", i);    
     printf("+-----------------------------------+\n"); 
 }
 
 void findAll(){ 
     char t;
     print();
     while((t = getch()) != 27);
 } 
 
 void findById() { //按学号查询 
     char t, id[15]; 
     int flag = 0; 
     dormitory p = head->next;
     system("cls"); 
     printf("请输入要查询的学生学号：\n");
     scanf("%s", id);
     printf("+-----------------------------------+\n"); 
     printf("|            住宿信息               |\n");
     printf("+-----------------------------------+\n");
     printf("| 宿舍号 |    学号    | 姓名 | 性别 |\n");
     printf("+-----------------------------------+\n");
     for(; p != NULL; p = p->next){ 
         if(!strcmp(p->id, id)){
             flag = 1;
             printf("|  %4d  | %11s | %6s | %2s  |\n", p->no, p->id, p->name,p->sex);
         }
     }
     printf("+-----------------------------------+\n");
     if(!flag)
         printf("\n未找到相关信息");
     while((t = getch()) != 27);
 }
 
 void findByName() { //按姓名查询 
     char t, name[10]; 
     int flag = 0; 
     dormitory p = head->next;
     system("cls"); 
     printf("请输入要查询的学生姓名：\n");
     scanf("%s", name);
     printf("+-----------------------------------+\n"); 
     printf("|            住宿信息(名)           |\n");
     printf("+-----------------------------------+\n");
     printf("| 宿舍号 |    学号    | 姓名 | 性别 |\n");
     printf("+-----------------------------------+\n");
     for(; p != NULL; p = p->next){ 
         if(!strcmp(p->name, name)) {
             flag = 1;
             printf("|  %4d  | %11s | %6s | %2s  |\n", p->no, p->id, p->name,p->sex);
         }
     }
     printf("+-----------------------------------+\n");
     if(!flag)
         printf("\n未找到相关信息");
     while((t = getch()) != 27);
 }
 
 void findByno() { //按宿舍号查询 
     char t;
     int no, i = 0;
     int flag = 0;
     dormitory p = head->next;
     system("cls"); 
     printf("请输入要查询的宿舍号：\n");
     scanf("%d", &no);
     printf("+-----------------------------------+\n"); 
     printf("|            住宿信息(宿)           |\n");
     printf("+-----------------------------------+\n");
     printf("| 宿舍号 |    学号    | 姓名 | 性别 |\n");
     printf("+-----------------------------------+\n");
     for(; p != NULL; p = p->next){ 
         if(p->no == no){
             i += 1;
             printf("|  %4d  | %11s | %6s | %2s  |\n", p->no, p->id, p->name,p->sex);
         }
     }
     printf("+-----------------------------------+\n");
     printf("|            共有%2d条信息           |\n", i);    
     printf("+-----------------------------------+\n"); 
    while((t = getch()) != 27);
}

void findBysex() { //按性别查询 
     char t, sex[10]; 
     int flag = 0; 
     dormitory p = head->next;
     system("cls"); 
     printf("请输入要查询的学生性别：\n");
     scanf("%s", sex);
     printf("+-----------------------------------+\n"); 
     printf("|            住宿信息(性)           |\n");
     printf("+-----------------------------------+\n");
     printf("| 宿舍号 |    学号    | 姓名 | 性别 |\n");
     printf("+-----------------------------------+\n");
     for(; p != NULL; p = p->next){ 
         if(!strcmp(p->sex, sex)) {
             flag = 1;
             printf("|  %4d  | %11s | %6s | %2s  |\n", p->no, p->id, p->name,p->sex);
         }
     }
     printf("+-----------------------------------+\n");
     if(!flag)
         printf("\n未找到相关信息");
     while((t = getch()) != 27);
}
