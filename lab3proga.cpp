// lab3proga.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <ctime>
#define MAX_CARDS 11
#define MAX_HAND 10
typedef struct {
    int value; // Значение карты
} Card;
typedef struct {
    Card hand[MAX_HAND]; // Массив карт игрока
    int cardCount; // Количество карт в руке
} Player;
//Ввод игральной колоды с очками от 1 до 11
void vvodkolodi(int arr[]) {
    for (int i = 0; i < MAX_CARDS; i++) {
        arr[i] = i + 1;
    }
}
//Случайный выбор карты из колоды(выбор числа из массива и удаление его из этого массива)
int viborkarti(int arr[], int* size) {
    int ri, randc;
    ri = rand() % *size;
    randc = arr[ri];
    for (int i = ri; i < *size - 1; i++) arr[i] = arr[i + 1];
    (*size)--;
    return randc;
}
//Взятие карты игроком 
void rukamy(Player* player, int arr[], int* size) {
    if (player->cardCount < MAX_HAND) {
        player->hand[player->cardCount].value = viborkarti(arr, size);
        player->cardCount++;
    }
}
//Взятие карты противником
void rukabota(Player* opponent, int arr[], int* size) {
    if (opponent->cardCount < MAX_HAND) {
        opponent->hand[opponent->cardCount].value = viborkarti(arr, size);
        opponent->cardCount++;
    }
}
//Вывод моих карт и их суммы очков
void vivodrukamy(Player* player) {
    int sum = 0;
    printf("\nМои карты: ");
    for (int i = 0; i < player->cardCount; i++) {
        printf("%d, ", player->hand[i].value);
        sum += player->hand[i].value;
    }
    printf("%d/21", sum);
}
//Вывод карт противника с учетом первой скрытой карты и суммы очков без первой карты
void vivodrukabota(Player* opponent) {
    int sum = 0;
    printf("\nКарты противника: ?,  ");
    for (int i = 1; i < opponent->cardCount; i++) {
        printf("%d, ", opponent->hand[i].value);
        sum += opponent->hand[i].value;
    }
    printf("?+%d/21", sum);
}
//Подсчет очков моих и противника и вывод результата игры
void vivodreza(Player* player, Player* opponent) {
    int sum1 = 0, sum2 = 0;
    for (int i = 0; i < player->cardCount; i++)
        sum1 += player->hand[i].value;
    for (int i = 0; i < opponent->cardCount; i++)
        sum2 += opponent->hand[i].value;
    // Логика определения результата
    if (sum1 > 21 && sum2 < 22) printf("У вас перебор. Вы проиграли\n");
    if (sum2 > 21 && sum1 < 22) printf("У противника перебор. Вы выиграли\n");
    if (sum1 > 21 && sum2 > 21 && sum1 < sum2) printf("У вас и противника перебор.Вы выиграли, так как имеете меньше очков\n");
    if (sum1 > 21 && sum2 > 21 && sum1 > sum2) printf("У вас и противника перебор.Вы проиграли, так как имеете больше очков\n");
    if (sum1 < 22 && sum2 < 22 && sum1 < sum2) printf("Вы проиграли. Противник ближе к 21 очку\n");
    if (sum1 < 22 && sum2 < 22 && sum1 > sum2) printf("Вы выиграли. Вы ближе к 21 очку\n");
    if (sum1 == sum2) printf("Ничья\n");
}
//Простейший искусственный интелект для противника, который берет карту если у него меньше 17 очков
int reshenie_ai(Player* opponent) {
    int sum = 0, randbot = 1;
    for (int i = 0; i < opponent->cardCount; i++)
        sum += opponent->hand[i].value;
    if (sum < 17) randbot = 0;
    return randbot;
}
int main() {
    setlocale(LC_ALL, "Rus");
    char ch;
    do {
        int arr[MAX_CARDS], n, sum, f1 = 1, f2 = 1, take, per = 0;
        Player player = { player.cardCount = 0 }; // Инициализация игрока
        Player opponent = { opponent.cardCount = 0 }; // Инициализация противника
        srand(time(NULL));
        sum = 0;
        n = MAX_CARDS;
        vvodkolodi(arr);
        printf("\n");
        //Начальная раздача карт и вывод того, что взяли
        rukamy(&player, arr, &n);
        rukamy(&player, arr, &n);
        rukabota(&opponent, arr, &n);
        rukabota(&opponent, arr, &n);
        vivodrukamy(&player);
        vivodrukabota(&opponent);
        //Основная игра с возможностью брать карту или пасовать, противник также берет карту или пасует
        while (f1 == 1 || f2 == 1) {
            if (f1 == 1) {
                printf("\nНажмите 1, чтобы тянуть карту\n");
                printf("Нажмите 2, чтобы спасовать\n");
                while (scanf("%d", &take) != 1 || take < 1 || take > 2) {
                    while (getchar() != '\n');
                    printf("Ошибка. Выберите 1 или 2: ");
                }
                while (getchar() != '\n');
                for (int i = 0; i < player.cardCount; i++)
                    sum += player.hand[i].value;
                if (sum > 21) per = 1;
                sum = 0;
                if (take == 1) {
                    if (per == 0) rukamy(&player, arr, &n);
                    else printf("Нельзя брать карту при переборе\n");
                }
                else {
                    printf("Вы спасовали");
                    f1 = 0;
                }
            }
            if (reshenie_ai(&opponent) == 0 && f2 == 1) rukabota(&opponent, arr, &n);
            if (reshenie_ai(&opponent) == 1 && f2 == 1) {
                printf("\nПротивник спасовал");
                f2 = 0;
            }
            vivodrukamy(&player);
            if (f1 == 1) {
                vivodrukabota(&opponent);
            }
            else {
                sum = 0;
                printf("\nКарты противника: ");
                for (int i = 0; i < opponent.cardCount; i++)
                    printf("%d, ", opponent.hand[i].value);
                for (int i = 0; i < opponent.cardCount; i++) sum += opponent.hand[i].value;
                printf("%d/21\n", sum);
            }
            if (f1 == 0 && f2 == 0) vivodreza(&player, &opponent);
        }
        puts("\nНажмите q, чтобы выйти или любую другую клавишу, чтобы сыграть заново\n\n");
    } while ((ch = _getch()) != 'q');
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
