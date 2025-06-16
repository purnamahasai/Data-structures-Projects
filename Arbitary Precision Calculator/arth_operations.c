#include"main.h"
extern int num1sign, num2sign,res_sign;

Status addition(dll *num1_head, dll *num1_tail, dll *num2_head, dll *num2_tail, dll **res_head, dll **res_tail)
{
    int sum_digit, carry = 0;
    //add digit by digit in 2 numbers
    while(num1_tail || num2_tail)
    {
        //if no digits in NUM2
        if(num2_tail == NULL)
        {
            sum_digit = num1_tail->digit+ carry;
            num1_tail = num1_tail->prev;
        }
        else if(num1_tail == NULL)//if no digits in NUM1
        {
            sum_digit = num2_tail->digit + carry;
            num2_tail = num2_tail->prev;  
        }
        else//if both numbers has digits to SUM
        {
            sum_digit = num1_tail->digit + num2_tail->digit + carry;
            num1_tail = num1_tail->prev;
            num2_tail = num2_tail->prev;
        }
        carry = (sum_digit > 9); //if sum > 9 set the carry else 0
        insert_first(sum_digit % 10, res_head, res_tail); //insert sumdigit into list
        
    }
    if (carry)//after addition of numbers if carry present add it to list
        insert_first(carry, res_head, res_tail);    
    return e_success;
}

Status subtraction(dll *num1_head, dll *num1_tail, dll *num2_head, dll *num2_tail, dll **res_head, dll **res_tail)
{
    //skipping leading Zeros in numbers
    while(num1_head && num1_head->digit == 0 )
    {
        num1_head = num1_head->next;    
    }
    while(num2_head && num2_head->digit == 0 )
    {
        num2_head = num2_head->next;
    }
    if (!num1_head && num2_head)//if 0 - x = -x
    {
        *res_head = num2_head;
        *res_tail = num2_tail;
        res_sign = 1;// result is -ve
    }
    else if(num1_head && !num2_head) // if x - 0 = x
    {
        *res_head = num1_head;
        *res_tail = num1_tail;
        res_sign = 0; //result is +ve
    }
    else if(!num1_head && !num2_head) // 0 - 0
    {
        *res_head = *res_tail = NULL;
        res_sign = 0;        
    }
    else // x - y
    {
        int res = e_failure;
        if((res = is_sec_operand_large(num1_head, num2_head)) == e_zero) //if 2 numbers are equal
        {
            *res_head = *res_tail = NULL;
            res_sign = 0;
            return e_success;
        }            
        else if(res ==  e_success)//if num1 < num2 swap the numbers and result is -ve
        {
            //swap
            //heads
            swap(&num1_head, &num1_tail, &num2_head, &num2_tail);
            res_sign = 1;
        } 
        int borrow = 0, difference_digit;
        //subtract digit by digit
        while(num1_tail || num2_tail)
        {        
            if(borrow)
            {
                num1_tail->digit -= 1;
                borrow = 0;
            }
            if(num2_tail == NULL) // if 2nd number has no more digits
            {
                if(num1_tail->digit == -1) //if num1digit is 0 and borrow pesent
                {
                    borrow = 1;
                    num1_tail->digit += 10;
                }
                difference_digit = num1_tail->digit;
                num1_tail = num1_tail->prev; 
            }
            else 
            {
                if(num1_tail->digit < num2_tail->digit || num1_tail->digit == -1)
                {
                    borrow = 1;
                    num1_tail->digit += 10;
                }
                difference_digit = num1_tail->digit - num2_tail->digit;
                num1_tail = num1_tail->prev; 
                num2_tail = num2_tail->prev; 
            }        
            insert_first(difference_digit, res_head, res_tail);
        }
    }
    return e_success;
}

Status multiplication(dll *num1_head, dll *num1_tail, dll *num2_head, dll *num2_tail, dll **res_head, dll **res_tail)
{
    dll *res1_head, *res1_tail, *temp, *res2_head = NULL, *res2_tail = NULL;
    int product = 0, carry = 0, zeros_count = 0;
    //multipy each digit in NUM2 with NUM1
    while(num2_tail != NULL)
    {        
        temp = num1_tail;
        res1_head = res1_tail = NULL;
        //insert Zeros for every digit in NUM2
        for(int i = 0; i<zeros_count; i++)
        {
            insert_first(0, &res1_head, &res1_tail);
        }
        //multiply num1 with num2's digit
        while(temp)
        {            
            product = (temp->digit * num2_tail->digit) + carry;            
            carry = product / 10;            
            insert_first(product%10, &res1_head, &res1_tail);
            temp = temp ->prev;
        }
        if(carry)
        {
            insert_first(carry,&res1_head, &res1_tail);
            carry= 0;
        }
        //copy res to res2
        res2_head = *res_head; res2_tail = *res_tail;
        *res_head =NULL; *res_tail = NULL;
        addition(res1_head, res1_tail, res2_head, res2_tail, res_head, res_tail); // add the current digit multiplication result with previous sum 
        zeros_count++;
        num2_tail = num2_tail->prev;            
    }
    return e_success;
}

Status divison(dll *num1_head, dll *num1_tail, dll *num2_head, dll *num2_tail, dll **res_head, dll **res_tail)
{
    int res=e_failure;
    if((!num1_head && !num2_head) || !num1_head) // 0/0 or 0 / x
    {
        insert_first(0, res_head, res_tail);
        return e_success;
    }
    if(num1_head && !num2_head) //if x/0
    {
        printf("Cannot divide by zero\n");
        return e_success;
    }
    
    if((res = is_sec_operand_large(num1_head, num2_head)) == e_success) //if x/y and x<y
    {
        insert_first(0, res_head,res_tail);
        return e_success;
    }
    else if(res == e_zero)// if x=y
    {
        insert_first(1, res_head, res_tail);
        return e_success;
    }
    dll *res1_head = num1_head, *res1_tail = num1_tail, *temp_res_head, *temp_res_tail;
    long long int quotient = 0;
    //do subtraction untill res will lessthan num2
    while ((res = is_sec_operand_large(res1_head, num2_head)) != e_success)
    {
        quotient++;//incr quotient for every iteration        
        temp_res_head = NULL, temp_res_tail = NULL; 
        subtraction(res1_head, res1_tail, num2_head, num2_tail, &temp_res_head, &temp_res_tail); //subtract  num2 from previous subtraction result    
        //remove leading zeros   
        while(temp_res_head && temp_res_head->digit == 0)
        {
            temp_res_head = temp_res_head->next;
        }
        //print_list(temp_res_head, temp_res_tail);
        //if res is NULL
        if(temp_res_head==NULL)
            break;   
        res1_head = temp_res_head;
        res1_tail = temp_res_tail;                   
    }
    if(num1sign ^ num2sign) //if any 1 number is -ve result is -ve
    {
        printf("-");
    }
    printf("%lld\n", quotient); //printing the result
    return e_success;
}
