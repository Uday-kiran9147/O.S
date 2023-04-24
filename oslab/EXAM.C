#include <stdio.h>
#include <pthread.h>

#define MAX_RESOURCES 5 // maximum number of resources of each type
#define MAX_PROCESSES 3 // maximum number of processes

int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

pthread_mutex_t mutex;

int request_resources(int pid, int *request) {
    pthread_mutex_lock(&mutex);
    // check if request is valid
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (request[i] > need[pid][i]) {
            pthread_mutex_unlock(&mutex);
            return -1; // request exceeds need
        }
        if (request[i] > available[i]) {
            pthread_mutex_unlock(&mutex);
            return -2; // request exceeds availability
        }
    }
    // try to allocate resources and check safety
    for (int i = 0; i < MAX_RESOURCES; i++) {
        available[i] -= request[i];
        allocation[pid][i] += request[i];
        need[pid][i] -= request[i];
    }
    if (!is_safe()) {
        // allocation is unsafe, rollback and deny request
        for (int i = 0; i < MAX_RESOURCES; i++) {
            available[i] += request[i];
            allocation[pid][i] -= request[i];
            need[pid][i] += request[i];
        }
        pthread_mutex_unlock(&mutex);
        return -3; // request denied
    }
    pthread_mutex_unlock(&mutex);
    return 0; // request granted
}

void release_resources(int pid, int *release) {
    pthread_mutex_lock(&mutex);
    // release allocated resources
    for (int i = 0; i < MAX_RESOURCES; i++) {
        available[i] += release[i];
        allocation[pid][i] -= release[i];
        need[pid][i] += release[i];
    }
    pthread_mutex_unlock(&mutex);
}

int is_safe() {
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES];
    // initialize work and finish arrays
    for (int i = 0; i < MAX_RESOURCES; i++) {
        work[i] = available[i];
    }
    for (int i = 0; i < MAX_PROCESSES; i++) {
        finish[i] = 0;
    }
    // find a safe sequence
    int count = 0;
    while (count < MAX_PROCESSES) {
        int found = 0;
        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < MAX_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == MAX_RESOURCES) {
                    for (j = 0; j < MAX_RESOURCES; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }
        if (!found) {
            break;
        }
    }
    return (count == MAX_PROCESSES);
}

void *customer(void *arg) {
    int pid = (int) arg;
    // generate random request
    int request[MAX_RESOURCES];
    for (int i = 0; i < MAX_RESOURCES; i++) {
        request[i] = rand() % (need[pid][i] + 1);
}
// request resources
printf("Customer %d requesting resources: ", pid);
for (int i = 0; i < MAX_RESOURCES; i++) {
printf("%d ", request[i]);
}
printf("\n");
int result = request_resources(pid, request);
if (result == 0) {
printf("Customer %d has been granted resources.\n", pid);
} else {
printf("Customer %d's request has been denied.\n", pid);
}
// generate random release
int release[MAX_RESOURCES];
for (int i = 0; i < MAX_RESOURCES; i++) {
release[i] = rand() % (allocation[pid][i] + 1);
}
// release resources
printf("Customer %d releasing resources: ", pid);
for (int i = 0; i < MAX_RESOURCES; i++) {
printf("%d ", release[i]);
}
printf("\n");
release_resources(pid, release);
return NULL;
}

int main() {
// initialize data structures
for (int i = 0; i < MAX_RESOURCES; i++) {
available[i] = MAX_RESOURCES;
}
for (int i = 0; i < MAX_PROCESSES; i++) {
for (int j = 0; j < MAX_RESOURCES; j++) {
maximum[i][j] = rand() % (MAX_RESOURCES + 1);
allocation[i][j] = 0;
need[i][j] = maximum[i][j];
}
}
// create threads
pthread_t threads[MAX_PROCESSES];
for (int i = 0; i < MAX_PROCESSES; i++) {
pthread_create(&threads[i], NULL, customer, (void *) i);
}
// wait for threads to finish
for (int i = 0; i < MAX_PROCESSES; i++) {
pthread_join(threads[i], NULL);
}
return 0;
}
