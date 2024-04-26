#include <iostream>

#define LIMIT 3

enum Lempengan {
	MERAH = 50,
	KUNING = 75,
	HIJAU = 100
};

template <typename T> struct Stack {
	int top = -1;
	T data[LIMIT];

	Stack()
	{
		for (int i = 0; i < LIMIT; i++) data[i] = 0;
	}

	bool kosong() { return top <= -1; }
	bool penuh() { return top >= LIMIT; }

	void tampilkan()
	{
		if (kosong()) {
			std::cout << "Kosong\n";
			return;
		}

		for (int i = top; i >= 0; i--) std::cout << data[i] << ' ';
		std::cout << '\n';
	}

	void push(T n)
	{
		if (penuh())
			return;
		data[++top] = n;
	}

	T pop()
	{
		if (kosong())
			return -1;
		return data[top--];
	}

	void clear() { top = -1; }
};

void
tampilkan_tumpukan(size_t langkah, Stack<int> menara_a, Stack<int> menara_b,
                   Stack<int> menara_c)
{
	std::cout << "Langkah " << langkah << ":\n";
	std::cout << "Menara A: ";
	menara_a.tampilkan();
	std::cout << "Menara B: ";
	menara_b.tampilkan();
	std::cout << "Menara C: ";
	menara_c.tampilkan();
	std::cout << '\n';
}

int
main()
{
	Stack<int> menara_a;
	Stack<int> menara_b;
	Stack<int> menara_c;

	menara_a.push(HIJAU);
	menara_a.push(KUNING);
	menara_a.push(MERAH);
	tampilkan_tumpukan(0, menara_a, menara_b, menara_c);

	menara_b.push(menara_a.pop());
	tampilkan_tumpukan(1, menara_a, menara_b, menara_c);

	menara_c.push(menara_a.pop());
	tampilkan_tumpukan(2, menara_a, menara_b, menara_c);

	menara_a.push(menara_b.pop());
	tampilkan_tumpukan(3, menara_a, menara_b, menara_c);

	menara_b.push(menara_c.pop());
	tampilkan_tumpukan(4, menara_a, menara_b, menara_c);

	menara_b.push(menara_a.pop());
	tampilkan_tumpukan(5, menara_a, menara_b, menara_c);

	menara_c.push(menara_a.pop());
	tampilkan_tumpukan(6, menara_a, menara_b, menara_c);

	menara_a.push(menara_b.pop());
	tampilkan_tumpukan(7, menara_a, menara_b, menara_c);

	menara_c.push(menara_b.pop());
	tampilkan_tumpukan(8, menara_a, menara_b, menara_c);

	menara_c.push(menara_a.pop());
	tampilkan_tumpukan(9, menara_a, menara_b, menara_c);

	return 0;
}
