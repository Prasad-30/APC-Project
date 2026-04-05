/*******************************************************************************************************************************************************************
*Title			: Subtraction
*Description	: This function performs subtraction of two given large numbers and store the result in the resultant list.
*Prototype		: int Subtraction(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **res_head, Dlist **res_tail);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: res_head: Pointer to the first node of the resultant double linked list.
			: res_tail: Pointer to the last node of the resultant double linked list.
*Output		: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"

/*Function definition for subtraction function*/
int Subtraction(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **res_head, Dlist **res_tail)
{
	
    int borrow=0;
    //run till tail1 reaches NULL
    while(tail1!=NULL){
        //store tail1 data in op1 by subtracting 1 if borrow is taken
        int op1 = tail1->data - borrow;
        //store op2 = 0
        int op2=0;
        if(tail2!=NULL){
            //if data is present in tail2 then update op2
            op2 = tail2->data;
        }

        //check for borrow
        if(op1 < op2){
            op1 += 10;
            borrow = 1;
        }
        else{
            borrow = 0;
        }
        //perform subtraction
        int sub = op1 - op2;
        //insert sub in result list
        if (insert_first(res_head, res_tail, sub) == FAILURE)
            return FAILURE;
        
        //traverse tail pointers
        tail1 = tail1->prev;
        if(tail2){
            tail2 = tail2->prev;
        }
    }

    return SUCCESS;
}
