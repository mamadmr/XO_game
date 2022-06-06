#include<stdio.h>

#define MX 6

struct Cell{
    int x,y;
    int status; // {0: empty, 1: X, 2: O}
};

struct Cell game_map[MX][MX];


void print_map(struct Cell inp[MX][MX]){
    for(int i = 0; i<MX; i++){
        for(int j = 0; j<MX; j++){
            if(inp[i][j].status == 0) printf("_");
            else if(inp[i][j].status == 1) printf("X");
            else if(inp[i][j].status == 2) printf("O");
            printf(" ");
        }
        printf("\n");
    }
}


int main(){
    return 0;
}
