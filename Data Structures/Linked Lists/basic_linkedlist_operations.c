#include<stdio.h>
#include<stdlib.h>

struct node
{
	int data;
	struct node *next;
};


// Add a node at the front
void push(struct node** head_ref, int new_data)
{
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	new_node->data = new_data;
	new_node->next = *head_ref;
	*head_ref = new_node;
}


// Recursive implementation of deleting a node with a given value
struct node* delete_rec(struct node* curr, int value)
{
	if (curr == NULL)
		return NULL;

	// check to see if current node is the one to be deleted
	if (curr->data == value) {
		struct node* temp;
		temp = curr->next;
		free(curr);
		//return the new pointer to where we were called from
		//the pointer of the upper caller will use it to skip over
		//the removed node
		return temp;
	}

	// chekck the rest of the list
	curr->next = delete_rec(curr->next, value);
	return curr;
}

// iterative implementation of deleting a node with a given value
void delete_iter(struct node** head_ref, int key)
{
	// store head node
	struct node* curr = *head_ref;
	struct node* prev;

	// If head node itself holds the key to be deleted
	if (curr != NULL && curr->data == key)
	{
		*head_ref = curr->next;
		free(curr);
		return;
	}

	// search the key in the rest of the list
	while (curr != NULL && curr->data != key)
	{
		prev = curr;
		curr = curr->next;
	}

	// if key was not present in the list
	if (curr == NULL) return;

	// skip over the node to be deleted
	prev->next = curr->next;
	free(curr);
}

// insert a node after an given node
void insert(struct node* prev_node, int new_data)
{
	if (prev_node == NULL)
	{
		printf("the given previous node cannot be NULL");
		return;
	}

	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	new_node->data = new_data;
	new_node->next = prev_node->next;
	prev_node->next = new_node;
}


// append a node to the end of the list
void append(struct node** head_ref, int new_data)
{
	// allocate node
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	struct node* last = *head_ref;

	//put in the data
	new_node->data = new_data;

	// The new node will be the last one, so make next of it as NULL
	new_node->next = NULL;

	// If the list is empty, then make the new node as head
	if (*head_ref == NULL)
	{
		*head_ref = new_node;
		return;
	}

	// traverse till the last node
	while (last->next != NULL)
		last = last->next;

	// change the next of last node
	last->next = new_node;
}

// print the data of every nodes
void printList(struct node *n)
{
	while (n != NULL)
	{
		printf(" %d ", n->data);
		n = n->next;
	}
}

int main()
{
	struct node* head = NULL;

	append(&head, 1);
	append(&head, 4);
	insert(head, 5);
	push(&head, 7);
	head = delete_rec(head, 1);
	delete_iter(&head, 4);
	printList(head);

	getchar();
	return 0;
}