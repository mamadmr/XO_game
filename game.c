#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define MX 6
#define MX_user 10
#define MX_maps 10

int map_count;
int user_count;
int score_board[MX_user][MX_user];
bool finish_map[MX_maps];

struct Cell{
    int x,y;
    int status; // {0: empty, 1: X, 2: O}
};

struct User{
    char username[30];
    struct Cell (*f)(struct Cell[MX][MX]);
}users[MX_user];

struct Map{
    struct Cell map[MX][MX];
}maps[MX_maps];


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

void AddUser(){
    printf("-----------------------------------------\n");
    printf("Enter the username: ");
    scanf("%s", users[user_count].username);
    user_count ++;
}

int choose_player(){
    while(1){
        printf("-----------------------------------------\n");
        printf("0. make user\n");
        for(int i = 1; i<user_count; i++){
            printf("%d. %s\n", i, users[i].username);
        }
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);
        if(choice == 0) AddUser();
        if(choice < user_count && choice > 0) return choice;
        printf("\n\n**********Enter a valid choice************\n\n");
    }
}

void OnePlayer(){
    int user2 = 0;
    int user2 = choose_player();
    map_count++;
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
        if(choice == 1) OnePlayer();
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

void init(){
    strcpy(users[0].username, "Computer");
    user_count = 1;    
}

// struct Cell test(struct Cell inp[MX][MX]){
//     return inp[0][0];
// }

// struct Map game_map;

int main(){    
    init();   
    MainMenu();
    // struct User user1;
    // user1.f = &test;    
    // printf("%d", user1.f(game_map.map).x);
    return 0;
}
