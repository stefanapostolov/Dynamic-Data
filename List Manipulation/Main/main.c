/*

	The program manipulates a list of characters. It is possible to
	insert a character in the list in alphabetic order (with an insert
	function) or delete a character from the list (with a delete function)
	                                      

*/

#include <stdio.h>
#include <stdlib.h>

struct listNode {
	char data; // every listNode contains a character
	struct listNode *nextPtr; // pointer to the next node
};

typedef struct listNode ListNode; // typedefing listNode
typedef ListNode *ListNodePtr; // typedefing ListNode*

// prototipi
void insert(ListNodePtr *sPtr, char value);
char delete(ListNodePtr *sPtr, char value);
int isEmpty(ListNodePtr sPtr);
void printList(ListNodePtr currentPtr);
void instructions();

int main(int argc, char *argv[]){

	ListNodePtr startPtr = NULL; // at the beginning there aren't any nodes
	char item; // the character is inserted by the user
	unsigned int choice; // user's choice

	instructions(); // print the menu
	printf("%s", "? ");
	scanf("%u", &choice);

	// repeat the cycle until the user doesn't chose number 3
	while(choice!=3){
		switch(choice){
			case 1:
				printf("%s", "Enter a character: ");
				scanf("\n%c", &item);
				insert(&startPtr, item); // insert the element in the list
				printList(startPtr);
				break;
			case 2: // delete an element
				// if the list is empty
				if(!isEmpty(startPtr)){
					printf("%s", "Enter character to be deleted: ");
					scanf("\n%c", &item);

					// if the character is found, delete it
					if(delete(&startPtr, item)){
						// delete element
						printf("%c deleted.\n", item);
						printList(startPtr);
					}
					else {
						printf("%c is not found.\n\n", item);
					}
				}
				else {
					puts("List is empty");
				}
				break;
			default:
				puts("Invalid choice.\n");
				instructions();
				break;
		}
		printf("%s", "? ");
		scanf("%u", &choice);
	}

	puts("End of run.\n");

	return 0;
}

// print the user instructions
void instructions(){
	puts("Enter your choice:\n"
		"	1 to insert an element into the list.\n"
		"	2 to delete an element from the list.\n"
		"	3 to end.");
}

// insert a new element in the list
void insert(ListNodePtr *sPtr, char value){

	ListNodePtr newPtr = malloc(sizeof(ListNode)); // create a node

	if(newPtr != NULL){
		// and there is memory available
		newPtr->data = value; // insert value in the node
		newPtr->nextPtr = NULL; // the node isn't connected to other nodes

		ListNodePtr previousPtr = NULL;
		ListNodePtr currentPtr = *sPtr;

		// repeat the cycle until the correct position is found
		while(currentPtr != NULL && value > currentPtr->data){
			previousPtr = currentPtr; // keep going
			currentPtr = currentPtr->nextPtr; // on the next node
		}

		// insert the new node at the beggining of the list
		if(previousPtr == NULL){
			newPtr->nextPtr = *sPtr;
			*sPtr = newPtr;
		} else {
			// insert the new node between previousPtr and currentPtr
			previousPtr->nextPtr = newPtr;
			newPtr->nextPtr = currentPtr;
		}
	}
	else {
		printf("%c not inserted. No memory available.\n", value);
	}
}

// delete an element from the list
char delete(ListNodePtr *sPtr, char value){

	// delete the first node and if there is another one found
	if(value == (*sPtr)->data){
		ListNodePtr tempPtr = *sPtr; // connect the node that needs to be removed
		*sPtr = (*sPtr)->nextPtr; // detach the node
		free(tempPtr); // free the node
		return value;
	}
	else {
		ListNodePtr previousPtr = *sPtr;
		ListNodePtr currentPtr = (*sPtr)->nextPtr;

		// repeat until the correct position gets identified
		while(currentPtr != NULL && currentPtr->data != value){
			previousPtr = currentPtr; // keep going
			currentPtr = currentPtr->nextPtr; // on the next node
		}

		// delete the node which is pointed by currentPtr
		if(currentPtr != NULL){
			ListNodePtr tempPtr = currentPtr;
			previousPtr->nextPtr = currentPtr->nextPtr;
			free(tempPtr);
			return value;
		}
	}

	return '\0';
}

// return 1 if the list is empty, else 0
int isEmpty(ListNodePtr sPtr){
	return sPtr == NULL;
}

// print the list
void printList(ListNodePtr currentPtr){
	// if the list is empty
	if(isEmpty(currentPtr)){
		puts("List is empty.\n");
	}
	else {
		puts("The list is:");

		// until the end of the list isn't reached
		while(currentPtr!=NULL){
			printf("%c --> ", currentPtr->data);
			currentPtr = currentPtr->nextPtr;
		}

		puts("NULL\n");
	}
}


