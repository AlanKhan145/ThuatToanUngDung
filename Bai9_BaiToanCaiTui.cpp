/*Phát biểu bài toán
Có n đồ vật: Mỗi đồ vật i có trọng lượng W_i và giá trị sử dụng C_i, với i = 1, 2, ..., n.
Yêu cầu: Tìm cách chọn các đồ vật này vào cái túi có dung lượng b sao cho tổng trọng lượng của các đồ vật được chọn vào túi không vượt quá b, đồng thời tổng giá trị của chúng là lớn nhất.
Ký hiệu: Ký hiệu S = {1, 2, ..., n} là tập chỉ số của các đồ vật. Bài toán đặt ra là:
Tìm I thuộc S sao cho
Tối đa hóa tổng giá trị:
+max (tổng giá trị C_i của các đồ vật trong I)
với điều kiện: tổng trọng lượng W_i của các đồ vật trong I không vượt quá b.
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    int weight;
    int value;
    double value_per_weight;
};

// Hàm so sánh để sắp xếp đồ vật theo giá trị trên trọng lượng giảm dần
bool compare(Item a, Item b) {
    return a.value_per_weight > b.value_per_weight;
}

int knapsack(int capacity, std::vector<Item>& items) {
    // Sắp xếp các đồ vật theo giá trị trên trọng lượng giảm dần
    for (auto& item : items) {
        item.value_per_weight = (double)item.value / item.weight;
    }
    sort(items.begin(), items.end(), compare);

    int total_value = 0;
    for (const auto& item : items) {
        if (capacity >= item.weight) {
            // Lấy toàn bộ đồ vật
            capacity -= item.weight;
            total_value += item.value;
        } else {
            // Lấy một phần đồ vật (nếu cần)
            total_value += item.value_per_weight * capacity;
            break;
        }
    }

    return total_value;
}

int main() {
    int n, capacity;
    cout << "Nhập số đồ vật: ";
    cin >> n;
    cout << "Nhập dung lượng của túi: ";
    cin >> capacity;

    vector<Item> items(n);
    cout << "Nhập thông tin đồ vật (trọng lượng và giá trị):\n";
    for (int i = 0; i < n; ++i) {
        cout << "Đồ vật " << i + 1 << ": ";
        cin >> items[i].weight >> items[i].value;
    }

    int max_value = knapsack(capacity, items);
    cout << "Tổng giá trị lớn nhất là: " << max_value << "\n";

    return 0;
}
