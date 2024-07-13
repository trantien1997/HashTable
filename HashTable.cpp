#include <iostream>
#include <vector>
#include <string>

// Khai báo cấu trúc node cho danh sách liên kết
struct Node {
    std::string key;
    std::string value;
    Node* next;
    Node(const std::string& k, const std::string& v) : key(k), value(v), next(nullptr) {}
};

// Lớp bảng băm
class HashTable {
private:
    std::vector<Node*> buckets; // Danh sách các bucket
    size_t capacity; // Số lượng bucket

	// Hàm băm
    size_t hashFunction(const std::string& key) const {
        size_t hash = 0;
        for (char c : key) {
            hash += static_cast<size_t>(c);
        }
        return hash % capacity;
    }

public:
    HashTable(size_t size) : capacity(size) {
        buckets.resize(capacity, nullptr);
    }

    // Thêm phần tử vào bảng băm
    void insert(const std::string& key, const std::string& value) {
        size_t index = hashFunction(key);
        Node* newNode = new Node(key, value);
        if (!buckets[index]) {
            buckets[index] = newNode;
        } else {
            Node* current = buckets[index];
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // Tìm kiếm phần tử trong bảng băm
    std::string search(const std::string& key) const {
        size_t index = hashFunction(key);
        Node* current = buckets[index];
        while (current) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        return "Not found";
    }

    // Hủy bỏ bảng băm
    ~HashTable() {
        for (Node* node : buckets) {
            while (node) {
                Node* temp = node;
                node = node->next;
                delete temp;
            }
        }
    }
};

int main() {
    HashTable ht(10); // Khởi tạo bảng băm với 10 bucket
    ht.insert("apple", "fruit");
    ht.insert("banana", "fruit");
    ht.insert("carrot", "vegetable");

    std::cout << "Value for 'banana': " << ht.search("banana") << std::endl;
    std::cout << "Value for 'grape': " << ht.search("grape") << std::endl;

    return 0;
}
