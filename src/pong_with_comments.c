#include <stdio.h> // Подключаем библиотеку для ввода/вывода

void print_field(int, int, int, int); // Прототип функции отрисовки поля
int ping_pong(void); // Прототип функции игры в ping-pong
void print_score(int, int); // Рисуем счёт

int main(void) { // Главная функция, которая запускает игру
    int winner;

    winner = ping_pong(); // Запускает функцию игры ping-pong, которая возвращает номер победившего игрока
    if (winner == 1) // Если побеждаеь 1 игрок
        printf("Игрок 1, поздравляем с победой!");
    else // Если побеждает 2 игрое
        printf("Игрок 2, поздравляем с победой!");

    return 0;
}

int ping_pong(void) { // Функция игры ping-pong
    int pos_racket1 = 12, pos_racket2 = 12; // Изначальные позиции ракеток
    int pos_ball_x = 8, pos_ball_y = 12; // Изначальная позиция мяча по X и Y
    int move_x = 1, move_y = 1; // Изначальное движение мяча, каждый ход X + 1 и Y + 1
    char move_racket1, move_racket2; // Вводим перменные куда буду считываться клавиши управления
    int score1 = 0, score2 = 0; // Изначальный счет 0:0

    while ((score1 < 21) && (score2 < 21)) { // Циклы игры, рабоатет пока кто-то не наберет 21 очко
        print_score(score1, score2); // Отрисовываем счёт
        print_field(pos_racket1, pos_racket2, pos_ball_x, pos_ball_y); //Рисуем поле с позициями ракеток мяча
        if (pos_ball_x == 0) { // Условие если забил 2й игрок
            score2++; // Прибавляем второму игроку очко
            pos_ball_x = 8; // Возвращаем мяч на позицию по X = 8 и Y = 12
            pos_ball_y = 12;
            move_x = 1; // Мяч теперь двигается в правую сторону
            pos_racket1 = 12; // Возвращаем ракетку на позицию Y = 12
        }
        if (pos_ball_x == 79) { // Аналогично условию выше, только если забил 1й игрок
            score1++;
            pos_ball_x = 72;
            pos_ball_y = 12;
            move_x = -1;
            pos_racket2 = 12;
        }
        if (pos_ball_y == 0 || pos_ball_y == 24) move_y *= -1; //Меняем напрвление мяча если коснулся поля
        if ((pos_ball_x == 7 && (pos_ball_y <= (pos_racket1 + 1) && pos_ball_y >= (pos_racket1 - 1))) ||
            (pos_ball_x == 73 && (pos_ball_y <= (pos_racket2 + 1) && pos_ball_y >= (pos_racket2 - 1))))
            move_x *= -1; // Меняем направление мяча, если коснулся ракетки

        pos_ball_x += move_x; // Сдвигаем мяч по Х либо на +1 либо на -1
        pos_ball_y += move_y; // Аналогично, только по Y

        printf("Игрок 1, введите A/Z дле перемещения: ");
        scanf("%c", &move_racket1); // Считываем управление для 1ого игрока
        if (move_racket1 != '\n') // Цикл который чистит поток ввода после считывания управления
            while (getchar() != '\n')
                ;
        if ((move_racket1 == 'a' || move_racket1 == 'A') && (pos_racket1 > 1)) pos_racket1--; // Ракетка вниз
        if ((move_racket1 == 'z' || move_racket1 == 'Z') && (pos_racket1 < 23)) pos_racket1++; // Вверх

        printf("Игрок 2, введите K/M для перемещения: "); 
        scanf("%c", &move_racket2); // Аналогично для 2ого игрока
        if (move_racket2 != '\n')
            while (getchar() != '\n')
                ;
        if ((move_racket2 == 'k' || move_racket2 == 'K') && (pos_racket2 > 1)) pos_racket2--;
        if ((move_racket2 == 'm' || move_racket2 == 'M') && (pos_racket2 < 23)) pos_racket2++;
    }
    return score1 == 21 ? 1 : 2; // Псоле того как кто-то побеждает, возвращаем номер победившего
}

void print_score(int score1, int score2) { // Отрисвока счета
    for (int i = 0; i <= 62; i++) {
        if (i == 15 || i == 47) printf("Score %2d", i == 15 ? score1 : score2); // Рисуем счет для игроков
        if (i == 62)
            printf("\n");
        else
            printf(" ");
    }
}

void print_field(int pos_racket1, int pos_racket2, int pos_ball_x, int pos_ball_y) { // Рисуем поле
    for (int i = 0; i <= 24; i++) // Пробегаемcя циклом по оси Y
        for (int j = 0; j <= 80; j++) { // Пробегаемся циклом  по оси X для выше заданого Y
            if ((i == pos_ball_y) && (j == pos_ball_x)) // Если по указаным координатам находится мяч
                printf("*"); // Рисуем мяч
            else if (j == 39) // Рисуем разделение поля
                printf("|"); 
            else if (j == 80) // Перевод строки
                printf("\n");
            else if ((i >= (pos_racket1 - 1) && i <= (pos_racket1 + 1)) && j == 6) // Рисуем ракетку 1 игрока
                printf("|");
            else if ((i >= (pos_racket2 - 1) && i <= (pos_racket2 + 1)) && j == 74) // Ракетка 2ого игрока
                printf("|");
            else
                printf(" "); // Рисуем пустоту
        }
}
