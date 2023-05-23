#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// 프로세스를 나타내는 구조체
struct Process {
    int pid;            // 프로세스 ID
    int burstTime;      // 실행 시간
    int remainingTime;  // 남은 실행 시간

    Process(int id, int burst) : pid(id), burstTime(burst), remainingTime(burst) {}
};

// Round Robin 알고리즘을 구현한 함수
void roundRobinScheduling(const vector<Process>& processes, int timeQuantum) {
    queue<Process> processQueue;  // 프로세스 큐
    int currentTime = 0;          // 현재 시간

    // 프로세스 큐에 모든 프로세스를 추가
    for (const Process& process : processes) {
        processQueue.push(process);
    }

    // 라운드 로빈 스케줄링 실행
    while (!processQueue.empty()) {
        Process currentProcess = processQueue.front();  // 큐의 가장 앞에 있는 프로세스 가져오기
        processQueue.pop();  // 큐에서 프로세스 제거

        // 현재 프로세스 실행
        int executionTime = min(timeQuantum, currentProcess.remainingTime);  // 시간 할당량과 남은 실행 시간 중 작은 값 선택
        currentTime += executionTime;  // 현재 시간 업데이트
        currentProcess.remainingTime -= executionTime;  // 남은 실행 시간 업데이트

        // 남은 실행 시간이 있는 경우 다시 큐에 추가
        if (currentProcess.remainingTime > 0) {
            processQueue.push(currentProcess);
        }

        // 프로세스 실행 정보 출력
        cout << "PID: " << currentProcess.pid << " | Executed Time: " << executionTime
             << " | Remaining Time: " << currentProcess.remainingTime << " | Current Time: " << currentTime << endl;
    }
}

int main() {
    // 프로세스 생성
    vector<Process> processes;
    processes.push_back(Process(1, 10));
    processes.push_back(Process(2, 4));
    processes.push_back(Process(3, 6));
    processes.push_back(Process(4, 2));

    int timeQuantum = 3;  // 시간 할당량

    // Round Robin 스케줄링 실행
    roundRobinScheduling(processes, timeQuantum);

    return 0;
}
