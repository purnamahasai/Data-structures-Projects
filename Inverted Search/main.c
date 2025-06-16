#include "inverted_search.h"

int main(int argc , char *argv[])
{
    system("clear");       //clear the console
    
    if(argc <= 1)    //validate CLA
    {
        printf("Enter valid no of arg\n");
        printf("./.a.out f1.txt f2.txt.....\n");
        return 0;
    }

    //declare file linked list head pointer
    FLIST *f_head = NULL;

    //validate the filenames passed in CLA
    file_validation_n_file_list(&f_head , argv);

    if(f_head == NULL)      //if no files added to file linked list
    {
        printf("No files are available in the file linked list\n");
        printf("Hence the process terminated\n");
        return 0;
    }
    // Declare an array of pointers to Wlist, representing the word database.
    Wlist *head[27] = {NULL};

    char choice;
    int option;
    
    do
    {
         // Display the menu for user choices.
        printf("Select your choice among the following options:\n");
        printf("1. Create DATABASE\n");
        printf("2. Display Database\n");
        printf("3. Update DATABASE\n");
        printf("4. Search\n");
        printf("5. Save Database\n");
        scanf("%d", &option);
      
        switch(option)
        {
            case 1:
            {
                 // Create the word database using the file linked list.            
                create_database(f_head , head);
                break;
            }
            case 2:
            {
                //display the current database contents
                display_database(head);
                break;
            }             
            case 3:
            {
                //update database with new file content
                update_database(head , &f_head);
                break;
                
            }            
            case 4:
            {
                char word[WORD_SIZE];   //buffer to store the word
                printf("Enter the word\n");
                scanf(" %s" , word);

                //finding the index for word
                int index = tolower(word[0]) % 97;  
                if(!(index >=0 && index <=25))
                    index = 26; //for non alphabet

                //serch for the word in corrosponding list
                search(head[index] , word);
                break;
                
            }            
            case 5:
            {
                //Save the word database to a file
                save_database(head);
                break;
            }
            default:
            {
                printf("Invalid option. Please try again.\n");
                break;
            }
        }
        // Prompt the user to continue or exit the program.
        printf("Do you want to continue ? press y/Y \n");
        printf("enter your choice : ");
        scanf(" %c",&choice);
        
    } while (choice == 'Y' || choice == 'y');        
}

