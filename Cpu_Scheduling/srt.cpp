#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// 프로세스를 나타내는 구조체
struct Process {
    int pid;            // 프로세스 ID
    int arrivalTime;    // 도착 시간
    int burstTime;      // 실행 시간
    int remainingTime;  // 남은 실행 시간

    Process(int id, int arrival, int burst)
        : pid(id), arrivalTime(arrival), burstTime(burst), remainingTime(burst) {}
};

// SRT 알고리즘을 구현한 함수
void srtScheduling(vector<Process>& processes) {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > processQueue;
    int currentTime = 0;

    int numProcesses = processes.size();
    int completedProcesses = 0;

    while (completedProcesses < numProcesses) {
        // 도착한 프로세스를 큐에 추가
        for (int i = 0; i < numProcesses; ++i) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                processQueue.push(make_pair(processes[i].remainingTime, i));
            }
        }

        // 큐에서 실행 시간이 가장 짧은 프로세스 선택
        if (!processQueue.empty()) {
            int processIndex = processQueue.top().second;
            processQueue.pop();

            Process& currentProcess = processes[processIndex];

            // 현재 프로세스 실행
            cout << "PID: " << currentProcess.pid << " | Current Time: " << currentTime << endl;
            currentProcess.remainingTime--;

            // 프로세스 실행 완료
            if (currentProcess.remainingTime == 0) {
                completedProcesses++;
            }
        } else {
            // 큐가 비어있는 경우 대기
            cout << "Waiting..." << " | Current Time: " << currentTime << endl;
        }

        currentTime++;
    }
}

int main() {
    // 프로세스 생성
    vector<Process> processes;
    processes.push_back(Process(1, 0, 6));
    processes.push_back(Process(2, 2, 2));
    processes.push_back(Process(3, 4, 8));
    processes.push_back(Process(4, 6, 3));

    // SRT 스케줄링 실행
    srtScheduling(processes);

    return 0;
}
