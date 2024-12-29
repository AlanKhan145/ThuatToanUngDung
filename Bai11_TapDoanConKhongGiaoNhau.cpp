#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Cấu trúc lưu trữ một công việc
struct Job {
    int start; // Thời gian bắt đầu
    int finish; // Thời gian kết thúc
};

// Hàm so sánh để sắp xếp các công việc theo thời gian kết thúc
bool compareByFinishTime(const Job& a, const Job& b) {
    return a.finish < b.finish;
}

// Hàm chọn tập con lớn nhất các công việc phù hợp
vector<Job> activitySelection(vector<Job>& jobs) {
    // Sắp xếp các công việc theo thời gian kết thúc
    sort(jobs.begin(), jobs.end(), compareByFinishTime);

    vector<Job> selectedJobs; // Danh sách công việc được chọn
    int lastFinishTime = 0; // Thời gian kết thúc của công việc cuối cùng đã chọn

    // Duyệt qua các công việc
    for (const auto& job : jobs) {
        if (job.start >= lastFinishTime) { // Kiểm tra xem công việc có phù hợp không
            selectedJobs.push_back(job);  // Thêm công việc vào danh sách được chọn
            lastFinishTime = job.finish; // Cập nhật thời gian kết thúc
        }
    }

    return selectedJobs;
}

int main() {
    // Danh sách công việc (bắt đầu, kết thúc)
    vector<Job> jobs = {
        {1, 3}, {2, 5}, {4, 6}, {6, 7}, {5, 8}, {8, 9}
    };

    // Gọi hàm chọn công việc
    vector<Job> result = activitySelection(jobs);

    // Hiển thị kết quả
    cout << "Các công việc được chọn là: \n";
    for (const auto& job : result) {
        cout << "Bắt đầu: " << job.start << ", Kết thúc: " << job.finish << "\n";
    }

    return 0;
}
