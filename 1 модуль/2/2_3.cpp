#include <iostream>

#define MEMORY_ERROR -1

void binary_search(int *A_arr, int num, size_t n, size_t m, size_t *min_left_border, size_t max_right_border);
void prep_binary_search(int *A_arr, int *B_arr, int n, int m);
void end_search(int *A_arr, int *B_arr, size_t n, size_t m, int koef, size_t* expected_max, size_t B_arr_position);
int* input(size_t size);

int main(int argc, char** argv) {
	int *A_arr = nullptr, *B_arr = nullptr;
	int n = 0, m = 0;
	std::cin >> n >> m;
	A_arr = input(n);
	if (A_arr == nullptr) {
		return MEMORY_ERROR;
	}
	B_arr = input(m);
	if (B_arr == nullptr) {
		return MEMORY_ERROR;
	}
	if (B_arr[0] <= A_arr[n-1]) {
		prep_binary_search(A_arr, B_arr, n, m);
	}
	return 0;
}

void prep_binary_search(int *A_arr, int *B_arr, int n, int m) {
	size_t min_left_border = 0 , max_right_border = 0, expected_max = 1, B_arr_position;
	int koef = 2;
	for (size_t i = 0; i < m; ++i) {
		end_search(A_arr, B_arr, n, m, koef, &expected_max, B_arr_position);
		if (expected_max != 0) {
			if (max_right_border < n - 1) {
				max_right_border = expected_max;
			} else {
				max_right_border = n - 1;
			}
		}
		binary_search(A_arr, B_arr[i], n, m, &min_left_border, n);
	}
	std::cout << std::endl;
}

void binary_search(int *A_arr, int num, size_t n, size_t m, size_t *min_left_border, size_t max_right_border) {
	int left_border = *min_left_border, right_border = max_right_border;
	while (left_border <= right_border) {
		int middle = (left_border + right_border) / 2;
		if (num == A_arr[middle]) {
			std::cout << num << " ";
			*min_left_border = left_border;
			return;
		}
		if (num < A_arr[middle]) {
			right_border = middle - 1;
		} else {
			left_border = middle + 1;
		}
	}
}

void end_search(int *A_arr, int *B_arr, size_t n, size_t m, int koef, size_t* expected_max, size_t B_arr_position) {
	while ((*expected_max * koef <= n) && (A_arr[*expected_max * koef] > B_arr[B_arr_position])) {
		*expected_max = *expected_max * 2;
	} 
}

int* input(size_t size) {
	int *arr = new int[size];
	if (arr == nullptr) {
		return nullptr;
	}
	for (size_t i = 0; i < size; ++i) {
		std::cin >> arr[i];
	}
	return arr;
}