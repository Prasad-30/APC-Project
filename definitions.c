#include "apc.h"

/*This File contains all the necessary function definitions*/


/*function to validate the the arguments*/
int validate_arg(int argc, char *argv[]){
    //validate number of arguments
    if(argc!=4){
        return FAILURE;
    }
    //validate first operand
    int i=0;
    while(argv[1][i]){
        //ignore the first signs
        if(argv[1][0]=='+' || argv[1][0]=='-'){
            i++;
            continue;
        }
        //if operand1 contains any character, return failure
        if(!isdigit(argv[1][i])){
            printf(RED"Operand1 should contain only digits!!\n"RESET);
            return FAILURE;
        }
        i++;
    }
    //operator length should be 1
    if(argv[2][1]!='\0'){
        return FAILURE;
    }
    //validate operator
    if(argv[2][0]!='+' && argv[2][0]!='-' && argv[2][0]!='x' && argv[2][0]!='/' && argv[2][0]!='%' && argv[2][0]!='^'){
        return FAILURE;
    }
    
    //validate 2nd operand
    i=0;
    while(argv[3][i]){
        //ignore the first signs if present
        if(argv[3][0]=='+' || argv[3][0]=='-'){
            i++;
            continue;
        }
        //if operand2 contains any character, return failure
        if(!isdigit(argv[3][i])){
            printf(RED"Operand2 should contain only digits!!\n"RESET);
            return FAILURE;
        }
        i++;
    }
    
    return SUCCESS;
}

/*function for converting operand string into DLL*/
int convert_str_list(char *argv[], Dlist **head1, Dlist **tail1,Dlist **head2, Dlist **tail2)
{   
    //for 1st operand
    int i=0;
    if(argv[1][0] == '+' || argv[1][0] == '-'){
        i++;
    }
    //run a loop until \0
    while(argv[1][i]!='\0'){
        
        //convert each character to int
        int data1 = argv[1][i] -'0';
        //insert at last
        if(insert_last(head1,tail1,data1)==FAILURE)
            return FAILURE;
        i++;
    }

    //for 2nd operand
    i=0;
    if(argv[3][0] == '+' || argv[3][0] == '-'){
        i++;
    }
    //run a loop until \0
    while(argv[3][i]!='\0'){
        //convert each character to int
        int data2 = argv[3][i]-'0';
        //insert at last
        if(insert_last(head2,tail2,data2)==FAILURE)
            return FAILURE;
        i++;
    }
    
    return SUCCESS;
}

/*function for inserting element at last in DLL*/
int insert_last(Dlist **head, Dlist **tail, int data){
    //create a newnode
    Dlist *newnode = malloc(sizeof(Dlist));
    //check memory allocation
    if(!newnode){
        return FAILURE;
    }
    //handle data and linking part
    newnode->data = data;
    newnode->prev = NULL;
    newnode->next = NULL;
    //if list is empty
    if(*head == NULL){
        //point head and tail to same node
        *head = *tail = newnode;
        return SUCCESS;
    }
    //if list is not empty
    newnode->prev = *tail;
    (*tail)->next = newnode;
    *tail = newnode;
    return SUCCESS;
}

/*Function to print the result*/
int print_list(Dlist *res_head){
    if(res_head == NULL){
        return FAILURE;
    }
    // printf("Result: ");
	while (res_head)		
	{
		/* Printing the list */
		printf("%d", res_head -> data);

		/* Travering in forward direction */
		res_head = res_head -> next;
	}
    printf("\n");
    return SUCCESS;
}

/*Function to insert first in reslist*/
int insert_first(Dlist **head, Dlist **tail, int sum){
    //create newnode
		Dlist *newnode = malloc(sizeof(Dlist));
        if(!newnode){
            return FAILURE;
        }
		//assign sum to newnode
		newnode->data = sum;
		newnode->prev = NULL;
		newnode->next = NULL;
		//insert first in result list
		if(*head == NULL){ //if empty
			*head = *tail = newnode;
		}
		else{
            //if not empty
			newnode->next = *head;
			(*head)->prev = newnode;
			*head = newnode;
		}
        
        return SUCCESS;
} 

/*Function to compare the two list*/
int compare_operands(Dlist *head1, Dlist *head2){
    //first skip the leading zeros from both lists
    while(head1!=NULL && head1->data == 0)
        head1 = head1->next;

    while(head2!=NULL && head2->data == 0)
        head2 = head2->next;

    //now find the length of both list
    int len1=0, len2=0;
    Dlist *t1 = head1, *t2 = head2;
    //for list1
    while(t1){
        len1++;
        t1 = t1->next;
    }
    //for list2
    while(t2){
        len2++;
        t2 = t2->next;
    }
    //compare lenghts
    if(len1 > len2)
        return 1; //if op1>op2
    if(len1 < len2)
        return -1; //if op<op2

    //if same lenghts, means compare datas until next digit varies
    while(head1!=NULL && head2!=NULL){
        if(head1->data > head2->data)
            return 1;
        if(head1->data < head2->data)
            return -1;
        //traverse
        head1=head1->next;
        head2=head2->next;
    }
    //if remains equal
    return 0;
}

/*Function to remove the leading zeros from both input lists*/
int rm_leading_zeros(Dlist **head1, Dlist **tail1){
    //check for 0's 
    while(*head1!=NULL && (*head1)->data==0){
        //if only one 0
        if((*head1)->next==NULL){
            free(*head1);
            *head1 = *tail1 = NULL;
        }
        else{
            Dlist *temp1 = *head1;
            *head1 = (*head1)->next;
            (*head1)->prev=NULL;
            free(temp1);
        }
    }
    //if only zeros are in input list
    //when all zeros removed, insert 1 zero
    if(*head1==NULL){
        if(insert_first(head1,tail1,0)==FAILURE)
            return FAILURE;
        return SUCCESS;
    }

    return SUCCESS;
}

/*function definition to delete the entire list*/
int dl_delete_list(Dlist **head, Dlist **tail)
{   
    //check if list is empty or not
    if(*head == NULL){
        return FAILURE;
    }
    //if not empty
    Dlist *temp; //declare a temp pointer
    //traverse through the list using head
    while(*head){
        //update temp with head everytime
        temp = *head;
        //update the head with next node
        *head = (*head)->next;
        //delete one by one temp
        free(temp);
    }
    //lastly make tail points to NULL, head is already pointing to NULL
    temp = *tail = NULL;
    
    return SUCCESS;
}

/*Function to copy one list into another*/
int copy_list(Dlist *src_head, Dlist *src_tail,
              Dlist **dest_head, Dlist **dest_tail)
{
    // initialize destination list
    *dest_head = NULL;
    *dest_tail = NULL;

    // if source list is empty
    if (src_head == NULL)
        return FAILURE;

    Dlist *temp = src_head;
    //traverse through the src list and insert data in dest list one by one
    while (temp)
    {
        insert_last(dest_head, dest_tail, temp->data);
        temp = temp->next;
    }

    return SUCCESS;
}
