#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf(" Binary Search Tree #1 [----- [chae seohee] [2022041084] -----] \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
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
	return 1;
}


/* 중위순회 */
void inorderTraversal(Node* ptr)
{
	if(ptr) //ptr != NULL
	{
		inorderTraversal(ptr->left); //ptr의 왼쪽자식노드를 중위순회로 재귀호출
		printf(" [%d] ", ptr->key); //ptr 출력
		inorderTraversal(ptr->right); //ptr의 오른쪽자식노드를 중위순회로 재귀호출
	}
}

/* 전위순회 */
void preorderTraversal(Node* ptr)
{
	if(ptr) 
	{
		printf(" [%d] ", ptr->key); //ptr 출력
		preorderTraversal(ptr->left); //ptr의 왼쪽자식노드를 전위순회로 재귀호출
		preorderTraversal(ptr->right); //ptr의 오른쪽자식노드를 전위순회로 재귀호출
	}
}

/* 후위순회 */
void postorderTraversal(Node* ptr)
{
	if(ptr) 
	{
		postorderTraversal(ptr->left); //ptr의 왼쪽자식노드를 후위순회로 재귀호출
		postorderTraversal(ptr->right); //ptr의 오른쪽자식노드를 후위순회로 재귀호출
		printf(" [%d] ", ptr->key); //ptr 출력
	}
}


int insert(Node* head, int key)
{
	/* 삽입할 새로운 노드 만들기 */
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	/* 트리가 비어있는 경우 */
	if (head->left == NULL) {
		head->left = newNode; //head의 left에 newnode를 삽입하고
		return 1; //함수종료
	}

	Node* ptr = head->left;
	Node* parentNode = NULL;

	while(ptr != NULL) {

		/* 삽입할 새로운 노드의 key값과 같은 key값을 가진 노드가 이미 존재하는 경우 */
		if(ptr->key == key) 
			return 1; //1을 리턴하고 함수종료 

		parentNode = ptr; //부모노드에는 ptr값을 삽입

		if(ptr->key < key) //ptr의 key값이 새로운 노드의 key값보다 작으면
			ptr = ptr->right; //ptr이 ptr의 오른쪽자식노드를 가리키게
		else //ptr의 key값이 새로운 노드의 key값보다 크면
			ptr = ptr->left; //ptr이 pre의 왼쪽자식노드를 가리키게
	}

	/* 새로운 노드와 부모 노드를 이어주기 */
	if(parentNode->key > key) //부모노드의 key값보다 새로운 노드의 key값이 작으면
		parentNode->left = newNode; //부모노드의 왼쪽에 삽입
	else //부모노드의 key값보다 새로운 노드의 key값이 크면
		parentNode->right = newNode; //부모노드의 오른쪽에 삽입
	return 1;
}

int deleteLeafNode(Node* head, int key)
{
	/* 트리가 비어있는 경우 */
	if (head == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	Node* ptr = head->left;
	Node* parentNode = head;

	while(ptr != NULL) {
		/* ptr의 key값이 삭제할 key값과 같은 경우 */
		if(ptr->key == key) {
			if(ptr->left == NULL && ptr->right == NULL) {

				/* 삭제할 노드가 루트노드인 경우 */
				if(parentNode == head)
					head->left = NULL;

				/* 삭제할 노드가 루트노드가 아닌 경우 */
				if(parentNode->left == ptr)
					parentNode->left = NULL;
				else
					parentNode->right = NULL;

				free(ptr);
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

	
		parentNode = ptr;

		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;

	}

	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

/* 재귀호출로 탐색 */
Node* searchRecursive(Node* ptr, int key)
{
	/* 탐색을 마쳤지만 찾고자하는 key값을 가진 노드가 없는 경우  */
	if(ptr == NULL) 
		return NULL; //NULL을 리턴하고 함수종료

	if(ptr->key < key) //ptr의 key값이 찾고자하는 key값보다 작으면
		ptr = searchRecursive(ptr->right, key); //ptr의 오른쪽 서브트리를 탐색
	else if(ptr->key > key) //ptr의 key값이 찾고자하는 key값보다 크면
		ptr = searchRecursive(ptr->left, key); //ptr의 왼쪽 서브트리를 탐색

	/* 찾고자하는 key값을 가진 노드를 찾은 경우 */
	if(ptr->key == key)
		return ptr; //ptr을 리턴하고 함수종료
}

/* 재귀호출 없이 탐색 */
Node* searchIterative(Node* head, int key)
{
	/* root node */
	Node* ptr = head->left;

	while(ptr != NULL) 
	{
		/* 찾고자하는 key값을 찾은 경우 */
		if(ptr->key == key) 
			return ptr; //ptr을 리턴하고 함수종료

		/* 찾고자 하는 key값을 아직 찾지 못한 경우 */
		if(ptr->key < key) //ptr의 key값이 찾고자하는 key값보다 큰 경우
			ptr = ptr->right; //ptr의 오른쪽 서브트리를 탐색
		else ////ptr의 key값이 찾고자하는 key값보다 작은 경우
			ptr = ptr->left; //ptr의 왼쪽 서브트리를 탐색
	}

	/* 탐색을 마쳤는데 찾고자 하는 key값을 찾지 못한 경우 */
	return NULL; //NULL을 리턴하고 함수종료
}

void freeNode(Node* ptr)
{
	if(ptr) //ptr != NULL
	{
		freeNode(ptr->left); //ptr 왼쪽자식으로 freeNode를 재귀호출
		freeNode(ptr->right); //ptr 오른쪽자식으로 freeNode를 재귀호출
		free(ptr); //ptr을 free
	}
}

int freeBST(Node* head)
{
	/* 트리가 비어있는 경우 */
	if(head->left == head) 
	{
		free(head); //head 메모리 해제 후
		return 1; //freeBST() 종료
	}

	/* 트리가 비어있지 않은 경우 */
	Node* p = head->left; //노드 포인터가 트리의 루트를 가리키게 하고

	freeNode(p); //p를 인자로 freeNode함수 호출

	free(head); //head 메모리 해제
	return 1; //freeBST() 종료
}