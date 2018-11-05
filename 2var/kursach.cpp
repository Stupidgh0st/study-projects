#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>   

struct Bank {double number, pasport ;
			 char vklad [10]; double cash ; 
			 int day, month, year;};
			 
			 
typedef Bank DataType;

struct list
{
			 DataType data;
			 list * next;
};

typedef  list * List;

DataType input_dannie (void); 
List add (List, DataType);
void show (List);
void redact (List);
List del (List);
void search_list(List);
void Year (List); 
List read_file (List); 
void write_file (List); 
void delete_list (List); 
 
 
int main (void){
	setlocale(LC_ALL, "rus");
	char menu;
	int kol, i, n;
	List  clients= NULL;
	do
	{
	system("CLS");
	puts("               ����:");
	puts("(�������� � ������� ������ ����� ����)");
	puts ("1. ���������� ����� �������� � ���� ������ �����");
	puts ("2. �������� ���� ������ �����");
	puts ("3. ������������� ���� ������ �����");
	puts ("4. �������� ������� �� ���� ������ �����");
	puts ("5. ����� ������� �����");
	puts ("6. �������� ������, �������� �� ������� �� ����������� � ������� 5 ���");
	puts ("7. ��������� ���� ������");
	puts ("8. ��������� ���� ������");
	puts ("9. �����");
	menu = getchar();
	switch (menu)
	{
	case '1': system("CLS");
	puts("������� ���������� ��������:");
	scanf("%d",&kol);
	for(i=0;i<kol;i++) 
	clients = add (clients, input_dannie()); break;
	case '2': show (clients);
	system ("pause");
	break;
	case '3': redact (clients); break;
	case '4': clients = del (clients); break;
	case '5': search_list(clients); break;
	case '6': Year (clients); break;						
    case '7': clients = read_file (clients); break;
	case '8': write_file (clients); break;
	case '9': delete_list (clients); break;
	}
	}
	while (menu!='9');
	return 0;
}


DataType input_dannie (void){
	DataType client;
	printf ("\n����� ������:");
		scanf("%lf",&client.number);	
	printf("\n���������� ������:");
		scanf("%lf",&client.pasport);	
	printf("\n��� ������:");
		scanf("%s",client.vklad);	
	printf("\n����������� �������:");
		scanf("%lf",&client.cash);	
	printf("\n���� ��������� ��������:\n");
	printf("\n����:");
		scanf("%d", &client.day);
	printf("\n�����:");
		scanf("%d", &client.month);
	printf("\n���:");
		scanf("%d", &client.year);
	return client;
}


List add (List head, DataType client){
	List tmp, l=head;
	tmp=new list;
	tmp->data=client;
	tmp->next=NULL;
	if (head == NULL)
		return tmp;
	 while (l->next!=NULL)
		l = l->next;
	l->next =tmp;
	return head;
}


void show (List head){
	int k=1;
	char shapka[6][16]={"�","����� �����:", "�������:", "��� ������:",
							 "��������:", "����:"};
	system("CLS");
	if (head == NULL)
	{
	puts ("������ ����.");
	getch();
	return;
	}		
	printf("\n%s%14s%15s%19s%16s%14s\n", shapka[0], 
	shapka[1],shapka[2],shapka[3],shapka[4],shapka[5] );
	puts ("-------------------------------------------------------------------------------");
	while (head){
	printf("%d%14.0lf%15.0lf%19s%16.0lf%7d.%d.%d\n",k++, head->data.number,
	 	head->data.pasport, head->data.vklad, head->data.cash, 
		head->data.day, head->data.month, head->data.year);
	puts ("-------------------------------------------------------------------------------");
	head = head->next;}	
}


void edit_cash (List cl){
	double money;
	char oper;
	system("CLS");
	puts ("������ �������� ��� ����� �������� �� �����? \n+ -��������\t- -�����");
	do
		oper=getchar();
	while (oper!='+' && oper!='-');
	puts("������� �����");
	scanf("%lf",&money);
	if (oper=='+'){
	cl->data.cash+=money;
	puts("�������� ��������� �� ����.");
	}
	else{
	if(cl->data.cash>=money){
	cl->data.cash-=money;
	puts("�������� ������� ����� �� �����.");
	}
	else
	puts ("�� ����� ����� ������������ �������.");
	}
	system ("pause");			
}


void print1 (List cl){
	char shapka[5][16]={"����� �����:", "�������:", "��� ������:",
							 "��������:", "����:"};
	printf("\n%14s%15s%19s%16s%14s\n", shapka[0], 
					shapka[1],shapka[2],shapka[3],shapka[4]);
	puts ("-------------------------------------------------------------------------------");
	printf("%14.0lf%15.0lf%19s%16.0lf%7d.%d.%d\n", cl->data.number,
	 			cl->data.pasport, cl->data.vklad, cl->data.cash, 
				 cl->data.day, cl->data.month, cl->data.year);
	puts ("-------------------------------------------------------------------------------");	 	
}


void redact (List head){
	double N_or_P;
	char yes, menu;
	system("CLS");
	if (head == NULL)
	{
		puts ("���� ������ �����.");
		getch();
		return;
	}
	puts ("������� ����� ����� ��� ���������� ������ �������:.");
	scanf ("%lf", &N_or_P);
	if (N_or_P < 1)
	{
		puts ("�� ����� ������� ������.");
		system ("pause");
		return;
	}	 
	while (head && head->data.number != N_or_P && head->data.pasport!=N_or_P){
		 head = head->next;}
	if (head == NULL)
	{
		puts ("����� �� ������");
		getch();
		return;
	}
	print1 (head);
	puts ("�� �������, ��� ������ ��������������?\n y-��\tn-���");
	do
		yes=getchar();
	while (yes!='y' && yes!='Y' && yes!='n' && yes!='N');
	if (yes=='y' || yes=='Y')
	{
	do
	{
	system("CLS");
	puts("�������� � ������� ����� ���� ��� �������������\n");
	puts ("1.���������� ������");
	puts ("2.��� ������");
	puts ("3.���������� �������");
	puts ("4.�� ��������������");
	menu=getchar();
	switch (menu)
	{
	case '1': system("CLS");
	puts("������� ����� ���������� ������:");
	scanf("%lf",&head->data.pasport);
	head->data.day=16;
	head->data.month=06;
	head->data.year=2016;
	puts("���������� ������ ������� ��������.");
	system ("pause");
	return;
	case '2':system("CLS");
	puts("������� ����� ��� ������:");	
	scanf("%s",&head->data.vklad);
	head->data.day=16;
	head->data.month=06;
	head->data.year=2016;
	puts("��� ������ ������� ������.");
	system ("pause");
	return;
	case '3': system("CLS");
	edit_cash (head);
	head->data.day=16;
	head->data.month=06;
	head->data.year=2016; 
	return;
	}	
	}
	while (menu!='4');
	}					
}


List del (List head){
	int n, k=1;
	char yes;
	List temp, temp1;
	system("CLS");  
	if (head == NULL)
	{
		puts ("���� ������ �����");
		system ("pause");
		return NULL;
	}
	show (head);
	puts ("������� ���������� ����� ����� �������.");
	scanf ("%d", &n);
	if (n < 1)
	{
		puts ("������� ������� ������.");
		system ("pause");
		return head;
	}
	if (n == 1)
	{
		puts ("�� ������������� ������ ������� ���� ����?\n y-��\tn-���");
		do
			yes=getchar();
		while (yes!='y' && yes!='Y' && yes!='n' && yes!='N');
		if (yes=='y' || yes=='Y')
		{
		temp = head->next;
		delete head;
		puts("���� ������� �����.");
		system ("pause");
		return temp;
		}
		else return head;
	}
	if (head->next == NULL && n > 1)
	{
		puts ("�� �������� ������ �� ������� �� ������ �����.");
		system ("pause");
		return head;
	}
	temp = head;
	temp1 = temp->next;
	while (temp1->next && k < n-1)
	{
		temp = temp1;
		temp1 = temp->next;
		k++;
	}
	if (k < n-1)
	{
		puts ("�� �������� ������ �� ������� �� ������ �����.");
		system ("pause");
		return head;
	}
	puts ("�� ������������� ������ ������� ���� ����?\n y-��\tn-���");
	do
		yes=getchar();
	while (yes!='y' && yes!='Y' && yes!='n' && yes!='N');
	if (yes=='y' || yes=='Y')
	{
		temp->next = temp1->next;
		delete temp1;
		puts("���� ������� �����.");
		system ("pause");
	}
	return head;
 }


void search_list(List head){
	int N_or_P;
	system("CLS");
	if (head == NULL)
	{
		puts ("���� ������ �����");
		system ("pause");
		return;
	}
	puts("������� ����� ����� ��� ���������� ������");
	scanf("%d",&N_or_P);
	if (N_or_P < 1)
	{
		puts ("������� ������� ������.");
		system ("pause");
		return;
	}
	while (head && head->data.number != N_or_P && head->data.pasport!=N_or_P){
		 head = head->next;}
	if (head == NULL)
	{
		puts("� ���� ������ ��� ������� � ������ �������.");
		system ("pause");
		return;
	}
	print1 (head);
	system ("pause");	 
}


 void Year (List head) {
	int k=1;
	system("CLS");
	if (head == NULL)
	{
		puts ("���� ������ �����");
		system ("pause");
		return;
	}
	while (head)
	{
		if(2016-head->data.year==5)
		{
			print1 (head);
			k=0;}
		 head = head->next;
	}
	if (head == NULL && k)
	{
		puts("� ������ ��� ������ �������.");
		system ("pause");
		return;
	}	 
	system ("pause");
}


List read_file (List head){	
	char file[50];
	FILE * f;
	DataType client;
	system("CLS");
	puts ("������� ��� �����, � ������� ��������� ���� ���� ������:");
	scanf ("%s",file);
	if ((f = fopen (file, "rb")) == NULL)
	{
		puts("��� ������ �����");
		system ("pause");
		return head;
	}
	while (fread(&client, sizeof(client), 1, f))
			head = add (head, client);
    fclose(f);
    puts("���� ������ ������� ���������.");
    system ("pause");
	return head;
}


void write_file (List head){		
	char file[50];
	FILE * f;
	system("CLS");
	puts ("������� ��� �����, � ������� ����� ��������� ���� ���� ������:");
	scanf("%s",file);
	if ((f = fopen (file, "wb")) == NULL)
	{
		puts("������������ ������ ��� ��������� ���� ������.");
		system ("pause");
		return;
	}
	while (head)
	{
		fwrite (&head->data, sizeof(DataType), 1, f);
		head = head->next;
	}
	fclose(f);
	puts("���� ������ ������� ���������.");
    system ("pause");
}


void delete_list (List head){
	system("CLS");
	List temp = head;
    while (temp)
    {
		head = temp->next;
		delete temp;
		temp = head;
	}
	puts("��������� ������� ���������.");
}
