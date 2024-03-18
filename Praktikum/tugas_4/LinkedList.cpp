#include <iostream>

struct Node {
	std::string nama;
	Node* next;

	Node(const std::string& nama)
	{
		this->nama = nama;
		next = NULL;
	}
};

struct LinkedList {
	Node* Head = NULL;

	void insert(const std::string& nama);
	void append(const std::string& nama);
	void print();
};

void
LinkedList::insert(const std::string& nama)
{
	Node* new_node = new Node(nama);

	if (Head == NULL) {
		Head = new_node;
	} else {
		Node* old_head = Head;
		Head = new_node;
		Head->next = old_head;
	}
}

void
LinkedList::append(const std::string& nama)
{
	Node* new_node = new Node(nama);

	if (Head == NULL) {
		Head = new_node;
	} else {
		Node* h = Head;
		while (h->next != NULL) h = h->next;
		h->next = new_node;
	}
}

void
LinkedList::print()
{
	Node* h = Head;
	while (h != NULL) {
		std::cout << "-> " << h->nama << "\n";
		h = h->next;
	};
}

int
main()
{
	LinkedList list;

	list.insert("Sigit");  // { sigit }
	list.append("Gogon");  // { sigit, gogon }
	list.insert("Alipia"); // { alipia, sigit, gogon }
	list.append("Wardah"); // { alipia, sigit, gogon, wardah}

	list.print();

	return 0;
}
