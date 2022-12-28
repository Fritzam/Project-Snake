#include <iostream>
#include <vector>

using namespace std;

void Display(char granice_mapy[][16]) {
    //Displaying borders, and the snake.
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            cout << granice_mapy[i][j];
        }
        cout << endl;
    }
}

void MoveForward(char granice_mapy[][16], bool alive, int &position_y, int position_x, vector <char> snake_segments) {
    while(alive) {
        //Moving snake.
        for (int j = 0; j < snake_segments.size(); j++) {
            if (j != snake_segments.size() - 1) {
                granice_mapy[(position_y - 1) + j][position_x] = snake_segments[j];
            }
            else if (j == snake_segments.size() - 1) {
                granice_mapy[(position_y - 1) + j][position_x] = snake_segments[j];
                granice_mapy[(position_y) + j][position_x] = ' ';
            }
        }
        position_y--;
        Display(granice_mapy);
        if (granice_mapy[position_y - 1][position_x] == '=') {
            cout << "YOU ARE DEAD!" << endl;
            alive=false;
        }
    }
}


int main() {
    //Declarations for the game.
    char granice_mapy[16][16];
    vector <char> snake_segments{'@', '#', '#'};
    bool alive = true;
    int position_y = 7;
    int position_x = 7;


    //Generating borders of the snake game.
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            if (i == 0 || i == 15) {
                granice_mapy[i][j] = '=';
            }
            else if ((i != 0 || i != 15) && (j == 0 || j == 15)) {
                granice_mapy[i][j] = '|';
            }
            else {
                granice_mapy[i][j] = ' ';
            }
        }
    }


    //Generating snake inside of the borders.
    for (int i = 0; i < snake_segments.size(); i++) {
        granice_mapy[7][7] = snake_segments[i];
    }

    MoveForward(granice_mapy, alive, position_y, position_x, snake_segments);

    return 0;
}

