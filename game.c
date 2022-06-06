#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define MX 6
#define MX_user 10
#define MX_maps 10
#define MX_name 20

int map_count;
int user_count;
int score_board[MX_user][MX_user];
bool finish_map[MX_maps];

struct Cell{
    int x,y;
    int status; // {0: empty, 1: X, 2: O}
};

struct User{
    char username[MX_name];
    struct Cell (*f)(struct Cell[MX][MX]);
}users[MX_user];

struct Map{
    struct Cell map[MX][MX];
}maps[MX_maps];

void print_map(struct Cell inp[MX][MX]);


void StartGame(int user1, int user2, int game_map){
    printf("is playing ...\n");
}

struct Cell ComputerPlayer(struct Cell inp[MX][MX]){
    for(int i = 0; i<MX; i++)
        for(int j = 0; j<MX; j++)
            if(inp[i][j].status == 0) return inp[i][j];
}

struct Cell PlayerChoose(struct Cell inp[MX][MX]){
    while(1){
        print_map(inp);
        int x, y;
        printf("Enter x: ");
        scanf("%d", &x);
        printf("Enter x: ");
        scanf("%d", &x);
        if(x >= 0 && x<MX && y>=0 && y<MX) return inp[x][y];
    }
}

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
    printf("Enter the username(shouldn't contain space): ");
    scanf("%s", users[user_count].username);
    users[user_count].f = &PlayerChoose;
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
        else if(choice < user_count && choice > 0) return choice;
        else printf("\n\n**********Enter a valid choice************\n\n");
    }
}

void OnePlayer(){
    int user1 = 0;
    int user2 = choose_player();
    StartGame(user1, user2, map_count);
    map_count++;
}

void TwoPlayer(){
    int user1 = 0, user2 = 0;
    while(1){
        printf("Choose first player\n");
        user1 = choose_player();
        printf("Choose second player\n");
        user2 = choose_player();
        if(user1 != user2) break;
        printf("choose different player\n");
    }
    StartGame(user1, user2, map_count);
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
        if(choice == 2) TwoPlayer();
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
    users[0].f = &ComputerPlayer;
    user_count = 1;    
}


int main(){    
    init();   
    MainMenu();
    return 0;
}
