#include <iostream>

using namespace std;

int main() {
    //Declarations for the game.
    int wymiary_mapy = 16;
    int snake_segments = 3;
    char granice_mapy[wymiary_mapy][wymiary_mapy];
    char snake[snake_segments] = {'@', '#', '#'};

    //Generating borders of the snake game.
    for (int i = 0; i < wymiary_mapy; i++) {
        for (int j = 0; j < wymiary_mapy; j++) {
            if (i == 0 || i == wymiary_mapy - 1) {
                granice_mapy[i][j] = '=';
            }
            else if ((i != 0 || i != wymiary_mapy - 1) && (j == 0 || j == wymiary_mapy - 1)) {
                granice_mapy[i][j] = '|';
            }
            else {
                granice_mapy[i][j] = ' ';
            }
        }
    }


    //Generating snake inside of the borders.
    for (int i = 0; i < snake_segments; i++) {
        granice_mapy[(wymiary_mapy/2 - 1 + i)][wymiary_mapy/2 - 1] = snake[i];
    }

    //Displaying borders, and the snake.
    for (int i = 0; i < wymiary_mapy; i++) {
        for (int j = 0; j < wymiary_mapy; j++) {
            cout << granice_mapy[i][j];
        }
        cout << endl;
    }

    cout << "--------------------------------------------" << endl;
    cout << snake[0] << snake[1] << snake[2] << endl;
    cout << "--------------------------------------------" << endl;

    return 0;
}
