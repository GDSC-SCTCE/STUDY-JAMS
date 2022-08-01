#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define FRAMES 4

struct Frame{
    int content;
    int arrivalTime;
    int accessTime;
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
                pages[j]->accessTime = time;
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
                pages[j]->arrivalTime =  pages[j]->accessTime = time;
                break;
            }
        }
        if(found) continue;

        // Else, do replacement as per lru
        // Find min access time and corresponding frame
        int min_frame = -1, min_ctime = INT_MAX, min_atime = INT_MAX;
        for(int j=0; j<FRAMES; j++){
            // If accesstime is same, follow fifo
            if(pages[j]->accessTime < min_atime || (pages[j]->accessTime == min_atime && pages[j]->arrivalTime < min_ctime)){
                min_frame = j;
                min_ctime = pages[j]->arrivalTime;
                min_atime = pages[j]->accessTime;
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