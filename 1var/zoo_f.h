#include <string.h>
#include <stdio.h>
#include <stdlib.h>
struct person
{
char Animal[30],Zone[30];
float zatrata;};
typedef person D;

struct list
{
D inf;
list *next;};
typedef list *L;
D in_zoo (void);
L r_file(char* file,L begin);
void w_file(char*,L begin);
L add (L begin, D zoo);
void deleteL(L begin);
void edit(L begin);
void show(L begin);
void search (L begin);
void search2 (L begin);
L del (L begin);
