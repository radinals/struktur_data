#include <iostream>

template <typename T> class Stack
{
      private:
	struct Slice {
		T data;
		Slice* Next = nullptr;
		Slice(T new_data) : data{new_data} {};
	};

	Slice* top = nullptr;
	size_t element_count = 0;

      public:
	Stack(){};
	~Stack() { clear(); };

	inline T peek() { return getTop()->data; }
	inline bool isEmpty() { return getTop() == nullptr; };
	inline size_t getElementCount() { return element_count; };
	inline Slice* const getTop() { return top; }

	bool push(const T& data)
	{
		Slice* new_slice;

		try {
			new_slice = new Slice(data);
		} catch (...) {
			return false;
		}

		if (isEmpty()) {
			top = new_slice;
		} else {
			new_slice->Next = top;
			top = new_slice;
		}

		++element_count;

		return true;
	}

	T pop()
	{
		if (isEmpty())
			return false;

		Slice* popped_slice = top;
		T ret_data = popped_slice->data;

		if (top->Next == nullptr) {
			top = nullptr;
		} else {
			top = top->Next;
		}

		--element_count;
		delete popped_slice;

		return ret_data;
	}

	void clear()
	{
		Slice* slice = getTop();
		while (slice != nullptr) {
			Slice* del_slice = slice;
			slice = slice->Next;
			delete del_slice;
			element_count--;
		}
	}
};

int
main()
{
	Stack<int> stack;

	for (int i = 0; i < 10; i++) stack.push(i);

	std::cout << "Element Count: " << stack.getElementCount() << '\n';

	// stack.clear();
	// std::cout << "Element Count: " << stack.getElementCount() << '\n';

	auto* slice = stack.getTop();
	std::cout << "Data: ";
	while (slice != nullptr) {
		std::cout << slice->data << ' ';
		slice = slice->Next;
	}
	std::cout << '\n';

	return 0;
}
