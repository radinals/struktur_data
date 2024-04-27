#include <iostream>

template <typename T> class Queue
{
      private:
	struct Node {
		T m_data;
		Node* next = nullptr;
		Node(const T& data) : m_data(data){};
	};

	Node* m_front = nullptr;
	Node* m_rear = nullptr;

      public:
	Queue(){};
	~Queue() { clear(); };

	inline bool isEmpty() { return m_front == nullptr; }

	void enqueue(const T& data, bool& sucess)
	{
		Node* new_node;

		try {
			new_node = new Node(data);
		} catch (...) {
			sucess = false;
			delete new_node;
			return;
		}

		if (isEmpty()) {
			m_front = new_node;
			m_rear = m_front;
		} else {
			m_rear->next = new_node;
			m_rear = new_node;
		}

		sucess = true;
	}

	T dequeue(bool& success)
	{
		if (isEmpty()) {
			success = false;
			return T();
		} else {
			Node* front = m_front;
			T ret_data = front->m_data;
			m_front = m_front->next;
			delete front;

			return ret_data;
		}
	}

	T peek(bool& success)
	{
		if (isEmpty()) {
			success = false;
			return T();
		}

		return m_front->m_data;
	}

	void print()
	{
		if (isEmpty())
			return;
		Node* node = m_front;
		while (node != nullptr) {
			std::cout << node->m_data << ' ';
			node = node->next;
		}
		std::cout << '\n';
	}

	void clear()
	{
		if (isEmpty())
			return;

		Node* node = m_front;
		while (node != nullptr) {
			Node* del = node;
			node = node->next;
			delete del;
		}

		m_front = m_rear = nullptr;
	}
};

int
main()
{
	bool status;
	Queue<int> data;

	data.enqueue(1, status);
	data.enqueue(2, status);
	data.enqueue(3, status);
	data.enqueue(4, status);
	data.dequeue(status);
	// data.clear();

	data.print();

	return 0;
}
