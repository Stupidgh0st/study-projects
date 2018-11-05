#include "zoo_f.h"
#include "zoo_f.c"
#include <string.h>
#include <windows.h>

int main (void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char file[50];
	char menu;
	L zoo = NULL;
   do
   {
     system ("CLS");
     puts ("1. Добавить");
     puts ("2. Изменить");
     puts ("3. Показать");
     puts ("4. Удалить");
     puts ("5. Чтение из файла ");
     puts ("6. Запись в файл");
     puts ("7. Поиск животных степной зоны");
	 puts ("8. Затрата на содержание животного за месяц");
	 puts ("0. Выход");
     menu = getchar();
     switch (menu)
     {
       case '1': zoo=add(zoo, in_zoo());break;
       case '2': edit (zoo); break;
       case '3': show (zoo); break;
       case '4': zoo=del(zoo);break;
       case '5': fflush(stdin);system("CLS");puts("Имя файла" );gets(file);zoo=r_file(file,zoo);break; 
       case '6': fflush(stdin);system("CLS");puts("Имя файла" );gets(file);w_file(file,zoo);break;
       case '7': search (zoo);break;
       case '8': search2 (zoo);
     }
   }
   while (menu!='0');
   deleteL(zoo);
   zoo=NULL;
   return 0;}

