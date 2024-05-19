#include <iostream>
#include <queue>

template <typename T> struct Node {
	T m_data;
	Node* m_left;
	Node* m_right;
	Node(T data) : m_right(nullptr), m_left(nullptr), m_data(data){};
};

template <typename T> class BinaryTree
{
      private:
	Node<T>* m_root = nullptr;

      public:
	BinaryTree(){};
	~BinaryTree() { destroyTree(m_root); };
	bool isEmpty(Node<T>*& node) { return node == nullptr; }
	Node<T>*& getRoot() { return m_root; };

	void add(T data)
	{
		if (isEmpty(m_root)) {
			m_root = new Node(data);
			return;
		}

		std::queue<Node<T>*> Q;

		Q.push(m_root);

		// by the ordering of this loop, the left node will be
		// checked first, and will be added to first (from the second
		// time this function is ran)

		while (!Q.empty()) {
			Node<T>* current_node = Q.front();
			Q.pop();

			// check if left of parent is null
			if (isEmpty(current_node->m_left)) {
				current_node->m_left = new Node(data);
				break;
			} else {
				// if left is occupied, push the left to the
				// stack
				Q.push(current_node->m_left);
			}

			// check if right of parent is null
			if (isEmpty(current_node->m_right)) {
				current_node->m_right = new Node(data);
				break;
			} else {
				// if right is occupied, push the right to the
				// stack
				Q.push(current_node->m_right);
			}
		}
	}

	void initRoot(T data)
	{
		if (isEmpty(m_root)) {
			m_root = new Node(data);
		}
	}

	void addLeft(Node<T>*& parent, const T& data)
	{
		if (isEmpty(parent->m_left)) {
			parent->m_left = new Node(data);
		} else {
			parent->m_left->m_data = data;
		}
	}

	void addRight(Node<T>*& parent, const T& data)
	{
		parent->m_right = new Node(data);
	}

	void inorder(Node<T>* parent)
	{
		if (!isEmpty(parent)) {
			inorder(parent->m_left);
			std::cout << parent->m_data << " ";
			inorder(parent->m_right);
		}
	}

	void preorder(Node<T>* parent)
	{
		if (!isEmpty(parent)) {
			std::cout << parent->m_data << " ";
			preorder(parent->m_left);
			preorder(parent->m_right);
		}
	}

	void postorder(Node<T>* parent)
	{
		if (!isEmpty(parent)) {
			postorder(parent->m_left);
			postorder(parent->m_right);
			std::cout << parent->m_data << " ";
		}
	}

	void destroyTree(Node<T>*& parent)
	{
		if (!isEmpty(parent)) {
			destroyTree(parent->m_left);
			destroyTree(parent->m_right);
			delete parent;
			parent = nullptr;
		}
	}

	bool hasLeft(Node<T>*& parent) { return parent->m_left != nullptr; }
	bool hasRight(Node<T>*& parent) { return parent->m_right != nullptr; }
};

int
main()
{
	BinaryTree<int> tree;
	tree.add(10);
	tree.add(12);
	tree.add(13);
	tree.postorder(tree.getRoot());
}
