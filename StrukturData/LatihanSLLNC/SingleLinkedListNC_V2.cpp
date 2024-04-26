#include <iostream>
#include <string>

typedef struct Node {
	std::string str;
	Node* next;
} Node;

void add_node(Node*, const std::string&);
void print_all(Node* head);
void delete_nodes(Node* head);

int
main()
{
	Node* head = new Node;

	add_node(head, "hello");
	add_node(head, "World");

	print_all(head);
	delete_nodes(head);

	return 0;
}

void
add_node(Node* head, const std::string& str)
{

	if (head->str.empty()) { // if the head is not set
		head->str = str;
		head->next = nullptr;
	} else { // new nodes
		Node* nw_node;
		Node* current = head;
		// find the last node
		while (current->next != nullptr) current = current->next;

		// create the node
		nw_node = new Node;
		nw_node->str = str;
		nw_node->next = nullptr;

		// add the node to the linked list
		current->next = nw_node;
	}
}

void
print_all(Node* head)
{
	Node* current = head;
	// print all the data in the node list
	while (current != nullptr) {
		std::cout << current->str;
		current = current->next;
	};
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
