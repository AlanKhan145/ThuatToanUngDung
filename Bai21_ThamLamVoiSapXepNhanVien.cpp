#include <bits/stdc++.h>
using namespace std;

int n, d, a, b;
vector<vector<bool>> coTheNghi;  // Indicates if employee i can rest on day j
vector<vector<int>> x, nvtrongca;  // x stores the shifts, nvtrongca stores how many employees in each shift
vector<int> soCaDem;  // Stores the number of night shifts each employee has
vector<pair<int, int>> employees;  // To store employee ID and number of days off, for sorting

// Function to assign shifts in a greedy manner
void assignShifts() {
    // Sorting employees by their number of off days (prioritize employees with more days off)
    for (int i = 1; i <= n; i++) {
        int offDays = 0;
        for (int j = 1; j <= d; j++) {
            if (coTheNghi[i][j]) offDays++;
        }
        employees.push_back({offDays, i});
    }
    sort(employees.rbegin(), employees.rend());  // Sort in descending order of off days

    // Initializing structures
    x.assign(n + 1, vector<int>(d + 1, 0));
    nvtrongca.assign(d + 1, vector<int>(5, 0));  // There are 4 shifts + 1 (for '0' - rest)

    // Greedily assign shifts
    for (auto& emp : employees) {
        int empID = emp.second;
        for (int day = 1; day <= d; day++) {
            if (coTheNghi[empID][day]) {
                x[empID][day] = 0;  // This employee is off that day
                continue;
            }

            // Try assigning the least restrictive shift (avoid night shifts if possible)
            bool assigned = false;
            for (int shift = 1; shift <= 3; shift++) {
                if (nvtrongca[day][shift] < b) {  // Can this shift accommodate more employees?
                    x[empID][day] = shift;
                    nvtrongca[day][shift]++;
                    assigned = true;
                    break;
                }
            }

            if (!assigned) {
                // If no day shift is available, assign the night shift if allowed
                if (nvtrongca[day][4] < b) {
                    x[empID][day] = 4;
                    nvtrongca[day][4]++;
                    soCaDem[empID]++;
                }
            }
        }
    }
}

int main() {
    cin >> n >> d >> a >> b;

    // Read the list of off days for each employee
    coTheNghi.assign(n + 1, vector<bool>(d + 1, false));  // n employees, d days
    for (int i = 1; i <= n; i++) {
        while (true) {
            int temp;
            cin >> temp;
            if (temp == -1) break;
            coTheNghi[i][temp] = true;  // Mark the days the employee cannot work
        }
    }

    assignShifts();  // Assign shifts to employees greedily

    // Output the result matrix X
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= d; j++) {
            cout << x[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
