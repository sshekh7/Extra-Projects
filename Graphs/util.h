/*util.h*/

#pragma once

#include <iostream>
#include <string>

#include "graph.h"


using namespace std;

void buildGraph(string filename, graph& g);
vector<char> DFS(graph& g, char startV);
vector<char> BFS(graph& g, char startV);
vector<char> Dijkstra(graph& g, char startV, int distArr[26], char predArr[26]);