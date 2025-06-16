
#include "inverted_search.h"


// Function to search for a word in the database at particular index
void search( Wlist *head, char *word)
{
    //if no words present at that index
    if(head == NULL)
    {
		printf("Search is not possible , list is empty\n");
    }

    //traverse the list 
    while(head)
    {
        
		 // Compare the search word with the current node's word
		if(!(strcmp(head->word , word)))
		{
            // Display the word and its file count
			printf("Word %s is present in %d file/s \n" , word , head->file_count);

            // Traverse the linked table (Ltable) to display file-specific details
			Ltable *Thead = head->Tlink;
			while(Thead)
			{
                 // Print the file name and word count for each file
				printf("In file : %s --> %d time/s \n" , Thead->file_name , Thead->word_count);
				Thead = Thead->table_link;
			}
			printf("\n");
			return;     // Exit the function after successfully finding the word
		}
		head = head->word_link;     // Move to the next word node in the list
    }

    // If the word is not found in the list
    printf("Search word is not present in the list\n");
}




