#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char *argv[]){

    if(argc<2){
        printf("Please enter atleast 1 value.!\n");
        return 1;
    }

    int n = argc -1;
    int arr[n];

    for(int i = 0 ; i<n; i++){
        arr[i] = atoi(argv[i+1]);
    }

    int p1[2], p2[2];
    pipe(p1);
    pipe(p2);

    int id = fork();
    if(id == -1){
        printf("Error in fork creation!\n");
        exit(EXIT_FAILURE);
    }

    if(id == 0){
        //Child Process
        close(p1[1]);
        close(p2[0]);
        
        read(p1[0], &arr, sizeof(arr));

        for(int i = 0 ; i<n; i++){
            for(int j = 0; j<n-i-1; j++){
                if(arr[j] > arr[j+1]){
                    int temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
            }
        }

        write(p2[1], &arr, sizeof(arr));

        close(p1[0]);
        close(p2[1]);
        printf("Child Process Completed!\n");

    }else{
        //Parent Process
        close(p1[0]); close(p1[1]);
        close(p2[1]);

        read(p2[0], &arr, sizeof(arr));

        printf("Sorted Array: ");
        for(int i = 0; i<n; i++){
            printf("%d ", arr[i]);
        }


        close(p2[0]);
        wait();
        printf("Parent Process Completed!\n");
    }

    

    return 0;
}
