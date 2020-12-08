/*util.cpp*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <string>
#include <fstream>
#include <limits>

#include "graph.h"
#include "util.h"
#include "minqueue.h"

using namespace std;


//
// DFS:
//
// Performs a depth-first search from the given starting vertex.  
// Returns the vertices in the order they were visited; startV will
// be first.
//
vector<char> DFS(graph& g, char startV)
{
  vector<char>  visited;            // trace the path of visiting the graph       
  stack<char>   frontierStack;      // stack for graph
  set<char>     visitedSet;         // stores the vertices already visited

  frontierStack.push(startV);
  visitedSet.insert(startV);
  
  while(!frontierStack.empty())
  {
     char currentV = frontierStack.top();  // pops the top of the stack
     frontierStack.pop();
     visited.push_back(currentV);          // updates the path
    if(visitedSet.find(currentV) == visitedSet.end())
    {
        visitedSet.insert(currentV);       // update the visited set
    }
     vector<char> neighbors = g.neighbors(currentV); // stores neighbors of the current vertex
     for(size_t i = 0; i < neighbors.size(); i++)
     {
        if(visitedSet.find(neighbors[i]) == visitedSet.end()) // if not visited before
        {
           frontierStack.push(neighbors[i]);    // update stack
           visitedSet.insert(neighbors[i]);     // update set
        }
     }
  }
// 	return tha visited path
  return visited;
}


//
// buildGraph:
//
// Inputs the graph vertices and edges from the given file, building
// the graph g.  File format:
//   vertex vertex vertex ... #
//   src dest weight ... #
//
void buildGraph(string filename, graph& g)
{
  ifstream file(filename);
  char     v;

  if (!file.good())
  {
    cout << endl;
    cout << "**Error: unable to open input file '" << filename << "'." << endl;
    cout << endl;
    return;
  }

  //
  // Input vertices as single uppercase letters:  A B C ... #
  //
  file >> v;

  while (v != '#')
  {
    g.addvertex(v);

    file >> v;
  }

  //
  // Now input edges:  Src Dest Weight ... #
  //
  char src, dest;
  int  weight;

  file >> src;

  while (src != '#')
  {
    file >> dest;
    file >> weight;

    g.addedge(src, dest, weight);

    file >> src;
  }
}

//
// BFS:
//
// Performs a breadth-first search from the given starting vertex.  
// Returns the vertices in the order they were visited; startV will
// be first.
//
vector<char> BFS(graph& g, char startV)
{
  vector<char>  visited;                // trace the path of visiting the graph
  queue<char>   frontierQueue;          // queue for graph
  set<char>     discoveredSet;          // stores the vertices already visited
 
  frontierQueue.push(startV);
  discoveredSet.insert(startV);
  
  while(!frontierQueue.empty())
  {
     char currentV = frontierQueue.front();           // pops the front of the queue
     frontierQueue.pop();
     visited.push_back(currentV);                     // updates the path
     vector<char> neighbors = g.neighbors(currentV);  // neighbors of the current vector
     for(size_t i = 0; i < neighbors.size(); i++)
     {
        if(discoveredSet.find(neighbors[i]) == discoveredSet.end())   // if not discovered earlier
        {
         frontierQueue.push(neighbors[i]);                            // update queue
         discoveredSet.insert(neighbors[i]);                          // update set
        }
     }
  }
  
// 	return tha path
  return visited;      
}

// 
// Dijkstra:
// 
// This is the Dijkstra function which finds the shortest path between two vertices in the graph.
// 

vector<char> Dijkstra(graph& g, char startV, int distArr[], char predArr[])
{
	vector<char> vertices = g.vertices();                   // Stores all the vertices in the tree
	const int Infinity = numeric_limits<int>::max();        // Initialize the distance io Infinity
	minqueue<char, int> unvisitedQueue(vertices.size());                     // stores the vertives of the graph in ascending order
	vector<char> visited;                                   // visited path trace

	// Initialize :- Distance: Infinity, Predecssesor: '0', Queue: (Vertex, Infinity) 
	for(size_t i = 0; i < vertices.size(); i++)
	{
		distArr[vertices[i] - 'A'] = Infinity;
		predArr[vertices[i] - 'A'] = '0';
		unvisitedQueue.pushinorder(vertices[i],Infinity);
	}
	
	distArr[startV - 'A'] = 0;                // Distance from self is zero
	unvisitedQueue.pushinorder(startV,0);     // Push to queue
	
	while(!unvisitedQueue.empty())
	{
// 		Visit vertex with minimum distance from startV
		char currentV = unvisitedQueue.minfront();           // pops front
		unvisitedQueue.minpop();
		if(distArr[currentV-'A'] == Infinity)                // if isolated
			break;
		visited.push_back(currentV);                         // trace path
		vector<char> neighbors = g.neighbors(currentV);      // store neighbors
		for(size_t i = 0; i < neighbors.size(); i++)
		{
			int edgeWeight = g.getweight(currentV, neighbors[i]);                   // weight to neighbors
			int alternativePathDistance = distArr[currentV-'A'] + edgeWeight;       // overall distance
			if(alternativePathDistance < distArr[neighbors[i]-'A'])                 // if finds a better distance
			{
				distArr[neighbors[i]-'A'] = alternativePathDistance;                // update better distance
				predArr[neighbors[i]-'A'] = currentV;                               // update new predecessor
				unvisitedQueue.pushinorder(neighbors[i], alternativePathDistance);  // update the queue
			}
		}
		
		
	}
// 	return the visited path
	return visited;
}













