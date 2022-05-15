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



typedef struct node { // typedef ����� Node ����ü ����
	int key; // ������ ���� ���� 
	struct node *left; // ���� ��� ����
	struct node *right; // ������ ��� ����
} Node;

/* for stack */
#define MAX_STACK_SIZE		20 // max_stack ������ ���� 
Node* stack[MAX_STACK_SIZE]; // ���� ���� 
int top = -1; // top �ʱⰪ

Node* pop(); // ���� ��� ���� 
void push(Node* aNode); // ���� �Լ� ���� 

/* for queue */
#define MAX_QUEUE_SIZE		20 // ť max�� ���� 
Node* queue[MAX_QUEUE_SIZE]; // ť ���� 
int front = -1; // front �ʱⰪ
int rear = -1; // rear �ʱⰪ 

Node* deQueue(); // ���� ť ���� 
void enQueue(Node* aNode); // ���� ť ���� 


int initializeBST(Node** h);  // �ʱ�ȭ �Լ�

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack(); // ���� ��� �Լ� 



int main()
{
	char command; // ������ ���� ����
	int key; // ������ ���� ����
	Node* head = NULL; // ����� null ��

    printf("[----- [�����] [2018038099] -----]");

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

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {  // �ʱ�ȭ �Լ�

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL) // *h�� null�� �ƴϸ�
		freeBST(*h); // �����޸� ����

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));  // �����޸� �Ҵ�
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;  // right ��� *h��
	(*h)->key = -9999; // key ��

	top = -1; // top -1 ��

	front = rear = -1; // -1�� 

	return 1;
}



void recursiveInorder(Node* ptr) // ��ȯ�Լ� ���� ��ȸ
{
	if(ptr) {
		recursiveInorder(ptr->left); // recursiveInorderȣ�� �� ptr�� ����Ű�� left �ѱ� 
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right); // recursiveInorderȣ�� �� ptr�� ����Ű�� right �ѱ�
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node) // �ݺ� ���� ��ȸ 
{
	for(;;)
	{
		for(; node; node = node->left) // left��� �̵�
			push(node); // ���ÿ� ��� ���� 
		node = pop(); // ���ÿ��� ����

		if(!node) break; // ���� ����
		printf(" [%d] ", node->key);

		node = node->right; // node�� right ��
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr) // �������� ��ȸ 
{
	// int front = rear = -1;

	if(!ptr) return; /* empty tree */

	enQueue(ptr); // enQueue ȣ�� 

	for(;;)
	{
		ptr = deQueue(); // deQueue ȣ�� 
		if(ptr) {  // ptr�� null�� �ƴϸ�
			printf(" [%d] ", ptr->key);

			if(ptr->left) // left�� null �� �ƴϸ�
				enQueue(ptr->left); // enQueue left
			if(ptr->right) // right�� null �� �ƴϸ� 
				enQueue(ptr->right); // enQueue right
		}
		else
			break;

	}

}


int insert(Node* head, int key) // ��� ���� �Լ�
{
	Node* newNode = (Node*)malloc(sizeof(Node));  // �����޸� �Ҵ�
	newNode->key = key; // ��忡 �Էµ� Ű�� ����
	newNode->left = NULL; // left�� null
	newNode->right = NULL; // right�� null

	if (head->left == NULL) { // left�� null �̸�
		head->left = newNode; // left�� ��尪 ����
		return 1;  // 1�� ��ȯ 
	}

	/* head->left is the root */
	Node* ptr = head->left; // ptr�� left�� 

	Node* parentNode = NULL; // parentNode�� null ��
	while(ptr != NULL) {  // ptr�� null�� �ƴϸ� �ݺ�

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1; // key���� ������ 1�� ��ȯ

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr; //ptr�� ���� 

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) // ptr�� ����Ű�� key���� ������ key������ ������
			ptr = ptr->right; // ptr�� right��
		else
			ptr = ptr->left;  // ptr�� left
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)  // parentNode�� ����Ű�� key���� �Է� key���� ������
		parentNode->left = newNode; // left�� newNode�� ����
	else
		parentNode->right = newNode; //right�� newNode�� 
	return 1;
}


int deleteNode(Node* head, int key) // ��� ���� �Լ� 
{
	if (head == NULL) { // head�� null �̸�
		printf("\n Nothing to delete!!\n");
		return -1; // -1�� ��ȯ
	}

	if (head->left == NULL) { // left�� null �̸�
		printf("\n Nothing to delete!!\n");
		return -1; // -1�� ��ȯ
	} 

	/* head->left is the root */
	Node* root = head->left; // ptr�� left��



	Node* parent = NULL; // parent null��
	Node* ptr = root; // ptr root��

	while((ptr != NULL)&&(ptr->key != key)) { // ptr�� null �� �ƴϸ鼭 ptr�� key���� �Է°��� ���� ������ �ݺ� 
		if(ptr->key != key) { // ptr�� ����Ű�� key���� �Է� Ű�� ���� ������ 

			parent = ptr;	/* save the parent */

			if(ptr->key > key) // �Է�Ű������ ptr key���� ũ��
				ptr = ptr->left; // ptr�� left��
			else
				ptr = ptr->right; // ptr�� right ��
		}
	}

	/* there is no node for the key */
	if(ptr == NULL) // ptr null �̸�
	{
		printf("No node for key [%d]\n ", key);
		return -1; // -1�� ��ȯ
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if(ptr->left == NULL && ptr->right == NULL) // left�� null �̸鼭 right�� null �̸�
	{
		if(parent != NULL) { /* parent exists, parent's left and right links are adjusted */
			if(parent->left == ptr)  // left�� ptr�� ������
				parent->left = NULL; // parent�� ����Ű�� left�� null��
			else
				parent->right = NULL; // parent�� ����Ű�� right�� null��
		} else {
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL; // head�� ����Ű�� left�� null ��

		}

		free(ptr); // �޸� ����
		return 1;
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL)) // left�� null �̸鼭 right�� null �̸�
	{
		Node* child; // ��� clide
		if (ptr->left != NULL) // left�� null�� �ƴϸ�
			child = ptr->left; // child�� left�� 
		else
			child = ptr->right; // child�� left�� 

		if(parent != NULL) // parent�� null�� �ƴϸ� 
		{
			if(parent->left == ptr) // parent left�� ptr�� ������ 
				parent->left = child; // parent�� ����Ű�� left �� child ��
			else
				parent->right = child;  // parent�� ����Ű�� right �� child ��
		} else {
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child; // root�� child ��
		}

		free(ptr); // �޸� ����
		return 1;
	}

	/**
	 * case 3: the node (ptr) has two children
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */

	Node* candidate; // ��� ���� 
	parent = ptr; // parent�� ptr��


	candidate = ptr->right; // candidate�� right��

	/* the smallest node is left deepest node in the right subtree of the ptr */
	while(candidate->left != NULL) // left�� null�� �ƴϸ�
	{
		parent = candidate; // parent�� candidate�� 
		candidate = candidate->left; // candidate �� candidate�� ����Ű�� left��
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate) // parent�� ����Ű�� right�� candidate�� ������ 
		parent->right = candidate->right; // parent right�� candidate right ��
	else
		parent->left = candidate->right; // parent left�� candidate right ��

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key; // ptr�� ����Ű�� key�� candidate�� key �� ���� 

	free(candidate); // �޸� ���� 
	return 1;
}


void freeNode(Node* ptr) // �޸� ���� �Լ�
{
	if(ptr) {
		freeNode(ptr->left);  // left �����޸� ����
		freeNode(ptr->right); // right �����޸� ����
		free(ptr); // ptr �����޸� ����
	}
}

int freeBST(Node* head) // �޸� ���� �Լ�
{

	if(head->left == head) // left�� head���� ������ 
	{
		free(head); // head �����޸� ����
		return 1;
	}

	Node* p = head->left;  // p �� left ��

	freeNode(p); // p �����޸� ����

	free(head);  // head �����޸� ����
	return 1;
}



Node* pop() // ��� ���� �Լ� 
{
	if (top < 0) return NULL; // ���� top�� 0���� ������ null�� ��ȯ 
	return stack[top--]; // stack top -- �� ��ȯ 
}

void push(Node* aNode) // ���� ���� �Լ� 
{
	stack[++top] = aNode; // stack�� ��� ����
}


void printStack() // ��������Լ� 
{
	int i = 0; // ������ ���� ����
	printf("--- stack ---\n");
	while(i <= top) // top�� i�� ���ų� ũ�� 
	{
		printf("stack[%d] = %d\n", i, stack[i]->key); 
	}
}


Node* deQueue() // ť ���� �Լ� 
{
	if (front == rear) { // front�� rear�� ������ 
		// printf("\n....Now Queue is empty!!\n" );
		return NULL; // null�� ��ȯ
	}

	front = (front + 1) % MAX_QUEUE_SIZE; // front�� front+1�� maxť�� ������ ��
	return queue[front]; // queue�� front�� ����

}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE; // rear �� rear+1�� maxť�� ������ ��
	if (front == rear) { // front�� rear�� ������ 
		// printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode; // queue�� aNode �� 
}





