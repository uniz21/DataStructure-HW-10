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
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}


void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224s
 */
void iterativeInorder(Node* node)
{
	for (;;) {
		for (; node; node = node->left)
			push(node); /*스택에 삽입 */
		node = pop(); /*스택에서 삭제 */
		if (!node) break; /* 공백 스택 */
		printf(" [%d] ", node->key);
		node = node->right;
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	/* 레벨 순서 트리 순회 */
	if (!ptr) return; /* 공백 트리 */
	enQueue(ptr);
	for (; ; ) {
		ptr = deQueue();
		if (ptr) {
			printf(" % d ", ptr->key);
			if (ptr->left)
				enQueue(ptr->left);
			if (ptr->right)
				enQueue(ptr->right);
		}
		else break;
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

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
	Node* p = head->left;
	Node* parentNode = NULL;
	Node* childNode = NULL;
	int direction = 0;

	while (p != NULL)
	{
		if (key == p->key)
		{
			/* 리프 노드의 삭제 -> 그냥 삭제*/
			if ((p->left || p->right) == NULL)/* 두 자식노드가 모두 NULL이어야 한다. */
			{
				free(p);
				if (direction == 1)
					parentNode->right = NULL;
				else if (direction == -1)
					parentNode->left = NULL;

				return 1;
			}
			/* 하나의 자식을 가진 줄기 노드 삭제 -> 자식노드로 대체 */
			/* 두 자식노드가 모두 NULL인 경우를 위에서 지나왔으므로 적어도 하나 이상의 자식노드가 NULL이 아니다. */
			else if ((p->left && p->right) == NULL)/* AND 논리 연산을 통해 두 노드중 하나만 NULL인 경우 */
			{
				if (p->left != NULL)
					childNode = p->left;
				else
					childNode = p->right;

				free(p);
				if (direction == 1)
					parentNode->right = childNode;
				else if (direction == -1)
					parentNode->left = childNode;

				return 1;
			}
			/* 두개의 자식을 가진 줄기 노드 삭제 -> 오른쪽 서브트리의 가장 작은 원소로 root를 대체 */
			/* 자식노드들이 (NULL,NULL), (left,NULL), (NULL, right)인 경우를 모두 확인한 뒤이므로 모든 자식노드들이 비어있지 않은 상태 */
			else
			{


				return 1;
			}
		}

		parentNode = p;

		if (key > p->key)
		{
			direction = 1;
			p = p->right;
		}
		else 
		{
			direction = -1;
			p = p->left;
		}
	}
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}


int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	if (top == -1)
	{
		/* 스택이 비어있는 경우 Iterative Inorder를 종료하므로 경고를 출력할 필요가 없다. */
		/* printf("Stack is empty"); */
		return NULL;
	}
	Node* temp = stack[top];
	stack[top] = NULL;
	top--;

	return temp;
}


void push(Node* aNode)
{
	if (top == MAX_STACK_SIZE - 1)
	{
		/* 스택이 가득 차있더라도, Iterative Inorder 수행과정에서 pop된 이후 다시 push하므로 경고를 출력할 필요가 없다. */
		/* printf("Stack is full"); */
		return;
	}
	top++;
	stack[top] = aNode;

	return;
}


Node* deQueue()
{

}


void enQueue(Node* aNode)
{

}
