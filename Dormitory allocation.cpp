#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
 
#define N sizeof(struct DORMITORY)
struct DORMITORY {
     int no;  //�����
     char id[15];      //ѧ��
     char name[10];    //����
     char sex[10];     //�Ա� 
     struct DORMITORY* next;//ָ����
 };

typedef struct DORMITORY* dormitory;

char set[16][15];//ѧ�ż��ϣ������ظ�
dormitory head;     //����ͷ�ڵ㣬����������ס�޼�¼�����㽨������ͷ�巨�� 

void menu();           //���˵�
void menu_query();  //��Ϣ��ѯ�˵� 
void direction();    //ʹ��˵��    
void checkIn();        //��ס      
void checkOut();       //�˷�      
void print();        //��ӡȫ����Ϣ 
void findAll();        //�鿴ȫ����Ϣ
void findById();       //��ѧ�Ų�ѯ 
void findByName();     //��������ѯ 
void findByno();      //������Ų�ѯ
void findBysex();     //���Ա��ѯ 
void del(dormitory node);    //ɾ��һ��ס�޼�¼ 
void destroy();                //��������       
int repeated(char id[15]);     //�ж�ѧ���Ƿ��ظ� 
dormitory create();         //����һ��ס�޼�¼ 

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
 
 void menu() { //���˵�
     char t;
    int flag = 1;
    while(flag) {
        system("cls");
        printf("+--------------------+\n");
        printf("|    �������ϵͳ    |\n");
        printf("+--------------------+\n");
        printf("|  ��1����ס ����    |\n");
        printf("|                    |\n");
        printf("|  ��2���˷� ����    |\n");
        printf("|                    |\n");
        printf("|  ��3����Ϣ ��ѯ    |\n");
        printf("|                    |\n");
        printf("|  ��4��ʹ�� ˵��    |\n");
        printf("|                    |\n");
        printf("|  ��5���˳� ϵͳ    |\n");
        printf("+--------------------+\n");
        t=getch();  
        switch(t) {
		             case '1':
                checkIn();     //��ס����
			                 break;
            case '2':
                checkOut();     //�˷�����
                break;
            case '3':
                menu_query();//��Ϣ��ѯ
                break;
            case '4':
                direction(); //ʹ��˵�� 
                break;
            case '5':
                printf("\n��л����ʹ�ã��ټ�");
                destroy(); 
                flag = 0;    
                break;
            default:
                break;
        }
    }
 }
 
void menu_query() { //��ѯ�˵�
    char t;
    int flag = 1;
    while(flag) {
        system("cls"); 
        printf("+---------------------+\n");
        printf("|      ��Ϣ ��ѯ      |\n");
        printf("+---------------------+\n");
        printf("|  ��1��ȫ��  ��ѯ    |\n");
        printf("|                     |\n");
        printf("|  ��2��ѧ��  ��ѯ    |\n");
        printf("|                     |\n");
        printf("|  ��3������  ��ѯ    |\n");
        printf("|                     |\n");
        printf("|  ��4������Ų�ѯ    |\n");
        printf("|                     |\n");
        printf("|  ��5���Ա�  ��ѯ    |\n");
        printf("+---------------------+\n");
        t=getch();  
        switch(t) {
            case '1':
                findAll();     //��ѯȫ��
                break;
            case '2':
                findById();     //��ѧ�Ų�ѯ
                break;
            case '3':
                findByName();//��������ѯ
                break;
            case '4':
                findByno(); //������Ų�ѯ
                break;
			case '5':
                findBysex(); //��ѯ
                break;
            case 27:
                flag = 0;     //�������˵�
                break;
            default:         //������������
                break;
        }
    }
}

int repeated(char id[15]){ //���ѧ���Ƿ��Ѿ����� 
    int i;
    for(i = 0; i < 16; ++i){
        if(!strcmp(id, set[i]))//���ѧ���Ѿ����ڣ�����1
            return 1;
    }
    return 0;
}

dormitory create() { //����һ����ס��Ϣ
    dormitory record = (dormitory)malloc(N);//����ռ� 
    //����ѧ��
    printf("������ѧ�ţ�\n");
    scanf("%s", record->id); 
    //����  
    if(repeated(record->id))
        return NULL;
    strcpy(set[16 - head->no], record->id);//�����ظ���ѧ�ż�¼��set���� 
    //��������
    printf("������������\n");  
    scanf("%s", record->name);
    //�����Ա� 
    printf("�������Ա�\n");  
    scanf("%s", record->sex);
    //ȷ��Ҫ����ķ���� 
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
     //ָ��ָ�� 
     record->next = NULL; 
     return record;
 }
 
 void del(dormitory node){ //ɾ��һ��ס�޼�¼
     int no = node->no, i = 0;
     dormitory m = node->next;
     dormitory p = head->next;
     //set���鱣���Ķ�Ӧѧ��ɾ��
     for(i = 0; i < 16; ++i){
         if(!strcmp(node->id, set[i])){//�ҵ�ѧ�ţ��ÿ� 
             strcpy(set[i], "\0");
             break; 
         }
     }
     //�Ѷ�Ӧ�ķ������޸�
     if(no == 101)
         head->id[0] += 1;
     else if(no == 102)
         head->id[1] += 1;
     else if(no == 201)
         head->id[2] += 1;
     else
         head->id[3] += 1;
     //ɾ����㣬�ͷſռ� 
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
             printf("ѧ���Ѵ��ڣ������½�����Ӳ�����");
             break;
         }
         printf("\n+--------------------+");
         printf("\n|    �Ƿ�������    |");
         printf("\n+--------------------+");
         printf("\n|��1����      ��2����|");
         printf("\n+--------------------+");
         t = getch();
         if(t == '1')
             continue;
         else
             break;
     }
     if(head->no == 0)
         printf("\n���᷿�������������޷�������ס��");
     printf("\n�����������˵�����"); 
     Sleep(1500);    
 }
 
 void checkOut() { 
     char id[15];
     int flag = 0; 
     dormitory p = head->next;
     system("cls"); 
     print(); 
     printf("������Ҫ���д˲�����ѧ��ѧ��(������󴥣�������escȷ�Ϸ���)��\n");
     scanf("%s", id);
     if(!strcmp(id, "esc\0")){
         p =NULL;
         flag = 1; 
     } 
     for(; p != NULL; p = p->next){
         if(!strcmp(p->id, id)){
             del(p);      
             head->no += 1;
             printf("�˷�����ɹ���"); 
             flag = 1;
         }
     } 
     if(!flag)
         printf("ѧ�Ų����ڣ�");
     printf("\n�����������˵�����"); 
     Sleep(1500); 
 }
 
 void direction() { 
     char t; 
     while(1){
         system("cls"); 
         printf("+------------------------------------------+\n");
         printf("|              ʹ  ��  ˵  ��              |\n");
         printf("+------------------------------------------+\n");
         printf("| 1. ÿ���������ж�Ӧ��'����'������ʾ      |\n");
         printf("|                                          |\n");
         printf("| 2. ����������ʾ����'ESC'��������һ���˵� |\n");
         printf("|                                          |\n");
         printf("| 3. Ԥף��ʹ����죡\n");
         printf("+------------------------------------------+\n");
         t = getch();
         if(t == 27)
             break;
     } 
 }
  
 void print() { //���ȫ�� 
     int i = 0; 
     dormitory p = head->next;
     system("cls"); 
     printf("+-----------------------------------+\n"); 
     printf("|            ס����Ϣ(ȫ)           |\n");
     printf("+-----------------------------------+\n");
     printf("| ����� |    ѧ��    | ���� | �Ա� |\n");
     printf("+-----------------------------------+\n");
     for(; p != NULL; p = p->next, ++i) 
     printf("|  %4d  | %11s | %6s | %2s  |\n", p->no, p->id, p->name,p->sex);
     printf("+-----------------------------------+\n");
     printf("|            ����%2d����Ϣ           |\n", i);    
     printf("+-----------------------------------+\n"); 
 }
 
 void findAll(){ 
     char t;
     print();
     while((t = getch()) != 27);
 } 
 
 void findById() { //��ѧ�Ų�ѯ 
     char t, id[15]; 
     int flag = 0; 
     dormitory p = head->next;
     system("cls"); 
     printf("������Ҫ��ѯ��ѧ��ѧ�ţ�\n");
     scanf("%s", id);
     printf("+-----------------------------------+\n"); 
     printf("|            ס����Ϣ               |\n");
     printf("+-----------------------------------+\n");
     printf("| ����� |    ѧ��    | ���� | �Ա� |\n");
     printf("+-----------------------------------+\n");
     for(; p != NULL; p = p->next){ 
         if(!strcmp(p->id, id)){
             flag = 1;
             printf("|  %4d  | %11s | %6s | %2s  |\n", p->no, p->id, p->name,p->sex);
         }
     }
     printf("+-----------------------------------+\n");
     if(!flag)
         printf("\nδ�ҵ������Ϣ");
     while((t = getch()) != 27);
 }
 
 void findByName() { //��������ѯ 
     char t, name[10]; 
     int flag = 0; 
     dormitory p = head->next;
     system("cls"); 
     printf("������Ҫ��ѯ��ѧ��������\n");
     scanf("%s", name);
     printf("+-----------------------------------+\n"); 
     printf("|            ס����Ϣ(��)           |\n");
     printf("+-----------------------------------+\n");
     printf("| ����� |    ѧ��    | ���� | �Ա� |\n");
     printf("+-----------------------------------+\n");
     for(; p != NULL; p = p->next){ 
         if(!strcmp(p->name, name)) {
             flag = 1;
             printf("|  %4d  | %11s | %6s | %2s  |\n", p->no, p->id, p->name,p->sex);
         }
     }
     printf("+-----------------------------------+\n");
     if(!flag)
         printf("\nδ�ҵ������Ϣ");
     while((t = getch()) != 27);
 }
 
 void findByno() { //������Ų�ѯ 
     char t;
     int no, i = 0;
     int flag = 0;
     dormitory p = head->next;
     system("cls"); 
     printf("������Ҫ��ѯ������ţ�\n");
     scanf("%d", &no);
     printf("+-----------------------------------+\n"); 
     printf("|            ס����Ϣ(��)           |\n");
     printf("+-----------------------------------+\n");
     printf("| ����� |    ѧ��    | ���� | �Ա� |\n");
     printf("+-----------------------------------+\n");
     for(; p != NULL; p = p->next){ 
         if(p->no == no){
             i += 1;
             printf("|  %4d  | %11s | %6s | %2s  |\n", p->no, p->id, p->name,p->sex);
         }
     }
     printf("+-----------------------------------+\n");
     printf("|            ����%2d����Ϣ           |\n", i);    
     printf("+-----------------------------------+\n"); 
    while((t = getch()) != 27);
}

void findBysex() { //���Ա��ѯ 
     char t, sex[10]; 
     int flag = 0; 
     dormitory p = head->next;
     system("cls"); 
     printf("������Ҫ��ѯ��ѧ���Ա�\n");
     scanf("%s", sex);
     printf("+-----------------------------------+\n"); 
     printf("|            ס����Ϣ(��)           |\n");
     printf("+-----------------------------------+\n");
     printf("| ����� |    ѧ��    | ���� | �Ա� |\n");
     printf("+-----------------------------------+\n");
     for(; p != NULL; p = p->next){ 
         if(!strcmp(p->sex, sex)) {
             flag = 1;
             printf("|  %4d  | %11s | %6s | %2s  |\n", p->no, p->id, p->name,p->sex);
         }
     }
     printf("+-----------------------------------+\n");
     if(!flag)
         printf("\nδ�ҵ������Ϣ");
     while((t = getch()) != 27);
}
