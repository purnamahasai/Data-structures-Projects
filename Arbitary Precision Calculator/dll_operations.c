#include"dll.h"
Status insert_last(int data, dll **head, dll **tail)
{
    if(data == 0 && *head == NULL)
        return e_zero;
    dll *new = malloc(sizeof(dll));
    if(new == NULL)
    {
        return e_failure;
    }
    new ->digit = data;
    new ->prev = NULL;
    new ->next = NULL;
    if(*head == NULL)
    {
        *head = *tail = new;
    }
    else
    {
        new ->prev = *tail;
        (*tail)->next = new;
        *tail = new;
    }
    return e_success;
}

Status insert_first(int data, dll **head, dll **tail)
{    
    dll *new = malloc(sizeof(dll));
    if(new == NULL)
    {
        return e_failure;
    }
    new ->digit = data;
    new ->prev = NULL;
    new ->next = NULL;
    if(*head == NULL)
    {
        *head = *tail = new;
    }
    else
    {
        (*head) ->prev = new;
        new ->next = *head;
        *head = new;
    }
    return e_success;
}
Status print_list(dll *head, dll *tail)
{
    if(head == NULL)
        printf("NULL\n");
    while(head != tail)
    {
        printf("%d ", head ->digit);
        head = head ->next;
    }
    if(tail != NULL)
    {
        printf("%d\n", tail ->digit);
    }
    return e_success;
}