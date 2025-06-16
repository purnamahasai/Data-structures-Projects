#include "inverted_search.h"

// Function to update the database with a new file's contents
void update_database( Wlist *head[], FLIST **f_head)
{
    char file_name[FILENAME_SIZE];  //buffer to store file name

    //prompt the user
    printf("Enter the file name for updating the database\n");
    scanf("%s" , file_name);

    //validate the file name
    
    if(file_validation(f_head, file_name) == SUCCESS)    // Check if the file is valid and not empty
    {
        FLIST *temp = *f_head;
        // Traverse the file linked list
        while(temp) 
        {
            // Compare the current file name in the linked list with the entered file name
            if(!(strcmp(temp->f_name , file_name)))
            {
                // If a match is found, read data from the file and update the database
                read_data_from_file(temp , head , temp->f_name);
                return;
            }
            temp = temp->link;        //move to next file in file linked list
        }
    }
}


