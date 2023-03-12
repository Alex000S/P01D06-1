#include <stdio.h>

void print_field(int, int, int, int);
int ping_pong(void);
void print_score(int, int);

int main(void) {
    int winner;

    winner = ping_pong();
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
    char move_racket1, move_racket2;
    int score1 = 0, score2 = 0;

    while ((score1 < 21) && (score2 < 21)) {
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

        printf("Игрок 1, введите A/Z дле перемещения: ");
        scanf("%c", &move_racket1);
        if (move_racket1 != '\n')
            while (getchar() != '\n')
                ;
        if ((move_racket1 == 'a' || move_racket1 == 'A') && (pos_racket1 > 1)) pos_racket1--;
        if ((move_racket1 == 'z' || move_racket1 == 'Z') && (pos_racket1 < 23)) pos_racket1++;

        printf("Игрок 2, введите K/M для перемещения: ");
        scanf("%c", &move_racket2);
        if (move_racket2 != '\n')
            while (getchar() != '\n')
                ;
        if ((move_racket2 == 'k' || move_racket2 == 'K') && (pos_racket2 > 1)) pos_racket2--;
        if ((move_racket2 == 'm' || move_racket2 == 'M') && (pos_racket2 < 23)) pos_racket2++;
    }
    return score1 == 21 ? 1 : 2;
}

void print_score(int score1, int score2) {
    for (int i = 0; i <= 62; i++) {
        if (i == 15 || i == 47) printf("Score %2d", i == 15 ? score1 : score2);
        if (i == 62)
            printf("\n");
        else
            printf(" ");
    }
}

void print_field(int pos_racket1, int pos_racket2, int pos_ball_x, int pos_ball_y) {
    for (int i = 0; i <= 24; i++)
        for (int j = 0; j <= 80; j++) {
            if ((i == pos_ball_y) && (j == pos_ball_x))
                printf("*");
            else if (j == 39)
                printf("|");
            else if (j == 80)
                printf("\n");
            else if ((i >= (pos_racket1 - 1) && i <= (pos_racket1 + 1)) && j == 6)
                printf("|");
            else if ((i >= (pos_racket2 - 1) && i <= (pos_racket2 + 1)) && j == 74)
                printf("|");
            else
                printf(" ");
        }
}
