#include "inverted_search.h"

// Function to display the contents of the word database
void display_database( Wlist *head[] )
{
    // Heading for the display output
    printf("[index]   [     word     ]   file_count file/s   File : File_name   word_count\n"
	       "----------------------------------------------------------------------\n");

    // Iterate through all 27 indices of the word list ( a-z and remaining)
    for(int i = 0 ; i<27 ; i++)
    {
		if(head[i] != NULL)     // If the index contains words
		{
			print_words_info(head[i]);      // Print information about the words in that index
		}
    }
}

// Function to print information of all words in a word list node
void print_words_info(Wlist *head)
{
    //traverse through the Wlist till last node
    while(head != NULL)
    {
        // Calculate the index
        int index = tolower(head->word[0]) % 97;
		if(!(index >= 0 && index <= 25))
		{
			index = 26;     //other than alphabets 
		}

        // Print the word's index, word, and file count
		printf("[%2d]      [%-15s]   %d         file/s : ", index, head->word, head->file_count);

        // Pointer to traverse the file list table for the current word
		Ltable *Thead = head->Tlink;
		
        // If the file list is not empty, print the first file's details
        if(Thead)
        {
            printf("File : %-15s   %d\n", Thead->file_name, Thead->word_count);
            Thead = Thead->table_link; //move to next file
        }

        // // Print details of the remaining files in the list
		while(Thead)
		{
			printf("                                                 File : %-15s   %d\n", Thead->file_name, Thead->word_count);
            Thead = Thead->table_link;      //move to next file
		}
		printf("\n");
		head = head->word_link;      // Move to the next word in the list
    }
}
