#include <iostream>
#include <ncurses.h>
#include <vector>

using namespace std;

struct Segment {
        char symbol;
        int position_y;
        int position_x;
    };

void Display(char mapa[][16]) {
    //Displaying borders, and the snake.
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            mvaddch(i, j, mapa[i][j]);
        }
    }
}

void GenerateGameMap(char mapa[][16]) {
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

bool MoveUp (char mapa[][16], bool &alive, vector <Segment> &Snake) {

    //If next execution of the function would put Snake in the wall set the game controlling flag to false.
    if (mapa[Snake[0].position_y - 1][Snake[0].position_x] == '=') {
        printw("You are dead!");
        return false;
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
            //Print an empty sign at it's location.
            mapa[Snake[i].position_y][Snake[i].position_x] = ' ';

            //Change it's position to the position of segment's before it.
            Snake[i].position_y = current_y;
            Snake[i].position_x = current_x;

            //Print it's symbol at an updated location.
            mapa[Snake[i].position_y][Snake[i].position_x] = Snake[i].symbol;
        }

    }

    //If function reaches this point return true to allow game controlling loop to carry on.
    return true;
}

bool MoveLeft (char mapa[][16], bool &alive, vector <Segment> &Snake) {

    //If next execution of the function would put Snake in the wall set the game controlling flag to false.
    if (mapa[Snake[0].position_y][Snake[0].position_x - 1] == '|') {
        printw("You are dead!");
        return false;
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
            //Print an empty sign at it's location.
            mapa[Snake[i].position_y][Snake[i].position_x] = ' ';

            //Change it's position to the position of segment's before it.
            Snake[i].position_y = current_y;
            Snake[i].position_x = current_x;

            //Print it's symbol at an updated location.
            mapa[Snake[i].position_y][Snake[i].position_x] = Snake[i].symbol;
        }

    }

    //If function reaches this point return true to allow game controlling loop to carry on.
    return true;
}

bool MoveRight (char mapa[][16], bool &alive, vector <Segment> &Snake) {

    //If next execution of the function would put Snake in the wall set the game controlling flag to false.
    if (mapa[Snake[0].position_y][Snake[0].position_x + 1] == '|') {
        printw("You are dead!");
        return false;
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
            //Print an empty sign at it's location.
            mapa[Snake[i].position_y][Snake[i].position_x] = ' ';

            //Change it's position to the position of segment's before it.
            Snake[i].position_y = current_y;
            Snake[i].position_x = current_x;

            //Print it's symbol at an updated location.
            mapa[Snake[i].position_y][Snake[i].position_x] = Snake[i].symbol;
        }

    }

    //If function reaches this point return true to allow game controlling loop to carry on.
    return true;
}

bool MoveDown (char mapa[][16], bool &alive, vector <Segment> &Snake) {

    //If next execution of the function would put Snake in the wall set the game controlling flag to false.
    if (mapa[Snake[0].position_y + 1][Snake[0].position_x] == '=') {
        printw("You are dead!");
        return false;
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
            //Print an empty sign at it's location.
            mapa[Snake[i].position_y][Snake[i].position_x] = ' ';

            //Change it's position to the position of segment's before it.
            Snake[i].position_y = current_y;
            Snake[i].position_x = current_x;

            //Print it's symbol at an updated location.
            mapa[Snake[i].position_y][Snake[i].position_x] = Snake[i].symbol;
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

    //Variable responsible for holding user's input.
    int key;

    //Initializing struct elements.
    head = {'@', 6, 7};
    body1 = {'#', 7, 7};
    body2 = {'#', 8, 7};
    body3 = {'#', 9, 7};
    body4 = {'#', 10, 7};

    //Pushing Snake segments to Snake vector.
    Snake.push_back(head);
    Snake.push_back(body1);
    Snake.push_back(body2);
    Snake.push_back(body3);
    Snake.push_back(body4);

    //Generating game window, and containing game functions inside.
        //Calling ncurses required functions + raw() and noecho().
        initscr();
        raw();
        noecho();
        keypad(stdscr, TRUE);

        //Generating map and snake;
        GenerateGameMap(mapa);
        GenerateSnake(mapa, Snake);

        //Loop controlling the game.
        while (alive) {
            //Displays map on each iteration.
            Display(mapa);

            //Receives input and assigns it to key variable.
            key = getch();

            //Executes movement functions. Which one depends on user input.
            switch(key) {
                case KEY_UP:
                    alive = MoveUp(mapa, alive, Snake);
                    break;
                case KEY_LEFT:
                    alive = MoveLeft(mapa, alive, Snake);
                    break;
                case KEY_RIGHT:
                    alive = MoveRight(mapa, alive, Snake);
                    break;
                case KEY_DOWN:
                    alive = MoveDown(mapa, alive, Snake);
                    break;
            }
        }

        //Getch waits for user input before closing the window, endwin() closes the window.
        getch();
        endwin();


    return 0;
}

