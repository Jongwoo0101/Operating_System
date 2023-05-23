#include <stdio.h>

void FCFS(int arrival_time[], int burst_time[], int n) {
    int completion_time[n]; //각 프로세스의 완료 시간
    int waiting_time[n]; //각 프로세스의 대기 시간
    int turnaround_time[n]; //각 프로세스의 반환 시간
    int total_waiting_time = 0; //전체 대기 시간의 합
    int total_turnaround_time = 0; //전체 반환 시간의 합

    completion_time[0] = arrival_time[0] + burst_time[0]; //첫 번째 프로세스의 완료 시간은 도착 시간 + 실행 시간
    waiting_time[0] = 0; //첫 번째 프로세스의 대기 시간은 0
    turnaround_time[0] = burst_time[0]; //첫 번째 프로세스의 반환 시간은 실행 시간

    //두 번째 프로세스부터 마지막 프로세스까지 반복
    for (int i = 1; i < n; i++) {
        completion_time[i] = completion_time[i-1] + burst_time[i]; // 현재 프로세스의 완료 시간 = 이전 프로세스의 완료 시간 + 실행 시간
        waiting_time[i] = completion_time[i-1] - arrival_time[i]; // 대기 시간 = 이전 프로세스의 완료 시간 - 현재 프로세스의 도착 시간
        turnaround_time[i] = burst_time[i] + waiting_time[i]; // 반환 시간 = 실행 시간 + 대기 시간
        total_waiting_time += waiting_time[i]; // 전체 대기 시간의 합을 업데이트
        total_turnaround_time += turnaround_time[i]; // 전체 반환 시간의 합을 업데이트
    }

    printf("FCFS 스케줄링 결과:\n");
    printf("프로세스\t도착 시간\t실행 시간\t완료 시간\t대기 시간\t반환 시간\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i+1, arrival_time[i], burst_time[i], completion_time[i], waiting_time[i], turnaround_time[i]);
    }

    float average_waiting_time = (float)total_waiting_time / n; //평균 대기 시간 계산
    float average_turnaround_time = (float)total_turnaround_time / n; // 평균 반환 시간 계산

    printf("평균 대기 시간: %.2f\n", average_waiting_time);
    printf("평균 반환 시간: %.2f\n", average_turnaround_time);
}

int main() {
    int arrival_time[] = {0, 2, 4, 5, 7};
    int burst_time[] = {7, 4, 1, 4, 1};
    int n = sizeof(arrival_time) / sizeof(arrival_time[0]);

    FCFS(arrival_time, burst_time, n);

    return 0;
}
