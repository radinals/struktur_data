#include <iostream>

struct Node {
	int data;
	Node* next = nullptr;
	Node* prev = nullptr;
	Node(int data) : data(data){};
};

struct DoubleLinkedListCircular {
      private:
	Node* head = nullptr;
	Node* tail = nullptr;
	Node* new_node(int data) { return new Node(data); };
	size_t node_count = 0;

      public:
	// DoubleLinkedListCircular(){};
	~DoubleLinkedListCircular() { clear(); };

	void clear();

	bool is_empty() { return head == nullptr; };
	void tambah_awal(int data);
	void tambah_akhir(int data);
	void tambah_setelah(size_t index, int data);

	void hapus_awal();
	void hapus_setelah(size_t index);
	void hapus_akhir();

	size_t size() { return node_count; }

	void print(bool reversed = false);
};

void
DoubleLinkedListCircular::clear()
{
	Node* node_dihapus = head;

	while (node_dihapus != nullptr) {
		head = head->next;
		delete node_dihapus;
		node_dihapus = nullptr;
	}
}

void
DoubleLinkedListCircular::tambah_awal(int data)
{
	Node* nw_node = new_node(data);
	if (is_empty()) {
		head = nw_node;

		head->prev = head;
		head->next = head;
		tail = head;

	} else {
		Node* old_head = head;

		old_head->prev = nw_node;
		tail->next = nw_node;
		nw_node->next = old_head;
		nw_node->prev = tail;

		head = nw_node;
	}
	node_count++;
}

void
DoubleLinkedListCircular::tambah_akhir(int data)
{
	if (is_empty()) {
		tambah_awal(data);
	} else {
		Node* old_tail = tail;
		Node* nw_node = new_node(data);

		tail = nw_node;

		tail->next = head;
		tail->prev = old_tail;
		old_tail->next = tail;
		head->prev = tail;
	}
	node_count++;
}

void
DoubleLinkedListCircular::tambah_setelah(size_t index, int data)
{

	if (index >= node_count) {
		tambah_akhir(data);
	} else if (is_empty() || index <= 0) {
		tambah_awal(data);
	} else {
		Node* node_target = head;
		for (size_t i = 0; i < index; i++) {
			node_target = node_target->next;
		}

		Node* nw_node = new_node(data);

		nw_node->next = node_target->next;
		node_target->next->prev = nw_node;
		node_target->next = nw_node;
		nw_node->prev = node_target;
	}
	node_count++;
}

void
DoubleLinkedListCircular::hapus_awal()
{
	if (is_empty()) {
		return;
	}

	Node* node_dihapus = head;

	if (node_count < 2) {
		delete node_dihapus;
		head = nullptr;
		tail = nullptr;
	} else {
		head = node_dihapus->next;
		head->prev = tail;
		tail->next = head;

		delete node_dihapus;
	}

	node_count--;
}

void
DoubleLinkedListCircular::hapus_setelah(size_t index)
{
	if (is_empty()) {
		return;
	}

	if (index >= node_count) {
		hapus_akhir();
	} else if (index <= 0) {
		hapus_awal();
	} else {
		Node* node_dihapus = head;
		for (size_t i = 0; i <= index; i++) {
			node_dihapus = node_dihapus->next;
		}

		node_dihapus->next->prev = node_dihapus->prev;
		node_dihapus->prev->next = node_dihapus->next;

		delete node_dihapus;
	}
}

void
DoubleLinkedListCircular::hapus_akhir()
{
	if (is_empty()) {
		return;
	}

	Node* node_dihapus = tail;

	if (node_count <= 2) {
		delete node_dihapus;
		head = nullptr;
		tail = nullptr;
	} else {
		tail = node_dihapus->prev;
		tail->next = head;
		head->prev = tail;
		delete node_dihapus;
	}
	node_count--;
}

void
DoubleLinkedListCircular::print(bool reversed)
{
	if (is_empty()) {
		std::cout << "List masih kosong!\n";
		return;
	}

	if (!reversed) {
		Node* current_node = head;
		do {
			std::cout << current_node->data << ',';
			current_node = current_node->next;
		} while (current_node != head);
	} else {
		Node* current_node = tail;
		do {
			std::cout << current_node->data << ',';
			current_node = current_node->prev;
		} while (current_node != tail);
	}

	std::cout << '\n';
}

int
main()
{
	DoubleLinkedListCircular DLLNC;

	DLLNC.tambah_akhir(1);
	DLLNC.tambah_akhir(2);
	DLLNC.tambah_akhir(3);
	DLLNC.tambah_awal(4);
	DLLNC.tambah_akhir(5);
	DLLNC.tambah_setelah(2, 99);
	DLLNC.hapus_setelah(2);

	DLLNC.print(false);
	DLLNC.print(true);
	return 0;
}
