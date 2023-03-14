// Идз 2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <tuple>
struct node {
	char bukva;
	int key;
	node* left;
	node* right;
};
int tabs = 0;

void AddNode(node*& tree, char b, int elem) {
	node* tmp = new node();
	tmp->bukva = b;
	tmp->key = elem;
	tmp->left = nullptr;
	tmp->right = nullptr;

	if (tree == nullptr) {
		tree = tmp;
	}
	else {
		if (std::tie(tree->bukva, tree->key) < std::tie(b, elem))
			AddNode(tree->right, b, elem);
		else
			AddNode(tree->left, b, elem);
	}
}

void print(node* tree)
{
	if (!tree) return;
	tabs += 5;
	print(tree->right);
	for (int i = 0; i < tabs; i++) std::cout << " ";
	std::cout << tree->bukva << tree->key << std::endl;
	print(tree->left);
	tabs -= 5;
	return;
}

bool FindElem(node* tree, char b, int elem) {
	bool flag = false;
	if (tree != nullptr) {
		if (std::tie(tree->bukva, tree->key) == (std::tie(b, elem)))
		{
			flag = true;
			return flag;
		}
		else if (std::tie(tree->bukva, tree->key) > (std::tie(b, elem)))
		{
			return FindElem(tree->left, b, elem);
		}
		else return FindElem(tree->right, b, elem);
	}
	else return flag;
}

void Del_al(node*& tree)
{
	if (tree == nullptr)
	{
		return;
	}

	Del_al(tree->left);
	Del_al(tree->right);
	delete tree;
	tree = nullptr;
}

node* deleteNode (node*&CurrentNode, char b, int keyValue)

{
	if (CurrentNode == nullptr) return CurrentNode;
	else
	{
		node* traveler = CurrentNode;
		node* parentminright = traveler;
		while ((std::tie(traveler->bukva, traveler->key) != std::tie(b, keyValue)))
		{
			if (std::tie(traveler->bukva, traveler->key) <= std::tie(b, keyValue))
			{
				parentminright = traveler;
				traveler = traveler->right;
			}
			else
			{
				parentminright = traveler;
				traveler = traveler->left;
			}
			if (traveler == nullptr)return CurrentNode;
		}

		if (traveler->right == nullptr)
		{
			if (parentminright->left == traveler) {
				if (traveler->left != nullptr) parentminright->left = traveler->left;
				else parentminright->left = nullptr;
			}
			else if (parentminright->right == traveler) {
				if (traveler->left != nullptr) parentminright->right = traveler->left;
				  else	parentminright->right = nullptr;
			}
			else if (parentminright == traveler) {
				CurrentNode = CurrentNode->left;
			}
			delete(traveler);
		}
		else
			if (traveler->left == nullptr)
			{
				if (parentminright->right == traveler) {
					if (traveler->right != nullptr) {
						parentminright->right = traveler->right;
						delete(traveler);
					}
					else {
						parentminright->right = nullptr;
						delete(traveler);
					}
				}
				else if (parentminright->left == traveler) {
					if (traveler->right != nullptr) {
						parentminright->left = traveler->right;
						delete(traveler);
					}
					else {
						parentminright->left = nullptr;
						delete(traveler);
					}
				}
				else if (parentminright == traveler) {
					CurrentNode = CurrentNode->right;
					delete(traveler);
				}
			}
		else
		{
			node* minright = traveler->right;
				while (minright->left != nullptr) {
					parentminright = minright; minright = minright->left;
				}
				if (traveler->right == minright)
				{
					traveler->key = minright->key; traveler->bukva = minright->bukva;
					if (minright->right != nullptr)traveler->right = minright->right;
					else traveler->right = nullptr;
					delete(minright);
				}
				else
				{
					traveler->key = minright->key; traveler->bukva = minright->bukva;
					if (minright->right == nullptr)
					{
						if (parentminright->left = minright)
							parentminright->left = nullptr;
						else if (parentminright->right = minright)
							parentminright->right = nullptr;
						delete(minright);
					}
					else
					{
						parentminright->left = minright->right;
						delete(minright);
					}
			}
		}
	}

	return CurrentNode;

}

int kol_voVershin(node* tree)
{
	int comunist, liberal;
	if (tree != nullptr)
		comunist = kol_voVershin(tree->left);
	else
		comunist = 0;

	if (tree != nullptr)
		liberal = kol_voVershin(tree->right);
	else
		liberal = 0;

	return comunist + liberal + 1;
	
}

void srav(node* tree) {
	std::cout << std::endl << std::endl << std::endl;
	if (tree == nullptr) std::cout << "пусто\n";
	else if (tree->right == nullptr && tree->left == nullptr) std::cout << "left = right\n";
	else {
		int l = kol_voVershin(tree->left);
		int r = kol_voVershin(tree->right);
		if (l > r)
			std::cout << "left > right\n";
		else if (l < r)
			std::cout << "left < right\n";
		else std::cout << "left = right\n";
	}
 }



int main()
{
	setlocale(LC_ALL, "Russian");
	node* tree = nullptr;
	AddNode(tree, 'A', 618);
	AddNode(tree, 'A', 619);
	AddNode(tree, 'A', 615);
	AddNode(tree, 'A', 615);
	AddNode(tree, 'A', 619);
	AddNode(tree, 'A', 621);
	AddNode(tree, 'A', 620);
	AddNode(tree, 'A', 616);
	AddNode(tree, 'A', 617);
	AddNode(tree, 'A', 622);
	AddNode(tree, 'A', 614);

	AddNode(tree, 'A', 650);
	AddNode(tree, 'A', 622);
	print(tree);
	Del_al(tree);
	AddNode(tree, 'A', 610);

	AddNode(tree, 'A', 620);
	AddNode(tree, 'A', 625);

	AddNode(tree, 'A', 615);
	print(tree);
	deleteNode(tree, 'A', 610);
	print(tree);
	std::cout << FindElem(tree, 'A', 656);
	srav(tree);
}