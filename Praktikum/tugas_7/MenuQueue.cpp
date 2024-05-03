#include <functional>
#include <iostream>
#include <string>

enum class Level {
	TINGGI,
	MENENGAH,
	RENDAH
};

template <typename T> class Queue
{
      private:
	int m_front = -1;
	int m_QueueSize = 100;
	T* m_array = nullptr;

	void create_array() { m_array = new T[m_QueueSize]; }

	void geserElemen(int start)
	{
		for (int i = start; i < m_front; i++) {
			m_array[i + 1] = m_array[i];
		}
	}

	void tambah_tengah(const T& data)
	{
		geserElemen((m_front - 1) / 2);
		m_array[m_front / 2] = data;
		m_front++;
	}

	void tambah_akhir(const T& data) { m_array[++m_front] = data; }

	void tambah_awal(const T& data)
	{
		m_array[++m_front] = data;
		geserElemen(0);
		m_array[0] = data;
		m_front++;
	}

      public:
	Queue() { create_array(); }
	Queue(int size) : m_QueueSize(size) { create_array(); }
	~Queue() { delete[] m_array; }

	inline bool isEmpty() { return m_front < 0; }
	inline bool isFull() { return m_front >= m_QueueSize; }

	void enqueue(const T& data, Level level)
	{
		if (isFull()) {
			return;
		}

		switch (level) {
		case Level::TINGGI:
			tambah_awal(data);
			break;
		case Level::MENENGAH:
			tambah_tengah(data);
			break;
		case Level::RENDAH:
			tambah_akhir(data);
			break;
		}
	}

	T dequeue()
	{
		if (isEmpty()) {
			return T();
		}
		T data = m_array[m_front--];
		return data;
	}

	void foreach (std::function<void(T&)> func)
	{
		if (isEmpty()) {
			return;
		}
		for (int i = 0; i < m_front; i++) {
			func(m_array[i]);
		}
		std::cout << '\n';
	}

	;

	inline T clear() { m_front = -1; }
};

void
clear_screen()
{
	system("clear");
}

std::string
input_loop(const std::string& prompt)
{
	while (true) {

		std::string input;
		std::cout << prompt;
		getline(std::cin, input);

		if (input.empty()) {
			continue;
		}

		return input;
	}
}

int
main()
{
	Queue<std::string> data;

	auto print = [](std::string& str) {
		std::cout << '"' << str << '"' << ' ';
	};

	while (true) {
		clear_screen();
		std::cout << "===: Queue Menu :===\n";
		std::cout << "1. Enqueue\n";
		std::cout << "2. Dequeue\n";
		std::cout << "3. Print\n";
		std::cout << "4. Exit\n";

		std::string input = input_loop("Pilihan: ");

		switch (input.at(0)) {
		case '1': {
			std::string pesan = input_loop("Input Pesan: ");
			while (true) {
				std::cout << "\n1. Level Tinggi\n";
				std::cout << "2. Level Menengah\n";
				std::cout << "3. Level Rendah\n";
				std::string Level =
				    input_loop("Input Level Pesan: ");
				switch (Level.at(0)) {
				case '1':
					data.enqueue(pesan, Level::TINGGI);
					break;
				case '2':
					data.enqueue(pesan, Level::MENENGAH);
					break;
				case '3':
					data.enqueue(pesan, Level::RENDAH);
					break;
				default:
					continue;
				}

				break;
			}
		}
			continue;
		case '2':
			std::cout << "data yang di dequeue:" << data.dequeue()
			          << '\n';
			break;
		case '3':
			data.foreach (print);
			break;
		case '4':
			return 0;
		default:
			continue;
		}

		std::cin.get();
	}

	return 0;
}