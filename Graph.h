#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

using Matrix = std::vector<std::vector<int>>;
using AdjacencyList = std::vector<std::vector<int>>;

Matrix generateGraph(int size);
void printMatrix(const Matrix& graph);
AdjacencyList makeAdjacencyList(const Matrix& graph);
void printAdjacencyList(const AdjacencyList& graph);
std::vector<int> bfsMatrix(const Matrix& graph);
std::vector<int> bfsList(const AdjacencyList& graph);
std::vector<int> bfsLinkedQueue(const Matrix& graph);
void printOrder(const std::vector<int>& order);
void compareTime();

#endif
