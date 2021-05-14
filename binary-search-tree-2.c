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
			/* head�� �ʱ�ȭ���� �ʾҴٸ� head->left�� �����Ҽ� ���� */
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
			/* head�� �ʱ�ȭ���� �ʾҴٸ� head->left�� �����Ҽ� ���� */
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
			/* head�� �ʱ�ȭ���� �ʾҴٸ� head->left�� �����Ҽ� ���� */
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

/* �ʱ�ȭ */
int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	/* ���� �ʱ�ȭ */
	top = -1;

	/* ť �ʱ�ȭ */
	front = rear = -1;

	return 1;
}


void recursiveInorder(Node* ptr)
{
	/* Ʈ���� ��尡 ���� ��� ���� */
	if (ptr == NULL)
	{
		printf("There is no Tree");
		return ;
	}

	if(ptr) {/* ���� ��尡 NULL�� �ƴϸ� */
		recursiveInorder(ptr->left);/* ���� ��� ���Ž�� */
		printf(" [%d] ", ptr->key);/* ��� */
		recursiveInorder(ptr->right);/* ������ ��� ���Ž�� */
	}
}

/**
 * textbook: p 224s
 */
void iterativeInorder(Node* node)
{
	/* Ʈ���� ��尡 ���� ��� ���� */
	if (node == NULL)
	{
		printf("There is no Tree");
		return;
	}

	/* ���ѹݺ� */
	for (;;) {
		/* ����ǥ�� */
		for (; node; node = node->left)/* ���� ��尡 NULL�� �ƴϸ�, */
			push(node); /* ���ÿ� ���� �ϰ� ���� ��� Ž���Ѵ� */

		node = pop(); /* ���ÿ��� ��带 ����, */
		if (!node) break; /* ���� �����̸� ����, */
		printf(" [%d] ", node->key);/* ���� ������ �ƴϸ� ����Ѵ� */

		node = node->right;/* ������ ��� Ž�� */
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	/* Ʈ���� ��尡 ���� ��� ���� */
	if (ptr == NULL)
	{
		printf("There is no Tree");
		return;
	}

	/* ���� ���� Ʈ�� ��ȸ */
	if (!ptr) return; /* ���� Ʈ�� */
	
	enQueue(ptr);/* ť�� ��� ���� */

	/* ���ѹݺ� */
	for (; ; ) {
		ptr = deQueue(); /* ť���� ������ ��带 ptr�� ���� */

		if (ptr) {/* ptr�� ������(NULL)�� �ƴϸ� */
			printf(" [%d] ", ptr->key);/* ��� */
		
			if (ptr->left)/* ���� ��尡 �ִٸ� */
				enQueue(ptr->left);/* ť�� ���� */
			if (ptr->right)/* ������ ��尡 �ִٸ� */
				enQueue(ptr->right);/* ť�� ���� */
		}
		else break;/* ptr�� ���� ���� ���� */
	}
}


int insert(Node* head, int key)
{
	/* head�� �ʱ�ȭ���� ������� */
	if (head == NULL)
	{
		printf("Initialize First");
		return 0;
	}

	/* ������ ��� ���� */
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	/* Ʈ���� ��尡 ���ٸ� */
	if (head->left == NULL) {
		/* root���� ���� */
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	/* Ž�� �� ���� �θ� ��带 ����ϱ� ���� ��� */
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
	/* head�� �ʱ�ȭ���� ������� */
	if (head == NULL)
	{
		printf("Initialize First");
		return 0;
	}
	/* root��尡 NULL�� ��� */
	else if (head->left == NULL)
	{
		printf("There is no Tree");
		return 0;
	}

	Node* p = head;
	Node* parentNode = NULL; /* ������ ����� �θ��� */
	Node* childNode = NULL; /* ������ ��带 ��ü�� �ڽĳ�� */
	int direction = 0; /* ������ ����� ���� */

	while (p != NULL)
	{
		/* �����ؾ��� ��尡 root����� ���, �ڽĳ�尡 �ִٸ� root��带 ��ü�ؾ� �ϹǷ�
		*  ù ���� �� head��带 �θ���� �����Ѵ�. */
		if (p->right == p)/* ���� ��尡 head��� */
		{
			parentNode = p; /* head�� �θ���� ���� */
			direction = -1; /* head���� ���ʿ� root ��带 ���´� */
			p = p->left; /* root��� �̾ Ž�� */
			continue;
		}

		if (key == p->key) /* ������ ��� �߽߰� */
		{
			/* ���� ����� ���� -> �׳� ����*/
			if ((p->left || p->right) == NULL)/* �� �ڽĳ�尡 ��� NULL�̾�� �Ѵ�. */
			{
				free(p);/* �޸� ���� */

				/* ������ ��尡 �θ����� ��� ���⿡ �ִ� �ڽ� ������� Ȯ�� */
				if (direction == 1)/* ������ ��� */
					parentNode->right = NULL;/* ����ó�� */
				else if (direction == -1)/*  ���� ���*/
					parentNode->left = NULL;/* ����ó�� */

				return 1;
			}
			/* �ϳ��� �ڽ��� ���� �ٱ� ��� ���� -> �ڽĳ��� ��ü */
			/* �� �ڽĳ�尡 ��� NULL�� ��츦 ������ ���������Ƿ� ��� �ϳ� �̻��� �ڽĳ�尡 NULL�� �ƴϴ�. */
			else if ((p->left && p->right) == NULL)/* AND �� ������ ���� �� ����� �ϳ��� NULL�� ��� */
			{
				/* �ڽĳ���� ��ġ�� Ȯ�� */
				if (p->left != NULL) /* ���� */
					childNode = p->left;/* ��ü�� �ڽ� ��� ���� */
				else/* ������ */
					childNode = p->right;/* ��ü�� �ڽ� ��� ���� */

				free(p);/* �޸� ���� */

				/* ������ ��尡 �θ����� ��� ���⿡ �ִ� �ڽ� ������� Ȯ�� */
				if (direction == 1)/* ������ ��� */
					parentNode->right = childNode;/* ������ �� �ڽĳ��� ��ü */
				else if (direction == -1)/* ���� ��� */
					parentNode->left = childNode;/* ������ �� �ڽĳ��� ��ü */

				return 1;
			}
			/* �ΰ��� �ڽ��� ���� �ٱ� ��� ���� 
			*  -> ���� ����Ʈ���� ���� ū ���� Ȥ�� ������ ����Ʈ���� ���� ���� ���ҷ� root�� ��ü(������ ������)
			*  (�̿�Ž�� Ʈ���� Ư���� �����ϱ� ����) */
			/* �ڽĳ����� (NULL,NULL), (left,NULL), (NULL, right)�� ��츦 ��� Ȯ���� ���̹Ƿ� ��� �ڽĳ����� ������� ���� ���� */
			else
			{
				/* ������ ����Ʈ���� ���� ���� Ű ���� ���� ��带 ���� */
				childNode = minSub(p->right);/* �ڽĳ��� ���� */

				/* ��ü�� ���� ������ �ڽĳ���� �������� ������ ����� ���� �ڽ� ������ ���� */
				childNode->right = p->right;
				childNode->left = p->left;

				free(p);/* �޸� ���� */

				/* ������ ��尡 �θ����� ��� ���⿡ �ִ� �ڽ� ������� Ȯ�� */
				if (direction == 1)/* ������ ��� */
					parentNode->right = childNode;/* ������ �� �ڽĳ��� ��ü */
				else if (direction == -1)/* ���� ��� */
					parentNode->left = childNode;/* ������ �� �ڽĳ��� ��ü */

				return 1;
			}
		}

		/* ���� �ڽ� ��� Ž�� ������ ���� ��带 �θ� ���� ���� */
		parentNode = p;

		if (key > p->key)/* ã�� Ű ���� ���� ��庸�� ũ�ٸ� */
		{
			direction = 1;/* Ž���� �ڽĳ���� ������ ���������� ����Ѵ�. */
			p = p->right;/* ������ ��� Ž�� */
		}
		else /* ã�� Ű ���� ���� ��庸�� �۴ٸ� */
		{
			direction = -1;/* Ž���� �ڽĳ���� ������ �������� ����Ѵ�. */
			p = p->left;/* ���� ��� Ž�� */
		}
	}

	/* Ʈ���� ��� Ž�� �ϰ� ������ ��带 ã�� ���ߴٸ� */
	printf("Cannot fint the Node");/* �ȳ� ��� �� ���� */
	return 0;
}

/* subtree Ž�� �� (�ּҰ� Ű)��� ���� �Լ� */
Node* minSub(Node* ptr)
{
	Node* temp;
	Node* parent;
	/* Ű ���� �ּ��� ��常 ã���� �ǹǷ� �������θ� Ž���Ѵ�.(�̿� Ž�� Ʈ���� Ư���� Ű�� �� ���ʿ�) */
	while (ptr != NULL)/* ���̻� Ž���� ��尡 ���� �� ���� �ݺ�*/
	{
		if (ptr->left == NULL)/* ���� �ڽ� ��尡 ���ٸ� ���� ��尡 �ּ� Ű���� ���� ��� */
		{
			parent->left = NULL;/* �θ� ����� ���� �ڽ��� ����ó�� */
			return ptr;/* �����带 ��ȯ */
		}
		parent = ptr; /* ���� ��� Ž�� ������ �����带 �θ���� ����Ѵ�. */
		ptr = ptr->left;/* ���� ��� Ž�� */
	}
}

/* �޸� ���� */
void freeNode(Node* ptr)
{
	if(ptr) {/* �����尡 ������ �ƴϸ� */
		freeNode(ptr->left);/* ���� ���(Ž�� �� �޸� ����) */
		freeNode(ptr->right);/* ������ ���(Ž�� �� �޸� ����) */
		free(ptr);/* �޸� ���� */
	}
}

int freeBST(Node* head)
{
	/* root��尡 head����� ���?? */
	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left; /* root��� */

	freeNode(p); /* root���(������� ����) �޸� ���� */
	free(head);/* head��� �޸� ���� */
	
	return 1;
}

/* ���� POP */
Node* pop()
{
	if (top == -1)/* ������ �����̸� */
	{
		/* ������ ����ִ� ��� Iterative Inorder�� �����ϹǷ� ��� ����� �ʿ䰡 ����. */
		/* printf("Stack is empty"); */
		return NULL; /* ���� */
	}
	Node* temp = stack[top]; /* ���ÿ��� ���� ��� ���� */
	stack[top] = NULL;/* ��� ���� */
	top--;/* ���ÿ� ��尡 ����� ��ġ�� ����Ű�� top�� 1���ҽ�Ų�� */

	return temp; /* ���� ��� temp�� ��ȯ */
}

/* ���� PUSH */
void push(Node* aNode)
{
	if (top == MAX_STACK_SIZE - 1)/* ������ ���� ���ִٸ� */
	{
		/* ������ ���� ���ִ���, Iterative Inorder ����������� pop�� ���� �ٽ� push�ϹǷ� ��� ����� �ʿ䰡 ����. */
		/* printf("Stack is full"); */
		return;/* ���� */
	}
	top++; /* top�� 1��ŭ ������Ų�� */
	stack[top] = aNode;/* ��� ���� */
}

/* ť deQueue */
Node* deQueue()
{
	/* ť�� �����̸� ���� */
	if (front == rear) return NULL;/* front�� rear�� ���� ���ٸ� ť�� � ��嵵 ����. */
	front++;/* ť�� ������ ����Ű��(front �������� ��尡 ť�� Ż��(����)��) front���� 1��ŭ ������Ų��. */
	Node* temp = queue[front];/* ������ ��� ���� */
	queue[front] = NULL;/* ��� ���� */
	return temp;/* ��� ��ȯ */
}

/* ť enQueue */
void enQueue(Node* aNode)
{
	/* ť�� ���� á�ٸ� */
	if (rear == MAX_QUEUE_SIZE - 1)
	{
		/* ���� ť ������ ������� */
		int size = rear - front;/* ť�� �����ִ� ����� ���� ���Ѵ�. */
		for (int i=0;i<size;i++)/* ���� ��� �� ��ŭ �ݺ� */
		{
			queue[i] = queue[front+(i+1)];/* ������ ť�� ������ �̵���Ų��*/
			queue[front + (i + 1)] = NULL;
		}
		front = -1;/* front �ʱ�ȭ */
		rear = size-1; /* rear���� size-1�� �ʱ�ȭ �Ͽ� front�� rear���� �Ÿ� ���� */
		return;
	}
	rear++;/* ť�� ���� ����Ű�� rear���� 1��ŭ ������Ų��.*/
	queue[rear] = aNode;/* ���ο� ��� ���� */
}