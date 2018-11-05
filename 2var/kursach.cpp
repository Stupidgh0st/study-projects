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
	puts("               МЕНЮ:");
	puts("(Выберите и введите нужный пункт меню)");
	puts ("1. Добавление новых клиентов в базу данных банка");
	puts ("2. Просмотр базы данных банка");
	puts ("3. Корректировка базы данных банка");
	puts ("4. Удаление клиента из базы данных банка");
	puts ("5. Поиск клиента банка");
	puts ("6. Показать вклады, операции по которым не выполнялись в течении 5 лет");
	puts ("7. Загрузить базу данных");
	puts ("8. Сохранить базу данный");
	puts ("9. Выход");
	menu = getchar();
	switch (menu)
	{
	case '1': system("CLS");
	puts("Введите количество клиентов:");
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
	printf ("\nНомер вклада:");
		scanf("%lf",&client.number);	
	printf("\nПаспортные данные:");
		scanf("%lf",&client.pasport);	
	printf("\nТип вклада:");
		scanf("%s",client.vklad);	
	printf("\nКолличество средств:");
		scanf("%lf",&client.cash);	
	printf("\nДата последней операции:\n");
	printf("\nДень:");
		scanf("%d", &client.day);
	printf("\nМесяц:");
		scanf("%d", &client.month);
	printf("\nГод:");
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
	char shapka[6][16]={"№","Номер счета:", "Паспорт:", "Тип вклада:",
							 "Средства:", "Дата:"};
	system("CLS");
	if (head == NULL)
	{
	puts ("Список пуст.");
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
	puts ("Хотите добавить или снять средства со счета? \n+ -добавить\t- -снять");
	do
		oper=getchar();
	while (oper!='+' && oper!='-');
	puts("Введите сумму");
	scanf("%lf",&money);
	if (oper=='+'){
	cl->data.cash+=money;
	puts("Средства зачислены на счёт.");
	}
	else{
	if(cl->data.cash>=money){
	cl->data.cash-=money;
	puts("Средства успешно сняты со счёта.");
	}
	else
	puts ("На Вашем счете недостаточно средств.");
	}
	system ("pause");			
}


void print1 (List cl){
	char shapka[5][16]={"Номер счета:", "Паспорт:", "Тип вклада:",
							 "Средства:", "Дата:"};
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
		puts ("База данных пуста.");
		getch();
		return;
	}
	puts ("Введите номер счета или паспартные данные клиента:.");
	scanf ("%lf", &N_or_P);
	if (N_or_P < 1)
	{
		puts ("Не верно введены данные.");
		system ("pause");
		return;
	}	 
	while (head && head->data.number != N_or_P && head->data.pasport!=N_or_P){
		 head = head->next;}
	if (head == NULL)
	{
		puts ("Вклад не найден");
		getch();
		return;
	}
	print1 (head);
	puts ("Вы уверены, что хатите корректировать?\n y-да\tn-нет");
	do
		yes=getchar();
	while (yes!='y' && yes!='Y' && yes!='n' && yes!='N');
	if (yes=='y' || yes=='Y')
	{
	do
	{
	system("CLS");
	puts("Выберите и введите номер поля для корректировки\n");
	puts ("1.Паспортные данные");
	puts ("2.Тип вклада");
	puts ("3.Количество средств");
	puts ("4.Не корректировать");
	menu=getchar();
	switch (menu)
	{
	case '1': system("CLS");
	puts("Введите новые паспортные данные:");
	scanf("%lf",&head->data.pasport);
	head->data.day=16;
	head->data.month=06;
	head->data.year=2016;
	puts("Паспортные данные успешно изменены.");
	system ("pause");
	return;
	case '2':system("CLS");
	puts("Введите новый тип вклада:");	
	scanf("%s",&head->data.vklad);
	head->data.day=16;
	head->data.month=06;
	head->data.year=2016;
	puts("Тип вклада успешно изменён.");
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
		puts ("База данных пуста");
		system ("pause");
		return NULL;
	}
	show (head);
	puts ("Введите порядковый номер счета клиента.");
	scanf ("%d", &n);
	if (n < 1)
	{
		puts ("Неверно введены данные.");
		system ("pause");
		return head;
	}
	if (n == 1)
	{
		puts ("Вы действительно хотите удалить этот счёт?\n y-да\tn-нет");
		do
			yes=getchar();
		while (yes!='y' && yes!='Y' && yes!='n' && yes!='N');
		if (yes=='y' || yes=='Y')
		{
		temp = head->next;
		delete head;
		puts("Счёт успешно удалён.");
		system ("pause");
		return temp;
		}
		else return head;
	}
	if (head->next == NULL && n > 1)
	{
		puts ("По введённым данным не найдено ни одного счёта.");
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
		puts ("По введённым данным не найдено ни одного счёта.");
		system ("pause");
		return head;
	}
	puts ("Вы действительно хотите удалить этот счёт?\n y-да\tn-нет");
	do
		yes=getchar();
	while (yes!='y' && yes!='Y' && yes!='n' && yes!='N');
	if (yes=='y' || yes=='Y')
	{
		temp->next = temp1->next;
		delete temp1;
		puts("Счёт успешно удалён.");
		system ("pause");
	}
	return head;
 }


void search_list(List head){
	int N_or_P;
	system("CLS");
	if (head == NULL)
	{
		puts ("База данных пуста");
		system ("pause");
		return;
	}
	puts("Введите номер счета или паспортные данные");
	scanf("%d",&N_or_P);
	if (N_or_P < 1)
	{
		puts ("Неверно введены данные.");
		system ("pause");
		return;
	}
	while (head && head->data.number != N_or_P && head->data.pasport!=N_or_P){
		 head = head->next;}
	if (head == NULL)
	{
		puts("В базе данных нет клиента с такими данными.");
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
		puts ("База данных пуста");
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
		puts("В списке нет такого клиента.");
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
	puts ("Введите имя файла, в котором храниться Ваша база данных:");
	scanf ("%s",file);
	if ((f = fopen (file, "rb")) == NULL)
	{
		puts("Нет такого файла");
		system ("pause");
		return head;
	}
	while (fread(&client, sizeof(client), 1, f))
			head = add (head, client);
    fclose(f);
    puts("База данных успешно загружена.");
    system ("pause");
	return head;
}


void write_file (List head){		
	char file[50];
	FILE * f;
	system("CLS");
	puts ("Введите имя файла, в котором будет храниться Ваша база данных:");
	scanf("%s",file);
	if ((f = fopen (file, "wb")) == NULL)
	{
		puts("Недостаточно памяти для сохранния базы данных.");
		system ("pause");
		return;
	}
	while (head)
	{
		fwrite (&head->data, sizeof(DataType), 1, f);
		head = head->next;
	}
	fclose(f);
	puts("База данных успешно сохранена.");
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
	puts("Программа успешно завершена.");
}
