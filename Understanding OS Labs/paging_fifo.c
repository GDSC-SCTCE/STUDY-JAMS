#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define FRAMES 4

struct Frame{
    int content;
    int arrivalTime;
};

void displayFrames(struct Frame **pages){
    printf("| ");
    for(int i=0; i<FRAMES; i++){
        if(pages[i]->content == -1)
            printf("  | ");
        else
            printf("%d | ", pages[i]->content);
    }
    putchar('\n');
}

int lru(struct Frame **pages, int *refStr, int n){
    int freepages = FRAMES;
    int time = -1, faults = 0;
    // Traverse Reference String
    for(int i=0; i<n; i++){
        time++;
        displayFrames(pages);
        // Check if page already exist
        int found = 0;
        for(int j=0; j<FRAMES; j++){
            if(pages[j]->content == refStr[i]){
                found = 1;
                break;
            }
        }
        if(found) continue; else faults++;

        // Check if gap exist
        found = 0;
        for(int j=0; j<FRAMES; j++){
            if(pages[j]->content == -1){
                found = 1;
                pages[j]->content = refStr[i];
                pages[j]->arrivalTime = time;
                break;
            }
        }
        if(found) continue;

        // Else, do replacement as per fifo
        // Find min arrival time and corresponding frame
        int min_frame = -1, min_time = INT_MAX;
        for(int j=0; j<FRAMES; j++){
            if(pages[j]->arrivalTime < min_time){
                min_frame = j;
                min_time = pages[j]->arrivalTime;
            }
        }
        // Swap current page with victim frame
        pages[min_frame]->content = refStr[i];
        pages[min_frame]->arrivalTime = time;
    }
    return faults;
}

void main(){
    struct Frame **pages = malloc(sizeof(pages)*FRAMES);
    for(int i=0; i<FRAMES; i++){
        pages[i] = malloc(sizeof(struct Frame));
        pages[i]->content = -1;
        pages[i]->arrivalTime = -1;
    }

    int n;
    printf("Length of reference string: ");
    scanf("%d", &n);
    int *refStr = malloc(sizeof(int)*n);

    printf("ReferenceString: ");
    for(int i=0; i<n; i++)
        scanf("%d", &refStr[i]);

    // Do algorithms
    int faults = lru(pages, refStr, n);
    printf("Page Faults: %d\n", faults);
}