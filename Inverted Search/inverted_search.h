#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define FILENAME_SIZE 15
#define WORD_SIZE 15

typedef struct node
{
    char f_name[FILENAME_SIZE];
    struct node *link;
}FLIST;

typedef struct linktable_node
{
    int word_count;
    char file_name[FILENAME_SIZE];
    struct linktable_node *table_link;    
}Ltable;

typedef struct word_node
{
    int file_count;
    char word[WORD_SIZE];
    Ltable *Tlink;
    struct word_node *word_link;    
}Wlist;


typedef enum
{
    FAILURE,
    SUCCESS,
    FILE_EMPTY,
    FILE_NOT_AVAILABLE,
    DUPLICATE_FOUND
}status;

/* FILE VALIDATION */
void file_validation_n_file_list(FLIST **f_head, char *filenames[]); // validating file list 
status file_validation(FLIST **f_head, char filename[]); //validating one file
status isFileEmpty(char filename[]); //file empty or not
status create_list_of_files(FLIST **head, char filename[]); // creating file list


/*Create Database*/
void create_database(FLIST *f_head, Wlist *w_head[]); //create database
void read_data_from_file(FLIST *f_head, Wlist *head[], char filename[]);//Read data from file
status insert_last(Wlist **head, char data[]); //insert last (strings)
status update_link_table( Wlist **head); //updating link table filename and word counts
int update_word_count(Wlist **head, char *filename); //updating wordcount in ltable


/*Display database*/
void display_database(Wlist *head[]);
void print_words_info(Wlist *head); //print data for one index


/*Update database*/
void update_database(Wlist *w_head[], FLIST **f_head);


/*Search Database*/
void search(Wlist *head, char word[]);


/*Save database*/
void save_database(Wlist *head[]);
void write_database_to_file(Wlist *head, FILE *fptr); //write one index words and its info to the output file