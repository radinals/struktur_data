#include <cstdlib>
#include <iostream>

struct Node {
	int data;
	Node* next = nullptr;
	Node* prev = nullptr;
	Node(int data) : data(data){};
};

class DoubleLinkedListNonCircular
{
      private:
	Node* head = nullptr;
	Node* tail = nullptr;

	Node* new_node(int data) { return new Node(data); };

      public:
	// DoubleLinkedListNonCircular(){};
	~DoubleLinkedListNonCircular() { clear(); };

	void clear();

	bool is_empty() { return head == nullptr; };
	void tambah_awal(int data);
	void tambah_akhir(int data);
	void tambah_tengah(int data);

	void hapus_awal();
	void hapus_tengah();
	void hapus_akhir();

	void print(bool reversed = false);

	std::size_t hitung_node();
};

void
DoubleLinkedListNonCircular::clear()
{
	Node* node_dihapus = nullptr;

	while (head != nullptr) {
		node_dihapus = head;
		head = head->next;
		delete node_dihapus;
	}
}

void
DoubleLinkedListNonCircular::tambah_awal(int data)
{
	if (is_empty()) {
		head = new_node(data);
		tail = head;
		return;
	}

	Node* node_baru = new_node(data);

	// sambungkan node baru dengan tail yang ada.
	node_baru->next = head;
	head->prev = node_baru;

	//  node yang baru menjadi head
	head = node_baru;
}

void
DoubleLinkedListNonCircular::tambah_akhir(int data)
{
	if (is_empty()) {
		tambah_awal(data);
		return;
	}

	Node* node_baru = new_node(data);

	// sambungkan node baru dengan tail yang ada.
	node_baru->prev = tail;
	tail->next = node_baru;

	// node baru menjadi tail
	tail = node_baru;
}

void
DoubleLinkedListNonCircular::tambah_tengah(int data)
{

	if (is_empty()) {
		tambah_awal(data);
		return;
	}

	size_t jumlah_node = hitung_node();

	if (jumlah_node < 2) {
		tambah_akhir(data);
	} else {
		size_t index_node_tengah = jumlah_node / 2;

		Node* node_tengah = head;

		// cari node_tengah.
		for (size_t i = 0; i < index_node_tengah; i++) {
			node_tengah = node_tengah->next;
		}

		// dapatkan node sebelum node di tengah
		Node* node_sebelum_tengah = node_tengah->prev;

		Node* node_baru = new_node(data);

		// sambungkan node baru dengan node di tengah.
		node_baru->next = node_tengah;
		node_tengah->prev = node_baru;

		// sambungkan node baru dengan node sebelum node di tengah
		node_sebelum_tengah->next = node_baru;
		node_baru->prev = node_sebelum_tengah;
	}
}

void
DoubleLinkedListNonCircular::hapus_awal()
{
	if (is_empty()) {
		return;
	}

	Node* node_dihapus = head;

	// cek jika node hanya ada satu
	if (head->next != nullptr) {
		head = head->next;
		head->prev = nullptr;
	} else {
		// jika hanya ada satu
		head = nullptr;
		tail = nullptr;
	}

	delete node_dihapus;
}

void
DoubleLinkedListNonCircular::hapus_tengah()
{
	if (is_empty()) {

		return;
	}

	size_t jumlah_node = hitung_node();

	if (jumlah_node < 2) {
		hapus_awal();
	} else {
		size_t index_node_tengah = jumlah_node / 2;

		Node* node_tengah = head;

		// cari node sebelum node di tengah.
		for (size_t i = 0; i < index_node_tengah; i++) {
			node_tengah = node_tengah->next;
		}

		// dapatkan node sebelum tengah dan setelahnya
		Node* node_sebelum_tengah = node_tengah->prev;
		Node* node_setelah_tengah = node_tengah->next;

		// sambungkan node seblum tengah dengan node setelah tengah
		node_sebelum_tengah->next = node_setelah_tengah;
		node_sebelum_tengah->prev = node_sebelum_tengah;

		// hapus node tengah
		delete node_tengah;
	}
}

void
DoubleLinkedListNonCircular::hapus_akhir()
{
	if (is_empty()) {
		return;
	}

	Node* node_dihapus = tail;

	// cek jika node hanya ada satu
	if (tail->prev != nullptr) {
		tail = tail->prev;
		tail->next = nullptr;
	} else {
		// jika hanya ada satu
		head = nullptr;
		tail = nullptr;
	}

	delete node_dihapus;
}

void
DoubleLinkedListNonCircular::print(bool reversed)
{
	if (is_empty()) {
		std::cout << "List masih kosong!\n";
		return;
	}

	Node* current_node = (reversed) ? tail : head;

	// lambda, hanya untuk menyingkat logika
	auto node_berikut = [&]() {
		return (reversed) ? current_node->prev : current_node->next;
	};

	while (node_berikut() != nullptr) {
		std::cout << current_node->data << ' ';

		current_node = node_berikut();
	}

	std::cout << current_node->data << '\n';
}

std::size_t
DoubleLinkedListNonCircular::hitung_node()
{
	Node* current_node = head;
	std::size_t count = 0;

	while (current_node->next != nullptr) {
		++count;
		current_node = current_node->next;
	}

	return count;
}

int
main()
{
	DoubleLinkedListNonCircular DLLNC;

	DLLNC.tambah_awal(1);
	DLLNC.tambah_akhir(2);
	DLLNC.tambah_tengah(3);

	// DLLNC.hapus_tengah();
	// DLLNC.hapus_awal();
	// DLLNC.hapus_akhir();

	DLLNC.print(false);
	return 0;
}
