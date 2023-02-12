#include <stdio.h>
#include <stdlib.h>


void printMatrix(int** A,int N){
	int i,j;
	printf("\nYour matrix\n-------------\n");
    for (i=0; i < N; i++){
    	int *R = A[i];
    	for(j=0; j<N; j++){
    		printf("%d ",R[j]);
		}
		printf("\n");
	}
}

void rotateRight(int** A, int N,int row){
	int i, tmp;
	int* R = A[row];
	tmp = R[N - 1]; //last element goes to head

	for(i=N-1; i>0; i--){
		R[i] = R[i-1];
	}
	R[0] = tmp;
}

int check(int** A, int N,int row){
	int i,j;
	int* R = A[row];
	int* R2;
	j = 0;
	for(i = row-1; i>=0; i--){
		R2 = A[i]; //the row which we are comparing currently
		//we check every number at the same column. Whenever we encounter same number we return 0 as a meaning of no check
		for(j=0 ; j < N; j++) {
			if (R[j] == R2[j])
			    return 0;
		}
	}
	return 1; // 1 means check
}


int backtrack(int** A, int N, int row, int mode){	    
	int result;	
	int* R = A[row];
	int i = 0;
	
	if (N == row) //it means we alredy checked all rows and there is no problem
		return 1;
	//we can rotate at most N times and if there is no check still, there is no solution
	for(i; i<N; i++){
		rotateRight(A,N,row);
		if(mode == 2){
			printMatrix(A,N);
		}
		if (check(A, N, row)) {
			result = backtrack(A,N,row+1,mode); //if check is true, we can call function with next row
		
			if (result == 1)
				return 1;
		}
	}
	return 0;
}


int main(){
	system("color 4F");
    int N, **A, i,j,pick;
    int res;
	printf("\tBACKTRACK PROBLEM\n");
	printf("How many colour do you have?(2<n<9) ");
    scanf("%d", &N);
    A = (int**) malloc(N * sizeof(int*));
    if(A == NULL){
    	printf("Allocation error!");
    	return;
	}

	printf("Enter your colours number side by side with spaces.\nYour colours are starting 0 and goes to %d\n",N-1);
    for (i=0; i < N; i++){
    	A[i] = (int*) malloc(N * sizeof(int));
    	printf("Row %d: ",i+1);
    	for(j=0; j<N; j++){
    		scanf("%d", &A[i][j]);
		}
	}
    
    printMatrix(A,N);
    
    printf("1->Normal Mode\n2->Detailed mode\nYour choice: ");
    scanf("%d",&pick);
    if(pick == 1 || pick == 2){
    	res = backtrack(A,N,1,pick);
	}
	else{
		printf("Unvalid choice!\n");
		return;
	}

    if(res == 0){
    	printf("\nThere is no solution!\n");
	}
	else{
		printf("\nSolved!\n");
		printMatrix(A,N);
	}
    
	for (i=0; i < N; i++){
		free(A[i]);
	}
    free(A);
    return 0;
}
