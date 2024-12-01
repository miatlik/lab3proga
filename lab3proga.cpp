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

// Исключение для переполнения колоды
class DeckOverflowException : public std::runtime_error {
public:
    DeckOverflowException() : std::runtime_error("Ошибка: Переполнение колоды карт.") {}
};

// Исключение для переполнения руки игрока
class HandOverflowException : public std::runtime_error {
public:
    HandOverflowException() : std::runtime_error("Ошибка: Переполнение руки игрока.") {}
};

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
        try {
            vvodkolodi();
        }
        catch (const DeckOverflowException& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    // Ввод игральной колоды с очками от 1 до 11
    void vvodkolodi() {
        if (MAX_CARDS > 11) {
            throw DeckOverflowException(); // Генерация исключения, если максимальное количество карт превышает 11
        }
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
    //Конструктор копирования
    Player(const Player& other) : cardCount(other.cardCount) {
        for (auto card : other.hand) {
            hand.push_back(new Card(card->getValue())); // Копируем каждую карту
        }
    }
    //  Перегрузка оператора присваивания
    Player& operator=(const Player& other) {
        if (this == &other) { // Проверка на самоприсваивание
            return *this;
        }

        // Освобождение памяти предыдущих карт
        for (auto card : hand) {
            delete card;
        }
        hand.clear(); // Очистка вектора карт
        cardCount = other.cardCount; // Копируем количество карт

        // Копируем карты из другого игрока
        for (auto card : other.hand) {
            hand.push_back(new Card(card->getValue())); // Глубокое копирование карт
        }

        return *this; // Возвращаем текущий объект
    }
    //Получение в руку игрока или противника карты
    void ruka(int cardValue) {
        try {
            if (cardCount >= MAX_HAND) { // Проверка переполнения руки
                throw HandOverflowException(); // Генерация исключения, если рука полна
            }
            hand.push_back(new Card(cardValue)); // Динамическое выделение карты
            cardCount++;
        }
        catch (const HandOverflowException& e) {
            std::cerr << e.what() << std::endl; // Вывод сообщения об ошибке
        }
    }
    // Дружественная функция для вывода информации о игроке
    friend void printPlayerInfo(const Player& player);
    // Перегрузка оператора вывода для Player
    friend std::ostream& operator<<(std::ostream& os, const Player& player) {
        os << "Карты игрока: ";
        for (auto card : player.hand) {
            os << card->getValue() << ", "; // Получаем значение через указатель
        }
        os << player.gettotalvalue() << "/21\n";
        return os;
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
        std::cout << sum << "/21\n";
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
    // Возвращает сумму очков через ссылку
    const int& getScoreReference() const {
        return gettotalvalue(); // Возвращаем сумму очков по ссылке
    }
    // Возвращает сумму очков через указатель
    const int* getScorePointer() const {
        int* score = new int(gettotalvalue()); // Динамически выделяем память для значения
        return score; // Возвращаем указатель на сумму
    }

};
// Дружественная функция для вывода информации о игроке
void printPlayerInfo(const Player& player) {
    std::cout << player; // Используем перегруженный оператор << для вывода
}
int main() {
    setlocale(LC_ALL, "Rus");
    char ch;
    do {
        int  f1 = 1, f2 = 1, take, per = 0;
        Deck deck;
        Player player;
        Player* opponent = new Player(); // Динамическое выделение противника
        srand(static_cast<unsigned int>(time(NULL)));

        deck.vvodkolodi();
        // Начальная раздача карт
        player.ruka(deck.viborkarti());
        player.ruka(deck.viborkarti());
        opponent->ruka(deck.viborkarti());
        opponent->ruka(deck.viborkarti());

        // Получение суммы очков через ссылку
        const int& scoreRef = player.getScoreReference();
        std::cout << "\nСумма очков через ссылку: " << scoreRef << std::endl;
        // Получение суммы очков через указатель
        const int* scorePtr = player.getScorePointer();
        std::cout << "\nСумма очков через указатель: " << *scorePtr << std::endl;
        printPlayerInfo(player);
        //Использование конструктора копии на примере карт игрока
        std::cout << "Копии карт игрока, сделанные с помощью конструктора копии: ";
        Player player2 = player;
        printPlayerInfo(player2);
        //Использование перегруженного оператора присваивания 
        std::cout << "Копии карт игрока, сделанные с помощью перегруженного оператора присваивания: ";
        Player player3;
        player3 = player;
        printPlayerInfo(player3);
        opponent->vivodrukabotaclose();
        //Основная игра
        while (f1 == 1 || f2 == 1) {
            if (f1 == 1) {
                std::cout << "\nНажмите 1, чтобы тянуть карту\n";
                std::cout << "Нажмите 2, чтобы спасовать\n";
                while (scanf("%d", &take) != 1 || take < 1 || take > 2) {
                    while (getchar() != '\n');
                    std::cout << "Ошибка. Выберите 1 или 2: ";
                }
                while (getchar() != '\n');
                if (player.gettotalvalue() > 21) per = 1;
                if (take == 1) {
                    if (per == 0) player.ruka(deck.viborkarti());
                    else std::cout << "Нельзя брать карту при переборе\n";
                }
                else {
                    std::cout << "Вы спасовали\n";
                    f1 = 0;
                }
            }
            if (opponent->reshenie_ai(opponent) == 0 && f2 == 1) opponent->ruka(deck.viborkarti());
            if (opponent->reshenie_ai(opponent) == 1 && f2 == 1) {
                std::cout << "\nПротивник спасовал\n";
                f2 = 0;
            }
            // Используем дружественную функцию для отображения информации о игроке
            printPlayerInfo(player);
            if (f1 == 1) opponent->vivodrukabotaclose();
            else opponent->vivodrukabotaopen();
            if (f1 == 0 && f2 == 0) player.vivodreza(&player, opponent);
        }
        // Освобождение памяти
        delete scorePtr;
        delete opponent;

        std::cout << "\nНажмите q, чтобы выйти или любую другую клавишу, чтобы сыграть заново\n";
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
