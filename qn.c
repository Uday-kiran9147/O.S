#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>

#define SIZE 8

int shrd_mem_id;
// writer process
void writerProcess(int *array) {
  int i = 0;
  while (1) {
    array[i] = i + 1;
    sleep(3);
    i++;
    if (i == SIZE) {
      break;
    }
  }
}

// reader process
void readerProcess(int *array) {
  int i = 0;
  while (1) {
    printf("Last element of the array read: %d\n", array[i]);
    sleep(5);
    i++;
    if (i == SIZE) {
      break;
    }
  }
}

int main() {
  pid_t pid;
  int i, status;

  // Parent process ID
  printf("Parent Process ID: %d\n", getpid());

  // Create a shared memory
  shrd_mem_id = shmget(IPC_PRIVATE, SIZE * sizeof(int), 0777 | IPC_CREAT);
  int *array = (int *) shmat(shrd_mem_id, 0, 0);
  printf("%d",&*array);

  // Create writer process
  pid = fork();
  if (pid == 0) {
    printf("Writer Process ID: %d\n", getpid());
    writerProcess(array);
    exit(0);
  }

  // Create five reader processes
  for (i = 0; i < 5; i++) {
    pid = fork();
    if (pid == 0) {
      printf("Reader Process ID %d: %d\n", i + 1, getpid());
      readerProcess(array);
      exit(0);
    }
  }

  // Parent process wait for all processes
  for (i = 0; i < 6; i++) {
    wait(&status);
  }

  // Detach and remove the shared memory
  shmdt(array);
  shmctl(shrd_mem_id, IPC_RMID, NULL);

  return 0;
}