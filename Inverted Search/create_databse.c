
#include "inverted_search.h"

char *fname;

// Function to create the database from the file linked list
void create_database(FLIST *f_head, Wlist *head[])
{
    //traverse through the file list
    while(f_head)
    {
        // Read data from the current file and update the database
		read_data_from_file(f_head , head , f_head->f_name);
		f_head = f_head->link;  //move to next file in linked list
    }
}

// Function to read data from a file and update the word database
void read_data_from_file(FLIST *file, Wlist *head[], char *filename)
{
    int flag = 1;   // Flag to check if the word is already in the database
    fname = filename; // make filename GLOBAL
    //open file in read mode
    FILE *fptr = fopen(filename ,"r");
    // Check if the file was successfully opened
    if(!fptr)
    {
        printf("Failed to open %s", filename);
        return;
    }
    //declare an array to store words
    char word[WORD_SIZE];

    // Read words from the file until the end of the file is reached
    while(fscanf(fptr , " %s" , word) != EOF)
    {
		// Calculate the index
		int index = tolower(word[0]) % 97;
		if(!(index >= 0 && index <= 25))
		{
			index = 26;     //other than alphabets 
		}

		//check whether words are repeated or not		
		if(head[index] != NULL)
		{
			Wlist *temp = head[index];			
            flag = 1;
			//compare the words at each node with new word
			while(temp)
			{				
				if(!strcmp(temp->word , word))  // If the word matches
				{
					update_word_count(&temp , filename);     // Update its count
					flag = 0;   // Reset flag to indicate word already exists
					break;
				}
				temp = temp->word_link;     // Move to the next word in the list
			}
        }

        // If the word is not found in the database, add it
        if(flag == 1)
        {
            if(insert_last(&head[index] , word) != SUCCESS)     //insert word to list
            {
                printf("Failed : inserting word into database\n");
            }     
        }
	}
    fclose(fptr);	// Closing the file	
}

// Function to update the word count in the database for a specific file
int update_word_count(Wlist **head, char *file_name)
{
   Ltable *ttemp = (*head)->Tlink;      // Traverse the file list for the word
   Ltable *prev = NULL;

   // Check if the file already exists in the word's file list
   while(ttemp != NULL)
   {
        if (strcmp(ttemp->file_name,file_name) == 0)       // If the file matches
        {
            ttemp->word_count += 1;     //increment word count for that file
            return SUCCESS;
        }
        // Move to the next node in the list    
        prev = ttemp;
        ttemp = ttemp-> table_link;        
   }

   // If the file is not found, create a new node for it
   Ltable *new = malloc(sizeof(Ltable));
   if (new == NULL)     //validation
   {
	    return FAILURE;
   }

   // Initialize the new node with file details
   strcpy(new ->file_name , file_name);
   new->word_count = 1;
   new ->table_link = NULL;
   // Link the new node to the end of the list
   if(prev)
        prev->table_link=new;

    // Increment the file count for the word
   (*head)->file_count += 1;
   return SUCCESS;
} 

