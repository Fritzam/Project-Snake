#include <iostream>
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
            cout << mapa[i][j];
        }
        cout << endl;
    }
}

void MoveFoward(char mapa[0][16], bool alive, vector <Segment> &Snake) {
    while(alive) {
        for (int i = 0; i < Snake.size(); i++) {
            if (i == Snake.size() - 1) {
                mapa[Snake[i].position_y - 1][Snake[i].position_x] = Snake[i].symbol;
                Snake[i].position_y--;
                mapa[Snake[i].position_y + 1][Snake[i].position_x] = ' ';

            }
            else {
                mapa[Snake[i].position_y + -1][Snake[i].position_x] = Snake[i].symbol;
                Snake[i].position_y--;
            }
        }
        Display(mapa);
        if (mapa[Snake[0].position_y - 1][Snake[0].position_x] == '=') {
            cout << "You are dead!" << endl;
            alive=false;
        }
    }
}

void MoveLeft(char mapa[0][16], bool alive, vector <Segment> &Snake) {
    while(alive) {
        int change_direction = Snake[0].position_y;
        for (int j = 0; j < Snake.size(); j++) {
            //Jeżeli dotyczy ostatniego segmentu węża.
            if (j == Snake.size() - 1) {
                //Jeżeli segment jest na wysokości głowy.
                if (Snake[j].position_y == change_direction) {
                    mapa[Snake[j].position_y][Snake[j].position_x - 1] = Snake[j].symbol;
                    mapa[Snake[j].position_y][Snake[j].position_x] = ' ';
                    Snake[j].position_x--;
                }
                else {
                    //Jeżeli nie jest na wysokości głowy.
                    mapa[Snake[j].position_y - 1][Snake[j].position_x] = Snake[j].symbol;
                    mapa[Snake[j].position_y][Snake[j].position_x] = ' ';
                    Snake[j].position_y--;
                }
            }
            else {
            //Jeżeli nie dotyczy ostatniego segmentu węża.
                //Jeżeli segment jest na pozycji Y głowy węża.
                if (Snake[j].position_y == change_direction) {
                    mapa[Snake[j].position_y][Snake[j].position_x - 1] = Snake[j].symbol;
                    Snake[j].position_x--;
                }
                //Jeżeli segment nie jest na pozycji Y głowy węża.
                else {
                    mapa[Snake[j].position_y - 1][Snake[j].position_x] = Snake[j].symbol;
                    Snake[j].position_y--;
                }
            }
        }
            Display(mapa);
            if (mapa[Snake[0].position_y][Snake[0].position_x - 1] == '|') {
                cout << "YOU ARE DEAD!";
                alive=false;
            }
        }
    }


int main() {
    //Deklaracja tabeli gry.
    char mapa[16][16];

    //Deklaracja structu snake'.
    struct Segment head, body1, body2, body3, body4;

    //Deklaracja vectora Snake
    vector <Segment> Snake;

    //Inicjalizacja boole'a odpowiadającego za życie Snake'a.
    bool alive = true;

    //Inizjalizowanie wartości struktur Segment.
    head = {'@', 6, 7};
    body1 = {'#', 7, 7};
    body2 = {'#', 8, 7};
    body3 = {'#', 9, 7};
    body4 = {'#', 10, 7};

    //Dodawanie struktur do vectora;
    Snake.push_back(head);
    Snake.push_back(body1);
    Snake.push_back(body2);
    Snake.push_back(body3);
    Snake.push_back(body4);





    //Wygenerowanie mapy gry.
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

    //Wygenerowanie Snake'a na mapie.
    for (int i = 0; i < Snake.size(); i++) {
        mapa[Snake[i].position_y][Snake[i].position_x] = Snake[i].symbol;
    }
    //Display(mapa);
    //Display(mapa);
    //Funkcja do poruszania się naprzód.
    //MoveFoward(mapa, alive, Snake);
    Display(mapa);
    MoveLeft(mapa, alive, Snake);


    return 0;
}

