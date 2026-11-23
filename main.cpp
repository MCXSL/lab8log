#include "Graph.h"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    int size;
    std::cout << "Введите число вершин (1–100): ";
    if (!(std::cin >> size) || size < 1 || size > 100) {
        std::cerr << "Ошибка: нужно целое число от 1 до 100.\n";
        return 1;
    }

    Matrix graph = generateGraph(size);
    std::cout << "\nМатрица смежности:\n";
    printMatrix(graph);
    std::cout << "\nОбход по матрице (std::queue):\n";
    printOrder(bfsMatrix(graph));

    AdjacencyList list = makeAdjacencyList(graph);
    std::cout << "\nСписки смежности:\n";
    printAdjacencyList(list);
    std::cout << "\nОбход по спискам (std::queue):\n";
    printOrder(bfsList(list));
    std::cout << "\nОбход по матрице (своя очередь):\n";
    printOrder(bfsLinkedQueue(graph));

    compareTime();
    return 0;
}
