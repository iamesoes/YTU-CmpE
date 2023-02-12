#include <stdio.h>
#include <stdlib.h>
#define INF 9999999

typedef struct result {
    int value;
    int start;
    int end;
} result;


result bruteForce(int *array, int n) {
	int i,j;
    result answer = {-INF, 0, 0};

	for(i=0; i<n; i++){
	
        result sub = {0, i, 0};

    	for(j = i; j < n; j++){
            sub.end = j;
    		sub.value += array[j];
    		
    		if(sub.value > answer.value){
    			answer = sub;
    		
			}
    			
		}
	
	}

    return answer;
}

result dq(int *array, int start, int end) {
    int mid, i;
    int left_sum = 0, right_sum = 0;
    int left_max = -INF, right_max = -INF;

    if(start == end){ 
        result answer = {array[start], start, end};
        return answer;
    } 

    mid = (start + end) / 2;

    result left_answer = dq(array, start, start < mid ? mid - 1 : start);
    result right_answer = dq(array, mid+1, end);
    result mid_answer = {array[mid], mid, mid};

    for(i = mid-1; start <= i; i--){
        left_sum += array[i];
        if(left_sum > 0 && left_max < left_sum){
            left_max = left_sum;
            mid_answer.start = i;
        }
    }

    for(i = mid+1; i <= end; i++){
        right_sum += array[i];
        if(right_sum > 0 && right_max < right_sum){
            right_max = right_sum;
            mid_answer.end = i;
        }
    }

    if(0 < left_max)
        mid_answer.value += left_max;

    if(0 < right_max)
        mid_answer.value += right_max;

    if(left_answer.value < right_answer.value && mid_answer.value < right_answer.value)
        return right_answer;

    else if(mid_answer.value < left_answer.value)
        return left_answer;

    return mid_answer;
}

int main(){
    int N, *A, i;
	printf("\tFINDING MAX SUBARRAY IN A ARRAY\n");
	printf("Your array's size: ");
	
    scanf("%d", &N);
    A = (int*) malloc(N * sizeof(int));

	printf("Enter your array's number side by side with spaces.\n");
    for (i=0; i < N; i++)
        scanf("%d", A + i);

    result answer = dq(A, 0, N-1);
    printf("%d %d %d \n", answer.start, answer.end, answer.value);
    answer = bruteForce(A, N);
    printf("%d %d %d \n", answer.start, answer.end, answer.value);

    free(A);
    return 0;
}
