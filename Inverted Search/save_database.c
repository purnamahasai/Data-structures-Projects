
#include "inverted_search.h"


// Function to save the database to a file
void save_database( Wlist *head[])
{
    // Prompt the user to enter the file name for saving the database
    char file_name[FILENAME_SIZE];
    printf("Enter the file name\n");
    scanf(" %s" , file_name);

    //open file in write mode
    FILE *fptr = fopen(file_name , "w");
    if (fptr == NULL)       //validating
    {
        printf("Error: Unable to open file for saving database.\n");
        return;
    }
    int i, flag = 0;        // Flag to track if there is any data to save

    // Loop through all indices of the array
    for(i=0; i<27 ; i++)
    {
        if(head[i] != NULL)     // If there are words present in the current index
        {
            flag = 1;       //set the flag
            fprintf(fptr,"#%d\n",i);        // Write the index 
            write_database_to_file(head[i] , fptr);     // Save data from this index
        }
    }
    fclose(fptr);       // Close the file after writing

    // Inform the user about the save status
    if(flag)
        printf("Database saved\n");

    else
        printf("Database is empty, Nothing to save!!!\n");
}

//function to write word list data to a file
void write_database_to_file(Wlist *head, FILE* fptr)
{
    Wlist *temp = head;
    while(temp)
    {
         // Write the word and its file count to the file
        fprintf(fptr,"word is [%s] : file count is %d : ",temp->word,temp->file_count);
        Ltable *stemp = temp->Tlink;

        // Traverse the linked table for file-specific data
        while(stemp)
        {
            // Write file name and word count to the file
            fprintf(fptr,"file name is %s : word count is %d\n", stemp -> file_name, stemp -> word_count);
            stemp = stemp ->table_link;     // Move to the next linked table node
        }
        temp = temp->word_link;     // Move to the next word node in the list
    }
}

