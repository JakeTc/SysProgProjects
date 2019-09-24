//structure for generic linked list
typedef struct _Node {
	void *data;
	struct _Node *next;
} Node;

//makes a new node
Node *mkNode(void *data) {
	Node *nwNode = malloc(sizeof(Node));
	nwNode->data = data;
	nwNode->next = NULL;

	return nwNode;
}

//makes a new node at the front
Node *push(void *data, Node *head) {
	Node *nwNode = malloc(sizeof(Node));
	nwNode->data = data;
	nwNode->next = head;

	return nwNode;
}

//deletes the entirety of a linked list!
void deleteLL(Node *head) {
	Node *current = head;
	Node *next;
	
	while(current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}

}
