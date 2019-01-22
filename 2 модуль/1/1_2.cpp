#include <iostream>
#include <string>

class hash_table {
public:
    hash_table(size_t _size = 1);
    ~hash_table();
    void hash_table_rebuild();
    bool has(const std::string& key);
    bool add(const std::string& key);
    bool remove(const std::string& key);
    size_t first_hash(const std::string str);
    size_t second_hash(const std::string str);
private:
    std::string* records_;
    size_t size_;
    size_t max_size_;
    const size_t a = 26;
    const std::string empty_ = "~!empty!~";
    const std::string deleted_ = "~!deleted!~";
};

int main(int argc, char **argv) {
    hash_table strings(8);
    char command = 0;
    std::string key;
    while (std::cin >> command >> key) {
        switch (command) {
            case '?':
                std::cout << (strings.has(key) ? "OK" : "FAIL") << std::endl;
                break;
            case '+':
                std::cout << (strings.add(key) ? "OK" : "FAIL") << std::endl;
                break;
            case '-':
                std::cout << (strings.remove(key) ? "OK" : "FAIL") << std::endl;
                break;
        }
    }
    return 0;
}

hash_table::~hash_table() {
    delete [] records_;
}

void hash_table::hash_table_rebuild() {
    max_size_ *= 2;
    std::string* new_array_for_records = new std::string[max_size_];
    for (size_t i = 0; i < max_size_; ++i) {
        new_array_for_records[i] = empty_;
    }

    for (size_t i = 0; i < max_size_ / 2; ++i) {
        if (records_[i] != empty_ && records_[i] != deleted_) {
            size_t fh_result = first_hash(records_[i]) % max_size_;
            size_t sh_result = second_hash(records_[i]);
            for (size_t i = 0; i < max_size_ && new_array_for_records[fh_result] != empty_; ++i) {
                fh_result = (fh_result + sh_result) % max_size_;
            }
            new_array_for_records[fh_result] = records_[i];
        }
    }

    delete [] records_;
    records_ = new_array_for_records;
}

hash_table::hash_table(size_t _size) {
    size_ = 0;
    max_size_ = _size;
    records_ = new std::string[max_size_];
    for (size_t i = 0; i < max_size_; ++i) {
        records_[i] = empty_;
    }
}

size_t hash_table::first_hash(const std::string str) {
    size_t hash  =  0;
    for(auto it = str.begin();  it != str.end();  ++it ) {
        hash = (hash * a + *it) % max_size_;
    }
    return hash;
}

size_t hash_table::second_hash(const std::string str) {
    size_t hash = first_hash(str);
    if (hash < 3) {
        hash = 3;
    }
    if (hash % 2 == 0) {  //  !!! Всегда возвращать нечетные числа (из лекции)
        --hash;
    }
    return hash;
}

bool hash_table::add(const std::string& key) {
    if (static_cast<double> (size_ / max_size_) > 0.75) {
        hash_table_rebuild();
    }
    size_t fh_result = first_hash(key) % max_size_;
    size_t sh_result = second_hash(key);
    long int firstDeleted = -1;
    for (size_t i = 0; i < max_size_ && records_[fh_result] != empty_ && records_[fh_result] != key; ++i) {
        fh_result = (fh_result + sh_result) % max_size_;
        if (records_[fh_result] == deleted_) {
            firstDeleted = fh_result;
        }
    }
    if (records_[fh_result] == key) {
        return false;
    }
    if (records_[fh_result] != empty_) {
        if (firstDeleted >= 0) {
            records_[firstDeleted] = key;
            ++size_;
            return true;
        }
        return false;
    }
    records_[fh_result] = key;
    ++size_;
    return true;
}

bool hash_table::has(const std::string& key) {
    size_t fh_result = first_hash(key) % max_size_;
    size_t sh_result = second_hash(key);
    for (size_t i = 0; i < max_size_ && records_[fh_result] != empty_ && records_[fh_result] != key; ++i) {
        fh_result = (fh_result + sh_result) % max_size_;
    }
    if (records_[fh_result] == key) {
        return true;
    }
    return false;
}

bool hash_table::remove(const std::string& key) {
    size_t fh_result = first_hash(key) % max_size_;
    size_t sh_result = second_hash(key);
    for (size_t i = 0; i < max_size_ && records_[fh_result] != empty_ && records_[fh_result] != key; ++i) {
        fh_result = (fh_result + sh_result) % max_size_;
    }
    if (records_[fh_result] == key) {
        records_[fh_result] = deleted_;
        --size_;
        return true;
    }
    return false;
}