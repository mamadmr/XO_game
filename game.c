#include<stdio.h>
#include<string.h>

#define map_size 6 // size of the map is map_size*map_size
#define MX_user 10 // maximum number of users
#define MX_maps 10 // maximum number of maps
#define MX_name 20 // maximum lengh of username

int map_count;                          // number of maps exist
int user_count;                         // number of users exist
int score_board[MX_user][MX_user];   // each user has row and colum 

// each map made of map_size*map_size Cells
struct Cell{
    int x,y;
    int status; // {0: empty, 1: X, 2: O}
};

// map is just a 2D array of Cells
struct Map{
    struct Cell map[map_size][map_size];
    int user1, user2;
    int status; // {0: not finished yet, 1: finished}
}maps[MX_maps];

// there are different users in the game, they can play with each other
struct User{
    char username[MX_name];
    struct Cell (*f)(struct Map);
}users[MX_user];

void StartGame(int game_map);                       // the Main game happens here after users pass the menus
int check(int game_map);
int check_cell(int game_map, int x, int y, int status);
int check_full(int game_map);
void print_map(struct Map inp);                                      
struct Cell ComputerPlayer(struct Map inp);         // computer choose a Cell to continue the game 
struct Cell PlayerChoose(struct Map inp);           // ask user to choose a Cell to conitnue the game
void AddUser();                                     // ask and add a new user to users
int ChoosePlayer();
void OnePlayer();
void TwoPlayer();
void NewPlayMenu();
void MainMenu();
void init();

int main(){    
    init();   
    MainMenu();
    return 0;
}

int check_cell(int game_map, int x, int y, int status){
    if(x <= 0 || x >= map_size) return 0;
    if(y <= 0 || y >= map_size) return 0;
    if(status == 0) return 0;
    if(maps[game_map].map[x][y].status == status) return 1;
    return 0;
}

int check(int game_map){
    for(int i = 0; i<map_size; i++){
        for(int j = 0; j<map_size; j++){
            int status = maps[game_map].map[i][j].status;
            if(status == 0) continue;
            if(check_cell(game_map, i, j+1, status) && check_cell(game_map, i, j+2, status)) return status;
            if(check_cell(game_map, i+1, j, status) && check_cell(game_map, i+2, j, status)) return status;
            if(check_cell(game_map, i+1, j+1, status) && check_cell(game_map, i+2, j+2, status)) return status;
        }
    }
    return 0;   
}

int check_full(int game_map){
    for(int i = 0; i<map_size;i++){
        for(int j = 0; j<map_size; j++){
            if(maps[game_map].status == 0) return 0;
        }
    }
    return 1;
}

// The main game happes here : 
void StartGame(int game_map){
    printf("/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\n");
    while(1){
        printf("----------------------------------------\n");
        printf("first player turn\n");
        struct Cell choic1 = users[maps[game_map].user1].f(maps[game_map]);
        while(maps[game_map].map[choic1.x][choic1.y].status != 0){
            printf("choose a valid cell\n");
            choic1 = users[maps[game_map].user1].f(maps[game_map]);
        }
        maps[game_map].map[choic1.x][choic1.y].status = 1;
        
        // check
        int status = check(game_map);
        if(status){
            maps[game_map].status = 1;
            if(status == 1) {
                score_board[maps[game_map].user1][maps[game_map].user2] += 1;
                printf("%s won\n", users[maps[game_map].user1].username);
            }
            else {
                score_board[maps[game_map].user2][maps[game_map].user1] += 1;
                printf("%s won\n", users[maps[game_map].user2].username);
            }
            print_map(maps[game_map]);
            break;
        }
        if(check_full(game_map)){
            maps[game_map].status = 1;
            printf("game finished, no one won\n");
            break;
        }


        printf("second player turn\n");
        struct Cell choic2 = users[maps[game_map].user2].f(maps[game_map]);
        while(maps[game_map].map[choic2.x][choic2.y].status != 0){
            printf("choose a valid cell\n");
            choic2 = users[maps[game_map].user2].f(maps[game_map]);
        }
        maps[game_map].map[choic2.x][choic2.y].status = 2;
        // check
        status = check(game_map);
        if(status){
            maps[game_map].status = 1;
            if(status == 1) {
                score_board[maps[game_map].user1][maps[game_map].user2] += 1;
                printf("%s won\n", users[maps[game_map].user1].username);
            }
            else {
                score_board[maps[game_map].user2][maps[game_map].user1] += 1;
                printf("%s won\n", users[maps[game_map].user2].username);
            }
            print_map(maps[game_map]);
            break;
        }
        if(check_full(game_map)){
            maps[game_map].status = 1;
            printf("game finished, no one won\n");
            break;
        }

        printf("do you want to continue?(yes/no)\n");
        char ans[20]; scanf("%s", ans); 
        if(ans[0] == 'n') break;
    }
}

// users functions:
//      first:
struct Cell ComputerPlayer(struct Map inp){
    for(int i = 0; i<map_size; i++)
        for(int j = 0; j<map_size; j++)
            if(inp.map[i][j].status == 0) return inp.map[i][j];
}

//      second:
struct Cell PlayerChoose(struct Map inp){
    while(1){
        print_map(inp);
        int x, y;
        printf("Enter x: ");
        scanf("%d", &x);
        printf("Enter y: ");
        scanf("%d", &y);
        if(x >= 0 && x<map_size && y>=0 && y<map_size) return inp.map[x][y];
        printf("Enter a valid coordinate\n");
    }
}

// just print map:
void print_map(struct Map inp){
    for(int i = 0; i<map_size; i++){
        for(int j = 0; j<map_size; j++){
            if(inp.map[i][j].status == 0) printf("_");
            else if(inp.map[i][j].status == 1) printf("X");
            else if(inp.map[i][j].status == 2) printf("O");
            printf(" ");
        }
        printf("\n");
    }
}

// if user wants to add a new player to the game this function will run
void AddUser(){
    printf("-----------------------------------------\n");
    printf("Enter the username(shouldn't contain space): ");
    scanf("%s", users[user_count].username);
    users[user_count].f = &PlayerChoose;
    user_count ++;
}

// this function will start working when user choose player for a new game
int ChoosePlayer(){
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


// choose the only player for playing against 
void OnePlayer(){
    printf("-----------------------------------------\n");
    int user1 = 0;
    int user2 = ChoosePlayer();
    maps[map_count].user1 = user1;
    maps[map_count].user2 = user2;
    StartGame(map_count);
    map_count++;
}


// choose two players to play against each other 
void TwoPlayer(){
    int user1 = 0, user2 = 0;
    while(1){
        printf("-----------------------------------------\n");
        printf("Choose first player\n");
        user1 = ChoosePlayer();
        printf("Choose second player\n");
        user2 = ChoosePlayer();
        if(user1 != user2) break;
        printf("choose different player\n");
    }
    maps[map_count].user1 = user1;
    maps[map_count].user2 = user2;
    StartGame(map_count);
    map_count++;
}

// choose the mod of the new game
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
    for(int t = 0; t<MX_maps; t++){
        for(int i = 0; i<map_size; i++){
            for(int j = 0; j<map_size;j++){
                maps[t].map[i][j].x = i;
                maps[t].map[i][j].y = j;
            }
        }
    }
    strcpy(users[0].username, "Computer");
    users[0].f = &ComputerPlayer;
    user_count = 1;    
}
