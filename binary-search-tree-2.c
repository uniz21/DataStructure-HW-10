/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);

int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */
Node* minSub(Node* ptr);
//void printStack();

int main()
{
	char command;
	int key;
	Node* head = NULL;

	printf("[----- [Yoon Yong Jin] [2016039040] -----]");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			/* head?? ?????????? ???????? head->left?? ???????? ???? */
			if (head == NULL)
			{
				printf("Initialize First");
				break;
			}
			else
			{
				recursiveInorder(head->left);
				break;
			}
		case 't': case 'T':
			/* head?? ?????????? ???????? head->left?? ???????? ???? */
			if (head == NULL)
			{
				printf("Initialize First");
				break;
			}
			else
			{
				iterativeInorder(head->left);
				break;
			}

		case 'l': case 'L':
			/* head?? ?????????? ???????? head->left?? ???????? ???? */
			if (head == NULL)
			{
				printf("Initialize First");
				break;
			}
			else
			{
				levelOrder(head->left);
				break;
			}

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

/* ?????? */
int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	/* ???? ?????? */
	top = -1;

	/* ?? ?????? */
	front = rear = -1;

	return 1;
}


void recursiveInorder(Node* ptr)
{
	if(ptr) {/* ???? ?????? NULL?? ?????? */
		recursiveInorder(ptr->left);/* ???? ???? ???????? */
		printf(" [%d] ", ptr->key);/* ???? */
		recursiveInorder(ptr->right);/* ?????? ???? ???????? */
	}
}

/**
 * textbook: p 224s
 */
void iterativeInorder(Node* node)
{
	/* ?????? ?????? ???? ???? ???? */
	if (node == NULL)
	{
		printf("There is no Tree");
		return;
	}

	/* ???????? */
	for (;;) {
		/* ???????? */
		for (; node; node = node->left)/* ???? ?????? NULL?? ??????, */
			push(node); /* ?????? ???? ???? ???? ???? ???????? */

		node = pop(); /* ???????? ?????? ????, */
		if (!node) break; /* ???? ???????? ????, */
		printf(" [%d] ", node->key);/* ???? ?????? ?????? ???????? */

		node = node->right;/* ?????? ???? ???? */
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	/* ?????? ?????? ???? ???? ???? */
	if (ptr == NULL)
	{
		printf("There is no Tree");
		return;
	}

	front = -1;
	rear = -1;

	/* ???? ???? ???? ???? */
	if (!ptr) return; /* ???? ???? */
	
	enQueue(ptr);/* ???? ???? ???? */

	/* ???????? */
	for (; ; ) {
		ptr = deQueue(); /* ?????? ?????? ?????? ptr?? ???? */

		if (ptr) {/* ptr?? ????????(NULL)?? ?????? */
			printf(" [%d] ", ptr->key);/* ???? */
		
			if (ptr->left)/* ???? ?????? ?????? */
				enQueue(ptr->left);/* ???? ???? */
			if (ptr->right)/* ?????? ?????? ?????? */
				enQueue(ptr->right);/* ???? ???? */
		}
		else break;/* ptr?? ???? ?????? ???? */
	}
}


int insert(Node* head, int key)
{
	/* head?? ?????????? ???????? */
	if (head == NULL)
	{
		printf("Initialize First");
		return 0;
	}

	/* ?????? ???? ???? */
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	/* ?????? ?????? ?????? */
	if (head->left == NULL) {
		/* root?????? ???? */
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	/* ???? ?? ???? ???? ?????? ???????? ???? ???? */
	Node* parentNode = NULL;

	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	/* head?? ?????????? ???????? */
	if (head == NULL)
	{
		printf("Initialize First");
		return 0;
	}
	/* root?????? NULL?? ???? */
	else if (head->left == NULL)
	{
		printf("There is no Tree");
		return 0;
	}

	Node* p = head;
	Node* parentNode = NULL; /* ?????? ?????? ???????? */
	Node* childNode = NULL; /* ?????? ?????? ?????? ???????? */
	int direction = 0; /* ?????? ?????? ???? */

	while (p != NULL)
	{
		/* ?????????? ?????? root?????? ????, ?????????? ?????? root?????? ???????? ??????
		*  ?? ???? ?? head?????? ?????????? ????????. */
		if (p->right == p)/* ???? ?????? head???? */
		{
			parentNode = p; /* head?? ?????????? ???? */
			direction = -1; /* head?????? ?????? root ?????? ?????? */
			p = p->left; /* root???? ?????? ???? */
			continue;
		}

		if (key == p->key) /* ?????? ???? ?????? */
		{
			/* ???? ?????? ???? -> ???? ????*/
			if ((p->left || p->right) == NULL)/* ?? ?????????? ???? NULL?????? ????. */
			{
				free(p);/* ?????? ???? */

				/* ?????? ?????? ?????????? ???? ?????? ???? ???? ???????? ???? */
				if (direction == 1)/* ?????? ???? */
					parentNode->right = NULL;/* ???????? */
				else if (direction == -1)/*  ???? ????*/
					parentNode->left = NULL;/* ???????? */

				return 1;
			}
			/* ?????? ?????? ???? ???? ???? ???? -> ?????????? ???? */
			/* ?? ?????????? ???? NULL?? ?????? ?????? ???????????? ?????? ???? ?????? ?????????? NULL?? ??????. */
			else if ((p->left && p->right) == NULL)/* AND ???? ?????? ???? ?? ?????? ?????? NULL?? ???? */
			{
				/* ?????????? ?????? ???? */
				if (p->left != NULL) /* ???? */
					childNode = p->left;/* ?????? ???? ???? ???? */
				else/* ?????? */
					childNode = p->right;/* ?????? ???? ???? ???? */

				free(p);/* ?????? ???? */

				/* ?????? ?????? ?????????? ???? ?????? ???? ???? ???????? ???? */
				if (direction == 1)/* ?????? ???? */
					parentNode->right = childNode;/* ?????? ?? ?????????? ???? */
				else if (direction == -1)/* ???? ???? */
					parentNode->left = childNode;/* ?????? ?? ?????????? ???? */

				return 1;
			}
			/* ?????? ?????? ???? ???? ???? ???? 
			*  -> ???? ?????????? ???? ?? ???? ???? ?????? ?????????? ???? ???? ?????? root?? ????(?????? ??????)
			*  (???????? ?????? ?????? ???????? ????) */
			/* ???????????? (NULL,NULL), (left,NULL), (NULL, right)?? ?????? ???? ?????? ???????? ???? ???????????? ???????? ???? ???? */
			else
			{
				/* ?????? ?????????? ???? ???? ?? ???? ???? ?????? ???? */
				childNode = minSub(p->right);/* ?????????? ???? */

				if (childNode == p->right) /* ?????? ?????????? ????????(???????? NULL?? ????????)???? */
				{
					if (childNode->right != NULL) /* ?????????? ?????? ?????? ?????? */
						childNode->right = p->right->right;/* ???? */
				}
				/* ?????? ?????????? ?????????? ?? ???????? */
				else
					childNode->right = p->right;/* ?????? ???? ?????? ?????????? ???????? ?????? ?????? ???? ???? ???????? ???? */

				childNode->left = p->left;/* ???? ???? ???? */

				free(p);/* ?????? ???? */

				/* ?????? ?????? ?????????? ???? ?????? ???? ???? ???????? ???? */
				if (direction == 1)/* ?????? ???? */
					parentNode->right = childNode;/* ?????? ?? ?????????? ???? */
				else if (direction == -1)/* ???? ???? */
					parentNode->left = childNode;/* ?????? ?? ?????????? ???? */

				return 1;
			}
		}

		/* ???? ???? ???? ???? ?????? ???? ?????? ???? ?????? ???? */
		parentNode = p;

		if (key > p->key)/* ???? ?? ???? ???? ???????? ?????? */
		{
			direction = 1;/* ?????? ?????????? ?????? ?????????? ????????. */
			p = p->right;/* ?????? ???? ???? */
		}
		else /* ???? ?? ???? ???? ???????? ?????? */
		{
			direction = -1;/* ?????? ?????????? ?????? ???????? ????????. */
			p = p->left;/* ???? ???? ???? */
		}
	}

	/* ?????? ???? ???? ?????? ?????? ?????? ???? ???????? */
	printf("Cannot fint the Node");/* ???? ???? ?? ???? */
	return 0;
}

/* subtree ???? ?? (?????? ??)???? ???? ???? */
Node* minSub(Node* ptr)
{
	Node* temp;
	Node* parent = NULL;/* ?????????? ?????? ?????? ?????????? ?????? ?????????? ???? ???? parent?? NULL*/
	/* ?? ???? ?????? ?????? ?????? ?????? ?????????? ????????.(???? ???? ?????? ?????? ???? ???? ??????) */
	while (ptr != NULL)/* ?????? ?????? ?????? ???? ?? ???? ????*/
	{
		if (ptr->left == NULL)/* ???? ???? ?????? ?????? ???? ?????? ???? ?????? ???? ???? */
		{
			if (parent != NULL)/* parent?? ??????????*/
			{
				parent->left = NULL;/* ???? ?????? ???? ?????? ???????? */
				return ptr;/* ?????????? ???? */
			}
			else break; /* parent?? NULL???? ?????????? ?????????? root?????????? break */
		}
		parent = ptr; /* ???? ???? ???? ?????? ?????????? ?????????? ????????. */
		ptr = ptr->left;/* ???? ???? ???? */
	}
	return ptr;/* ?????? ?????? ?????????? ?????? ???? ????????, ???? ?????? ???? ???? ???? ???? ?????? ???? ?????? ?????????? root???? */
}

/* ?????? ???? */
void freeNode(Node* ptr)
{
	if(ptr) {/* ?????????? ?????? ?????? */
		freeNode(ptr->left);/* ???? ????(???? ?? ?????? ????) */
		freeNode(ptr->right);/* ?????? ????(???? ?? ?????? ????) */
		free(ptr);/* ?????? ???? */
	}
}

int freeBST(Node* head)
{
	/* root?????? head?????? ?????? */
	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left; /* root???? */

	freeNode(p); /* root????(???????? ????) ?????? ???? */
	free(head);/* head???? ?????? ???? */
	
	return 1;
}

/* ???? POP */
Node* pop()
{
	if (top == -1)/* ?????? ???????? */
	{
		/* ?????? ???????? ???? Iterative Inorder?? ?????????? ?????? ?????? ?????? ????. */
		/* printf("Stack is empty"); */
		return NULL; /* ???? */
	}
	Node* temp = stack[top]; /* ???????? ???? ???? ???? */
	stack[top] = NULL;/* ???? ???? */
	top--;/* ?????? ?????? ?????? ?????? ???????? top?? 1?????????? */

	return temp; /* ???? ???? temp?? ???? */
}

/* ???? PUSH */
void push(Node* aNode)
{
	if (top == MAX_STACK_SIZE - 1)/* ?????? ???? ???????? */
	{
		/* ?????? ???? ??????????, Iterative Inorder ???????????? pop?? ???? ???? push?????? ?????? ?????? ?????? ????. */
		/* printf("Stack is full"); */
		return;/* ???? */
	}
	top++; /* top?? 1???? ?????????? */
	stack[top] = aNode;/* ???? ???? */
}

/* ?? deQueue */
Node* deQueue()
{
	/* ???? ???????? ???? */
	if (front == rear) return NULL;/* front?? rear?? ???? ?????? ???? ???? ?????? ????. */
	front++;/* ???? ?????? ????????(front ???????? ?????? ???? ????(????)??) front???? 1???? ??????????. */
	Node* temp = queue[front];/* ?????? ???? ???? */
	queue[front] = NULL;/* ???? ???? */
	return temp;/* ???? ???? */
}

/* ?? enQueue */
void enQueue(Node* aNode)
{
	/* ???? ???? ?????? */
	if (rear == MAX_QUEUE_SIZE - 1)
	{
		/* ???? ?? ?????? ?????????? */
		int size = rear - front;/* ???? ???????? ?????? ???? ??????. */
		for (int i=0;i<size;i++)/* ???? ???? ?? ???? ???? */
		{
			queue[i] = queue[front+(i+1)];/* ???????? ???? ?????? ??????????*/
			queue[front + (i + 1)] = NULL;
		}
		front = -1;/* front ?????? */
		rear = size-1; /* rear???? size-1?? ?????? ???? front?? rear???? ???? ???? */
		return;
	}
	rear++;/* ???? ???? ???????? rear???? 1???? ??????????.*/
	queue[rear] = aNode;/* ?????? ???? ???? */
}