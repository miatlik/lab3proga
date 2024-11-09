// lab3proga.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#define MAX_CARDS 11
#define MAX_HAND 10

class Card {
private:
    int value; // Значение карты

public:
    Card(int val) : value(val) {}
    int getValue() const { return value; }
};

class Deck {
private:
    int cards[MAX_CARDS]; // Массив для хранения значений карт
    int size; // Текущий размер колоды

public:
    Deck() {
        vvodkolodi();
    }

    // Ввод игральной колоды с очками от 1 до 11
    void vvodkolodi() {
        for (int i = 0; i < MAX_CARDS; i++) {
            cards[i] = i + 1;
        }
        size = MAX_CARDS; // Инициализация размера колоды
    }

    // Случайный выбор карты из колоды
    int viborkarti() {
        if (size <= 0) return -1; // Возвращаем невалидное значение
        int ri = rand() % size;
        int randc = cards[ri];
        for (int i = ri; i < size - 1; i++) {
            cards[i] = cards[i + 1];
        }
        size--;
        return randc;
    }
    //Размер колоды
    int getSize() const {
        return size;
    }
};

class Player {
private:
    std::vector<Card*> hand; // Вектор для хранения указателей на карты
    int cardCount; // Количество карт в руке

public:
    Player() : cardCount(0) {}

    ~Player() {
        for (auto card : hand) {
            delete card; // Освобождение памяти для каждой карты
        }
    }
    //Получение в руку игрока или противника карты
    void ruka(int cardValue) {
        if (cardCount < MAX_HAND) {
            hand.push_back(new Card(cardValue)); // Динамическое выделение карты
            cardCount++;
        }
    }
    //Вывод руки игрока
    void vivodrukamy() const {
        int sum = 0;
        std::cout << "\nМои карты: ";
        for (auto card : hand) {
            std::cout << card->getValue() << ", "; // Получаем значение через указатель
            sum += card->getValue();
        }
        std::cout << sum << "/21";
    }
    //Вывод руки противника без первой карты
    void vivodrukabotaclose() const {
        int sum = 0;
        std::cout << "\nКарты противника: ?, ";
        for (int i = 1; i < cardCount; i++) {
            std::cout << hand[i]->getValue() << ", "; // Получаем значение через указатель
            sum += hand[i]->getValue();
        }
        std::cout << "? + " << sum << "/21";
    }
    //Вывод руки противника с первой картой
    void vivodrukabotaopen() const {
        int sum = 0;
        std::cout << "\nКарты противника: ";
        for (auto card : hand) {
            std::cout << card->getValue() << ", "; // Получаем значение через указатель
            sum += card->getValue();
        }
        std::cout << sum << "/21";
    }
    //Сумма очков противника или игрока
    int gettotalvalue() const {
        int sum = 0;
        for (auto card : hand) {
            sum += card->getValue();
        }
        return sum;
    }
    //Количество карт игрока или противника
    int getcardcount() const {
        return cardCount;
    }
    // Подсчет очков и вывод результата игры
    void vivodreza(Player* player, Player* opponent) {
        int sum1 = player->gettotalvalue();
        int sum2 = opponent->gettotalvalue();
        if (sum1 > 21 && sum2 < 22) std::cout << "\nУ вас перебор. Вы проиграли\n";
        if (sum2 > 21 && sum1 < 22) std::cout << "\nУ противника перебор. Вы выиграли\n";
        if (sum1 > 21 && sum2 > 21 && sum1 < sum2) std::cout << "\nУ вас и противника перебор.Вы выиграли, так как имеете меньше очков\n";
        if (sum1 > 21 && sum2 > 21 && sum1 > sum2) std::cout << "\nУ вас и противника перебор.Вы проиграли, так как имеете больше очков\n";
        if (sum1 < 22 && sum2 < 22 && sum1 < sum2) std::cout << "\nВы проиграли. Противник ближе к 21 очку\n";
        if (sum1 < 22 && sum2 < 22 && sum1 > sum2) std::cout << "\nВы выиграли. Вы ближе к 21 очку\n";
        if (sum1 == sum2) std::cout << "\nНичья\n";
    }
    //Простейший искусственный интелект для противника, который берет карту если у него меньше 17 очков
    int reshenie_ai(Player* opponent) const {
        int sum = opponent->gettotalvalue(); // Получаем сумму очков
        return (sum < 17) ? 0 : 1; // Возвращаем 0 (взять карту) или 1 (остановиться)
    }
};

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
