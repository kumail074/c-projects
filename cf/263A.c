#include <stdio.h>
#include <stdlib.h>

int main(){
    int matrix[5][5];
    int row,col,steps=0,temp;
    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++){
            scanf("%d",&matrix[i][j]);
            if(matrix[i][j] != 0) {
                row = i; 
                col = j; }
        }

    if(matrix[2][2] != 0)
        steps=0;
    while(matrix[2][2] != 0){
        if(row>3){
            temp=matrix[row-1][col];
            matrix[row-1][col]=matrix[row][col];
            matrix[row][col]=temp; 
            steps++;
            row=row-1;
            }
        if(row<1){
            temp=matrix[row+1][col];
            matrix[row+1][col]=matrix[row][col];
            matrix[row][col]=temp; 
            steps++;
            row=row+1;
        }
        if(col>3){
            temp=matrix[row][col-1];
            matrix[row][col-1]=matrix[row][col];
            matrix[row][col]=temp;
            steps++;
            col=col-1;
        }
        if(col<1){
            temp=matrix[row][col+1];
            matrix[row][col+1]=matrix[row][col];
            matrix[row][col]=temp;
            steps++;
            col=col+1; 
        }
        
                  

    }
    return 0;
}
