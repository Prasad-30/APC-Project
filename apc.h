/*This file contains the structure and all the function prototypes*/

#ifndef APC_H
#define APC_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

// Text colors to use
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

// Reset
#define RESET   "\033[0m"

#define SUCCESS 0
#define FAILURE -1

//structure declaration
typedef struct apc
{
	int data;
	struct apc *prev;
	struct apc *next;
}Dlist;

/*Function Prototypes*/

/*Function to validate arguments*/
int validate_arg(int , char *argv[]);

/*Function to convert cmd argument into linked list*/
int convert_str_list(char *argv[],Dlist **,Dlist **,Dlist **,Dlist **);

/*Function to insert element at last in list*/
int insert_last(Dlist **head, Dlist **tail, int data);

/*Function to add two operands*/
int Addition(Dlist *, Dlist *, Dlist *, Dlist *, Dlist **, Dlist **);

/*Function to subtract 1 operand from another*/
int Subtraction(Dlist *, Dlist *, Dlist *, Dlist *, Dlist **, Dlist **);

/*Function to multiply 2 operands*/
int Multiplication(Dlist *, Dlist *, Dlist *, Dlist *, Dlist **, Dlist **);

/*Function to perform division operation*/
int Division(Dlist *, Dlist *, Dlist *, Dlist *, Dlist **, Dlist **);

/*Function to perform modulo operation*/
int Modulus(Dlist *, Dlist *, Dlist *, Dlist *, Dlist **, Dlist **);

/*Function to insert element at first in the list*/
int insert_first(Dlist**, Dlist**,int);

/*Function to print the entire list*/
int print_list(Dlist *);

/*Function to compare two lists*/
int compare_operands(Dlist *, Dlist *);

/*Function to remove leading zeros from list*/
int rm_leading_zeros(Dlist **, Dlist **);

/*Function to delete the entire list*/
int dl_delete_list(Dlist **, Dlist **);

/*Function to copy one list into another*/
int copy_list(Dlist *, Dlist *,Dlist **, Dlist **);
#endif