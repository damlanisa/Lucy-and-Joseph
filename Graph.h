//
//  Graph.h
//  dijkstra
//
//  Created by Damla Nisa Cevik on 12.04.2020.
//  Copyright © 2020 Damla Nisa Cevik. All rights reserved.
//

#ifndef Graph_h
#define Graph_h

#include <iostream>
#include <fstream>
#include <sstream>
#include "Paths.h"
using namespace std;

class Graph {
public:
    int **adjacencyMatrix;
    int **alternativeAdjacencyMatrix;
    int numberOfVertices;
    int josephsHotel;
    int lucysHotel;
    int josephsDestination;
    int lucysDestination;
    Paths paths;
    
    Graph(int numberOfVerticies) {
        this->numberOfVertices = numberOfVerticies;
        adjacencyMatrix = new int*[numberOfVerticies];
        alternativeAdjacencyMatrix = new int*[numberOfVerticies];
        for (int i = 0; i < numberOfVerticies; i++) {
            adjacencyMatrix[i] = new int[numberOfVerticies];
            alternativeAdjacencyMatrix[i] = new int[numberOfVerticies];
            for (int j = 0; j < numberOfVerticies; j++) {
                adjacencyMatrix[i][j] = 0;
                alternativeAdjacencyMatrix[i][j] = 0;
            }
        }
    }
    
    void addEdge(int, int, int);
    void startTravel();
    void dijkstra(char, bool);
    void alternativeDijkstra(char, bool);
    int minimumDistance(vector<int>&, vector<bool>&);
    int isThereIntersection(bool, char, bool, bool);
    bool isThereAlternativePath(int, bool, char);
    void printSolution();
};

#endif /* Graph_h */
