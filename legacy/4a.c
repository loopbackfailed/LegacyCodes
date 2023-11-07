#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define PRODUCERS_COUNT 3
#define CONSUMERS_COUNT 2

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

sem_t empty, full;
pthread_mutex_t mutex;

void *producer(void *arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        item = i + 1; // Produce an item

        sem_wait(&empty); // Wait if the buffer is full
        pthread_mutex_lock(&mutex); // Lock the critical section

        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;

        printf("Producer %ld produced: %d\n", (long)arg, item);

        pthread_mutex_unlock(&mutex); // Unlock the critical section
        sem_post(&full); // Signal that an item has been added
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        sem_wait(&full); // Wait if the buffer is empty
        pthread_mutex_lock(&mutex); // Lock the critical section

        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;

        printf("Consumer %ld consumed: %d\n", (long)arg, item);

        pthread_mutex_unlock(&mutex); // Unlock the critical section
        sem_post(&empty); // Signal that an item has been consumed
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producer_threads[PRODUCERS_COUNT];
    pthread_t consumer_threads[CONSUMERS_COUNT];

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    for (long i = 0; i < PRODUCERS_COUNT; i++) {
        pthread_create(&producer_threads[i], NULL, producer, (void *)i);
    }

    for (long i = 0; i < CONSUMERS_COUNT; i++) {
        pthread_create(&consumer_threads[i], NULL, consumer, (void *)i);
    }

    for (int i = 0; i < PRODUCERS_COUNT; i++) {
        pthread_join(producer_threads[i], NULL);
    }

    for (int i = 0; i < CONSUMERS_COUNT; i++) {
        pthread_join(consumer_threads[i], NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
