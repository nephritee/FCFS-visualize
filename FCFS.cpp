#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

struct Process {
    int id;          // ID của tiến trình
    int arrivalTime; // Thời điểm đến
    int burstTime;   // Thời gian thực thi
};

void textColor(int x)
{
    HANDLE color;
    color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(color, x);
}

void fcfsScheduling(const vector<Process>& processes) {
    int n = processes.size();

    int currentTime = 0; // Thời điểm hiện tại
    int totalWaitingTime = 0; // Tổng thời gian chờ
    int sumTurnAround = 0;
    textColor(10);
    cout << "Qua trinh dieu phoi chien luoc FCFS:" << endl;

    for (int i = 0; i < n; i++) {
        const Process& currentProcess = processes[i];

        // Tính thời gian chờ của tiến trình hiện tại
        int waitingTime = max(0, currentTime - currentProcess.arrivalTime);
        totalWaitingTime += waitingTime;
        // Tính thời gian thực hiện của tiến trình hiện tại 
        int turn = currentTime + currentProcess.burstTime - currentProcess.arrivalTime; 
        sumTurnAround += turn;
        textColor(15);
        // In thông tin về tiến trình
        cout << "Thoi diem thu: " << currentTime << endl;
        cout << "Tien trinh bat dau thuc hien: P" << currentProcess.id << endl;
        //cout << "Tien trinh da hoan thanh: P" << currentProcess.arrivalTime << endl;
        cout << "Thoi gian thuc hien: " << currentProcess.burstTime << endl;
        cout << "Thoi gian cho: " << waitingTime << endl;
        cout << "Thoi diem hoan thanh tien trinh: " << currentTime + currentProcess.burstTime << endl; 
        textColor(3);
        cout << "------------------------" << endl;

        // Cập nhật thời gian hiện tại
        currentTime += currentProcess.burstTime;
    }

    // Tính thời gian chờ trung bình
    float averageWaitingTime = static_cast<float>(totalWaitingTime) / n;
    // Tính thời gian hoan thanh trung bình
    float turnAround = static_cast<float>(sumTurnAround) / n;

    textColor(14);
    cout << "Thoi gian cho trung binh: " << averageWaitingTime << endl;
    cout << "Thoi gian hoan thanh trung binh:" << turnAround << endl; 
    textColor(15);
}

int main() {
    int numProcesses;
    cout << "Nhap so tien trinh: ";
    cin >> numProcesses;

    vector<Process> processes(numProcesses);

    for (int i = 0; i < numProcesses; i++) {
        textColor(11);
        cout << "Tien trinh P" << i + 1 << endl;
        textColor(15);
        cout << "Nhap thoi diem vao: ";
        cin >> processes[i].arrivalTime;
        cout << "Nhap thoi gian thuc hien : ";
        cin >> processes[i].burstTime;
        processes[i].id = i + 1;
    }

    // Gọi hàm thực thi thuật toán FCFS
    fcfsScheduling(processes);

    return 0;
}