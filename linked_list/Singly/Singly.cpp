#include <cstddef>
#include <iostream>
#include <iterator>
#include <string>

typedef struct Node {
	std::string text;
	Node* next;
} Node;

void push(Node* head, std::string text);
void printnodes(Node* head);

int
main()
{
	Node* head = new Node;
	head->next = nullptr;
	std::size_t count = 0;
	std::string text;

	for (int i = 0; i < 3; i++) {
		std::cout << "INPUT: ";
		getline(std::cin, text);
		if (count <= 0)
			head->text = text;
		else
			push(head, text);
		count++;
	}

	printnodes(head);

	return 0;
}

void
push(Node* head, std::string text)
{
	Node* current = head;
	while (current->next != nullptr) current = current->next;
	current->next = new Node;
	current->next->text = text;
	current->next->next = nullptr;
}

void
printnodes(Node* head)
{
	Node* current = head;

	while (current != nullptr) {
		std::cout << current->text << "\n";
		current = current->next;
	}
}
