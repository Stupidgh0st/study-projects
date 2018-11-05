#include <string.h>

D in_zoo(void)
{ 
D zoo;
system("CLS");
fflush(stdin);
puts ("Название животного");
gets (zoo.Animal);
puts ("Природная зона");
gets (zoo.Zone);
puts ("Затрата");
scanf ("%f", &zoo.zatrata);
return zoo;}

L add (L begin , D train)
{

L tmp,l=begin;
tmp=(L)malloc(sizeof(list));
tmp->inf=train;
tmp->next=NULL;
if(begin==NULL)
return tmp;
while(l->next!=NULL)
l=l->next;
l->next=tmp;
return begin;}

void print (L begun)
{
printf ("Название животного : %s\nПриродная зона  : %s\nЗатрата  : %.2f\n",begun->inf. Animal,begun->inf. Zone,begun->inf. zatrata);}

void edit (L begin)
{
int i,k=1;
char  yn[4],y[4]="да ",n[4]="нет";
system("CLS");
if(begin==NULL)
{puts ("Ошибка открытия файла"); 
system ("pause");
return;}
printf ("Номер записи");
scanf ("%d",&i);
fflush(stdin);
if(i<1){puts("Ошибка");system("pause");return;}
while (begin&&k<i)
{k++;
begin=begin->next;}
if(begin==NULL) {puts("Не найдено");system("pause");return;}
print(begin);
puts ("Редактировать? (да /нет)");fflush(stdin);
do
gets(yn);
while (strcmp(yn,y)!=0&&strcmp(yn,n)!=0);
if (strcmp(yn,y)==0)
begin->inf=in_zoo();
}


void show (L begin)
{

int k=0;
system ("CLS");
if (begin==NULL)
{puts ("Ошибка открытия файла")  ; 
system ("pause"); 
return;}
puts ("| N |       Название животного      | Природная зона  |    Затрата    |"); 
puts ("-----------------------------------------------------------------------");
while (begin)
{printf ("|%2d |           %-20s |      %-9s  |   %-10.2f |\n", 
++k, begin->inf.Animal, begin->inf.Zone,begin->inf.zatrata);
puts ("-----------------------------------------------------------------------");
begin=begin->next;}
system ("pause");}

L del (L begin )
{
system ("CLS");
int i=1,k;
L q=begin,tmp;
if (q==NULL)
{puts ("Ошибка открытия файла");
system("pause");return begin;}
puts("Введите номер");
scanf("%d",&k);
if (k<1) {puts("Ошибка");system("pause");return begin;}

if(k==1)
 {tmp=begin->next;
free(begin);
return tmp;}

if (begin->next == NULL && k > 1)
 {puts ("Не найдено");
system("pause");
return begin;}
tmp=q;
  q=tmp->next;
while (q->next!=NULL&&i<k-1)
 {i++; tmp=q;
 q=tmp->next;}

if(i<k-1) {puts("Не найдено");system("pause");return begin;}
tmp->next=q->next;
free(q);
return begin;
}

L r_file(char* file,L begin)
{
FILE *f;
D t;
if((f=fopen(file,"rb"))==NULL)
{puts("Нет такого файла");
system("pause");return begin;}
while (fread(&t,sizeof(D),1,f))
begin=add(begin,t);
fclose(f);
return begin;}


void w_file(char* file,L begin)
{
FILE *f;
if((f=fopen(file,"wb"))==NULL)
{puts("Ошибка ");
system("pause");return;}
while(begin)
{fwrite(&begin->inf,sizeof(D),1,f);
begin=begin->next;}
fclose(f);}



void deleteL(L begin)
{
L tmp=begin;
while (tmp)
{begin=tmp->next;
free(tmp);
tmp=begin;}}


void search (L begin) 
{

L q=begin;
int k=0;
system ("CLS");
if (begin==NULL)
{puts ("Список пуст"); 
system ("pause");
return ;}
puts ("Природная зона ");
fflush(stdin);
system("CLS");
while (q!=NULL)
{if (strcmp("Степь",q->inf.Zone)==0)
{puts(q->inf.Animal); k++;
}q=q->next;}
printf ("Количество: %d\n",k);
system ("pause");}


void search2 (L begin) 
{
char name[15];
L q=begin;
float zatrata;
system ("CLS");
if (begin==NULL)
{puts ("Список пуст"); 
system ("pause");
return;}
puts ("Название животного");
fflush(stdin);
gets(name);
system("CLS");
while (q!=NULL)
{if (strcmp(name,q->inf.Animal)==0)
{puts(q->inf.Animal);printf("%.2f$\n",q->inf.zatrata*30);}q=q->next;}
system ("pause");}

