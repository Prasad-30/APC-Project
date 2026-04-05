/*******************************************************************************************************************************************************************
*Title			: Addition
*Description	: This function performs addition of two given large numbers and store the result in the resultant list.
*Prototype		: int Addition(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **res_head, Dlist **res_tail);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: res_head: Pointer to the first node of the resultant double linked list.
			: res_tail: Pointer to the last node of the resultant double linked list.
*Output		: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"

int Addition(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **res_head, Dlist **res_tail)
{
	/* Definition goes here */
	int carry=0;
	//repeat till all the nodes
    while(tail1!=NULL && tail2!=NULL){
		//store sum
		int sum = tail1->data + tail2->data + carry;
		//check for carry
		if(sum>9){
			carry=1;
			sum = sum%10; //to get last digit
		}
		else{
			carry=0; //if single digit sum means kepp carry 0
		}
		if(insert_first(res_head,res_tail,sum)==FAILURE)
			return FAILURE;
		
		//traverse
		tail1 = tail1->prev;
		tail2 = tail2->prev;
	}
	// handle remaining nodes of longer list
	Dlist *rem = NULL;

	// decide which list still has elements
	if (tail1 != NULL)
		rem = tail1;
	else if (tail2 != NULL)
		rem = tail2;

	// process remaining digits
	while (rem != NULL)
	{	//perform addition of carry with remaining data
		int sum = rem->data + carry;
        carry=0;
		if(sum>9){
			carry=1;
			sum = sum%10;
		}
		else{
			carry=0;
		}
		//call insert_first function
		if (insert_first(res_head, res_tail, sum) == FAILURE)
			return FAILURE;
		//traverse the list
		rem = rem->prev;
	}

	//add final carry if present
	if(carry){
		//insert carry at first
		if(insert_first(res_head,res_tail,carry)==FAILURE)
			return FAILURE;
	}

	return SUCCESS;
}
