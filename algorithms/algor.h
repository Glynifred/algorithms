#pragma once
#include <vector>
#include <string>
using namespace std;


//stucture for each node that holds what it connects to and the distance
struct nodes
{
	vector<char> path;
	vector<int> distance;
};
//loading in the sample data for each node in alphabeticale order
vector<nodes> node = {
{ {'B','D','G','H'},{10,12,11,4} },
{ {'A','D','H'},{10,8,20} },
{ {'D','E','G','H'},{17,8,13,10} },
{ {'A','B','C','F','G','H'},{12,8,17,16,24,14}},
{ {'C','F','G','H'},{8,8,11,5} },
{ {'D','E','G','H'},{16,8,18,21} },
{ {'A','C','D','E','F','H'},{11,13,24,11,18,30}},
{ {'A','B','C','D','E','F','G'},{4,20,10,14,5,21,30}} 
};
//vectors to save the position previous layer nodes to go back to
vector<int> pos1;
vector<int> pos2;
//int to store the current shortest path
int shortdist;
//saves the position of the shortest distance
vector<int> posshort;
//vector of strings that i add chars too
vector<string> pathway;
//vector which holds the distance of pathways
vector<int>dist;
//temp string to avoid a char to string error
string tempstring;
//saves a char to be used later
char tempchar;
//captures the starting node
char startchar;
//captures the ending node
char endchar;
//flag used to track if the algorithm should stop
bool found = false;
//function to split up the two algorithms
void leastnode();
void leastdist();
