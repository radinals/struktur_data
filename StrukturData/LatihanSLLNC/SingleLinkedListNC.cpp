#include <iostream>
#include <string>

struct Node {
	int data = 0;
	Node* next = NULL;
};

struct LinkedList {
	Node* head = NULL;
	Node* tail = NULL;

	// cek jika list kosong
	bool kosong() { return head == NULL; }
};

void bersihkan_layar();
void tambah_node(LinkedList* linked_list, int data);
void hapus_node_awal(LinkedList* linked_list);
void print_linked_list(LinkedList* linked_list);
size_t hitung_node(LinkedList* linked_list);
void hapus_node_tengah(LinkedList* linked_list);
void keluar_program(LinkedList* linked_list);
void menu(LinkedList* linked_list);

// bersihkan layar terminal
void
bersihkan_layar()
{
#ifdef _WIN32
	system("cls");
#endif // untuk windows

#ifdef __linux__
	system("clear");
#endif // untuk linux
}

// menambah node baru diawal jika list kosong
// atau diakhir.
void
tambah_node(LinkedList* linked_list, int data)
{
	Node* node_baru = new Node;
	node_baru->data = data;

	// jika list kosong tambah di head
	if (linked_list->kosong()) {
		linked_list->head = node_baru;
		linked_list->tail = linked_list->head;
	} else {
		// tambah di tail
		linked_list->tail->next = node_baru;
		linked_list->tail = node_baru;
	}
}

// hapus node diawal (head)
void
hapus_node_awal(LinkedList* linked_list)
{
	if (linked_list->kosong())
		return;

	Node* node_dihapus = linked_list->head;
	int data_dihapus = node_dihapus->data;

	// cek jika tidak ada node setelah head
	if (linked_list->head->next != NULL) {
		// jika ada set head ke node berikutnya
		linked_list->head = linked_list->head->next;
	} else {
		// jika tidak ada head == NULL
		linked_list->head = NULL;
	}

	delete node_dihapus;

	std::cout << "Data Dihapus: " << data_dihapus << "\n";
}

// print semua node
void
print_linked_list(LinkedList* linked_list)
{

	if (linked_list->kosong()) {
		std::cout << "Linked List Kosong!\n";
	} else {

		Node* node = linked_list->head;

		std::cout << "HEAD: ";

		// iterasikan seluruh node dan
		// print nilai mereka
		while (node != NULL) {
			std::cout << "[ " << node->data << " ]->";
			node = node->next;
		}

		std::cout << " NULL\n";
	}
}

// hitung jumlah node
size_t
hitung_node(LinkedList* linked_list)
{
	size_t jumlah_node = 0;

	// jika kosong jumlah == 0
	if (linked_list->kosong())
		return jumlah_node;

	Node* node = linked_list->head;

	// iterasikan seluruh node di list
	// hitung satu persatu
	while (node != NULL) {
		++jumlah_node;
		node = node->next;
	}

	return jumlah_node;
}

// hapus node ditengah list
void
hapus_node_tengah(LinkedList* linked_list)
{
	size_t jumlah_node = hitung_node(linked_list);

	if (linked_list->kosong()) {
		std::cout << "Linked List Kosong!\n";
	} else if (jumlah_node <= 2) {
		// jika jumlah node <= 2, hapus saja dari head
		hapus_node_awal(linked_list);
	} else {

		size_t index_node_tengah = jumlah_node / 2;

		Node* node_tengah = linked_list->head;
		Node* node_sebelum_tengah = linked_list->head;

		// iterasikan sebanyak jumlah node tengah
		for (size_t i = 0; i < index_node_tengah; i++) {

			// simpan node sebelum node tengah
			node_sebelum_tengah = node_tengah;

			// simpan node tengah
			node_tengah = node_tengah->next;
		}

		// putuskan hubungan node tengah dengan node selanjutnya
		node_sebelum_tengah->next = node_tengah->next;

		// dapatkan data yg disimpan
		size_t data_node_tengah = node_tengah->data;

		// hapus data di tengah
		delete node_tengah;

		// print data node yang dihapus
		std::cout << "Data Dihapus: " << data_node_tengah << "\n";
	}
}

// keluar dan de-alokassikan memory list
void
keluar_program(LinkedList* linked_list)
{
	while (!linked_list->kosong()) {
		hapus_node_awal(linked_list);
	}
	exit(0);
}

// menu opsi
void
menu(LinkedList* linked_list)
{
	while (true) {
		std::string pilihan;

		bersihkan_layar();

		std::cout << "SINGLE LINKED LIST NON CIRCULAR\n";
		std::cout << "-------------------------------\n";
		std::cout << "Menu : \n";
		std::cout << "1. Input data\n";
		std::cout << "2. Hapus data\n";
		std::cout << "3. Cetak data\n";
		std::cout << "4. Hapus tengah\n";
		std::cout << "5. Exit\n";

		std::cout << "Masukkan pilihan Anda: ";
		std::getline(std::cin, pilihan);

		if (pilihan.empty())
			continue;

		switch (pilihan.at(0)) {
		case '1': {
		INPUT_ULANG: // label goto
			std::string data_str;
			int data = 0;

			std::cout << "Masukan Data: ";
			std::getline(std::cin, data_str);

			if (data_str.empty())
				goto INPUT_ULANG; // kembali ke label atas

			// konversikan string ke int,
			// jika error kembali keatas
			try {
				data = std::stoi(data_str);
			} catch (...) {
				goto INPUT_ULANG; // kembali ke label atas
			}

			tambah_node(linked_list, data);
		}
			continue;
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

		std::cin.get(); // tunggu sebelum membersihkan layar
	}
}

int
main()
{
	LinkedList List;

	menu(&List);

	return 0;
}
