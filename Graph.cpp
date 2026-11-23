#include "Graph.h"
#include "LinkedQueue.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <queue>
#include <random>

Matrix generateGraph(int size) {
    static std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> randomEdge(0, 1);
    Matrix graph(size, std::vector<int>(size, 0));
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            graph[i][j] = randomEdge(generator);
            graph[j][i] = graph[i][j];
        }
    }
    return graph;
}

void printMatrix(const Matrix& graph) {
    for (const auto& row : graph) {
        for (int value : row) {
            std::cout << value << ' ';
        }
        std::cout << '\n';
    }
}

AdjacencyList makeAdjacencyList(const Matrix& graph) {
    int size = static_cast<int>(graph.size());
    AdjacencyList list(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (graph[i][j] == 1) {
                list[i].push_back(j);
            }
        }
    }
    return list;
}

void printAdjacencyList(const AdjacencyList& graph) {
    for (int i = 0; i < static_cast<int>(graph.size()); ++i) {
        std::cout << i + 1 << ": ";
        for (int neighbor : graph[i]) {
            std::cout << neighbor + 1 << ' ';
        }
        std::cout << '\n';
    }
}

std::vector<int> bfsMatrix(const Matrix& graph) {
    int size = static_cast<int>(graph.size());
    std::vector<bool> visited(size, false);
    std::vector<int> order;
    std::queue<int> queue;

    // Внешний цикл позволяет обойти также несвязный граф.
    for (int start = 0; start < size; ++start) {
        if (visited[start]) {
            continue;
        }
        queue.push(start);
        visited[start] = true;
        while (!queue.empty()) {
            int vertex = queue.front();
            queue.pop();
            order.push_back(vertex);
            for (int i = 0; i < size; ++i) {
                if (graph[vertex][i] == 1 && !visited[i]) {
                    queue.push(i);
                    visited[i] = true;
                }
            }
        }
    }
    return order;
}

std::vector<int> bfsList(const AdjacencyList& graph) {
    int size = static_cast<int>(graph.size());
    std::vector<bool> visited(size, false);
    std::vector<int> order;
    std::queue<int> queue;
    for (int start = 0; start < size; ++start) {
        if (visited[start]) {
            continue;
        }
        queue.push(start);
        visited[start] = true;
        while (!queue.empty()) {
            int vertex = queue.front();
            queue.pop();
            order.push_back(vertex);
            for (int neighbor : graph[vertex]) {
                if (!visited[neighbor]) {
                    queue.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
    }
    return order;
}

std::vector<int> bfsLinkedQueue(const Matrix& graph) {
    int size = static_cast<int>(graph.size());
    std::vector<bool> visited(size, false);
    std::vector<int> order;
    LinkedQueue queue;
    for (int start = 0; start < size; ++start) {
        if (visited[start]) {
            continue;
        }
        queue.push(start);
        visited[start] = true;
        while (!queue.empty()) {
            int vertex = queue.front();
            queue.pop();
            order.push_back(vertex);
            for (int i = 0; i < size; ++i) {
                if (graph[vertex][i] == 1 && !visited[i]) {
                    queue.push(i);
                    visited[i] = true;
                }
            }
        }
    }
    return order;
}

void printOrder(const std::vector<int>& order) {
    for (int vertex : order) {
        std::cout << vertex + 1 << ' ';
    }
    std::cout << '\n';
}

void compareTime() {
    const int repeats = 10;
    std::cout << "\nСреднее время обхода, мс (10 повторений):\n";
    std::cout << "Вершин\tstd::queue\tСвоя очередь\n";
    for (int size : {100, 500, 1000, 2000}) {
        Matrix graph = generateGraph(size);
        double standardTime = 0;
        double linkedTime = 0;
        for (int repeat = 0; repeat < repeats; ++repeat) {
            auto start = std::chrono::steady_clock::now();
            std::vector<int> standardOrder = bfsMatrix(graph);
            auto middle = std::chrono::steady_clock::now();
            std::vector<int> linkedOrder = bfsLinkedQueue(graph);
            auto finish = std::chrono::steady_clock::now();
            standardTime += std::chrono::duration<double, std::milli>(middle - start).count();
            linkedTime += std::chrono::duration<double, std::milli>(finish - middle).count();
            if (standardOrder != linkedOrder) {
                std::cout << "Ошибка: результаты обходов различаются.\n";
                return;
            }
        }
        std::cout << size << '\t' << std::fixed << std::setprecision(3)
                  << standardTime / repeats << "\t\t" << linkedTime / repeats << '\n';
    }
}
