/*main.cpp*/

//
// Program to input a graph from an input file, output to console, and then
// input starting vertex from user and run DFS algorithm.
//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Fall 2019
//

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <fstream>
#include <stack>
#include "graph.h"
#include "util.h"

using namespace std;


//
// outputGraph:
//
// Outputs graph g to the console.
//
void outputGraph(graph& g)
{
  vector<char> vertices = g.vertices();

  cout << "**Vertices: ";

  for (char c : vertices)
  {
    cout << c << " ";
  }

  cout << endl;

  cout << "**Edges: ";

  for (char v : vertices)
  {
    vector<char> neighbors = g.neighbors(v);

    for (char n : neighbors)
    {
      int weight = g.getweight(v, n);
      cout << "(" << v << "," << n << "," << weight << ") ";
    }
  }

  cout << endl;
}

// Prints the elements of a vector
void printOutput(vector<char> outputVector)
{
	for(size_t i = 0; i < outputVector.size(); i++)
	{
		cout << outputVector[i] << " ";
	}
	
	cout << endl;
}

// _recOutput:
// 
// Displays the predecessors recursively.
// 
void _recOutput(char vertex, char predArr[])
{
	if(vertex == '0')
		return;
	_recOutput(predArr[vertex - 'A'], predArr); // recursively calls itself
	cout << vertex << " ";
}

// 
// displayDijkstraOutput:
// 
// Displays the shortest distance from specified vertex to all the 
// vertices in the graph.
// 
void displayDijkstraOutput(const vector<char>& visited, int distArr[], char predArr[])
{
	for(size_t i = 0; i < visited.size(); i++)
	{
		cout << " " << visited[i] << ": " << distArr[visited[i] - 'A'] << " via ";
		_recOutput(visited[i], predArr);
		cout << endl;
	}
}


int main()
{
  graph  g;
  string filename;
  char   startV;

  cout << "Enter filename containing graph data> ";
  cin >> filename;

  //
  // Let's input the graph, and then output to see what we have:
  //
  buildGraph(filename, g);
  outputGraph(g);

  //
  // now ask user for a starting vertex, and run BFS as well as
  // strongly-connected algorithms:
  //
  cout << endl;
  cout << "Enter a starting vertex or #> ";
  cin >> startV;

  while (startV != '#')
  {
    vector<char> visited;
	int distArr[26];
	char predArr[26];
    //
    // DFS:
    //
    if (g.isvertex(startV))
    {
		visited = g.neighbors(startV);                       // gets the neighbors of the specified vertex.
		cout << "Neighbors: ";
		printOutput(visited);
		visited = BFS(g, startV);                            // traces the path by BFS algorithm.
		cout << "BFS: ";
		printOutput(visited);
		visited = DFS(g, startV);                            // traces the path by DFS algorithm.
		cout << "DFS: ";
		printOutput(visited);
		visited = Dijkstra(g, startV, distArr, predArr);     // traces the path by the Dijkstra algorithm.
		cout << "Dijkstra: ";
		printOutput(visited);
		displayDijkstraOutput(visited, distArr, predArr);    // displays the output of Dijkstra algorithm.
//         cout << predArr[1] << endl;
		cout << endl;
    }
    else
    {
      cout << "This is not a valid start vertex" << endl;
    }

    cout << endl;
    cout << "Enter a starting vertex or #> ";
    cin >> startV;
  }

  //
  // done:
  //
  return 0;
}
