#include <iostream>

class my_deque {
public:
	my_deque(size_t s = 3);
	void push_front(int data);
	int pop_front();
	void push_back(int data);
	int pop_back();
	void output();
 private:
	int *arr;
	int *first;
	int *last;
	size_t size;
	size_t real_size;
};

int main(int argc, char** argv) {
	my_deque Deque;
	unsigned int n;
	std::cin >> n;
	while (n > 0) {
		int num;
		unsigned short int command;
		std::cin >> command >> num;
		switch(command) {
			case 1:
				Deque.push_front(num);
				break;
			case 2:
				if (Deque.pop_front() == num) {
					std::cout << "YES\n";
				} else {
					std::cout << "NO\n";
				}
				break;
			case 3:
				Deque.push_back(num);
				break;
			case 4:
				if (Deque.pop_back() == num) {
					std::cout << "YES\n";
				} else {
					std::cout << "NO\n";
				}
				break;
		}
		--n;
	}
	return 0;
}

int my_deque::pop_front() {
	if (first == nullptr) {
		return -1;
	}
	return *first;
}

int my_deque::pop_back() {
	if (last == nullptr) {
		return -1;
	}
	return *last;
}

void my_deque::output() {
	for (size_t i = 0; i < size; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

void my_deque::push_back(int data) {
	if (last == nullptr) {
		first = last = &arr[size - 1];
		arr[size - 1] = data;
	} else if (real_size < size && first != &arr[0]) {
		++real_size;
		for (size_t i = size - 1 - real_size; i < size - 1; ++i) {
			arr[i] = arr[i + 1];
		}
		arr[size - 1] = data;
		first = &arr[size - 1 - real_size];
	} else {
		if (last != &arr[size - 1]) {
			last = &arr[size - 1];
		}
		for (size_t i = size / 2; i < size - 1; ++i) {
			arr[i] = arr[i + 1];
		}
		arr[size - 1] = data;
	}
}

void my_deque::push_front(int data) {
	if (first == nullptr) {
		first = last = &arr[0];
		arr[0] = data;
	} else if (real_size < size && last != &arr[size - 1]) {
		++real_size;
		for (size_t i = real_size; i > 0 ;--i) {
			arr[i] = arr[i - 1];
		}
		arr[0] = data;
		last = &arr[real_size];
	} else {
		if (first != &arr[0]) {
			first = &arr[0];
		}
		for (size_t i = size / 2; i > 0; --i) {
			arr[i] = arr[i - 1];
		}
		arr[0] = data;
	}
}

my_deque::my_deque(size_t s) {
	size = s;
	real_size = 0;
	arr = new int[size];
	for (size_t i = 0; i < size; ++i) {
		arr[i] = 0;
	}
	first = nullptr;
	last = nullptr;
}