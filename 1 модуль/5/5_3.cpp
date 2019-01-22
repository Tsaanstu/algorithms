#include <iostream>
#include <algorithm>
#include <cstring>

class Point;

class Straight {
public:
    Straight(size_t size = 0);
    ~Straight();
    size_t get_size() const;
    void push(size_t i, Point p);
    void merge_sort(Point *arr, size_t len);
    void my_merge(Point* first_begin, Point* first_end, Point* second_begin, Point* second_end, Point* arr);
    int shading();
    //  get
    Point* get_points();
    size_t get_size();
private:
    Point* points;
    size_t size;
};

class Point {
public:
    Point(int k = 0, bool t = 0) : koor(k), type(t){};
    //  get
    int get_koor() const;
    bool get_type() const;
    //  set
    void set_koor(int num);
private:
    int koor;
    bool type;  //  0 - begin, 1 - end
};

void input_straight(Straight& straight);

int main(int argc, char **argv) {
    size_t arr_size = 0;
    std::cin >> arr_size;
    Straight straight(arr_size * 2);
    input_straight(straight);
    straight.merge_sort(straight.get_points(), straight.get_size());
    std::cout << straight.shading() << std::endl;
    return 0;
}

int Straight::shading() {
    int sh = 0, len = 0;
    if (points[0].get_type() == 0) {
        sh++;
    } else {
        sh--;
    }
    for (size_t i = 1; i < size; ++i) {
        if (sh > 0) {
            len += points[i].get_koor() - points[i - 1].get_koor();
        }
        if (points[i].get_type() == 0) {
            sh++;
        } else {
            sh--;
        }
    }
    return len;
}

size_t Straight::get_size() {
    return size;
}

Point* Straight::get_points() {
    return points;
}

void Straight::my_merge(Point* first_begin, Point* first_end, Point* second_begin, Point* second_end, Point* arr) {
    while(true) {
        if (first_begin == first_end) {
            std::copy(second_begin, second_end, arr);
            return;
        }
        if (second_begin == second_end) {
            std::copy(first_begin, first_end, arr);
            return;
        }
        if (second_begin->get_koor() < first_begin->get_koor()) {
            *arr = *second_begin;
            *second_begin++;
        } else {
            *arr = *first_begin;
            *first_begin++;
        }
        *arr++;
    }
}

void Straight::merge_sort(Point *arr, size_t len) {
    if (len <= 1) {
        return;
    }
    size_t first = len / 2;
    size_t second = len - first;
    merge_sort(arr, first);
    merge_sort(arr + first, second);
    Point *c = new Point[len];
    my_merge(arr, arr + first, arr + first, arr + first + second, c);
    memcpy(arr, c, sizeof(Point) * len);
    delete [] c;
}

void input_straight(Straight& straight) {
    size_t size = straight.get_size();
    for (size_t i = 0; i < size; ++i) {
        int temp_num;
        std::cin >> temp_num;
        if (i % 2 == 0) {
            straight.push(i, Point(temp_num, 0));
        } else {
            straight.push(i, Point(temp_num, 1));
        }
    }
}

bool Point::get_type() const{
    return type;
}

void Point::set_koor(int num) {
    koor = num;
}

int Point::get_koor() const {
    return koor;
}

void Straight::push(size_t i, Point p) {
    points[i] = p;
}

Straight::Straight(size_t size) {
    this->size = size;
    points = new Point[size];
}

size_t Straight::get_size() const {
    return size;
}

Straight::~Straight() {
    delete[] points;
}