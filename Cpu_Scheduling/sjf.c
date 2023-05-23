#include <stdio.h>

void SJF(int arrival_time[], int burst_time[], int n) {
    int completion_time[n]; // 각 프로세스의 완료 시간
    int waiting_time[n]; // 각 프로세스의 대기 시간
    int turnaround_time[n]; // 각 프로세스의 반환 시간
    int total_waiting_time = 0; // 전체 대기 시간의 합
    int total_turnaround_time = 0; // 전체 반환 시간의 합

    int remaining_time[n]; // 각 프로세스의 남은 실행 시간
    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];  // 초기 실행 시간은 프로세스의 실행 시간과 동일
    }

    int completed = 0;        // 완료된 프로세스 수
    int current_time = 0;     // 현재 시간
    int shortest_job = 0;     // 가장 짧은 실행 시간을 가진 프로세스의 인덱스

    while (completed != n) {
        shortest_job = -1;      // 가장 짧은 실행 시간을 가진 프로세스가 없음
        int min_burst = 9999;   // 가장 짧은 실행 시간을 저장하는 변수

        // 현재 시간 이전에 도착하고, 실행 시간이 가장 짧은 프로세스를 찾음
        for (int i = 0; i < n; i++) {
            if (arrival_time[i] <= current_time && remaining_time[i] < min_burst && remaining_time[i] > 0) {
                shortest_job = i;      // 가장 짧은 실행 시간을 가진 프로세스의 인덱스 업데이트
                min_burst = remaining_time[i];  // 가장 짧은 실행 시간 업데이트
            }
        }

        // 가장 짧은 실행 시간을 가진 프로세스가 없는 경우, 시간을 1 증가시키고 다음 루프로 진행
        if (shortest_job == -1) {
            current_time++;
            continue;
        }

        remaining_time[shortest_job]--;  // 실행 시간을 1 감소시킴
        current_time++;

        // 프로세스의 실행이 완료된 경우
        if (remaining_time[shortest_job] == 0) {
            completion_time[shortest_job] = current_time;                             // 완료 시간 업데이트
            waiting_time[shortest_job] = completion_time[shortest_job] - arrival_time[shortest_job] - burst_time[shortest_job];  // 대기 시간 계산
            turnaround_time[shortest_job] = completion_time[shortest_job] - arrival_time[shortest_job];                         // 반환 시간 계산

            total_waiting_time += waiting_time[shortest_job];             // 전체 대기 시간의 합을 업데이트
            total_turnaround_time += turnaround_time[shortest_job];       // 전체 반환 시간의 합을 업데이트

            completed++;  // 완료된 프로세스 수를 증가시킴
        }
    }

    printf("SJF 스케줄링 결과:\n");
    printf("프로세스\t도착 시간\t실행 시간\t완료 시간\t대기 시간\t반환 시간\n");

    // 각 프로세스에 대한 정보를 출력
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i+1, arrival_time[i], burst_time[i], completion_time[i], waiting_time[i], turnaround_time[i]);
    }

    float average_waiting_time = (float)total_waiting_time / n;             // 평균 대기 시간 계산
    float average_turnaround_time = (float)total_turnaround_time / n;       // 평균 반환 시간 계산

    printf("평균 대기 시간: %.2f\n", average_waiting_time);
    printf("평균 반환 시간: %.2f\n", average_turnaround_time);
}

int main() {
    int arrival_time[] = {0, 2, 4, 5, 7};                             // 각 프로세스의 도착 시간
    int burst_time[] = {7, 4, 1, 4, 1};                               // 각 프로세스의 실행 시간
    int n = sizeof(arrival_time) / sizeof(arrival_time[0]);           // 프로세스 수 계산

    SJF(arrival_time, burst_time, n);

    return 0;
}
