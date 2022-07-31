#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <string.h>

#define SEGSIZE 1024

void main(){
    // Allocate Shared Segment
    int segid = shmget(IPC_PRIVATE, 1024, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

    // Attach(Mount) Shared Segment
    char *mem = shmat(segid, NULL, 0);
    
    char sample[] = "This is shared segment!!";
    strcpy(mem, sample);

    printf("Shared Mem has: %s\n", mem);

    // Detach(Unmount) Shared Segment
    shmdt(mem);

    // Deallocate shared memory segment
    shmctl(segid, IPC_RMID, 0);
}