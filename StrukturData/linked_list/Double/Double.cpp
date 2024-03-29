#include <iostream>

typedef struct Node {
	int num;
	Node* next;
	Node* prev;
} Node;

void print_all(Node* head);
void insert_after(Node* prev_node, const int& num);
void insert_before(Node* next_node, const int& num);
void delete_nodes(Node* head);
void delete_after(Node* prev_node);

int
main()
{
	Node* head = new Node;

	head->num = 0;
	head->prev = nullptr;
	head->next = nullptr;

	insert_after(head, 1);
	insert_after(head->next, 3);
	insert_after(head->next->next, 3);
	insert_before(head->next, 7);

	print_all(head);

	return 0;
}

void
insert_after(Node* prev_node, const int& num)
{
	if (prev_node == nullptr) { // if the head is not set
		return;
	} else {
		// new nodes
		Node* nw_node;

		// create the node
		nw_node = new Node;
		nw_node->num = num;

		nw_node->prev = prev_node;
		nw_node->next = prev_node->next;

		// add the node to the linked list
		prev_node->next = nw_node;
	}
}

void
insert_before(Node* next_node, const int& num)
{
	if (next_node == nullptr) { // if the head is not set
		return;
	} else {
		// new nodes
		Node* nw_node;

		// create the node
		nw_node = new Node;
		nw_node->num = num;

		nw_node->prev = next_node->prev;
		nw_node->next = next_node;

		next_node->prev->next = nw_node;
		next_node->prev = nw_node;
	}
}

void
delete_after(Node* prev_node)
{
	Node* target_node;
	Node* nw_next;

	if (prev_node->next == nullptr) {
		return;
	} else {
		target_node = prev_node->next;
		nw_next = prev_node->next->next;

		prev_node->next->prev = prev_node;

		if (nw_next != nullptr)
			prev_node->next = nw_next;
		else
			prev_node->next = nullptr;

		delete target_node;
	}
}

void
print_all(Node* head)
{
	Node* current = head;
	// print all the data in the node list
	std::cout << "[ ";
	while (current != nullptr) {
		std::cout << current->num << ", ";
		current = current->next;
	};
	std::cout << " ]";
}

void
delete_nodes(Node* head)
{
	Node* tmp = head;
	// delete the linked list nodes,
	// starting from the head.
	while (head != nullptr) {
		tmp = head;
		head = head->next;
		delete tmp;
	};
}
