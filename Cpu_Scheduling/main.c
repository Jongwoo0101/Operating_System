#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// 공유 자원
int shared_resource = 0;

// 뮤텍스 초기화
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// 스레드 함수
void* thread_function(void* arg) {
    int thread_id = *(int*)arg;

    // 크리티컬 섹션 진입
    pthread_mutex_lock(&mutex);

    // 공유 자원에 접근하여 작업 수행
    shared_resource += thread_id;
    printf("스레드 %d: 공유 자원에 접근하여 작업 수행\n", thread_id);

    // 크리티컬 섹션 탈출
    pthread_mutex_unlock(&mutex);

    // 스레드 종료
    pthread_exit(NULL);
}

int main() {
    int num_threads = 5;
    pthread_t threads[num_threads];
    int thread_ids[num_threads];

    // 스레드 생성 및 실행
    for (int i = 0; i < num_threads; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }

    // 모든 스레드 종료 대기
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // 결과 출력
    printf("최종 공유 자원 값: %d\n", shared_resource);

    return 0;
}
