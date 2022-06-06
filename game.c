#include<stdio.h>

#define MX 6

struct Cell{
    int x,y;
    int status; // {0: empty, 1: X, 2: O}
};

struct User{
    char username[30];
    int score;
    struct Cell (*f)(struct Cell[MX][MX]);
};

struct Map{
    struct Cell map[MX][MX];
};

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

void NewPlayMenu(){
    while (1)
    {
        printf("-----------------------------------------\n");
        printf("1. one player\n");
        printf("2. two players\n");
        printf("3. back\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);
        if(choice == 3) return;
    }
    
}

void MainMenu(){
    while(1)
    {
        printf("-----------------------------------------\n");
        printf("1. new game\n");
        printf("2. last games\n");
        printf("3. exit\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);
        if(choice == 1) NewPlayMenu();
        if(choice == 3) break;
        
    }
    
}


struct Cell test(struct Cell inp[MX][MX]){
    return inp[0][0];
}

struct Map game_map;

int main(){       
    MainMenu();
    // struct User user1;
    // user1.f = &test;    
    // printf("%d", user1.f(game_map.map).x);
    return 0;
}
