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
    char username[MX_name];    // save the name of the player
    struct Cell (*f)(struct Map); // save the stategy funtion of player
}users[MX_user];

void StartGame(int game_map);                       // the Main game happens here after users pass the menus
void LastGame();
int check(int game_map);
int check_cell(int game_map, int x, int y, int status);
int check_full(int game_map);
void ScoreBoard();
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
int check_finish(int game_map);

int main(){    
    init();   
    MainMenu();
    return 0;
}

// check if the input cell (x, y) in the game_map has the special status or no
int check_cell(int game_map, int x, int y, int status){
    // check if the input cell exist
    if(x < 0 || x >= map_size) return 0;
    if(y < 0 || y >= map_size) return 0;
    // check if the input cell empty
    if(status == 0) return 0;
    // check if the input cell status is ok
    if(maps[game_map].map[x][y].status == status) return 1;
    // if the status is different 
    return 0;
}

// check for a pattern that shows the winner 
int check(int game_map){
    for(int i = 0; i<map_size; i++){
        for(int j = 0; j<map_size; j++){
            // save the status of the cell
            int status = maps[game_map].map[i][j].status;
            // check if the cell empty
            if(status == 0) continue;
            // check if the cell chosen is a part of the three cells with same status
            if(check_cell(game_map, i, j+1, status) && check_cell(game_map, i, j+2, status)) return status;
            if(check_cell(game_map, i+1, j, status) && check_cell(game_map, i+2, j, status)) return status;
            if(check_cell(game_map, i+1, j+1, status) && check_cell(game_map, i+2, j+2, status)) return status;
            if(check_cell(game_map, i-1, j+1, status) && check_cell(game_map, i-2, j+2, status)) return status;
        }
    }
    return 0;   
}

// check all of the map if there is no empty cell 
int check_full(int game_map){
    for(int i = 0; i<map_size;i++){
        for(int j = 0; j<map_size; j++){
            if(maps[game_map].status == 0) return 0;
        }
    }
    return 1;
}

// a function to check if the game finished 
int check_finish(int game_map){
        int status = check(game_map);
        if(status){
            maps[game_map].status = 1;
            if(status == 1){
                score_board[maps[game_map].user1][maps[game_map].user2] += 1;
                printf("%s won\n", users[maps[game_map].user1].username);
            }
            else {
                score_board[maps[game_map].user2][maps[game_map].user1] += 1;
                printf("%s won\n", users[maps[game_map].user2].username);
            }
            print_map(maps[game_map]);
            return 1;
        }
        if(check_full(game_map)){
            maps[game_map].status = 1;
            printf("game finished, no one won\n");
            return 1;
        }
        // if the map has to continue
        return 0;
        
}

// The main game happes here : 
void StartGame(int game_map){
    printf("/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\n");
    while(1){
        printf("----------------------------------------\n");
        printf("first player turn\n");
        struct Cell choic1;
        // check until the player Enters a Cell that is not X or O 
        do{
            printf("choose a valid cell\n");
            choic1 = users[maps[game_map].user1].f(maps[game_map]);
        }while(maps[game_map].map[choic1.x][choic1.y].status != 0);

        // put the status of the cell as the first player cells 
        maps[game_map].map[choic1.x][choic1.y].status = 1;
        
        // check if the game finished 
        if(check_finish(game_map)) break;

        printf("second player turn\n");
        struct Cell choic2;

        // runs until getting an empty cell
        do{
            printf("choose a valid cell\n");
            choic2 = users[maps[game_map].user2].f(maps[game_map]);
        }while(maps[game_map].map[choic2.x][choic2.y].status != 0);

        // put the status of the cell as the cells of the second player
        maps[game_map].map[choic2.x][choic2.y].status = 2;
        
        // check if the game finished
        if(check_finish(game_map)) break;

        printf("do you want to continue?(yes/no)\n");
        char ans[20]; scanf("%s", ans); 
        if(ans[0] == 'n') break;
    }
}

// users strategy functions functions:
//      first(Computer strategy function):
//          choose the first empty cell
struct Cell ComputerPlayer(struct Map inp){
    for(int i = 0; i<map_size; i++)
        for(int j = 0; j<map_size; j++)
            if(inp.map[i][j].status == 0) return inp.map[i][j];
}

//      second:
struct Cell PlayerChoose(struct Map inp){
    // runs until user Enters a valid coordinate
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

//show the score board for users which played with each other
void ScoreBoard(){
    // print score board each username against the other one
    printf("-----------------------------------------\n");
    for(int i = 0; i<user_count; i++){
        for(int j = i+1; j<user_count; j++){
            // chech if they had any game against each other
            if(score_board[i][j] + score_board[j][i])
                printf("%s: %d %s: %d\n", users[i].username, score_board[i][j], users[j].username, score_board[j][i]);
        }
    }
}

// Enter to an  old game
void LastGame(){
    for(int i = 0; i<map_count; i++){
        if(maps[i].status != 0) continue;
        printf("map number: %d\n", i);
        print_map(maps[i]);
    }
    printf("%d. back\n", map_count);
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);
    if(choice == map_count) return;
    if(choice > map_count || choice < 0){
        printf("Enter a valid input\n");
        return;
    }
    StartGame(choice);
}
void MainMenu(){
    // first menu -> last menu -> exit from 
    while(1)
    {
        printf("-----------------------------------------\n");
        printf("0. score board\n");
        printf("1. new game\n");
        printf("2. last games\n");
        printf("3. exit\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);
        if(choice == 0) ScoreBoard();
        if(choice == 1) NewPlayMenu();
        if(choice == 2) LastGame();
        if(choice == 3) break;
    }
}

// do some preprocesses before game start
void init(){
    // initialize the x, y for each cell in maps
    for(int t = 0; t<MX_maps; t++){ // thers is MX_maps maps at all
        for(int i = 0; i<map_size; i++){ // each map has map_size number of rows
            for(int j = 0; j<map_size;j++){ // each map has map_size number of columns
                // initialize the cell of t-th map with a (i, j) coordinate 
                maps[t].map[i][j].x = i;  
                maps[t].map[i][j].y = j;
            }
        }
    }
    // make a user as computer to play in oneplayer mod    
    strcpy(users[0].username, "Computer"); // give a "Computer" username to this user
    users[0].f = &ComputerPlayer; // give a startegy function for computer
    user_count = 1;  // now we have a user("Computer") so the user count is 1 
}