#include <iostream>

class BinaryHeap {
 public:
	BinaryHeap(unsigned int size = 0);
	void input();
	void add_elem(unsigned int num);
	unsigned int get_max();
	unsigned int read_max();
	void balancing(unsigned int root);
	//  get
	unsigned int get_max_size() const;
	unsigned int get_real_size() const;
 private:
	unsigned int size;
	unsigned int *arr;
	unsigned int real_size;
};

unsigned int eating(BinaryHeap heap, unsigned int force);
unsigned int* relock(unsigned int *arr, size_t n);

int main(int argc, char **argv) {
	unsigned int heap_size, force;
	std::cin >> heap_size;
	BinaryHeap heap(heap_size);
	if (heap.get_max_size() == 0) {
		return 0;
	}
	heap.input();
	std::cin >> force;
	std::cout << eating(heap, force) << std::endl;
	return 0;
}

unsigned int eating(BinaryHeap heap, unsigned int force) {
	unsigned int i = 0;
	while(heap.get_real_size() > 0) {
		unsigned int* arr = nullptr;
		unsigned int weight = 0;
		size_t j = 0;
		unsigned int original_size = heap.get_real_size();
		while (weight + heap.read_max() <= force && heap.get_real_size() > 0) {
			unsigned int temp_weight = heap.get_max();
			arr = relock(arr, j);
			arr[j] = temp_weight;
			j++;
			weight += temp_weight;
		}

		while(j > 0) {
        		j--;
        		if (arr[j] != 1) {
        			heap.add_elem(arr[j] / 2);
			}
        	}

		if (arr != nullptr) {
			delete arr;
		}
		++i;
	}
	return i;
}

unsigned int* relock(unsigned int *arr, size_t n) {
	unsigned int* new_arr = new unsigned int[n+1];
	if (n > 0) {
		for (size_t i = 0; i < n; i++) {
			new_arr[i] = arr[i];
		}
		delete arr;
	}
	return new_arr;
}

unsigned int BinaryHeap::get_max_size() const {
	return size;
}

unsigned int BinaryHeap::get_real_size() const {
	return real_size;
}

void BinaryHeap::balancing(unsigned int root) {
	unsigned int left = 2 * root + 1, right = 2 * root + 2;
	if(left < real_size) {
		if(arr[root] < arr[left]) {
			std::swap(arr[root], arr[left]);
			balancing(left);
		}
	}
	if(right < real_size) {
		if(arr[root] < arr[right]) {
			std::swap(arr[root], arr[right]);
			balancing(right);
		}
	}
}

unsigned int BinaryHeap::read_max() {
	return arr[0];
}

unsigned int BinaryHeap::get_max() {
	int result = arr[0];
	arr[0] = arr[real_size - 1];
	balancing(0);
	real_size--;
	return result;
}

void BinaryHeap::input() {
	for (auto i = 0; i < size; ++i) {
		int num;
		std::cin >> num;
		add_elem(num);
	}
}

void BinaryHeap::add_elem(unsigned int num) {
	unsigned int new_elem_position = real_size;
	unsigned int parent_position = (new_elem_position - 1) / 2;
	arr[new_elem_position] = num;
	while (parent_position >= 0 && new_elem_position > 0) {
		if (arr[new_elem_position] > arr[parent_position]) {
			std::swap(arr[new_elem_position], arr[parent_position]);
		}
		new_elem_position = parent_position;
		parent_position = (new_elem_position - 1) / 2;
	}
	real_size++;
}

BinaryHeap::BinaryHeap(unsigned int size) {
	this->size = size;
	arr = new unsigned int[size];
	if (arr == nullptr) {
		size = 0;
	} else {
		real_size = 0;
	}
}