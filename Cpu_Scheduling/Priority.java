package Cpu_Scheduling;
import java.util.PriorityQueue;

// 프로세스를 나타내는 클래스
class Process implements Comparable<Process> {
    private int pid;            // 프로세스 ID
    private int burstTime;      // 실행 시간
    private int priority;       // 우선순위

    public Process(int pid, int burstTime, int priority) {
        this.pid = pid;
        this.burstTime = burstTime;
        this.priority = priority;
    }

    public int getPid() {
        return pid;
    }

    public int getBurstTime() {
        return burstTime;
    }

    public int getPriority() {
        return priority;
    }

    public void decreaseBurstTime() {
        burstTime--;
    }

    @Override
    public int compareTo(Process other) {
        // 우선순위가 높은 프로세스가 우선순위가 낮은 프로세스보다 작은 값을 가지도록 정렬
        if (this.priority < other.priority) {
            return -1;
        } else if (this.priority > other.priority) {
            return 1;
        } else {
            return 0;
        }
    }
}

// 우선순위 알고리즘을 구현한 클래스
class PriorityScheduling {
    public static void priorityScheduling(Process[] processes) {
        PriorityQueue<Process> processQueue = new PriorityQueue<>();

        // 프로세스 큐에 모든 프로세스를 추가
        for (Process process : processes) {
            processQueue.offer(process);
        }

        // 우선순위가 높은 순서대로 프로세스 실행
        while (!processQueue.isEmpty()) {
            Process currentProcess = processQueue.poll();

            // 현재 프로세스 실행
            System.out.println("PID: " + currentProcess.getPid() +
                    " | 실행 시간: " + currentProcess.getBurstTime() +
                    " | 우선순위: " + currentProcess.getPriority());

            // 실행 시간 감소
            currentProcess.decreaseBurstTime();

            // 실행 시간이 남아있으면 다시 큐에 추가
            if (currentProcess.getBurstTime() > 0) {
                processQueue.offer(currentProcess);
            }
        }
    }
}

public class Priority {
    public static void main(String[] args) {
        // 프로세스 생성
        Process[] processes = {
                new Process(1, 10, 3),
                new Process(2, 4, 1),
                new Process(3, 6, 4),
                new Process(4, 2, 2)
        };

        // 우선순위 스케줄링 실행
        PriorityScheduling.priorityScheduling(processes);
    }
}
