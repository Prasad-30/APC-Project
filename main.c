/*Name : Prasad Kumbhar
  Project Name: Arithmetic Precision Calculator (APC)
  Date : 22-01-2026

  Description :
  * This project performs arithmetic operations on very large numbers
  * that cannot be handled by normal C data types. Numbers are stored
  * using doubly linked lists, allowing high-precision calculations.
  * It supports addition, subtraction, multiplication, division, and
  * modulus operations through command-line input with proper sign handling.
  
  Concepts Used :
  * Doubly Linked List
  * Dynamic Memory Allocation
  * Command-Line Arguments
  * String Processing
  * Modular Programming(Different files according to the operation)

  Sample i/p & o/p:
  * For Addition : 
  * Input  : ./output.exe 123456789123456789 + 987654321987654321
  * Output : Addition is : 1111111111111111110
*/

#include "apc.h"

int main(int argc, char *argv[]){
	//declare the pointers for 3 lists
	Dlist *head1=NULL,*tail1=NULL, *head2=NULL,*tail2=NULL, *res_head=NULL,*res_tail=NULL;
	//validate the arguments from command line
	if(validate_arg(argc, argv)==FAILURE){
		//if arguments are not valid, then print error and usage message
		printf(RED "ERROR: Enter valid arguments!!\n" RESET);
		printf(MAGENTA"USAGE:\n"
				"\tTo perform Addition      : %s operand1 + operand2\n"
				"\tTo perform Subtraction   : %s operand1 - operand2\n"
				"\tTo perform Multiplication: %s operand1 x operand2\n"
				"\tTo perform Division      : %s operand1 / operand2\n"
				"\tTo perform Modulus       : %s operand1 %% operand2\n"RESET,argv[0], argv[0], argv[0], argv[0],argv[0]);

		return 0;
	}
	//function call to convert string from argv into double-linked list
	if(convert_str_list(argv,&head1,&tail1,&head2,&tail2) == FAILURE){
		printf("Conversion failed\n");
		return 0;
	}
	//remove leading zeros from both input lists(e.g 0004 -> 4)
	if(rm_leading_zeros(&head1,&tail1) == FAILURE){
		printf("Failed to remove zeros\n\n");
		return 0;
	}
	//for list2
	if(rm_leading_zeros(&head2,&tail2) == FAILURE){
		printf("Failed to remove zeros\n\n");
		return 0;
	}
	/*this is for handling the signs in maths operations*/
	char sign1='+';
	char sign2='+';
	//for operand1
	printf(MAGENTA "Operand 1 : " RESET);
	if(argv[1][0]=='-' || argv[1][0]=='+'){
		sign1 = argv[1][0];
		printf("%c",sign1);
	}
	print_list(head1);
	//for operand2
	printf(MAGENTA "Operand 2 : " RESET);
	if(argv[3][0]=='-' || argv[3][0]=='+'){
		sign2 = argv[3][0];
		printf("%c",sign2);
	}
	print_list(head2);

	//store the operator
    char opr = argv[2][0];
	//perform switch-case operation based on operator
	switch (opr)
	{
	/*For addition operation*/
	case '+':
		if(sign1 == sign2){
			//same signs means call addition and
			Addition(head1,tail1,head2,tail2,&res_head,&res_tail);
			printf(MAGENTA"Addition is : "RESET);
			if(sign1=='-')
				
				printf("-"); //give the sign of first number
		}
		else{
			//different sign means perform subtraction
			int ret = compare_operands(head1,head2);
			if(ret == 1 || ret == 0){ //if first number is greater or both equal
			    Subtraction(head1,tail1,head2,tail2,&res_head,&res_tail);
				printf(MAGENTA"Addition is : "RESET);
				if(ret!=0){
					if(sign1 == '-')
						printf("-");
				}
			}	
			else { //if second number is greater
				Subtraction(head2,tail2,head1,tail1,&res_head,&res_tail);
				printf(MAGENTA"Addition is : "RESET);
				if(sign2 == '-')
					printf("-");
			}
		}
		break;
	case '-':
		//same signs means do subtraction
		if(sign1 == sign2){
			int ret = compare_operands(head1,head2);
			if(ret == 1 || ret == 0){  //if first number is greater or both equal
			    Subtraction(head1,tail1,head2,tail2,&res_head,&res_tail);
				printf(MAGENTA"Subtraction is : "RESET);
				if(ret!=0){
					if(sign1 == '-')
						printf("-");
				}
			}
			else{ //if second number is greater
				Subtraction(head2,tail2,head1,tail1,&res_head,&res_tail);
				printf(MAGENTA"Subtraction is : "RESET);
				if(sign2 != '-')
					printf("-");
			}
		}
		//different signs means perform addition
		else{
			Addition(head1,tail1,head2,tail2,&res_head,&res_tail);
			printf(MAGENTA"Subtraction is : "RESET);
			if(sign1=='-')
				printf("-"); //give sign of first number
		}
		break;
	/*For division operation*/
	case '/':
	 	if(Division(head1,tail1,head2,tail2,&res_head,&res_tail)==FAILURE){
			printf(RED "ERROR:Can't Divide By Zero!!\n" RESET);
			return 0;
		}
		printf(MAGENTA"Division is : "RESET);
		//print the signs based on operands
		if((sign1 != sign2) && (res_head->data!=0))
			printf("-");
	 	break;
	/*For multiplication operation*/
	case 'x':
	 	if(Multiplication(head1,tail1,head2,tail2,&res_head,&res_tail)==FAILURE)
			printf("Failed to multiply!!\n");
	    printf(MAGENTA"Multiplication is : "RESET);
		//print the signs based on operands
		if((sign1!=sign2) && (res_head->data!=0))
			printf("-");
	 	break;
	/*For modulus operation*/
	case '%':
		if(Modulus(head1,tail1,head2,tail2,&res_head,&res_tail)==FAILURE){
			printf(RED"ERROR:Can't Divide By Zero!!\n"RESET);
			return 0;
		}
		//print the signs based on operand 1
		printf(MAGENTA"Remainder is : "RESET);
		if((sign1=='-') && (res_head->data!=0))
			printf("-");
		break;
		
	default:
		printf(RED"ERROR:Enter valid operation!\n"RESET);
		break;
	}
	//removing leading zeros from result also
    if(rm_leading_zeros(&res_head,&res_tail) == FAILURE){
		printf("Failed to remove zeros\n\n");
		return 0;
	}
	//display the result
	if(print_list(res_head)==FAILURE){
		printf("List is empty!\n");
	}

	/*Finally delete the lists*/
	dl_delete_list(&head1,&tail1);
	dl_delete_list(&head2,&tail2);
	dl_delete_list(&res_head,&res_tail);
	return 0;
}