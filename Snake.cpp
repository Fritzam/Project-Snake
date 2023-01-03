#include <iostream>
#include <ncurses.h>
#include <vector>
#include <random>

using namespace std;

struct Segment {
        char symbol;
        int position_y;
        int position_x;
    };

void Display(char mapa[][16]) {
    //Displays every cell in an array, character after character.
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            mvaddch(i, j, mapa[i][j]);
        }
    }
}

void GenerateGameMap(char mapa[][16]) {
    //Fills outermost cells with border symbols, and rest with empty chars.
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            if (i == 0 || i == 15) {
                mapa[i][j] = '=';
            }
            else if (j == 0 || j == 15) {
                mapa[i][j] = '|';
            }
            else {
                mapa[i][j] = ' ';
            }
        }
    }
}

void GenerateSnake(char mapa[][16], vector <Segment> Snake) {
    //Generating Snake on the map.
    for (int i = 0; i < Snake.size(); i++) {
        mapa[Snake[i].position_y][Snake[i].position_x] = Snake[i].symbol;
    }
}

void CreateInitialFruit(char mapa[][16]) {
    mapa[2][7] = '*';
}

void CreateFruit(char mapa[][16]) {
    //Declaring coordinates of a single fruit.
    int position_y;
    int position_x;

    //Declaring engines.
    random_device rd;
    mt19937 gen(rd());

    //Setting random range.
    uniform_int_distribution<> dist(1, 14);

    //Setting base value's.
    position_y = dist(gen);
    position_x = dist(gen);

    //While loop that generates another set of coordinates if base one would create a fruit in Snake's segment's place.
    while (mapa[position_y][position_x] == '@' || mapa[position_y][position_x] == '#') {
        position_y = dist(gen);
        position_x = dist(gen);
    }

    //Appending to the map.
    mapa[position_y][position_x] = '*';
}


bool MoveUp (char mapa[][16], bool &alive, vector <Segment> &Snake, int &score) {

    //Flag controlling whether the fruit has been eaten or not.
    bool FruitEaten = false;

    //If current execution of the function would put Snake in the wall or another Snake segment, return the game controlling flag as false.
    if (mapa[Snake[0].position_y - 1][Snake[0].position_x] == '=' || mapa[Snake[0].position_y - 1][Snake[0].position_x] == '#') {
        printw("You are dead!");
        return false;
    }

    //If in current execution of the function Snake will eat a fruit, create another one and give +10 points to the player.
    if (mapa[Snake[0].position_y - 1][Snake[0].position_x] == '*') {
        FruitEaten = true;
        score += 10;
        CreateFruit(mapa);
    }

    //Take the current y,x coords and put them into variables.
    int current_y = Snake[0].position_y;
    int current_x = Snake[0].position_x;

    //Since we're moving forward, put a snake's head symbol at y-- position from current.
    mapa[Snake[0].position_y - 1][Snake[0].position_x] = Snake[0].symbol;

    //Change the head's y position to y--;
    Snake[0].position_y--;

    //For each element of the Snake which is not it's head:
    for (int i = 1; i < Snake.size(); i++) {
        //If current Snake segment is not the last one:
        if (i < Snake.size() - 1) {
            //Record the current segment position into temp variables.
            int swap_y = Snake[i].position_y;
            int swap_x = Snake[i].position_x;

            //Change the segment's y and x position to the position of a segment after it.
            Snake[i].position_y = current_y;
            Snake[i].position_x = current_x;

            //Print a segment symbol in an updated position.
            mapa[Snake[i].position_y][Snake[i].position_x] = Snake[i].symbol;

            //Change the current y, x variables to swap, so that next in line segment will change it's position to the position of segment before it.
            current_y = swap_y;
            current_x = swap_x;
         }
        //If current segment is a last one:
        else if (i == Snake.size() - 1) {
            if (FruitEaten == false) {
                //Print an empty sign at it's location.
                mapa[Snake[i].position_y][Snake[i].position_x] = ' ';

                //Change it's position to the position of segment's before it.
                Snake[i].position_y = current_y;
                Snake[i].position_x = current_x;

                //Print it's symbol at an updated location.
                mapa[Snake[i].position_y][Snake[i].position_x] = Snake[i].symbol;
            }
            else if (FruitEaten == true) {
                //Record the current segment position into temp variables.
                int swap_y = Snake[i].position_y;
                int swap_x = Snake[i].position_x;

                //Change the segment's y and x position to the position of a segment after it.
                Snake[i].position_y = current_y;
                Snake[i].position_x = current_x;

                //Print a segment symbol in an updated position.
                mapa[Snake[i].position_y][Snake[i].position_x] = Snake[i].symbol;

                //Set the FruitEaten flag to false to prevent infinite loop.
                FruitEaten = false;

                //Add another segment to Snake's vector.
                Snake.push_back({'#', swap_y, swap_x});

                //Change the current y, x variables to swap, so that next in line segment will change it's position to the position of segment before it.
                current_y = swap_y;
                current_x = swap_x;

                //Set the symbol at an updated position.
                mapa[Snake[i].position_y][Snake[i].position_x] = Snake[i].symbol;
            }
        }

    }

    //If function reaches this point return true to allow game controlling loop to carry on.
    return true;
}

bool MoveLeft (char mapa[][16], bool &alive, vector <Segment> &Snake, int &score) {

    //Variable controlling whether fruit has been eaten or not.
    bool FruitEaten = false;

    //If current execution of the function would put Snake in the wall or another Snake segment, return the game controlling flag as false.
    if (mapa[Snake[0].position_y][Snake[0].position_x - 1] == '|' || mapa[Snake[0].position_y][Snake[0].position_x - 1] == '#') {
        printw("You are dead!");
        return false;
    }

    //If in current execution of the function Snake will eat a fruit, create another one and give +10 points to the player.
    if (mapa[Snake[0].position_y][Snake[0].position_x - 1] == '*') {
        FruitEaten = true;
        score += 10;
        CreateFruit(mapa);
    }

    //Take the current y,x coords and put them into variables.
    int current_y = Snake[0].position_y;
    int current_x = Snake[0].position_x;

    //Since we're moving left, put a snake's head symbol at x-- position from current.
    mapa[Snake[0].position_y][Snake[0].position_x - 1] = Snake[0].symbol;

    //Change the head's x position to x--;
    Snake[0].position_x--;

    //For each element of the Snake which is not it's head:
    for (int i = 1; i < Snake.size(); i++) {
        //If current Snake segment is not the last one:
        if (i < Snake.size() - 1) {
            //Record the current segment position into temp variables.
            int swap_y = Snake[i].position_y;
            int swap_x = Snake[i].position_x;

            //Change the segment's y and x position to the position of a segment after it.
            Snake[i].position_y = current_y;
            Snake[i].position_x = current_x;

            //Print a segment symbol in an updated position.
            mapa[Snake[i].position_y][Snake[i].position_x] = Snake[i].symbol;

            //Change the current y, x variables to swap, so that next in line segment will change it's position to the position of segment before it.
            current_y = swap_y;
            current_x = swap_x;
        }
        //If current segment is a last one:
        else if (i == Snake.size() - 1) {
            if (FruitEaten == false) {
                //Print an empty sign at it's location.
                mapa[Snake[i].position_y][Snake[i].position_x] = ' ';

                //Change it's position to the position of segment's before it.
                Snake[i].position_y = current_y;
                Snake[i].position_x = current_x;

                //Print it's symbol at an updated location.
                mapa[Snake[i].position_y][Snake[i].position_x] = Snake[i].symbol;
            }
            else if (FruitEaten == true) {
                //Record the current segment position into temp variables.
                int swap_y = Snake[i].position_y;
                int swap_x = Snake[i].position_x;

                //Change the segment's y and x position to the position of a segment after it.
                Snake[i].position_y = current_y;
                Snake[i].position_x = current_x;

                //Print a segment symbol in an updated position.
                mapa[Snake[i].position_y][Snake[i].position_x] = Snake[i].symbol;

                //Set the FruitEaten flag to false to prevent infinite loop.
                FruitEaten = false;

                //Add another segment to Snake's vector.
                Snake.push_back({'#', swap_y, swap_x});

                //Change the current y, x variables to swap, so that next in line segment will change it's position to the position of segment before it.
                current_y = swap_y;
                current_x = swap_x;

                //Set the symbol at an updated position.
                mapa[Snake[i].position_y][Snake[i].position_x] = Snake[i].symbol;
            }
        }

    }

    //If function reaches this point return true to allow game controlling loop to carry on.
    return true;
}

bool MoveRight (char mapa[][16], bool &alive, vector <Segment> &Snake, int &score) {

    //Variable controlling whether fruit has been eaten or not.
    bool FruitEaten = false;

    //If current execution of the function would put Snake in the wall or Snake segement, return the game controlling flag as false.
    if (mapa[Snake[0].position_y][Snake[0].position_x + 1] == '|' || mapa[Snake[0].position_y][Snake[0].position_x + 1] == '#') {
        printw("You are dead!");
        return false;
    }

    //If in current execution of the function Snake will eat a fruit, create another one and give +10 points to the player.
    if (mapa[Snake[0].position_y][Snake[0].position_x + 1] == '*') {
        FruitEaten = true;
        score += 10;
        CreateFruit(mapa);
    }

    //Take the current y,x coords and put them into variables.
    int current_y = Snake[0].position_y;
    int current_x = Snake[0].position_x;

    //Since we're moving right, put a snake's head symbol at x++ position from current.
    mapa[Snake[0].position_y][Snake[0].position_x + 1] = Snake[0].symbol;

    //Change the head's y position to x++;
    Snake[0].position_x++;

    //For each element of the Snake which is not it's head:
    for (int i = 1; i < Snake.size(); i++) {
        //If current Snake segment is not the last one:
        if (i < Snake.size() - 1) {
            //Record the current segment position into temp variables.
            int swap_y = Snake[i].position_y;
            int swap_x = Snake[i].position_x;

            //Change the segment's y and x position to the position of a segment after it.
            Snake[i].position_y = current_y;
            Snake[i].position_x = current_x;

            //Print a segment symbol in an updated position.
            mapa[Snake[i].position_y][Snake[i].position_x] = Snake[i].symbol;

            //Change the current y, x variables to swap, so that next in line segment will change it's position to the position of segment before it.
            current_y = swap_y;
            current_x = swap_x;
        }
        //If current segment is a last one:
        else if (i == Snake.size() - 1) {
            if (FruitEaten == false) {
                //Print an empty sign at it's location.
                mapa[Snake[i].position_y][Snake[i].position_x] = ' ';

                //Change it's position to the position of segment's before it.
                Snake[i].position_y = current_y;
                Snake[i].position_x = current_x;

                //Print it's symbol at an updated location.
                mapa[Snake[i].position_y][Snake[i].position_x] = Snake[i].symbol;
            }
            else if (FruitEaten == true) {
                //Record the current segment position into temp variables.
                int swap_y = Snake[i].position_y;
                int swap_x = Snake[i].position_x;

                //Change the segment's y and x position to the position of a segment after it.
                Snake[i].position_y = current_y;
                Snake[i].position_x = current_x;

                //Print a segment symbol in an updated position.
                mapa[Snake[i].position_y][Snake[i].position_x] = Snake[i].symbol;

                //Set the FruitEaten flag to false to prevent infinite loop.
                FruitEaten = false;

                //Add another segment to Snake's vector.
                Snake.push_back({'#', swap_y, swap_x});

                //Change the current y, x variables to swap, so that next in line segment will change it's position to the position of segment before it.
                current_y = swap_y;
                current_x = swap_x;

                //Set the symbol at an updated position.
                mapa[Snake[i].position_y][Snake[i].position_x] = Snake[i].symbol;
            }
        }

    }

    //If function reaches this point return true to allow game controlling loop to carry on.
    return true;
}

bool MoveDown (char mapa[][16], bool &alive, vector <Segment> &Snake, int &score) {

    //Variable controlling whether fruit has been eaten or not.
    bool FruitEaten = false;

    //If current execution of the function would put Snake in the wall or another Snake segment, return the game controlling flag as false.
    if (mapa[Snake[0].position_y + 1][Snake[0].position_x] == '=' || mapa[Snake[0].position_y + 1][Snake[0].position_x] == '#') {
        printw("You are dead!");
        return false;
    }

    //If in current execution of the function Snake will eat a fruit, create another one and give +10 points to the player.
    if (mapa[Snake[0].position_y + 1][Snake[0].position_x] == '*') {
        FruitEaten = true;
        score += 10;
        CreateFruit(mapa);
    }

    //Take the current y,x coords and put them into variables.
    int current_y = Snake[0].position_y;
    int current_x = Snake[0].position_x;

    //Since we're moving down, put a snake's head symbol at y++ position from current.
    mapa[Snake[0].position_y + 1][Snake[0].position_x] = Snake[0].symbol;

    //Change the head's y position to y++;
    Snake[0].position_y++;

    //For each element of the Snake which is not it's head:
    for (int i = 1; i < Snake.size(); i++) {
        //If current Snake segment is not the last one:
        if (i < Snake.size() - 1) {
            //Record the current segment position into temp variables.
            int swap_y = Snake[i].position_y;
            int swap_x = Snake[i].position_x;

            //Change the segment's y and x position to the position of a segment after it.
            Snake[i].position_y = current_y;
            Snake[i].position_x = current_x;

            //Print a segment symbol in an updated position.
            mapa[Snake[i].position_y][Snake[i].position_x] = Snake[i].symbol;

            //Change the current y, x variables to swap, so that next in line segment will change it's position to the position of segment before it.
            current_y = swap_y;
            current_x = swap_x;
        }
        //If current segment is a last one:
        else if (i == Snake.size() - 1) {
            if (FruitEaten == false) {
                //Print an empty sign at it's location.
                mapa[Snake[i].position_y][Snake[i].position_x] = ' ';

                //Change it's position to the position of segment's before it.
                Snake[i].position_y = current_y;
                Snake[i].position_x = current_x;

                //Print it's symbol at an updated location.
                mapa[Snake[i].position_y][Snake[i].position_x] = Snake[i].symbol;
            }
            else if (FruitEaten == true) {
                //Record the current segment position into temp variables.
                int swap_y = Snake[i].position_y;
                int swap_x = Snake[i].position_x;

                //Change the segment's y and x position to the position of a segment after it.
                Snake[i].position_y = current_y;
                Snake[i].position_x = current_x;

                //Print a segment symbol in an updated position.
                mapa[Snake[i].position_y][Snake[i].position_x] = Snake[i].symbol;

                //Set the FruitEaten flag to false to prevent infinite loop.
                FruitEaten = false;

                //Add another segment to Snake's vector.
                Snake.push_back({'#', swap_y, swap_x});

                //Change the current y, x variables to swap, so that next in line segment will change it's position to the position of segment before it.
                current_y = swap_y;
                current_x = swap_x;

                //Set the symbol at an updated position.
                mapa[Snake[i].position_y][Snake[i].position_x] = Snake[i].symbol;
            }
        }

    }
    //If function reaches this point return true to allow game controlling loop to carry on.
    return true;
}

int main() {
    //Declarating an array of chars, which will contain every game cell.
    char mapa[16][16];

    //Declaration of Snake's struct.
    struct Segment head, body1, body2, body3, body4;

    //Snake's vector declaration.
    vector <Segment> Snake;

    //Bool responsible for Snake's life.
    bool alive = true;

    //Initializing score variable.
    int score = 0;

    //Variables responsible for holding user's input.
    int key;

    //Initializing struct elements.
    head = {'@', 6, 7};
    body1 = {'#', 7, 7};
    body2 = {'#', 8, 7};

    //Pushing Snake segments to Snake vector.
    Snake.push_back(head);
    Snake.push_back(body1);
    Snake.push_back(body2);

    //Generating game window, and containing game functions inside.
        //Calling ncurses required functions + raw() and noecho().
        initscr();
        raw();
        noecho();
        keypad(stdscr, TRUE);

        //Generating map and snake;
        GenerateGameMap(mapa);
        GenerateSnake(mapa, Snake);
        CreateInitialFruit(mapa);

        //Displays initial map.
        Display(mapa);

        //Receives first input and assigns it to key variable.
        key = getch();

        //Loop controlling the game.
        while (alive) {
            //Displays map on each iteration.
            Display(mapa);

            //Executes movement functions. Which one depends on user input.
                switch(key) {
                    case KEY_UP:
                        //Execute corresponding function and assign it's return to alive.
                        alive = MoveUp(mapa, alive, Snake, score);

                        //Wait for 0,3s for user input, assign it to key if encountered.
                        halfdelay(3);
                        key = getch();

                        //if no input present, or input is unexpected assign previous value to key.
                        if (key != KEY_DOWN && key != KEY_LEFT && key != KEY_RIGHT && key != KEY_BACKSPACE) {
                            key = KEY_UP;
                        }
                        break;

                    case KEY_LEFT:
                        //Execute corresponding function and assign it's return to alive.
                        alive = MoveLeft(mapa, alive, Snake, score);

                        //Wait for 0,3s for user input, assign it to key if encountered.
                        halfdelay(3);
                        key = getch();

                        //if no input present, or input is unexpected assign previous value to key.
                        if (key != KEY_UP && key != KEY_DOWN && key != KEY_RIGHT && key != KEY_BACKSPACE) {
                            key = KEY_LEFT;
                        }
                        break;

                    case KEY_RIGHT:
                        //Execute corresponding function and assign it's return to alive.
                        alive = MoveRight(mapa, alive, Snake, score);

                        //Wait for 0,3s for user input, assign it to key if encountered.
                        halfdelay(3);
                        key = getch();

                        //if no input present, or input is unexpected assign previous value to key.
                        if (key != KEY_UP && key != KEY_DOWN && key != KEY_LEFT && key != KEY_BACKSPACE) {
                            key = KEY_RIGHT;
                        }
                        break;

                    case KEY_DOWN:
                        //Execute corresponding function and assign it's return to alive.
                        alive = MoveDown(mapa, alive, Snake, score);

                        //Wait for 0,3s for user input, assign it to key if encountered.
                        halfdelay(3);
                        key = getch();

                        //if no input present, or input is unexpected assign previous value to key.
                        if (key != KEY_UP && key != KEY_LEFT && key != KEY_RIGHT && key != KEY_BACKSPACE) {
                            key = KEY_DOWN;
                        }
                        break;

                    case KEY_BACKSPACE:
                        //Ends windows and exits program.
                        endwin();
                        return 0;
            }
        }

        //Getch waits for user input before closing the window, endwin() closes the window.
        getch();
        endwin();


    return 0;
}

