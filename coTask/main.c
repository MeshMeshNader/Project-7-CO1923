#include <stdio.h>
#include <stdlib.h>
#define SIZE 20

void storeRequest(char request);
void deleteRequestWithSpecificPriority(int *priority);
void processAllRequestsWithSpecificPriority(int *priority , int del);
void emptyAllLists();
void printList(char arr[] , int *size , int del);
void quicksort(char number[],int first,int last);
void requestSearch(char request , int priority);
int binarySearch(char requests[], int l, int r, char x);

char critical[SIZE] , high[SIZE] , medium[SIZE] , low[SIZE] ;
int  criticalSize , highSize , mediumSize , lowSize;


int main()
{

    int numberOfRequests = 0 , priority = 0 , task = 0;
    char request;

    while( task != -1){
        printf("\n0- Enter Requests\n1- Search about Request\n2- Search about priority \n3- Search about Request with Priority \n4- Delete All requests with specific priority \n5- Process All requests with specific priority \n6- Empty All Lists\n(-1) To Exit\n\nYour Choice:   ");
        scanf("\n%d" , &task);
        switch( task ){

            case 0 :
                    printf("Enter Number of requests that you have (maximum 80 requests):  ");
                    scanf("%d" , &numberOfRequests);
                    for(int i = 0 ; i<numberOfRequests ; i++){
                        printf("Enter your request:  ");
                        scanf("\n%c" , &request);
                        storeRequest(request);
                    }
                    if(criticalSize>0)
                        quicksort(critical, 0 ,criticalSize-1);
                    if (highSize>0)
                        quicksort(high, 0 ,highSize-1);
                    if (mediumSize>0)
                        quicksort(medium, 0 ,mediumSize-1);
                    if (lowSize>0)
                        quicksort(low, 0 ,lowSize-1);
                break;
            case 1:
                printf("Enter your request to Search:  ");
                scanf("\n%c" , &request);
                requestSearch(request , 0);
                break;
            case 2:
                printf("Enter your priority number to Search:  \n1-Critical\n2-High\n3-Medium\n4-Low\n");
                scanf("%d" , &priority);
                if(priority>0 && priority<5)
                    processAllRequestsWithSpecificPriority(&priority , 0);
                break;
            case 3:
                printf("Enter your request to Search:  ");
                scanf("\n%c" , &request);
                printf("Enter your priority number to Search:  \n1-Critical\n2-High\n3-Medium\n4-Low\n");
                scanf("%d" , &priority);
                if(priority>0 && priority<5)
                    requestSearch(request , priority);
                else
                    requestSearch(request , 0);
                break;
            case 4:
                printf("Enter the priority which you want to delete their requests:  ");
                scanf("%d" , &priority);
                deleteRequestWithSpecificPriority(&priority);
                break;
            case 5:
                printf("Enter the priority that you want to process their requests:  ");
                scanf("%d" , &priority);
                processAllRequestsWithSpecificPriority(&priority , 1);
                break;
            case 6:
                emptyAllLists();
                break;
            case -1:
                break;
            default :
                printf("You entered an invalid number... try again:  ");
                scanf("%d" , &task);
        }
    }

    return 0;
}



// Function that store requests in there lists
void storeRequest(char request){
    if (criticalSize < SIZE)
        critical[criticalSize++] = request;
    else if (highSize<SIZE)
        high[highSize++] = request;
    else if (mediumSize<SIZE)
        medium[mediumSize++] = request;
    else if (lowSize<SIZE)
        low[lowSize++]=request;

}

// Function that used in case 6 to empty all lists
void emptyAllLists(){
    criticalSize = 0;
    highSize = 0;
    mediumSize = 0 ;
    lowSize = 0 ;
    printf("All lists are empty now. \n");
}

// Function that used in case 4 delete request with specific priority
void deleteRequestWithSpecificPriority(int *priority){
    switch(*priority){
        case 1 :
            if(criticalSize == 0)
                printf("The list is already empty\n");
            else
            {
            criticalSize = 0;
            printf("List deleted successfully\n");
            }
            break;
        case 2 :
            if(highSize == 0)
                printf("The list is already empty\n");
            else
            {
            highSize = 0;
            printf("List deleted successfully\n");
            }
            break;
        case 3 :
            if(mediumSize == 0)
                printf("The list is already empty\n");
            else
            {
            mediumSize = 0;
            printf("List deleted successfully\n");
            }
            break;
        case 4 :
            if(lowSize == 0)
                printf("The list is already empty\n");
            else
            {
            lowSize = 0;
            printf("List deleted successfully\n");
            }            break;
        default :
            printf("Enter correct number of the list ");
            scanf("%d" , priority);
            deleteRequestWithSpecificPriority(priority);
            break;
    }
}

// function that process all requests used in case 5
void processAllRequestsWithSpecificPriority(int *priority , int del){
     switch(*priority){
        case 1 :
            if(criticalSize == 0)
                printf("\nThere's no requests here the list is empty\n");
            else
                printList(critical , &criticalSize , del);
            break;
        case 2 :
            if(highSize == 0)
                printf("\nThere's no requests here the list is empty\n");
            else
                printList(high , &highSize , del);
            break;
        case 3 :
            if(mediumSize == 0)
                printf("\nThere's no requests here the list is empty\n");
            else
                printList(medium , &mediumSize , del);
            break;
        case 4 :
            if(lowSize == 0)
                printf("\nThere's no requests here the list is empty\n");
            else
                printList(low , &lowSize , del);
            break;
        default :
                printf("Enter correct number of the list : ");
                scanf("%d" , priority);
                processAllRequestsWithSpecificPriority(priority , del);
            break;
    }
}

// function that prints the list and check if we delete elements or not (process & search about priority)
void printList(char requests[] , int *size , int del){
    printf("-----------------------------------------------\n");
    for(int i = 0 ; i <*size ; i++)
        printf("%c \n" , requests[i]);
    if (del==1)
        *size = 0;
    printf("-----------------------------------------------\n");
}

// Function that sort the list to make Binary search (Bonus)
void quicksort(char requests[],int first,int last){

int i, j, pivot, temp;
    if( first < last){
        pivot=first; // initializing the pivot
        i = first; // first index in array or subarray
        j = last; // last index in array or subarray
    while(i<j){
        while(requests[i] <= requests[pivot]&&i<last) // while the element is smaller than or equal the pivot and i not reach the end of array move i to the next element
            i++;
        while(requests[j]> requests[pivot]) // while the element is bigger than the pivot move it backward
            j--;
    //swap
    if(i<j){
        temp=requests[i];
        requests[i]=requests[j];
        requests[j]=temp;
        }
    }
    //swap
    temp=requests[pivot];
    requests[pivot]=requests[j];
    requests[j]=temp;
    //recursion in left and right subarray
    quicksort(requests,first,j-1);  // left subarray
    quicksort(requests,j+1 ,last); // Right subarray
    }
}

// Function that Request search to request binary search in all lists
void requestSearch(char request , int priority){
    int criticalPos , highPos , mediumPos , lowPos;

    criticalPos = binarySearch(critical , 0 , criticalSize-1 , request);
    highPos = binarySearch(high , 0 , highSize-1 , request);
    mediumPos = binarySearch(medium , 0 , mediumSize-1 , request);
    lowPos = binarySearch(low , 0 , lowSize-1 , request);

    if(priority==1 || priority==0)
    if(criticalPos > -1)
        printf("\n\nThe Request Founded in Critical List at Position : %d\n" , criticalPos);
    else
        printf("\n\nThe Request Not found in Critical List\n");

    if(priority==2 || priority==0)
    if(highPos > -1)
            printf("The Request Founded in High List at Position : %d\n" , highPos);
    else
        printf("The Request Not found in High List\n");

    if(priority==3 || priority==0)
    if(mediumPos > -1)
            printf("The Request Founded in Medium List at Position : %d\n" , mediumPos);
    else
        printf("The Request Not found in Medium List\n");

    if(priority==4 || priority==0)
    if(lowPos > -1)
            printf("The Request Founded in Low List at Position : %d\n\n\n" , lowPos);
    else
        printf("The Request Not found in Low List\n\n\n");

}

// Function that Search in specific element with Binary seaech algorithim
int binarySearch(char requests[], int left, int right, char request) {

  while (left <= right)
  {
    int m = left + (right - left )/2;

    // Check if request is present at mid
    if (requests[m] == request)
        return m;

    // If request is greater ignore left half
    if (requests[m] < request)
        left = m + 1;

    // If request is smaller, ignore right half
    else
         right = m - 1;
  }
  // if we reach here, then request was not present
  return -1;
}
