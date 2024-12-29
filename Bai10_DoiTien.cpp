/*Có các đồng tiền mệnh giá: 1, 5, 10, 25, 100 (xu).
Hãy tìm phương pháp đổi một lượng tiền x sử dụng một số lượng ít nhất các đồng tiền*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int price;
};

int n; // Số loại đồng tiền
int soTien; // Số tiền cần đổi

// Hàm so sánh để sắp xếp theo thứ tự giảm dần giá trị
bool compare(Item a, Item b) {
    return a.price > b.price;
}

int main() {
    cin >> n; // Nhập số loại đồng tiền
    vector<Item> items(n); // Mảng lưu giá trị của các đồng tiền
    for (int i = 0; i < n; i++) {
        cin >> items[i].price; // Nhập giá trị của đồng tiền
    }
    cin >> soTien; // Nhập số tiền cần đổi

    // Sắp xếp các đồng tiền theo thứ tự giảm dần giá trị
    sort(items.begin(), items.end(), compare);

    vector<int> heSo(n, 0); // Hệ số của từng loại đồng tiền
    int tongHeSo = 0; // Tổng hệ số các loại đồng tiền

    // Thực hiện đổi tiền
    for (int i = 0; i < n; i++) {
        if (soTien <= 0) break; // Nếu số tiền đã đổi hết, thoát vòng lặp
        heSo[i] = soTien / items[i].price; // Số lượng đồng tiền loại này
        soTien -= heSo[i] * items[i].price; // Cập nhật số tiền còn lại
        tongHeSo += heSo[i]; // Cộng vào tổng hệ số
    }

    cout << tongHeSo << endl; // In ra tổng số đồng tiền sử dụng
    for (int i = 0; i < n; i++) {
        cout << heSo[i] << " "; // In ra số lượng từng loại đồng tiền
    }
    cout << endl;

    return 0;
}
