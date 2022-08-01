#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>

void *shmalloc(size_t size){
    int prot = PROT_READ | PROT_WRITE;
    int flags = MAP_SHARED | MAP_ANON;
    return mmap(NULL, size, prot, flags, -1, 0);
}

void main(){
    char *shm = shmalloc(256);
    char samp[] = "This is in shared mem!!";
    strcpy(shm, samp);
    printf("Shared Mem has: %s\n", shm);

    munmap(shm, 256);