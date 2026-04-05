/*******************************************************************************************************************************************************************
*Title			: Multiplication
*Description	: This function performs multiplication of two given large numbers and store the result in the resultant list.
*Prototype		: int Multiplication(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **res_head, Dlist **res_tail);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: res_head: Pointer to the first node of the resultant double linked list.
			: res_tail: Pointer to the last node of the resultant double linked list.
*Output		: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"

int Multiplication(Dlist *head1, Dlist *tail1,Dlist *head2, Dlist *tail2, Dlist **res_head, Dlist **res_tail)
{
    Dlist *t1, *t2 = tail2;
    Dlist *op1_head = NULL, *op1_tail = NULL;
    Dlist *op2_head = NULL, *op2_tail = NULL;
	//to add the two rows every time
    Dlist *add_head = NULL, *add_tail = NULL;
	//count to add zeros while multiplying
    int zero_count = 0;
    //run a outer loop till NULL
    while (t2)
    {	//set carry to 0 everytime
        int carry = 0;
		//for every one iteration of inner loop, update t1 to tail again
        t1 = tail1;
        op2_head = op2_tail = NULL;

        // add zero's into second list after 1st iteration
        for (int j = 0; j < zero_count; j++)
            if(insert_first(&op2_head, &op2_tail, 0)==FAILURE)
				return FAILURE;

        // multiply until list reaches NULL
        while (t1)
        {
            int prod = (t1->data * t2->data) + carry;
            carry = prod / 10;
            prod = prod % 10;
			//insert prod into list
            if(insert_first(&op2_head, &op2_tail, prod)==FAILURE)
				return FAILURE;
			//traverse
            t1 = t1->prev;
        }
		//if carry remains after each iteration of list1
        if (carry)
            if(insert_first(&op2_head, &op2_tail, carry)==FAILURE)
				return FAILURE;

        // if first iteration then only store data in op1
        if (op1_head == NULL)
        {
            op1_head = op2_head;
            op1_tail = op2_tail;
        }
		//from 2 iteration onwards, call addition() to get result
        else
        {	add_head=NULL;
        	add_tail=NULL;
            if(Addition(op1_head, op1_tail,op2_head, op2_tail, &add_head, &add_tail)==FAILURE)
				return FAILURE;
			//delete two lists to store new data
            dl_delete_list(&op1_head, &op1_tail);
            dl_delete_list(&op2_head, &op2_tail);
			//update list 1 with res from addition function
            op1_head = add_head;
            op1_tail = add_tail;
        }
		//lastly update zero_count and traverse 2nd list
        zero_count++;
        t2 = t2->prev;
    }
	//atlast, store final result in res_list
    copy_list(op1_head,op1_tail,res_head,res_tail);
    
    dl_delete_list(&op1_head,&op1_tail);
    
    return SUCCESS;
}
