#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

void print_field(int, int, int, int);
int ping_pong(void);
void print_score(int, int);

int main(void) {
    int winner;

    initscr();
    timeout(100);
    curs_set(0);
    noecho();

    winner = ping_pong();

    endwin();

    if (winner == 1)
        printf("Игрок 1, поздравляем с победой!");
    else
        printf("Игрок 2, поздравляем с победой!");
    return 0;
}

int ping_pong(void) {
    int pos_racket1 = 12, pos_racket2 = 12;
    int pos_ball_x = 8, pos_ball_y = 12;
    int move_x = 1, move_y = 1;
    int score1 = 0, score2 = 0;

    system("clear");
    while ((score1 < 21) && (score2 < 21)) {
        move(0, 0);
        print_score(score1, score2);
        print_field(pos_racket1, pos_racket2, pos_ball_x, pos_ball_y);
        if (pos_ball_x == 0) {
            score2++;
            pos_ball_x = 8;
            pos_ball_y = 12;
            move_x = 1;
            pos_racket1 = 12;
        }
        if (pos_ball_x == 79) {
            score1++;
            pos_ball_x = 72;
            pos_ball_y = 12;
            move_x = -1;
            pos_racket2 = 12;
        }
        if (pos_ball_y == 0 || pos_ball_y == 24) move_y *= -1;
        if ((pos_ball_x == 7 && (pos_ball_y <= (pos_racket1 + 1) && pos_ball_y >= (pos_racket1 - 1))) ||
            (pos_ball_x == 73 && (pos_ball_y <= (pos_racket2 + 1) && pos_ball_y >= (pos_racket2 - 1))))
            move_x *= -1;

        pos_ball_x += move_x;
        pos_ball_y += move_y;

        char move_racket = getch();
        flushinp();
        if ((move_racket == 'a' || move_racket == 'A') && (pos_racket1 > 1)) pos_racket1--;
        if ((move_racket == 'z' || move_racket == 'Z') && (pos_racket1 < 23)) pos_racket1++;
        if ((move_racket == 'k' || move_racket == 'K') && (pos_racket2 > 1)) pos_racket2--;
        if ((move_racket == 'm' || move_racket == 'M') && (pos_racket2 < 23)) pos_racket2++;
    }
    return score1 == 21 ? 1 : 2;
}

void print_score(int score1, int score2) {
    for (int i = 0; i <= 62; i++) {
        if (i == 15 || i == 47) printw("Score %2d", i == 15 ? score1 : score2);
        if (i == 62)
            printw("\n");
        else
            printw(" ");
        refresh();
    }
}

void print_field(int pos_racket1, int pos_racket2, int pos_ball_x, int pos_ball_y) {
    for (int i = 0; i <= 24; i++)
        for (int j = 0; j <= 80; j++) {
            if ((i == pos_ball_y) && (j == pos_ball_x))
                printw("*");
            else if (j == 39)
                printw("|");
            else if (j == 80)
                printw("\n");
            else if ((i >= (pos_racket1 - 1) && i <= (pos_racket1 + 1)) && j == 6)
                printw("|");
            else if ((i >= (pos_racket2 - 1) && i <= (pos_racket2 + 1)) && j == 74)
                printw("|");
            else
                printw(" ");
            refresh();
        }
}
