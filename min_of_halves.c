#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char* argv[]){

    if(argc < 2){
        printf("Enter atleast 1 integer.!\n");
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);
    int arr[n];
    printf("Enter elements of an array: ");
    for(int i = 0 ; i<n; i++){
        scanf("%d", &arr[i]);
    }

    int half_1[n/2];
    int half_2[n/2];

    for(int i = 0 ; i<n/2; i++){
        half_1[i] = arr[i];
        half_2[i] = arr[i + n/2];
    } 

    int p1[2],p2[2],p3[2],p4[2];
    pipe(p1);
    pipe(p2);
    pipe(p3);
    pipe(p4);
    if(pipe(p1) == -1 || pipe(p2) == -1 || pipe(p3) == -1 || pipe(p4) == -1){
        printf("Error in Pipe creation.!\n");
        exit(EXIT_FAILURE);
    }

    int id1 = fork();
    if(id1 == -1){
        printf("Error in fork creation.!\n");
        exit(EXIT_FAILURE);
    }

    if(id1 == 0){
        //Child 1
        close(p3[0]); close(p3[1]);
        close(p4[0]); close(p4[1]);
        close(p1[1]);
        close(p2[0]);
        
        read(p1[0], &half_1, sizeof(half_1));

        int min1 = half_1[0];
        for(int i = 1; i<n/2; i++){
            if(min1 > half_1[i]){
                min1 = half_1[i];
            }
        }

        write(p2[1], &min1, sizeof(int));
        close(p1[0]);
        close(p2[1]);

        printf("Child 1 process completed.!\n");
    }else{
        int id2 = fork();
        if(id1 == -1){
            printf("Error in fork creation.!\n");
            exit(EXIT_FAILURE);
        }
        if(id2==0){
            //Child 2
            close(p1[0]); close(p1[1]);
            close(p2[0]); close(p2[1]);
            close(p3[1]);
            close(p4[0]);

            read(p3[0], &half_2, sizeof(half_2));

            int min2 = half_2[0];
            for(int i = 1; i<n/2; i++){
                if(min2 > half_2[i]){
                    min2 = half_2[i];
                }
            }

            write(p4[1], &min2, sizeof(int));
            close(p3[0]);
            close(p4[1]);

            printf("Child 2 process completed.!\n");
        }else{
            //Parent
            close(p1[0]); close(p1[1]);
            close(p2[1]);
            close(p3[0]); close(p3[1]);
            close(p4[1]);

            int min1, min2;
            read(p2[0], &min1, sizeof(int));
            read(p4[0], &min2, sizeof(int));

            close(p2[0]);
            close(p4[0]);

            waitpid(id1, NULL);
            waitpid(id2, NULL);

            printf("First Half Minimum: %d\n", min1);
            printf("Second Half Minimum: %d\n", min2);
            printf("Parent process completed.!\n");
        }
    }
    return 0;
}