#ifndef DLL_H
#define DLL_H
#include<stdlib.h>
#include<stdio.h>
typedef struct node
{
    struct node *prev;
    int digit;
    struct node *next;   
}dll;

typedef enum
{
    e_failure,
    e_success,
    e_zero
}Status;

Status insert_last(int , dll **, dll **);
Status insert_first(int data, dll **head, dll **tail);
Status print_list(dll *head, dll *tail);

#endif