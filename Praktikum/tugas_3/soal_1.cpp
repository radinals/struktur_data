#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

typedef struct Biodata {
	std::string nama;
	float tinggi_badan = 0;
	int umur = 0;
	char golongan_darah[3] = {'\0'};
} BioData;

void input_data(Biodata& biodata);
void print_data(const Biodata& biodata);

int
main()
{
	Biodata biodata;
	while (true) {

		std::cout << '\n';
		std::cout << "1. Input Data\n";
		std::cout << "2. Print Data\n";
		std::cout << "3. Keluar\n";

		std::string tmp;

		std::cout << "> ";
		getline(std::cin, tmp);

		if (tmp.empty())
			continue;

		std::cout << '\n';

		switch (tmp.at(0)) {
		case '1':
			input_data(biodata);
			break;
		case '2':
			print_data(biodata);
			break;
		case '3':
			return 0;
		default:
			continue;
		}
	}

	return -1;
}

void
print_data(const Biodata& biodata)
{
	std::cout << '\n';
	std::cout << "BIODATA:\n";
	std::cout << "NAMA           : " << biodata.nama << "\n";
	std::cout << "UMUR           : " << biodata.umur << "\n";
	std::cout << "TINGGI BADAN   : " << biodata.tinggi_badan << " cm\n";
	std::cout << "GOLONGAN DARAH : " << biodata.golongan_darah << "\n";
	std::cout << '\n';
}

void
input_data(Biodata& biodata)
{
	while (true) {
		std::cout << "Masukan Nama Anda: ";
		getline(std::cin, biodata.nama);

		if (biodata.nama.empty())
			continue;

		break;
	}

	while (true) {
		std::string tmp;
		std::cout << "Masukan Umur Anda: ";
		getline(std::cin, tmp);

		if (tmp.empty())
			continue;

		try {
			biodata.umur = std::stoi(tmp);
		} catch (std::invalid_argument) {
			continue;
		}

		break;
	}

	while (true) {
		std::string tmp;
		std::cout << "Masukan Tinggi Badan Anda: ";
		getline(std::cin, tmp);

		if (tmp.empty())
			continue;

		try {
			biodata.tinggi_badan = std::stof(tmp);
		} catch (std::invalid_argument) {
			continue;
		}

		break;
	}

	while (true) {
		std::string tmp;

		std::cout << '\n';
		std::cout << "1. A\n";
		std::cout << "2. B\n";
		std::cout << "3. O\n";
		std::cout << "4. AB\n\n";

		std::cout << "Apa Golongan Darah Anda: ";
		getline(std::cin, tmp);

		if (tmp.empty())
			continue;

		switch (tmp.at(0)) {
		case '1':
			strcpy(biodata.golongan_darah, "A");
			break;
		case '2':
			strcpy(biodata.golongan_darah, "B");
			break;
		case '3':
			strcpy(biodata.golongan_darah, "O");
			break;
		case '4':
			strcpy(biodata.golongan_darah, "AB");
			break;
		default:
			continue;
		}

		break;
	}
};
