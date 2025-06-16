#ifndef MAIN_H
#define MAIN_H
#include "dll.h"
#define DIGIT(X) (X - '0') 

#define SIGN_CHECK(x) \
{   \
    if(x == 1)  \
    printf("-");    \
}



void error_message();
Status number_string_to_list(char *, char *, dll **, dll **, dll **, dll **);
Status addition(dll *num1_head, dll *num1_tail, dll *num2_head, dll *num2_tail, dll **res_head, dll **res_tail);
Status subtraction(dll *num1_head, dll *num1_tail, dll *num2_head, dll *num2_tail, dll **res_head, dll **res_tail);
Status multiplication(dll *num1_head, dll *num1_tail, dll *num2_head, dll *num2_tail, dll **res_head, dll **res_tail);
Status divison(dll *num1_head, dll *num1_tail, dll *num2_head, dll *num2_tail, dll **res_head, dll **res_tail);
void swap(dll **num1_head, dll **num1_tail, dll **num2_head, dll **num2_tail);
Status is_sec_operand_large(dll *num1_head, dll *num2_head);
int list_length(dll *head);
#endif