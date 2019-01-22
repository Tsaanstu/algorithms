#include <iostream>
#include <unistd.h>
#include <assert.h>

#define MEMORY_ERROR {assert(arr == nullptr); return -1;};

template<typename T>
T search_order_statistics(T *arr, size_t size, size_t s_position);

template <typename T>
T* input_arr(T* type_arr, size_t size);

template<typename T>
size_t partition(T *arr, size_t left, size_t right);

int main(int argc, char **argv) {
    srand(getpid());
    size_t size, position;
    std::cin >> size >> position;
    unsigned int *arr = input_arr(arr, size);
    if (arr == nullptr) {
        MEMORY_ERROR;
    }
    std::cout << search_order_statistics(arr, size, position) << std::endl;
    delete [] arr;
    return 0;
}

template<typename T>
size_t partition(T *arr, size_t left, size_t right) {
    if (left == right) {
        return right;
    }
    size_t support_member_position = rand() % (right - left);
    std::swap(arr[left], arr[left + support_member_position]);
    T support_member = arr[left];
    size_t itterator = right;
    for (size_t i = right; i > left; --i) {
        if (arr[i] >= support_member) {
            std::swap(arr[i], arr[itterator--]);
        }
    }
    if (arr[left] >= support_member) {
        std::swap(arr[left], arr[itterator]);
    }
    return itterator;
}

template<typename T>
T search_order_statistics(T *arr, size_t size, size_t s_position) {
    size_t left = 0, right = size - 1, position = s_position + 1;
    while (position != s_position) {
        position = partition(arr, left, right);
        if (s_position <= position) {
            right = position - 1;
        } else if (s_position > position) {
            left = position + 1;
        }
    }
    return arr[position];
}

template <typename T>
T* input_arr(T* type_arr, size_t size) {
    T *arr = new T[size];
    if (arr == nullptr) {
        return nullptr;
    }
    for (size_t i = 0; i < size; ++i) {
        std::cin >> arr[i];
    }
    return arr;
}