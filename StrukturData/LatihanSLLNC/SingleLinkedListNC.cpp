#include <iostream>
#include <string>

struct Node {
	int data = 0;
	Node* next = NULL;
};

struct LinkedList {
	Node* head = NULL;
	Node* tail = NULL;

	bool kosong() {
		return head == NULL;
	}
};

void bersihkan_layar();
void tambah_node(LinkedList* linked_list, int data);
void hapus_node_awal(LinkedList* linked_list);
void print_linked_list(LinkedList* linked_list);
size_t hitung_node(LinkedList* linked_list);
void hapus_node_tengah(LinkedList* linked_list);
void keluar_program(LinkedList* linked_list);
void menu(LinkedList* linked_list);

void bersihkan_layar() {
	#ifdef _WIN32
		system("cls");
	#endif // untuk windows

	#ifdef __linux__
		system("clear");
	#endif // untuk linux
}

void
tambah_node(LinkedList* linked_list, int data)
{
	Node* node_baru = new Node;
	node_baru->data = data;

	if (linked_list->kosong()) {
		linked_list->head = node_baru;
		linked_list->tail = linked_list->head;
	} else {
		linked_list->tail->next = node_baru;
		linked_list->tail = node_baru;
	}

}

void
hapus_node_awal(LinkedList* linked_list)
{
	if (linked_list->kosong())
		return;

	Node* node_dihapus = linked_list->head;
	int data_dihapus = node_dihapus->data;

	if (linked_list->head->next != NULL) {
		linked_list->head = linked_list->head->next;
	} else {
		linked_list->head = NULL;
	}

	delete node_dihapus;

	std::cout << "Data Dihapus: " << data_dihapus << "\n";

}

void
print_linked_list(LinkedList* linked_list)
{

	if (linked_list->kosong()) {
		std::cout << "Linked List Kosong!\n";
	} else  {

		Node* node = linked_list->head;

		std::cout << "HEAD: ";

		while (node != NULL) {
			std::cout << "[ " << node->data << " ]->";
			node = node->next;
		}

		std::cout << " NULL\n";
	}
}

size_t
hitung_node(LinkedList* linked_list)
{
	size_t jumlah_node = 0;

	if (linked_list->kosong())
		return jumlah_node;

	Node* node = linked_list->head;

	while(node != NULL) {
		++jumlah_node;
		node = node->next;
	}

	return jumlah_node;
}

void
hapus_node_tengah(LinkedList* linked_list)
{
	size_t jumlah_node = hitung_node(linked_list);

	if (linked_list->kosong()) {
		std::cout << "Linked List Kosong!\n";
	} else if (jumlah_node <= 2) {
		hapus_node_awal(linked_list);
	} else {
		size_t index_node_tengah = jumlah_node / 2;
		Node* node_tengah = linked_list->head;
		Node* node_sebelum_tengah = linked_list->head;

		for(size_t i=0; i < index_node_tengah; i++) {
			node_sebelum_tengah = node_tengah;
			node_tengah = node_tengah->next;
		}

		node_sebelum_tengah->next = node_tengah->next;

		size_t data_node_tengah = node_tengah->data;

		delete node_tengah;

		std::cout << "Data Dihapus: " << data_node_tengah << "\n";
	}

}

void keluar_program(LinkedList* linked_list) {
	while(!linked_list->kosong()) {
		hapus_node_awal(linked_list);
	}
	exit(0);
}

void menu(LinkedList* linked_list)
{
	while(true) {
		std::string pilihan;

		bersihkan_layar();

		std::cout<<"SINGLE LINKED LIST NON CIRCULAR\n";
		std::cout<<"-------------------------------\n";
		std::cout<<"Menu : \n";
		std::cout<<"1. Input data\n";
		std::cout<<"2. Hapus data\n";
		std::cout<<"3. Cetak data\n";
		std::cout<<"4. Hapus tengah\n";
		std::cout<<"5. Exit\n";

		std::cout<<"Masukkan pilihan Anda: ";
		std::getline(std::cin, pilihan);

		if (pilihan.empty()) continue;

		switch (pilihan.at(0)) {
			case '1': {
				INPUT_ULANG:
				std::string data_str;
				int data = 0;

				std::cout << "Masukan Data: ";
				std::getline(std::cin, data_str);

				if (data_str.empty())
					goto INPUT_ULANG;

				try {
					data = std::stoi(data_str);
				} catch (...) {
					goto INPUT_ULANG;
				}

				tambah_node(linked_list, data);

			} continue;
			case '2':
				hapus_node_awal(linked_list);
				break;
			case '3':
				print_linked_list(linked_list);
				break;
			case '4':
				hapus_node_tengah(linked_list);
				break;
			case '5':
				keluar_program(linked_list);
				break;
			default:
				continue;
		}

		std::cin.get();
	}


}

int main()
{
	LinkedList List;

	menu(&List);

	return 0;
}
