
#include "inverted_search.h"
extern char *fname;

// Function to insert a new word node at the end of the word list
status insert_last(Wlist **head, char *data)
{
    Wlist *new = malloc(sizeof(Wlist));     //create node


    if(new == NULL)         //Validation
    {
	    return FAILURE;
    }

    //update the node fields
    new->file_count = 1;
    strcpy(new->word,data);
    new->Tlink = NULL;
    new->word_link = NULL;

    //call fun to update link table
    if(update_link_table(&new) != SUCCESS)
    {
        return FAILURE;
    }

    // Check if the word list is empty
   if(*head == NULL)
   {
      *head = new;      // If empty, make the new node the head of the list
      return SUCCESS;
   }

   //NON EMPTY
   Wlist *temp = *head;

   //traverse to the last node
   while(temp->word_link)
   {
       temp = temp->word_link;
   }

   // Append the new node at the end of the list
   temp->word_link = new;
   return SUCCESS;
}

// Function to update the link table (file information) for a word node
status update_link_table(Wlist **head)
{
    //create new node
    Ltable *new = malloc(sizeof(Ltable)); 
    if(new == NULL) //validating
    {
	    return FAILURE;
    }
    //updating fields
    new->word_count = 1; 
    strcpy(new->file_name,fname);
    new->table_link = NULL;
    (*head)->Tlink = new; //insert into wlist node element
    return SUCCESS;
}