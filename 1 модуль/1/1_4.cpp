#include <iostream>

struct List {
	List(int field);
	~List() = default;
	int field;
	List *next;
};

List* full_init(int N);
List* push(List* th, int num);
List* deletelem(List *lst);
void output(List *lst);

int main(int argc, char **argv) {
	int N, k;
	std::cin >> N >> k;
	List* root = full_init(N);
	if (root == nullptr) {
		return -1;
	}
	int temp_N = N;
	while(temp_N != 1) {
		for (auto i = 0; i < k - 2; ++i) {
			root = root->next;
		}
		root = deletelem(root);
		temp_N--;
	}
	std::cout << root->field << std::endl;
	return 0;
}

List::List(int field = 0) {
    this->field = field;
    this->next = nullptr;
}

List* full_init(int N) {
	List *root = new List(1), *dvig;
	if (root == nullptr) {
		return nullptr;
	}
	dvig = root;
	for (auto i = 1; i < N; ++i) {
		dvig = push(dvig, i+1);
	}
	dvig->next = root;
	return root;
}

List* push(List* th, int num) {
	List *temp = new List(num);
	if (temp == nullptr) {
		return nullptr;
	}
	th->next = temp;
	return temp;
}

List* deletelem(List *lst) {
	List *temp = lst->next;
	lst->next = temp->next;
	delete temp;
	return lst->next;
}
