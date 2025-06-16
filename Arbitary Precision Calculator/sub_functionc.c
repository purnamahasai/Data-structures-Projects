#include"main.h"
extern int num1sign, num2sign,res_sign;
Status number_string_to_list(char *num1, char *num2, dll **num1_head, dll **num1_tail, dll **num2_head, dll **num2_tail)
{  
    int ind1 =0, ind2 = 0;
    //each character digit convert to integer and 
    while(num1[ind1] || num2[ind2])
    {
        if(num1[ind1])
        {
            if(insert_last(DIGIT(num1[ind1]), num1_head, num1_tail) == e_failure)
                return e_failure;
            ind1++;
            
        }
        if(num2[ind2])
        {
            if(insert_last(DIGIT(num2[ind2]), num2_head, num2_tail) == e_failure)
                return e_failure;
            ind2++;
        }
    }
    //printing both NUMBERS
    printf("NUMBER 1 : ");
    print_list(*num1_head, *num1_tail);
    printf("NUMBER 2 : ");
    print_list(*num2_head, *num2_tail);
    return e_success;
}

Status is_sec_operand_large(dll *num1_head, dll *num2_head)
{
    //finding length of 2 lists (number of digits in both NUMBERS)    
    int len1, len2;
    len1 = list_length(num1_head);
    len2 = list_length(num2_head);
    //if both numbers have equal length  
    if (len1 == len2)
    {
        //compare each digit from MSB 
        while(num1_head != NULL)
        {
            //if num2's digit greater return SUCCESS
            if(num2_head->digit > num1_head->digit)
                return e_success;
            //if num1's digit greater return failure
            if(num1_head->digit > num2_head->digit)
                return e_failure;
            //move to next digits
            num1_head = num1_head->next;
            num2_head = num2_head->next;
        }
        //if both numbers are equal
        return e_zero;
    }
    //if len2 is large then return SUCCESS
    return ((len1 < len2) ? e_success : e_failure);
}

int list_length(dll *head)
{
    int len = 0;
    //traverse in list and finding length and return it
    while(head)
    {
        len++;
        head = head->next;
    }
    return len;
}

void swap(dll **num1_head, dll **num1_tail, dll **num2_head, dll **num2_tail)
{
    //swapping both numbers head and tail pointers
    //head
    dll *temp = *num1_head;
    *num1_head = *num2_head;
    *num2_head = temp;
    //tails
    temp = *num1_tail;
    *num1_tail = *num2_tail;
    *num2_tail = temp;
}

