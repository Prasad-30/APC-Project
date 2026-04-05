/*******************************************************************************************************************************************************************
*Title			: Division
*Description	: This function performs division of two given large numbers and store the result in the resultant list.
*Prototype		: int Division(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **res_head, Dlist **res_tail);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: res_head: Pointer to the first node of the resultant double linked list.
			: res_tail: Pointer to the last node of the resultant double linked list.
*Output		: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"

int Division(Dlist *head1, Dlist *tail1,
             Dlist *head2, Dlist *tail2,
             Dlist **res_head, Dlist **res_tail)
{
    //if 2nd operand is 0
    if(head2 == tail2 && head2->data==0){
        return FAILURE; //can't divide by 0
    }
    //if 1st operand is 0
    if(head1 == tail1 && head1->data==0){
        insert_first(res_head,res_tail,0); //directly store 0
        return SUCCESS;  
    }
    //to update list1 value everytime
    Dlist *new_head = NULL, *new_tail = NULL;
    //to traverse upto last digit in list1
    Dlist *temp = head1;

    while(temp){
        //get 1 digit from list1 and store in new_list
        insert_last(&new_head,&new_tail,temp->data);

        int count=0;
        //now compare until op1>=op2
        while(compare_operands(new_head,head2)>=0){
            //to store subtraction result
            Dlist *sub_head = NULL, *sub_tail = NULL;
            //perform subtraction
            Subtraction(new_head,new_tail,head2,tail2,&sub_head,&sub_tail);
            //free old data of new_list
            dl_delete_list(&new_head,&new_tail);

            //update new_list with sub_list from subtraction
            new_head = sub_head;
            new_tail = sub_tail;
            //remove zeros, because subtraction may contain leading 0's
            rm_leading_zeros(&new_head, &new_tail);
            
            count++; //increment the count
        }
        //insert count in res_list i.e quotient
        insert_last(res_head,res_tail,count);
        //traverse to next digit
        temp = temp->next;
    }
    rm_leading_zeros(res_head,res_tail);
    dl_delete_list(&new_head,&new_tail);

    return SUCCESS;
}
