#include "inverted_search.h"

// Function to validate files and add the file linked list.
void file_validation_n_file_list(FLIST **f_head, char *argv[])
{
    int i = 1; //ignoring program name(./a.out)
    while(argv[i] != NULL)
    {
		file_validation(f_head, argv[i]); //validating one file at a time
		i++; //move to next file name passed in CLA
    }
}

// Function to validate a single file and add it to the linked list if valid.
status file_validation(FLIST **f_head, char filename[])
{
	// Check if the file is empty or unavailable.
	int empty = isFileEmpty(filename);
	if(empty == FILE_NOT_AVAILABLE)
	{
	    printf("File : %s is not available\n" , filename);
	    printf("Hence we are not adding that file into file linked list\n");
	}
	else if(empty == FILE_EMPTY)
	{
	    printf("File : %s is not having contents in it.\n" , filename);
	    printf("Hence we are not adding that file into file linked list\n");
	}
	else
	{
		// if the file is not empty or available try to add the file to the linked list.
	    int ret_val = create_list_of_files(f_head , filename);

	    if(ret_val == SUCCESS)
	    {
			printf("Successfull : Inserting the file name %s into the file linked list\n" , filename);
			return SUCCESS;
	    }
	    else if(ret_val == DUPLICATE_FOUND)
	    {
			printf("This file name : %s is repeated. Do not add the files more than once\n" , filename);
	    }
	    else
	    {
			printf("Failure\n");
	    }
    }
	return FAILURE; 	 // Return failure if the file is invalid or not added.
}

// Function to check if a file is empty or unavailable.
status isFileEmpty(char *filename)
{
    FILE *fptr = fopen(filename , "r"); //open file in read mode
    if(fptr == NULL) //if file not present 
    {	
	    return FILE_NOT_AVAILABLE;	
    }
    fseek(fptr , 0, SEEK_END);
    if(ftell(fptr) == 0) //if file is empty
    {
		fclose(fptr);
		return FILE_EMPTY;
    }
	fclose(fptr);
	return SUCCESS;
}

//Insert last in file linked list
status create_list_of_files(FLIST **f_head, char *filename)
{
	FLIST *new = malloc(sizeof(FLIST)); //craeting new node
	if(new == NULL) //validating
	{
		return FAILURE;
	}
	strcpy(new->f_name,filename); //updating its fields
	new ->link = NULL;
	if(*f_head == NULL) //if list is empty
	{		
		*f_head = new;
		return SUCCESS;		
	}
	else //if list not empty
	{
		FLIST *temp = *f_head;
		while(temp->link != NULL)
		{
			if (strcmp(temp-> f_name, filename)==0) //if file already present
			{
				//free(new);
				return DUPLICATE_FOUND; //duplicate
			}
			temp = temp->link;
		}
		temp -> link = new; //insert new file at last in linked list
		return SUCCESS;
	}
}