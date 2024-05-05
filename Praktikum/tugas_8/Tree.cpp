#include <iostream>

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
		if (isEmpty(parent->m_right)) {
			parent->m_right = new Node(data);
		} else {
			parent->m_right->m_data = data;
		}
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

	tree.initRoot(10);
	tree.addLeft(tree.getRoot(), 12);
	tree.addLeft(tree.getRoot()->m_left, 19);
	tree.addRight(tree.getRoot(), 15);

	std::cout << "Data:";
	tree.inorder(tree.getRoot());
	std::cout << '\n';

	std::cout << "hapus dari root->kiri\n";
	tree.destroyTree(tree.getRoot()->m_left);

	std::cout << "Data:";
	tree.inorder(tree.getRoot());
	std::cout << '\n';

	std::cout << "hapus dari Root\n";
	tree.destroyTree(tree.getRoot());

	std::cout << "Data:";
	tree.inorder(tree.getRoot());
	std::cout << '\n';

	return 0;
}
