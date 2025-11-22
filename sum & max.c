#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>

int main(int argc, char*argv[]){

    if(argc<2){
        printf("Please enter atleast 1 element.!\n");
        exit(EXIT_FAILURE);
    }

    int n = argc - 1;
    int arr[n];
    for(int i = 0; i<n; i++){
        arr[i] = atoi(argv[i+1]);
    }

    int p1[2], p2[2], p3[2], p4[2];
    if(pipe(p1) == -1 || pipe(p2) == -1 || pipe(p3) == -1 || pipe(p4) == -1){
        printf("Error in pipe creation.!\n");
        exit(EXIT_FAILURE);
    }

    int id1 = fork();
    if(id1 == -1){
        printf("Error in fork creation.!\n");
        exit(EXIT_FAILURE);
    }

    if(id1 == 0){
        //Child 1
        close(p1[1]);
        close(p2[0]);
        close(p3[0]); close(p3[1]);
        close(p4[0]); close(p4[1]);

        read(p1[0], &arr, sizeof(arr));

        int sum = 0;
        for(int i = 0; i<n; i++){
            sum += arr[i];
        }

        write(p2[1], &sum, sizeof(int));
        close(p1[0]);
        close(p2[1]);
    }else{
        int id2 = fork();
        if(id2 == -1){
            printf("Error in fork creation.!\n");
            exit(EXIT_FAILURE);
        }
        
        if(id2 == 0){
            //Child 2
            close(p1[0]); close(p1[1]);
            close(p2[0]); close(p2[1]);
            close(p3[1]);
            close(p4[0]);

            read(p3[0], &arr, sizeof(arr));

            int max = 999;
            for(int i = 0; i<n; i++){
                if(max < arr[i]){
                    max = arr[i];
                }
            }

            write(p4[1], &max, sizeof(int));
            close(p3[0]);
            close(p4[1]);
        }else{
            //Parent
            close(p1[0]); close(p1[1]);
            close(p2[1]);
            close(p3[0]); close(p3[1]);
            close(p4[1]); 

            int sum, max;
            read(p2[0], &sum, sizeof(int));
            read(p4[0], &max, sizeof(int));

            close(p2[0]);
            close(p4[0]);

            printf("Sum of array elements: %d\n", sum);
            printf("Maximum of an Array: %d\n", max);

            waitpid(id1, 0);
            waitpid(id2, 0);
        }
    }

    return 0;
}