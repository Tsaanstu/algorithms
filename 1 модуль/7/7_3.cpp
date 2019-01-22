#include <iostream>

class QSort_MSD {
 public:
    QSort_MSD() = default;
    QSort_MSD(size_t size);
    ~QSort_MSD();
    void Binary_QSort(int left, int right, short int bit_number);
    void output();
    //  gget
    short int get_bitsword() const;
    size_t get_size() const;
 private:
    unsigned long long *arr;
    size_t size;
    const unsigned short int bitsword = 64;
    //  bit = (number >> i) & 1 - определение бита числа
};

int main(int argc, char** argv) {
    size_t size;
    std::cin >> size;
    QSort_MSD a(size);
    a.Binary_QSort(0, a.get_size() - 1, a.get_bitsword() - 1);
    a.output();
    return 0;
}

void QSort_MSD::Binary_QSort(int left, int right, short int bit_number) {
    if (right <= left || bit_number < 0) {
        return;
    }
    int i = left;
    int j = right;

    while( i != j ) {
        while (static_cast<int>(arr[i] >> bit_number & 1) == 0 && (i < j)) {
            ++i;
        }

        while (static_cast<int>(arr[j] >> bit_number & 1) == 1 && (j > i) ) {
            --j;
        }

        std::swap(arr[i], arr[j]);
    }


    if (static_cast<int>(arr[right] >> bit_number & 1) == 0) {
        ++j;
    }

    Binary_QSort(left, j - 1, bit_number - 1);
    Binary_QSort(j, right, bit_number - 1);
}

size_t QSort_MSD::get_size() const {
    return size;
}

short int QSort_MSD::get_bitsword() const {
    return bitsword;
}

void QSort_MSD::output() {
    for (size_t i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

QSort_MSD::QSort_MSD(size_t _size) {
    size = _size;
    arr = new unsigned long long[size];
    for (size_t i = 0; i < size; ++i) {
        std::cin >> arr[i];
    }
}

QSort_MSD::~QSort_MSD() {
    delete [] arr;
}
