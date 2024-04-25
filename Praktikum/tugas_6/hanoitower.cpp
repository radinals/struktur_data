#include <iostream>

#define LIMIT 3

enum Balok {
	MERAH = 50,
	KUNING = 60,
	HIJAU = 100,
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
		for (int i = LIMIT - 1; i >= 0; i--)
			std::cout << data[i] << ' ';
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
		T ret = data[top];
		data[top] = 0;
		--top;
		return ret;
	}

	void clear() { top = -1; }
};

void
tampilkan_tumpukan(Stack<int> menara_a, Stack<int> menara_b,
                   Stack<int> menara_c)
{
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

	tampilkan_tumpukan(menara_a, menara_b, menara_c);

	menara_a.push(HIJAU);

	tampilkan_tumpukan(menara_a, menara_b, menara_c);

	menara_a.push(KUNING);

	tampilkan_tumpukan(menara_a, menara_b, menara_c);

	menara_a.push(MERAH);

	tampilkan_tumpukan(menara_a, menara_b, menara_c);

	menara_b.push(menara_a.pop());

	tampilkan_tumpukan(menara_a, menara_b, menara_c);

	menara_c.push(menara_a.pop());

	tampilkan_tumpukan(menara_a, menara_b, menara_c);

	menara_a.push(menara_b.pop());

	tampilkan_tumpukan(menara_a, menara_b, menara_c);

	menara_b.push(menara_c.pop());

	tampilkan_tumpukan(menara_a, menara_b, menara_c);

	menara_b.push(menara_a.pop());

	tampilkan_tumpukan(menara_a, menara_b, menara_c);

	menara_c.push(menara_a.pop());

	tampilkan_tumpukan(menara_a, menara_b, menara_c);

	menara_a.push(menara_b.pop());

	tampilkan_tumpukan(menara_a, menara_b, menara_c);

	menara_c.push(menara_b.pop());

	tampilkan_tumpukan(menara_a, menara_b, menara_c);

	menara_c.push(menara_a.pop());

	tampilkan_tumpukan(menara_a, menara_b, menara_c);

	return 0;
}
