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




    for (int i = 0; i < 3; i++) {
        //Moving snake.
        for (int i = 0; i < snake_segments.size(); i++) {
            if (i == snake_segments.size() - 1) {
                granice_mapy[position_y - 1][position_x] = snake_segments[i];
                granice_mapy[position_y][position_x] = ' ';
                position_y--;
            } else {
                granice_mapy[position_y - 1][position_x] = snake_segments[i];
            }
        }
        Display(granice_mapy);
    }

    cout << "--------------------------------------------" << endl;
    cout << snake_segments[0] << snake_segments[1] << snake_segments[2] << endl;
    cout << "--------------------------------------------" << endl;

    return 0;
}

