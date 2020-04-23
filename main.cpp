// Student Name: Damla Nisa CEVIK
// Student ID: 150170712

#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
#include <vector>
#include "Graph.h"
using namespace std;


void Graph::addEdge(int firstNode, int secondNode, int weight) {
    adjacencyMatrix[firstNode][secondNode] = weight;
    alternativeAdjacencyMatrix[firstNode][secondNode] = weight;
}


int Graph::minimumDistance(vector<int> &distance, vector<bool> &visited) {
    int minimumDistance = INT_MAX;
    int index = -1;
    
    for (int i = 0; i < numberOfVertices; i++)
        if (visited[i] == false && distance[i] < minimumDistance) {
            minimumDistance = distance [i];
            index = i;
        }
    
    return index;
}


void Graph::dijkstra(char person, bool hotelToDestination) {
    vector<bool> visited;
    vector<int> distance;
    int parent[numberOfVertices];
    int startNode;
    
    for (int i = 0; i < numberOfVertices; i++) {
        visited.push_back(false);
        distance.push_back(INT_MAX);
        parent[i] = -1;
    }
    
    if (person == 'j' && hotelToDestination == true) startNode = josephsHotel;
        
    else if (person == 'j' && hotelToDestination == false) startNode = josephsDestination;
    
    else if (person == 'l' && hotelToDestination == true) startNode = lucysHotel;

    else startNode = lucysDestination;
    
    distance[startNode] = 0;
        
    for (int i = 0; i < numberOfVertices; i++) {
        int minimumDistanceIndex = minimumDistance(distance, visited);
        visited[startNode] = true;
        visited[minimumDistanceIndex] = true;
        
        for (int j = 0; j < numberOfVertices; j++)
            if (!visited[j] && adjacencyMatrix[minimumDistanceIndex][j] && distance[minimumDistanceIndex] != INT_MAX
                && distance[minimumDistanceIndex] + adjacencyMatrix[minimumDistanceIndex][j] < distance[j]){
                parent[j] = minimumDistanceIndex;
                distance[j] = distance[minimumDistanceIndex] + adjacencyMatrix[minimumDistanceIndex][j];
        }
    }
    
    if (person == 'j' && hotelToDestination == true) {
        int currentNode = josephsDestination;
        while (parent[currentNode] != -1) {
            paths.josephsHotelToDestination.insert(paths.josephsHotelToDestination.begin(), currentNode);
            currentNode = parent[currentNode];
        }
        paths.josephsHotelToDestination.insert(paths.josephsHotelToDestination.begin(), currentNode);
        paths.josephsHotelToDestinationTime.push_back(0);
        for (unsigned long i = 1; i < paths.josephsHotelToDestination.size(); i++)
            paths.josephsHotelToDestinationTime.push_back(paths.josephsHotelToDestinationTime[i-1] + adjacencyMatrix[paths.josephsHotelToDestination[i-1]][paths.josephsHotelToDestination[i]]);
    }
    
    else if (person == 'j' && hotelToDestination == false) {
        int currentNode = josephsHotel;
        while (parent[currentNode] != -1) {
            paths.josephsDestinationToHotel.insert(paths.josephsDestinationToHotel.begin(), currentNode);
            currentNode = parent[currentNode];
        }
        paths.josephsDestinationToHotel.insert(paths.josephsDestinationToHotel.begin(), currentNode);
        paths.josephsDestinationToHotelTime.push_back(paths.josephsHotelToDestinationTime[paths.josephsHotelToDestinationTime.size() - 1] + 30);
        for (unsigned long i = 1; i < paths.josephsDestinationToHotel.size(); i++)
            paths.josephsDestinationToHotelTime.push_back(paths.josephsDestinationToHotelTime[i-1] + adjacencyMatrix[paths.josephsDestinationToHotel[i-1]][paths.josephsDestinationToHotel[i]]);
    }
    
    else if (person == 'l' && hotelToDestination == true) {
           int currentNode = lucysDestination;
           while (parent[currentNode] != -1) {
               paths.lucysHotelToDestination.insert(paths.lucysHotelToDestination.begin(), currentNode);
               currentNode = parent[currentNode];
           }
           paths.lucysHotelToDestination.insert(paths.lucysHotelToDestination.begin(), currentNode);
           paths.lucysHotelToDestinationTime.push_back(0);
           for (unsigned long i = 1; i < paths.lucysHotelToDestination.size(); i++)
               paths.lucysHotelToDestinationTime.push_back(paths.lucysHotelToDestinationTime[i-1] + adjacencyMatrix[paths.lucysHotelToDestination[i-1]][paths.lucysHotelToDestination[i]]);
    }
    
    else {
        int currentNode = lucysHotel;
        while (parent[currentNode] != -1) {
            paths.lucysDestinationToHotel.insert(paths.lucysDestinationToHotel.begin(), currentNode);
            currentNode = parent[currentNode];
        }
        paths.lucysDestinationToHotel.insert(paths.lucysDestinationToHotel.begin(), currentNode);
        paths.lucysDestinationToHotelTime.push_back(paths.lucysHotelToDestinationTime[paths.lucysHotelToDestinationTime.size() - 1] + 30);
        for (unsigned long i = 1; i < paths.lucysDestinationToHotel.size(); i++)
            paths.lucysDestinationToHotelTime.push_back(paths.lucysDestinationToHotelTime[i-1] + adjacencyMatrix[paths.lucysDestinationToHotel[i-1]][paths.lucysDestinationToHotel[i]]);
    }
}


void Graph::alternativeDijkstra(char person, bool hotelToDestination) {
    vector<bool> visited;
    vector<int> distance;
    int parent[numberOfVertices];
    int startNode;
    
    for (int i = 0; i < numberOfVertices; i++) {
        visited.push_back(false);
        distance.push_back(INT_MAX);
        parent[i] = -1;
    }
    
    if (person == 'j' && hotelToDestination == true) startNode = josephsHotel;
        
    else if (person == 'j' && hotelToDestination == false) startNode = josephsDestination;
    
    else if (person == 'l' && hotelToDestination == true) startNode = lucysHotel;

    else startNode = lucysDestination;
    
    distance[startNode] = 0;
        
    for (int i = 0; i < numberOfVertices; i++) {
        int minimumDistanceIndex = minimumDistance(distance, visited);
        if (minimumDistanceIndex == -1) return;
        visited[startNode] = true;
        visited[minimumDistanceIndex] = true;
        
        for (int j = 0; j < numberOfVertices; j++)
            if (!visited[j] && alternativeAdjacencyMatrix[minimumDistanceIndex][j] && distance[minimumDistanceIndex] != INT_MAX && alternativeAdjacencyMatrix[minimumDistanceIndex][j] < INT_MAX && distance[minimumDistanceIndex] + alternativeAdjacencyMatrix[minimumDistanceIndex][j] < distance[j]){
                parent[j] = minimumDistanceIndex;
                distance[j] = distance[minimumDistanceIndex] + alternativeAdjacencyMatrix[minimumDistanceIndex][j];
        }
    }
    
    if (person == 'j' && hotelToDestination == true) {
        int currentNode = josephsDestination;
        while (parent[currentNode] != -1) {
            paths.alternativeJosephsHotelToDestination.insert(paths.alternativeJosephsHotelToDestination.begin(), currentNode);
            currentNode = parent[currentNode];
        }
        paths.alternativeJosephsHotelToDestination.insert(paths.alternativeJosephsHotelToDestination.begin(), currentNode);
        paths.alternativeJosephsHotelToDestinationTime.push_back(0);
        for (unsigned long i = 1; i < paths.alternativeJosephsHotelToDestination.size(); i++)
            paths.alternativeJosephsHotelToDestinationTime.push_back(paths.alternativeJosephsHotelToDestinationTime[i-1] + alternativeAdjacencyMatrix[paths.alternativeJosephsHotelToDestination[i-1]][paths.alternativeJosephsHotelToDestination[i]]);
    }
    
    else if (person == 'j' && hotelToDestination == false) {
        int currentNode = josephsHotel;
        while (parent[currentNode] != -1) {
            paths.alternativeJosephsDestinationToHotel.insert(paths.alternativeJosephsDestinationToHotel.begin(), currentNode);
            currentNode = parent[currentNode];
        }
        paths.alternativeJosephsDestinationToHotel.insert(paths.alternativeJosephsDestinationToHotel.begin(), currentNode);
        paths.alternativeJosephsDestinationToHotelTime.push_back(paths.josephsHotelToDestinationTime[paths.josephsHotelToDestinationTime.size() - 1] + 30);
        for (unsigned long i = 1; i < paths.alternativeJosephsDestinationToHotel.size(); i++)
            paths.alternativeJosephsDestinationToHotelTime.push_back(paths.alternativeJosephsDestinationToHotelTime[i-1] + alternativeAdjacencyMatrix[paths.alternativeJosephsDestinationToHotel[i-1]][paths.alternativeJosephsDestinationToHotel[i]]);
    }
    
    else if (person == 'l' && hotelToDestination == true) {
           int currentNode = lucysDestination;
           while (parent[currentNode] != -1) {
               paths.alternativeLucysHotelToDestination.insert(paths.alternativeLucysHotelToDestination.begin(), currentNode);
               currentNode = parent[currentNode];
           }
           paths.alternativeLucysHotelToDestination.insert(paths.alternativeLucysHotelToDestination.begin(), currentNode);
           paths.alternativeLucysHotelToDestinationTime.push_back(0);
           for (unsigned long i = 1; i < paths.alternativeLucysHotelToDestination.size(); i++)
               paths.alternativeLucysHotelToDestinationTime.push_back(paths.alternativeLucysHotelToDestinationTime[i-1] + alternativeAdjacencyMatrix[paths.alternativeLucysHotelToDestination[i-1]][paths.alternativeLucysHotelToDestination[i]]);
    }
    
    else {
        int currentNode = lucysHotel;
        while (parent[currentNode] != -1) {
            paths.alternativeLucysDestinationToHotel.insert(paths.alternativeLucysDestinationToHotel.begin(), currentNode);
            currentNode = parent[currentNode];
        }
        paths.alternativeLucysDestinationToHotel.insert(paths.alternativeLucysDestinationToHotel.begin(), currentNode);
        paths.alternativeLucysDestinationToHotelTime.push_back(paths.lucysHotelToDestinationTime[paths.lucysDestinationToHotelTime.size() - 1] + 30);
        for (unsigned long i = 1; i < paths.alternativeLucysDestinationToHotel.size(); i++)
            paths.alternativeLucysDestinationToHotelTime.push_back(paths.alternativeLucysDestinationToHotelTime[i-1] + alternativeAdjacencyMatrix[paths.alternativeLucysDestinationToHotel[i-1]][paths.alternativeLucysDestinationToHotel[i]]);
    }
}


int Graph::isThereIntersection(bool hotelToDestination, char lucyIndexOrJosephIndex, bool isJosephAlternative, bool isLucyAlternative) {
    if (isJosephAlternative && isLucyAlternative) {
        if (hotelToDestination) {
            for (unsigned long i = 0; i < paths.alternativeJosephsHotelToDestination.size(); i++)
                for (unsigned long j = 0; j < paths.alternativeLucysHotelToDestination.size(); j++) {
                    if (paths.alternativeJosephsHotelToDestination[i] == paths.alternativeLucysHotelToDestination[j]) {
                        if (paths.alternativeJosephsHotelToDestinationTime[i] == paths.alternativeLucysHotelToDestinationTime[j]) {
                            if (lucyIndexOrJosephIndex == 'j') return int(i);
                            else return int(j);
                        }
                        else if (j == paths.alternativeLucysHotelToDestinationTime.size() - 1 && paths.alternativeJosephsHotelToDestinationTime[i] > paths.alternativeLucysHotelToDestinationTime[paths.alternativeLucysHotelToDestinationTime.size() - 1] && paths.alternativeJosephsHotelToDestinationTime[i] <= (paths.alternativeLucysHotelToDestinationTime[paths.alternativeLucysHotelToDestinationTime.size() - 1] + 30)) {
                            if (lucyIndexOrJosephIndex == 'j') return int(i);
                            else return int(paths.alternativeLucysHotelToDestinationTime.size() - 1);
                        }
                        else if (i == paths.alternativeJosephsHotelToDestinationTime.size() - 1 && paths.alternativeLucysHotelToDestinationTime[j] > paths.alternativeJosephsHotelToDestinationTime[paths.alternativeJosephsHotelToDestinationTime.size() - 1] && paths.alternativeLucysHotelToDestinationTime[j] <= (paths.alternativeJosephsHotelToDestinationTime[paths.alternativeJosephsHotelToDestinationTime.size() - 1] + 30)) {
                            if (lucyIndexOrJosephIndex == 'j') return int(paths.alternativeJosephsHotelToDestinationTime.size() - 1);
                            else return int(j);
                        }
                    }
                }
            return -1;
        }
        
        else {
            for (unsigned long i = 0; i < paths.alternativeJosephsDestinationToHotel.size(); i++)
                for (unsigned long j = 0; j < paths.alternativeLucysDestinationToHotel.size(); j++) {
                    if (paths.alternativeJosephsDestinationToHotel[i] == paths.alternativeLucysDestinationToHotel[j]) {
                        if (paths.alternativeJosephsDestinationToHotelTime[i] == paths.alternativeLucysDestinationToHotelTime[j]) {
                            if (lucyIndexOrJosephIndex == 'j') return int(i);
                            else return int(j);
                        }
                        else if (j == paths.alternativeLucysDestinationToHotelTime.size() - 1 && paths.alternativeJosephsDestinationToHotelTime[i] > paths.alternativeLucysHotelToDestinationTime[paths.alternativeLucysHotelToDestinationTime.size() - 1] && paths.alternativeJosephsDestinationToHotelTime[i] <= (paths.alternativeLucysHotelToDestinationTime[paths.alternativeLucysHotelToDestinationTime.size() - 1] + 30)) {
                            if (lucyIndexOrJosephIndex == 'j') return int(i);
                            else return 1;
                        }
                        else if (i == paths.alternativeJosephsDestinationToHotelTime.size() - 1 && paths.alternativeLucysDestinationToHotelTime[j] > paths.alternativeJosephsHotelToDestinationTime[paths.alternativeJosephsHotelToDestinationTime.size() - 1] && paths.alternativeLucysDestinationToHotelTime[j] <= (paths.alternativeJosephsHotelToDestinationTime[paths.alternativeJosephsHotelToDestinationTime.size() - 1] + 30)) {
                            if (lucyIndexOrJosephIndex == 'j') return 1;
                            else return int(j);
                        }
                    }
                }
            return -1;
        }
    }
    
    
    else if (isJosephAlternative && !isLucyAlternative) {
        if (hotelToDestination) {
            for (unsigned long i = 0; i < paths.alternativeJosephsHotelToDestination.size(); i++)
                for (unsigned long j = 0; j < paths.lucysHotelToDestination.size(); j++)
                    if (paths.alternativeJosephsHotelToDestination[i] == paths.lucysHotelToDestination[j]) {
                        if (paths.alternativeJosephsHotelToDestinationTime[i] == paths.lucysHotelToDestinationTime[j]) {
                            if (lucyIndexOrJosephIndex == 'j') return int(i);
                            else return int(j);
                        }
                        else if (j == paths.lucysHotelToDestinationTime.size() - 1 && paths.alternativeJosephsHotelToDestinationTime[i] > paths.lucysHotelToDestinationTime[paths.lucysHotelToDestinationTime.size() - 1] && paths.alternativeJosephsHotelToDestinationTime[i] <= (paths.lucysHotelToDestinationTime[paths.lucysHotelToDestinationTime.size() - 1] + 30)) {
                            if (lucyIndexOrJosephIndex == 'j') return int(i);
                            else return int(paths.lucysHotelToDestinationTime.size() - 1);
                        }
                        else if (i == paths.alternativeJosephsHotelToDestinationTime.size() - 1 && paths.lucysHotelToDestinationTime[j] > paths.alternativeJosephsHotelToDestinationTime[paths.alternativeJosephsHotelToDestinationTime.size() - 1] && paths.lucysHotelToDestinationTime[j] <= (paths.alternativeJosephsHotelToDestinationTime[paths.alternativeJosephsHotelToDestinationTime.size() - 1] + 30)) {
                            if (lucyIndexOrJosephIndex == 'j') return int(paths.alternativeJosephsHotelToDestinationTime.size() - 1);
                            else return int(j);
                        }
                    }
            return -1;
        }
        else {
            for (unsigned long i = 0; i < paths.alternativeJosephsDestinationToHotel.size(); i++)
                for (unsigned long j = 0; j < paths.lucysDestinationToHotel.size(); j++)
                    if (paths.alternativeJosephsDestinationToHotel[i] == paths.lucysDestinationToHotel[j]) {
                        if (paths.alternativeJosephsDestinationToHotelTime[i] == paths.lucysDestinationToHotelTime[j]) {
                            if (lucyIndexOrJosephIndex == 'j') return int(i);
                            else return int(j);
                        }
                        else if (j == paths.lucysDestinationToHotelTime.size() - 1 && paths.alternativeJosephsDestinationToHotelTime[i] > paths.lucysHotelToDestinationTime[paths.lucysHotelToDestinationTime.size() - 1] && paths.alternativeJosephsDestinationToHotelTime[i] <= (paths.lucysHotelToDestinationTime[paths.lucysHotelToDestinationTime.size() - 1] + 30)) {
                            if (lucyIndexOrJosephIndex == 'j') return int(i);
                            else return 1;
                        }
                        else if (i == paths.alternativeJosephsDestinationToHotelTime.size() - 1 && paths.lucysDestinationToHotelTime[j] > paths.alternativeJosephsHotelToDestinationTime[paths.alternativeJosephsHotelToDestinationTime.size() - 1] && paths.lucysDestinationToHotelTime[j] <= (paths.alternativeJosephsHotelToDestinationTime[paths.alternativeJosephsHotelToDestinationTime.size() - 1] + 30)) {
                            if (lucyIndexOrJosephIndex == 'j') return 1;
                            else return int(j);
                        }
                    }
            return -1;
        }
    }
    
    
    else if (!isJosephAlternative && isLucyAlternative) {
        if (hotelToDestination) {
            for (unsigned long i = 0; i < paths.josephsHotelToDestination.size(); i++)
                for (unsigned long j = 0; j < paths.alternativeLucysHotelToDestination.size(); j++)
                    if (paths.josephsHotelToDestination[i] == paths.alternativeLucysHotelToDestination[j]) {
                        if (paths.josephsHotelToDestinationTime[i] == paths.alternativeLucysHotelToDestinationTime[j]) {
                            if (lucyIndexOrJosephIndex == 'j') return int(i);
                            else return int(j);
                        }
                        else if (j == paths.alternativeLucysHotelToDestinationTime.size() - 1 && paths.josephsHotelToDestinationTime[i] > paths.alternativeLucysHotelToDestinationTime[paths.alternativeLucysHotelToDestinationTime.size() - 1] && paths.josephsHotelToDestinationTime[i] <= (paths.alternativeLucysHotelToDestinationTime[paths.alternativeLucysHotelToDestinationTime.size() - 1] + 30)) {
                            if (lucyIndexOrJosephIndex == 'j') return int(i);
                            else return int(paths.alternativeLucysHotelToDestinationTime.size() - 1);
                        }
                        else if (i == paths.josephsHotelToDestinationTime.size() - 1 && paths.alternativeLucysHotelToDestinationTime[j] > paths.josephsHotelToDestinationTime[paths.josephsHotelToDestinationTime.size() - 1] && paths.alternativeLucysHotelToDestinationTime[j] <= (paths.josephsHotelToDestinationTime[paths.josephsHotelToDestinationTime.size() - 1] + 30)) {
                            if (lucyIndexOrJosephIndex == 'j') return int(paths.josephsHotelToDestinationTime.size() - 1);
                            else return int(j);
                        }
                    }
            return -1;
        }
        else {
            for (unsigned long i = 0; i < paths.josephsDestinationToHotel.size(); i++)
                for (unsigned long j = 0; j < paths.alternativeLucysDestinationToHotel.size(); j++)
                    if (paths.josephsDestinationToHotel[i] == paths.alternativeLucysDestinationToHotel[j]) {
                        if (paths.josephsDestinationToHotelTime[i] == paths.alternativeLucysDestinationToHotelTime[j]) {
                            if (lucyIndexOrJosephIndex == 'j') return int(i);
                            else return int(j);
                        }
                        else if (j == paths.alternativeLucysDestinationToHotelTime.size() - 1 && paths.josephsDestinationToHotelTime[i] > paths.lucysHotelToDestinationTime[paths.lucysHotelToDestinationTime.size() - 1] && paths.josephsDestinationToHotelTime[i] <= (paths.lucysHotelToDestinationTime[paths.lucysHotelToDestinationTime.size() - 1] + 30)) {
                            if (lucyIndexOrJosephIndex == 'j') return int(i);
                            else return 1;
                        }
                        else if (i == paths.josephsDestinationToHotelTime.size() - 1 && paths.alternativeLucysDestinationToHotelTime[j] > paths.josephsHotelToDestinationTime[paths.josephsHotelToDestinationTime.size() - 1] && paths.alternativeLucysDestinationToHotelTime[j] <= (paths.josephsHotelToDestinationTime[paths.josephsHotelToDestinationTime.size() - 1] + 30)) {
                            if (lucyIndexOrJosephIndex == 'j') return 1;
                            else return int(j);
                        }
                    }
            return -1;
        }
    }
    
    
    else {
        if (hotelToDestination) {
            for (unsigned long i = 0; i < paths.josephsHotelToDestination.size(); i++)
                for (unsigned long j = 0; j < paths.lucysHotelToDestination.size(); j++)
                    if (paths.josephsHotelToDestination[i] == paths.lucysHotelToDestination[j]) {
                        if (paths.josephsHotelToDestinationTime[i] == paths.lucysHotelToDestinationTime[j]) {
                            if (lucyIndexOrJosephIndex == 'j') return int(i);
                            else return int(j);
                        }
                        else if (j == paths.lucysHotelToDestinationTime.size() - 1 && paths.josephsHotelToDestinationTime[i] > paths.lucysHotelToDestinationTime[paths.lucysHotelToDestinationTime.size() - 1] && paths.josephsHotelToDestinationTime[i] <= (paths.lucysHotelToDestinationTime[paths.lucysHotelToDestinationTime.size() - 1] + 30)) {
                            if (lucyIndexOrJosephIndex == 'j') return int(i);
                            else return int(paths.lucysHotelToDestinationTime.size() - 1);
                        }
                        else if (i == paths.josephsHotelToDestinationTime.size() - 1 && paths.lucysHotelToDestinationTime[j] > paths.josephsHotelToDestinationTime[paths.josephsHotelToDestinationTime.size() - 1] && paths.lucysHotelToDestinationTime[j] <= (paths.josephsHotelToDestinationTime[paths.josephsHotelToDestinationTime.size() - 1] + 30)) {
                            if (lucyIndexOrJosephIndex == 'j') return int(paths.josephsHotelToDestinationTime.size() - 1);
                            else return int(j);
                        }
                    }
            return -1;
        }
        else {
            for (unsigned long i = 0; i < paths.josephsDestinationToHotel.size(); i++)
                for (unsigned long j = 0; j < paths.lucysDestinationToHotel.size(); j++)
                    if (paths.josephsDestinationToHotel[i] == paths.lucysDestinationToHotel[j]) {
                        if (paths.josephsDestinationToHotelTime[i] == paths.lucysDestinationToHotelTime[j]) {
                            if (lucyIndexOrJosephIndex == 'j') return int(i); // test1
                            else return int(j);
                        }
                        else if (j == 0 && paths.josephsDestinationToHotelTime[i] > paths.lucysHotelToDestinationTime[paths.lucysHotelToDestinationTime.size() - 1] && paths.josephsDestinationToHotelTime[i] <= (paths.lucysHotelToDestinationTime[paths.lucysHotelToDestinationTime.size() - 1] + 30)) {
                            if (lucyIndexOrJosephIndex == 'j') return int(i);
                            else return 1;
                        }
                        else if (i == 0 && paths.lucysDestinationToHotelTime[j] > paths.josephsHotelToDestinationTime[paths.josephsHotelToDestinationTime.size() - 1] && paths.lucysDestinationToHotelTime[j] <= (paths.josephsHotelToDestinationTime[paths.josephsHotelToDestinationTime.size() - 1] + 30)) {
                            if (lucyIndexOrJosephIndex == 'j') return 1;
                            else return int(j);
                        }
                    }
            return -1;
        }
    }
}


bool Graph::isThereAlternativePath(int intersectionIndex, bool hotelToDestination, char lucyIndexOrJosephIndex) {
    if (hotelToDestination) {
        alternativeAdjacencyMatrix[paths.lucysHotelToDestination[intersectionIndex - 1]][paths.lucysHotelToDestination[intersectionIndex]] = INT_MAX;
        this->alternativeDijkstra('l', true);
        alternativeAdjacencyMatrix[paths.lucysHotelToDestination[intersectionIndex - 1]][paths.lucysHotelToDestination[intersectionIndex]] = adjacencyMatrix[paths.lucysHotelToDestination[intersectionIndex - 1]][paths.lucysHotelToDestination[intersectionIndex]];
        int newIntersectionIndex = isThereIntersection(true, 'j', false, false);
        alternativeAdjacencyMatrix[paths.josephsHotelToDestination[newIntersectionIndex - 1]][paths.josephsHotelToDestination[newIntersectionIndex]] = INT_MAX;
        this->alternativeDijkstra('j', true);

        if (paths.alternativeLucysHotelToDestination.empty()) {
            if (paths.alternativeJosephsHotelToDestination.empty()) return false;
            else {
                if (isThereIntersection(true, 'j', true, false) == -1) {
                    paths.josephsDestinationToHotelTime[0] = paths.alternativeJosephsHotelToDestinationTime[paths.alternativeJosephsHotelToDestinationTime.size() - 1] + 30;
                    for (int i = 1; i < paths.josephsDestinationToHotel.size(); i++)
                        paths.josephsDestinationToHotelTime[i] = paths.josephsDestinationToHotelTime[i-1] + alternativeAdjacencyMatrix[i-1][i];
                    return true;
                }
                else return false;
            }
        }
        
        else {
            if (isThereIntersection(true, 'l', false, true) != -1) {
                paths.alternativeLucysHotelToDestination.clear();
                if (paths.alternativeJosephsHotelToDestination.empty()) return false;
                paths.josephsDestinationToHotelTime[0] = paths.alternativeJosephsHotelToDestinationTime[paths.alternativeJosephsHotelToDestinationTime.size() - 1] + 30;
                for (int i = 1; i < paths.josephsDestinationToHotelTime.size(); i++)
                    paths.josephsDestinationToHotelTime[i] = paths.josephsDestinationToHotelTime[i-1] + adjacencyMatrix[paths.josephsDestinationToHotel[i-1]][paths.josephsDestinationToHotel[i]];
                return true;
            }
            
            else if (paths.alternativeJosephsHotelToDestination.empty()){
                paths.josephsDestinationToHotelTime[0] = paths.alternativeJosephsHotelToDestinationTime[paths.alternativeJosephsHotelToDestinationTime.size() - 1] + 30;
                for (int i = 1; i < paths.josephsDestinationToHotel.size(); i++)
                    paths.josephsDestinationToHotelTime[i] = paths.josephsDestinationToHotelTime[i-1] + alternativeAdjacencyMatrix[paths.josephsDestinationToHotel[i-1]][paths.josephsDestinationToHotel[i]];
                return true;
            }
            
            else {
                if (isThereIntersection(true, 'j', true, false) != -1) {
                    paths.alternativeJosephsHotelToDestination.clear();
                    paths.lucysDestinationToHotelTime[0] = paths.alternativeLucysHotelToDestinationTime[paths.alternativeLucysHotelToDestinationTime.size() - 1] + 30;
                    for (int i = 1; i < paths.lucysDestinationToHotel.size(); i++)
                        paths.lucysDestinationToHotelTime[i] = paths.lucysDestinationToHotelTime[i-1] + alternativeAdjacencyMatrix[paths.lucysDestinationToHotel[i-1]][paths.lucysDestinationToHotel[i]];
                    return true;
                }
                else {
                    int alternativeLucyEfficiency = (paths.alternativeLucysHotelToDestinationTime[paths.alternativeLucysHotelToDestinationTime.size() - 1] + paths.josephsHotelToDestinationTime[paths.josephsHotelToDestinationTime.size() - 1]) / 2;
                    int alternativeJosephEfficiency = (paths.alternativeJosephsHotelToDestinationTime[paths.alternativeJosephsHotelToDestinationTime.size() - 1] + paths.lucysHotelToDestinationTime[paths.lucysHotelToDestinationTime.size() - 1]) / 2;
                    
                    if (alternativeLucyEfficiency <= alternativeJosephEfficiency) { // test2
                        paths.lucysDestinationToHotelTime[0] = paths.alternativeLucysHotelToDestinationTime[paths.alternativeLucysHotelToDestinationTime.size() - 1] + 30;
                        for (int i = 1; i < paths.lucysDestinationToHotel.size(); i++)
                            paths.lucysDestinationToHotelTime[i] = paths.lucysDestinationToHotelTime[i-1] + alternativeAdjacencyMatrix[paths.lucysDestinationToHotel[i-1]][paths.lucysDestinationToHotel[i]];
                        paths.alternativeJosephsHotelToDestination.clear();
                        paths.alternativeJosephsHotelToDestinationTime.clear();
                    }
                    else {
                        paths.josephsDestinationToHotelTime[0] = paths.alternativeJosephsHotelToDestinationTime[paths.alternativeJosephsHotelToDestinationTime.size() - 1] + 30;
                        for (int i = 1; i < paths.josephsDestinationToHotel.size(); i++)
                            paths.josephsDestinationToHotelTime[i] = paths.josephsDestinationToHotelTime[i-1] + alternativeAdjacencyMatrix[paths.josephsDestinationToHotel[i-1]][paths.josephsDestinationToHotel[i]];
                        paths.alternativeLucysHotelToDestination.clear();
                        paths.alternativeLucysHotelToDestinationTime.clear();
                    }
                    return true;
                }
            }
        }
    }
    
    else {
        alternativeAdjacencyMatrix[paths.lucysDestinationToHotel[intersectionIndex - 1]][paths.lucysDestinationToHotel[intersectionIndex]] = INT_MAX;
        this->alternativeDijkstra('l', false);
        alternativeAdjacencyMatrix[paths.lucysDestinationToHotel[intersectionIndex - 1]][paths.lucysDestinationToHotel[intersectionIndex]] = adjacencyMatrix[paths.lucysDestinationToHotel[intersectionIndex - 1]][paths.lucysDestinationToHotel[intersectionIndex]];
        int newIntersectionIndex = isThereIntersection(false, 'j', false, false);
        alternativeAdjacencyMatrix[paths.josephsDestinationToHotel[newIntersectionIndex - 1]][paths.josephsDestinationToHotel[newIntersectionIndex]] = INT_MAX;
        this->alternativeDijkstra('j', false);

        if (paths.alternativeLucysDestinationToHotel.empty()) {
            if (paths.alternativeJosephsDestinationToHotel.empty()) return false;
            else {
                if (isThereIntersection(false, 'j', true, false) == -1) return true;
                else return false;
            }
        }
        else {
            if (isThereIntersection(false, 'l', false, true) != -1) {
                paths.alternativeLucysDestinationToHotel.clear();
                if (paths.alternativeJosephsDestinationToHotel.empty()) return false;
            }
            else if (paths.alternativeJosephsDestinationToHotel.empty()) return true; // test1
            
            else {
                if (isThereIntersection(false, 'j', true, false) != -1) {
                    paths.alternativeJosephsDestinationToHotel.clear();
                    return true;
                }
                else {
                    if (!paths.alternativeLucysHotelToDestination.empty() && paths.alternativeJosephsHotelToDestination.empty()) {
                        paths.josephsDestinationToHotelTime[0] = paths.alternativeJosephsHotelToDestinationTime[paths.alternativeJosephsHotelToDestinationTime.size() - 1] + 30;
                        for (int i = 1; i < paths.josephsDestinationToHotel.size(); i++)
                            paths.josephsDestinationToHotelTime[i] = paths.josephsDestinationToHotelTime[i-1] + alternativeAdjacencyMatrix[paths.josephsDestinationToHotel[i-1]][paths.josephsDestinationToHotel[i]];
                        paths.alternativeLucysDestinationToHotel.clear();
                        paths.alternativeLucysDestinationToHotelTime.clear();
                        return true;
                    }
                    else if (paths.alternativeLucysHotelToDestination.empty() && !paths.alternativeJosephsHotelToDestination.empty()) {
                        paths.lucysDestinationToHotelTime[0] = paths.alternativeLucysHotelToDestinationTime[paths.alternativeLucysHotelToDestinationTime.size() - 1] + 30;
                        for (int i = 1; i < paths.lucysDestinationToHotel.size(); i++)
                            paths.lucysDestinationToHotelTime[i] = paths.lucysDestinationToHotelTime[i-1] + alternativeAdjacencyMatrix[paths.lucysDestinationToHotel[i-1]][paths.lucysDestinationToHotel[i]];
                        paths.alternativeJosephsHotelToDestination.clear();
                        paths.alternativeJosephsHotelToDestinationTime.clear();
                        return true;
                    }
                    else {
                        int alternativeLucyEfficiency = (paths.alternativeLucysDestinationToHotelTime[paths.alternativeLucysDestinationToHotelTime.size() - 1] + paths.josephsDestinationToHotelTime[paths.josephsDestinationToHotelTime.size() - 1]) / 2;
                        int alternativeJosephEfficiency = (paths.alternativeJosephsDestinationToHotelTime[paths.alternativeJosephsDestinationToHotelTime.size() - 1] + paths.lucysDestinationToHotelTime[paths.lucysDestinationToHotelTime.size() - 1]) / 2;
                        
                        if (alternativeLucyEfficiency <= alternativeJosephEfficiency) {
                            paths.lucysDestinationToHotelTime[0] = paths.alternativeLucysHotelToDestinationTime[paths.alternativeLucysHotelToDestinationTime.size() - 1] + 30;
                            for (int i = 1; i < paths.lucysDestinationToHotel.size(); i++)
                                paths.lucysDestinationToHotelTime[i] = paths.lucysDestinationToHotelTime[i-1] + alternativeAdjacencyMatrix[paths.lucysDestinationToHotel[i-1]][paths.lucysDestinationToHotel[i]];
                            paths.alternativeJosephsHotelToDestination.clear();
                            paths.alternativeJosephsHotelToDestinationTime.clear();
                        }
                        else {
                            paths.josephsDestinationToHotelTime[0] = paths.alternativeJosephsHotelToDestinationTime[paths.alternativeJosephsHotelToDestinationTime.size() - 1] + 30;
                            for (int i = 1; i < paths.josephsDestinationToHotel.size(); i++)
                                paths.josephsDestinationToHotelTime[i] = paths.josephsDestinationToHotelTime[i-1] + alternativeAdjacencyMatrix[paths.josephsDestinationToHotel[i-1]][paths.josephsDestinationToHotel[i]];
                            paths.alternativeLucysHotelToDestination.clear();
                            paths.alternativeLucysHotelToDestinationTime.clear();
                        }
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


void Graph::printSolution() {
    if (paths.alternativeJosephsHotelToDestination.empty() && paths.alternativeJosephsDestinationToHotel.empty()) {
        cout << "Joseph's Path, duration: " << paths.josephsDestinationToHotelTime.back() << endl;
        for (int i = 0; i < paths.josephsHotelToDestination.size(); i++) cout << "Node: " << paths.josephsHotelToDestination[i] << " Time: " << paths.josephsHotelToDestinationTime[i] << endl;
        cout << "--return--" << endl;
        for (int i = 0; i < paths.josephsDestinationToHotel.size(); i++) cout << "Node: " << paths.josephsDestinationToHotel[i] << " Time: " << paths.josephsDestinationToHotelTime[i] << endl;
    }
    else if (paths.alternativeJosephsHotelToDestination.empty() && !paths.alternativeJosephsDestinationToHotel.empty()) {
        cout << "Joseph's Path, duration: " << paths.alternativeJosephsDestinationToHotelTime.back() << endl;
        for (int i = 0; i < paths.josephsHotelToDestination.size(); i++) cout << "Node: " << paths.josephsHotelToDestination[i] << " Time: " << paths.josephsHotelToDestinationTime[i] << endl;
        cout << "--return--" << endl;
        for (int i = 0; i < paths.alternativeJosephsDestinationToHotel.size(); i++) cout << "Node: " << paths.alternativeJosephsDestinationToHotel[i] << " Time: " << paths.alternativeJosephsDestinationToHotelTime[i] << endl;
    }
    else if (!paths.alternativeJosephsHotelToDestination.empty() && paths.alternativeJosephsDestinationToHotel.empty()) {
        cout << "Joseph's Path, duration: " << paths.josephsDestinationToHotelTime.back() << endl;
        for (int i = 0; i < paths.alternativeJosephsHotelToDestination.size(); i++) cout << "Node: " << paths.alternativeJosephsHotelToDestination[i] << " Time: " << paths.alternativeJosephsHotelToDestinationTime[i] << endl;
        cout << "--return--" << endl;
        for (int i = 0; i < paths.josephsDestinationToHotel.size(); i++) cout << "Node: " << paths.josephsDestinationToHotel[i] << " Time: " << paths.josephsDestinationToHotelTime[i] << endl;
    }
    else {
        cout << "Joseph's Path, duration: " << paths.alternativeJosephsDestinationToHotelTime.back() << endl;
        for (int i = 0; i < paths.alternativeJosephsHotelToDestination.size(); i++) cout << "Node: " << paths.alternativeJosephsHotelToDestination[i] << " Time: " << paths.alternativeJosephsHotelToDestinationTime[i] << endl;
        cout << "--return--" << endl;
        for (int i = 0; i < paths.alternativeJosephsDestinationToHotel.size(); i++) cout << "Node: " << paths.alternativeJosephsDestinationToHotel[i] << " Time: " << paths.alternativeJosephsDestinationToHotelTime[i] << endl;
    }
    if (paths.alternativeLucysHotelToDestination.empty() && paths.alternativeLucysDestinationToHotel.empty()) {
        cout << "Lucy's Path, duration: " << paths.lucysDestinationToHotelTime.back() << endl;
        for (int i = 0; i < paths.lucysHotelToDestination.size(); i++) cout << "Node: " << paths.lucysHotelToDestination[i] << " Time: " << paths.lucysHotelToDestinationTime[i] << endl;
        cout << "--return--" << endl;
        for (int i = 0; i < paths.lucysDestinationToHotel.size(); i++) cout << "Node: " << paths.lucysDestinationToHotel[i] << " Time: " << paths.lucysDestinationToHotelTime[i] << endl;
    }
    else if (paths.alternativeLucysHotelToDestination.empty() && !paths.alternativeLucysDestinationToHotel.empty()) {
        cout << "Lucy's Path, duration: " << paths.alternativeLucysDestinationToHotelTime.back() << endl;
        for (int i = 0; i < paths.lucysHotelToDestination.size(); i++) cout << "Node: " << paths.lucysHotelToDestination[i] << " Time: " << paths.lucysHotelToDestinationTime[i] << endl;
        cout << "--return--" << endl;
        for (int i = 0; i < paths.alternativeLucysDestinationToHotel.size(); i++) cout << "Node: " << paths.alternativeLucysDestinationToHotel[i] << " Time: " << paths.alternativeLucysDestinationToHotelTime[i] << endl;
    }
    else if (!paths.alternativeLucysHotelToDestination.empty() && paths.alternativeLucysDestinationToHotel.empty()) {
        cout << "Lucy's Path, duration: " << paths.lucysDestinationToHotelTime.back() << endl;
        for (int i = 0; i < paths.alternativeLucysHotelToDestination.size(); i++) cout << "Node: " << paths.alternativeLucysHotelToDestination[i] << " Time: " << paths.alternativeLucysHotelToDestinationTime[i] << endl;
        cout << "--return--" << endl;
        for (int i = 0; i < paths.lucysDestinationToHotel.size(); i++) cout << "Node: " << paths.lucysDestinationToHotel[i] << " Time: " << paths.lucysDestinationToHotelTime[i] << endl;
    }
    else {
        cout << "Lucy's Path, duration: " << paths.alternativeLucysDestinationToHotelTime.back() << endl;
        for (int i = 0; i < paths.alternativeLucysHotelToDestination.size(); i++) cout << "Node: " << paths.alternativeLucysHotelToDestination[i] << " Time: " << paths.alternativeLucysHotelToDestinationTime[i] << endl;
        cout << "--return--" << endl;
        for (int i = 0; i < paths.alternativeLucysDestinationToHotel.size(); i++) cout << "Node: " << paths.alternativeLucysDestinationToHotel[i] << " Time: " << paths.alternativeLucysDestinationToHotelTime[i] << endl;
    }
}


void Graph::startTravel() {
    this->dijkstra('j', true);
    this->dijkstra('l', true);
    this->dijkstra('j', false);
    this->dijkstra('l', false);
    int intersectionIndex = isThereIntersection(true, 'l', false, false);   // check the hotel-destination path instersection
    if (intersectionIndex != -1) {  // there is an intersection in the hotel-destination path
        if (isThereAlternativePath(intersectionIndex, true, 'l')) {
            int newIntersectionIndex = isThereIntersection(false, 'l', false, false);
            if (newIntersectionIndex != -1)
                if (isThereAlternativePath(newIntersectionIndex, false, 'l')) {
                    printSolution();
                    return;
                }
            printSolution();
            return;
        }
    }
    else {  // no intersection in the hotel-destination path
        int intersectionIndex = isThereIntersection(false, 'l', false, false);  // check the destination-hotel path intersection
        if (intersectionIndex != -1) {  // there is an intersection in the destination-hotel path
            if (isThereAlternativePath(intersectionIndex, false, 'l')) {
                printSolution();
                return;
            }
        }
        else {
            printSolution();
            return;
        }
    }
    cout << "No solution!" << endl;
}


void readFile(const char* fileName) {
    ifstream inputFile;
    inputFile.open(fileName);
    Graph* graph;
    
    if(inputFile.is_open() && inputFile.good()){
        string line;
        char delimiter = ' ';
        string token;
        int firstNode = 0;
        int secondNode = 0;
        int weight = 0;
        getline(inputFile, line);
        graph = new Graph(stoi(line));
        getline(inputFile, line);
        stringstream ss(line);
        getline(ss, token, delimiter);
        graph->josephsHotel = stoi(token);
        getline(ss, token, delimiter);
        graph->josephsDestination = stoi(token);
        getline(ss, token, delimiter);
        graph->lucysHotel = stoi(token);
        getline(ss, token, delimiter);
        graph->lucysDestination = stoi(token);
        while(getline(inputFile, line)){
            stringstream ss(line);
            getline(ss, token, delimiter);
            firstNode = stoi(token);
            getline(ss, token, delimiter);
            secondNode = stoi(token);
            getline(ss, token, delimiter);
            weight = stoi(token);
            graph->addEdge(firstNode, secondNode, weight);
        }
    }
    else return;
    
    graph->startTravel();
}


int main(int argc, const char * argv[]) {
    
    if (argc == 2) readFile(argv[1]);
        
    else cout << "Wrong command line arguments!" << endl;
    
    return 0;
}
