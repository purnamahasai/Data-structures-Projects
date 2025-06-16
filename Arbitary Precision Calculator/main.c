#include"main.h"
int num1sign=0, num2sign=0, res_sign = 0, num1len = 0, num2len = 0;
int main(int argc, char *argv[])
{
    //validating CLA
    if(argc != 4)
    {
        error_message();
        return 0;
    }
    //declaring pointers for operands and Result lists
    dll *num1_head = NULL, *num1_tail = NULL;
    dll *num2_head = NULL, *num2_tail = NULL;
    dll *res_head = NULL, *res_tail = NULL;

    //checking if -ve sign present in operands
    if(argv[1][0] == '-')
    {
        num1sign =1;
        argv[1][0] = '0';
    }
    if(argv[3][0] == '-' )
    {
        num2sign =1;
        argv[3][0] = '0';
    }
    //finding the operation
    switch(*argv[2])
    {
        case '+': //ADDITION
            //convert string to list            
            if(number_string_to_list(argv[1], argv[3], &num1_head, &num1_tail, &num2_head, &num2_tail) == e_failure)
                error_message();
            //Doing addition and printing the result
            printf("RESULT : ");
            if(!num1_head && !num2_head) //0 + 0
                printf("0\n");
            else if(!num1_head) // 0 + x
            {
                SIGN_CHECK(num2sign)
                print_list(num2_head, num2_tail);
            }
            else if(!num2_head) // x + 0
            {
                SIGN_CHECK(num1sign)
                print_list(num1_head, num1_tail);
            }
            else if((num1sign && num2sign) || (!num1sign && !num2sign)) //-1 + -1 (or) 1+1
            {
                 if(addition(num1_head, num1_tail, num2_head, num2_tail, &res_head, &res_tail) == e_success)
                 {
                    SIGN_CHECK(num2sign) 
                    print_list(res_head, res_tail);
                 }
                 else 
                 {                
                     printf("Addition failed\n");
                 }
            }
            else
            {
                if(num1sign) // -x + y 
                {
                    if(subtraction(num2_head, num2_tail, num1_head, num1_tail, &res_head, &res_tail) == e_success) // y - x
                    {
                        if(res_sign) //if y < x
                            printf("-"); 
                        print_list(res_head,res_tail);
                    }
                    else
                    {
                        printf("Subtraction Failed \n");
                    }
                }
                if(num2sign) //x + -y
                {
                    if(subtraction(num1_head, num1_tail, num2_head, num2_tail, &res_head, &res_tail) == e_success) // x - y
                    {                        
                        if(res_sign) ///if x < y
                            printf("-");
                        print_list(res_head, res_tail);
                    }
                    else
                    {
                        printf("Subtraction Failed \n");
                    }  
                }
            }            
            break;
        case '-': //SUBTRACTION
            //convert string to list
            if(number_string_to_list(argv[1], argv[3], &num1_head, &num1_tail, &num2_head, &num2_tail) == e_failure)
                error_message();
            //Doing subtraction and printing result
            printf("RESULT : ");
            if(!num1_head && !num2_head) // 0 - 0
                printf("0\n");
            else if(!num1_head) // 0 - x
            {
                if(!num2sign) // if 0 - x
                    printf("-"); // -x otherwise -(-x) = x
                print_list(num2_head, num2_tail);
            }
            else if(!num2_head) // x - 0
            {
                SIGN_CHECK(num1sign) //-x - 0 = -x 
                print_list(num1_head, num1_tail);
            }
            else if((num1sign && num2sign) || (!num1sign && !num2sign)) // x - y or -x - -y
            {
                if(num1sign)//(-x - -y) ==> y-x
                {
                    swap(&num1_head, &num1_tail, &num2_head, &num2_tail); //swapping num1 and num2 x-y
                }
                if(subtraction(num1_head, num1_tail, num2_head, num2_tail, &res_head, &res_tail) == e_success)
                {
                    if(res_sign) //if y > x
                        printf("-");
                    print_list(res_head, res_tail);
                }
                else
                {
                    printf("Subtraction failed\n");
                }                
            }
            else if(num1sign ^ num2sign)// -x - y or x - -y
            {
                if(num1sign) //if -x result -ve
                    printf("-");
                if(addition(num1_head, num1_tail, num2_head, num2_tail, &res_head, &res_tail) == e_success)
                {
                    print_list(res_head, res_tail);
                }
                else
                {
                    printf("Subtraction failed\n");
                }
            }
                              
            break;
        case 'x': //MULTIPLICATION
        case 'X': 
        case '*':
            //converting string to list
            if(number_string_to_list(argv[1], argv[3], &num1_head, &num1_tail, &num2_head, &num2_tail) == e_failure)
                    error_message();
            //printing Multiplication result
            printf("RESULT : ");
            if(!num1_head || !num2_head) // 0 x b (or) b x 0 (or) 0 x 0
                printf("0\n");
            //if both numbers not 0 do multiplication           
            else if(multiplication(num1_head, num1_tail, num2_head, num2_tail, &res_head, &res_tail) == e_success)
            {
                if(num1sign ^ num2sign) // if any number is negative put the "-" i.e result is negative
                {
                    printf("-");
                }
                print_list(res_head, res_tail);
            }
            else
            {
                printf("Multiplication failed\n");
            }
            break;
        case '/'://DIVISION
            //converting string to list
            if(number_string_to_list(argv[1], argv[3], &num1_head, &num1_tail, &num2_head, &num2_tail) == e_failure)
                error_message();
            //printingn result
            printf("RESULT : ");
            //calling division to do
            if(divison(num1_head, num1_tail, num2_head, num2_tail, &res_head, &res_tail) != e_success)
            {
                printf("failure\n");
            }
            break;
        default:
            error_message();
    }
    return 0;
}
void error_message()
{
    printf("FAILED : \nUSAGE : please pass like ./a.out number1 <operator> number2\n"
                "operator : + or - or \"*\" or /\n");
}