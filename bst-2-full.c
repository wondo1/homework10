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



typedef struct node { // typedef 사용한 Node 구조체 선언
	int key; // 정수형 변수 선언 
	struct node *left; // 왼쪽 노드 선언
	struct node *right; // 오른쪽 노드 선언
} Node;

/* for stack */
#define MAX_STACK_SIZE		20 // max_stack 사이즈 정의 
Node* stack[MAX_STACK_SIZE]; // 스택 정의 
int top = -1; // top 초기값

Node* pop(); // 삭제 노드 정의 
void push(Node* aNode); // 삽입 함수 정의 

/* for queue */
#define MAX_QUEUE_SIZE		20 // 큐 max값 정의 
Node* queue[MAX_QUEUE_SIZE]; // 큐 정의 
int front = -1; // front 초기값
int rear = -1; // rear 초기값 

Node* deQueue(); // 삭제 큐 정의 
void enQueue(Node* aNode); // 삽입 큐 정의 


int initializeBST(Node** h);  // 초기화 함수

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack(); // 스택 출력 함수 



int main()
{
	char command; // 문자형 변수 선언
	int key; // 정수형 변수 선언
	Node* head = NULL; // 헤드노드 null 값

    printf("[----- [장원도] [2018038099] -----]");

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

int initializeBST(Node** h) {  // 초기화 함수

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL) // *h가 null이 아니면
		freeBST(*h); // 동적메모리 해제

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));  // 동적메모리 할당
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;  // right 노드 *h값
	(*h)->key = -9999; // key 값

	top = -1; // top -1 값

	front = rear = -1; // -1값 

	return 1;
}



void recursiveInorder(Node* ptr) // 순환함수 중위 순회
{
	if(ptr) {
		recursiveInorder(ptr->left); // recursiveInorder호출 및 ptr이 가르키는 left 넘김 
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right); // recursiveInorder호출 및 ptr이 가르키는 right 넘김
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node) // 반복 중위 순회 
{
	for(;;)
	{
		for(; node; node = node->left) // left노드 이동
			push(node); // 스택에 노드 삽입 
		node = pop(); // 스택에서 삭제

		if(!node) break; // 공백 스택
		printf(" [%d] ", node->key);

		node = node->right; // node에 right 값
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr) // 레벨순서 순회 
{
	// int front = rear = -1;

	if(!ptr) return; /* empty tree */

	enQueue(ptr); // enQueue 호출 

	for(;;)
	{
		ptr = deQueue(); // deQueue 호출 
		if(ptr) {  // ptr이 null이 아니면
			printf(" [%d] ", ptr->key);

			if(ptr->left) // left가 null 이 아니면
				enQueue(ptr->left); // enQueue left
			if(ptr->right) // right가 null 이 아니면 
				enQueue(ptr->right); // enQueue right
		}
		else
			break;

	}

}


int insert(Node* head, int key) // 노드 삽입 함수
{
	Node* newNode = (Node*)malloc(sizeof(Node));  // 동적메모리 할당
	newNode->key = key; // 노드에 입력된 키값 넣음
	newNode->left = NULL; // left값 null
	newNode->right = NULL; // right값 null

	if (head->left == NULL) { // left가 null 이면
		head->left = newNode; // left에 노드값 넣음
		return 1;  // 1값 반환 
	}

	/* head->left is the root */
	Node* ptr = head->left; // ptr에 left값 

	Node* parentNode = NULL; // parentNode에 null 값
	while(ptr != NULL) {  // ptr이 null이 아니면 반복

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1; // key값이 같으면 1값 반환

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr; //ptr값 넣음 

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) // ptr이 가르키는 key값이 작으면 key값보다 작으면
			ptr = ptr->right; // ptr에 right값
		else
			ptr = ptr->left;  // ptr에 left
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)  // parentNode가 가르키는 key값이 입력 key보다 작으면
		parentNode->left = newNode; // left에 newNode값 넣음
	else
		parentNode->right = newNode; //right에 newNode값 
	return 1;
}


int deleteNode(Node* head, int key) // 노드 삭제 함수 
{
	if (head == NULL) { // head가 null 이면
		printf("\n Nothing to delete!!\n");
		return -1; // -1값 반환
	}

	if (head->left == NULL) { // left가 null 이면
		printf("\n Nothing to delete!!\n");
		return -1; // -1값 반환
	} 

	/* head->left is the root */
	Node* root = head->left; // ptr에 left값



	Node* parent = NULL; // parent null값
	Node* ptr = root; // ptr root값

	while((ptr != NULL)&&(ptr->key != key)) { // ptr이 null 이 아니면서 ptr의 key값과 입력값이 같지 않으면 반복 
		if(ptr->key != key) { // ptr이 가르키는 key값과 입력 키와 같지 않으면 

			parent = ptr;	/* save the parent */

			if(ptr->key > key) // 입력키값보다 ptr key값이 크면
				ptr = ptr->left; // ptr에 left값
			else
				ptr = ptr->right; // ptr에 right 값
		}
	}

	/* there is no node for the key */
	if(ptr == NULL) // ptr null 이면
	{
		printf("No node for key [%d]\n ", key);
		return -1; // -1값 반환
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if(ptr->left == NULL && ptr->right == NULL) // left가 null 이면서 right가 null 이면
	{
		if(parent != NULL) { /* parent exists, parent's left and right links are adjusted */
			if(parent->left == ptr)  // left와 ptr이 같으면
				parent->left = NULL; // parent가 가르키는 left에 null값
			else
				parent->right = NULL; // parent가 가르키는 right에 null값
		} else {
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL; // head가 가르키는 left에 null 값

		}

		free(ptr); // 메모리 해제
		return 1;
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL)) // left가 null 이면서 right가 null 이면
	{
		Node* child; // 노드 clide
		if (ptr->left != NULL) // left가 null이 아니면
			child = ptr->left; // child에 left값 
		else
			child = ptr->right; // child에 left값 

		if(parent != NULL) // parent가 null이 아니면 
		{
			if(parent->left == ptr) // parent left가 ptr과 같으면 
				parent->left = child; // parent가 가르키는 left 에 child 값
			else
				parent->right = child;  // parent가 가르키는 right 에 child 값
		} else {
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child; // root에 child 값
		}

		free(ptr); // 메모리 해제
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

	Node* candidate; // 노드 선언 
	parent = ptr; // parent에 ptr값


	candidate = ptr->right; // candidate에 right값

	/* the smallest node is left deepest node in the right subtree of the ptr */
	while(candidate->left != NULL) // left가 null이 아니면
	{
		parent = candidate; // parent에 candidate값 
		candidate = candidate->left; // candidate 에 candidate가 가르키는 left값
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate) // parent가 가르키는 right와 candidate가 같으면 
		parent->right = candidate->right; // parent right에 candidate right 값
	else
		parent->left = candidate->right; // parent left에 candidate right 값

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key; // ptr이 가르키는 key에 candidate의 key 값 넣음 

	free(candidate); // 메모리 해제 
	return 1;
}


void freeNode(Node* ptr) // 메모리 해제 함수
{
	if(ptr) {
		freeNode(ptr->left);  // left 동적메모리 해제
		freeNode(ptr->right); // right 동적메모리 해제
		free(ptr); // ptr 동적메모리 해제
	}
}

int freeBST(Node* head) // 메모리 해제 함수
{

	if(head->left == head) // left와 head값이 같으면 
	{
		free(head); // head 동적메모리 해제
		return 1;
	}

	Node* p = head->left;  // p 에 left 값

	freeNode(p); // p 동적메모리 해제

	free(head);  // head 동적메모리 해제
	return 1;
}



Node* pop() // 노드 삭제 함수 
{
	if (top < 0) return NULL; // 스택 top이 0보다 작으면 null값 반환 
	return stack[top--]; // stack top -- 값 반환 
}

void push(Node* aNode) // 스택 삽입 함수 
{
	stack[++top] = aNode; // stack에 노드 삽입
}


void printStack() // 스택출력함수 
{
	int i = 0; // 정수형 변수 정의
	printf("--- stack ---\n");
	while(i <= top) // top이 i와 같거나 크면 
	{
		printf("stack[%d] = %d\n", i, stack[i]->key); 
	}
}


Node* deQueue() // 큐 삭제 함수 
{
	if (front == rear) { // front와 rear가 같으면 
		// printf("\n....Now Queue is empty!!\n" );
		return NULL; // null값 반환
	}

	front = (front + 1) % MAX_QUEUE_SIZE; // front에 front+1에 max큐값 나머지 값
	return queue[front]; // queue에 front값 리턴

}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE; // rear 에 rear+1에 max큐값 나머지 값
	if (front == rear) { // front와 rear가 같으면 
		// printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode; // queue에 aNode 값 
}





