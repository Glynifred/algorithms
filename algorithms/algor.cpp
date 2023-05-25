#include "algor.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
	//gets the starting node and converts a lower case to upper
	cout << "please input starting node" << endl;
	cin >> startchar;
	startchar = toupper(startchar);
	//makes sure the letter falls within the available nodes
	if (int(startchar) - 65 < 0 || int(startchar) - 65 > 7)
	{
		cout << "node does not exist" << endl;
		//stops program if the node doesnt exist
		return 0;
	}
	//same as start node but gets the ending node
	cout << "please input ending node" << endl;
	cin >> endchar;
	endchar = toupper(endchar);
	if (int(endchar) - 65 < 0 || int(endchar) - 65 > 7)
	{
		cout << "node does not exist" << endl;
		return 0;
	}
	//converts the start char to a string
	tempstring = startchar;
	pathway.push_back(tempstring);
	//runs the first algorithm to find the path with least nodes
	leastnode();
	//resets data ready for second algorithm
	pos1.clear();
	pos2.clear();
	pathway.clear();
	found = false;
	tempstring = startchar;
	pathway.push_back(tempstring);
	//sets a original distance of 0 so it matches pathways
	dist.push_back(0);
	//launches second algorithm to find the path with the shortest distance
	leastdist();
	return 0;
}


void leastnode()
{	//output to show what its displaying
	cout << "path with fewest nodes to go from " << startchar << " to " << endchar << endl;
	//loops for the amount of path the first node connects too 
	for (int i = 0; i < node[int(startchar) - 65].path.size(); i++)
	{	//adds the char of path i to a string stored in pathway
		pathway.push_back(pathway[0] + node[int(startchar) - 65].path[i]);
		//saves the position of the pathway to iterate back to in the next layer
		pos1.push_back(pathway.size() - 1);
		//checks if the char matches the end char
		if (node[int(startchar) - 65].path[i] == endchar)
		{	
			found = true;
			//outputs the correct path
			cout << pathway[pathway.size() - 1] << endl;
		}
	}
	//loops until a layer with a correct path is found
	while (found == false)
	{	//loops for all previous paths found
		for (int i = 0; i < pos1.size(); i++)
		{	//gets the last char from the pathway at the looped position
			tempchar = pathway[pos1[i]].at(pathway[pos1[i]].size() - 1);
			//uses the char to access that nodes data and loops for the amount of paths connected
			for (int j = 0; j < node[int(tempchar) - 65].path.size(); j++)
			{	//creates a pathway using the pathway at pos1 appended with the char of available path from the node
				pathway.push_back(pathway[pos1[i]] + node[int(tempchar) - 65].path[j]);
				//saves the position of the pathway to iterate back to in the next layer
				pos2.push_back(pathway.size() - 1);
				//checks if the char matches the end char
				if (node[int(tempchar) - 65].path[j] == endchar)
				{//sets found to true so the next layer wont be checked
					found = true;
					//outputs the correct path
					cout << pathway[pathway.size() - 1] << endl;
				}
			}
		}
		//resets pos 1 to be used again
		pos1.clear();
		//checks if found after completing each layer so all results of same length are outputted
		if (found == false)
		{//same as loop above but uses pos 2 as previous position and saves into pos 1
			for (int i = 0; i < pos2.size(); i++)
			{
				tempchar = pathway[pos2[i]].at(pathway[pos2[i]].size() - 1);

				for (int j = 0; j < node[int(tempchar) - 65].path.size(); j++)
				{
					pathway.push_back(pathway[pos2[i]] + node[int(tempchar) - 65].path[j]);
					pos1.push_back(pathway.size() - 1);
					if (node[int(tempchar) - 65].path[j] == endchar)
					{
						found = true;
						cout << pathway[pathway.size() - 1] << endl;
					}
				}
			}
		}
		//clears pos 2 for alter use
		pos2.clear();
	}
}


void leastdist()
{			//output to show what its displaying
		cout << "shortest distance to go from " << startchar << " to " << endchar << endl;
		//sets found to true at start of layer and should a path that could lead to a shorter path be found will set to false
		found = true;
		//loops for all available paths from original node
		for (int i = 0; i < node[int(startchar) - 65].path.size(); i++)
		{
			//makes new pathway with previous pathway + the char of available paths
			pathway.push_back(pathway[0] + node[int(startchar) - 65].path[i]);
			//gets distance of previous pathway and adds the distance of the new path
			dist.push_back(dist[0] + node[int(startchar) - 65].distance[i]);
			//saves the position of the pathway to iterate back to in the next layer
			pos1.push_back(pathway.size() - 1);
			//checks if the char is the same as the end char
			if (node[int(startchar) - 65].path[i] == endchar)
			{
				//looks if a correct path is shorter or the same as the current shortest path or that a path hasnt yet been found
				if (dist[pathway.size() - 1] <= shortdist || shortdist == 0)
				{	//checks if the path is the shorter than current shortest
					if (dist[pathway.size() - 1] < shortdist || shortdist == 0)
					{
						//overwrites the current shortest distance with the new one
						shortdist = dist[pathway.size() - 1];
						//overwrites the shortest position
						posshort.clear();
						//adds the position of the path to be outputted once confident its the shortest distance
						posshort.push_back(pathway.size() - 1);
					}
					//triggered if distances matches and adds both to be outputted
					else {
						//adds the position of the path to be outputted once confident its the shortest distance
						posshort.push_back(pathway.size() - 1);
						
					}
					
					
				}	
			}
			//sets found to false if no path or a shorter path was found in the layer
			if (dist[pathway.size() - 1] <= shortdist || shortdist == 0)
			{
				found = false;
			}
		}
		//loops until a path is found and a full layer exists that all paths are longer than the current shortest
		while (found == false)
		{	//sets flag to true so if no shorter path is found loop stops
			found = true;
			//loops for all previous pathways
			for (int i = 0; i < pos1.size(); i++)
			{	//gets the last char from the pathway at the looped position
				tempchar = pathway[pos1[i]].at(pathway[pos1[i]].size() - 1);
				//uses the char to access that nodes data and loops for the amount of paths connected
				for (int j = 0; j < node[int(tempchar) - 65].path.size(); j++)
				{	//makes new pathway with previous pathway + the char of available paths
					pathway.push_back(pathway[pos1[i]] + node[int(tempchar) - 65].path[j]);
					//gets distance of previous pathway and adds the distance of the new path
					dist.push_back(dist[pos1[i]] + node[int(tempchar) - 65].distance[j]);
					//saves the position of the pathway to iterate back to in the next layer
					pos2.push_back(pathway.size() - 1);
					//checks if the char is the same as the end char
					if (node[int(tempchar) - 65].path[j] == endchar)

					{	//looks if a correct path is shorter or the same as the current shortest path or that a path hasnt yet been found
						if (dist[pathway.size() - 1] <= shortdist || shortdist == 0)
						{	//checks if the path is the shorter than current shortest
							if (dist[pathway.size() - 1] < shortdist || shortdist == 0)
							{
								//overwrites the current shortest distance with the new one
								shortdist = dist[pathway.size() - 1];
								//overwrites the shortest position
								posshort.clear();
								//adds the position of the path to be outputted once confident its the shortest distance
								posshort.push_back(pathway.size() - 1);
							}
							//triggered if distances matches and adds both to be outputted
							else {
								//adds the position of the path to be outputted once confident its the shortest distance
								posshort.push_back(pathway.size() - 1);

							}


						}
					}
					//sets found to false if no path or a shorter path was found in the layer
					if (dist[pathway.size() - 1] <= shortdist || shortdist == 0)
					{
						found = false;
					}
				}
			}
			//resets pos 1 for resuse
			pos1.clear();
			//triggers only if a shorter path was found
			if (found == false)
			{
				//same as above but uses pos2 as location and pos1 to save for next cycle
				found = true;
				for (int i = 0; i < pos2.size(); i++)
				{
					tempchar = pathway[pos2[i]].at(pathway[pos2[i]].size() - 1);

					for (int j = 0; j < node[int(tempchar) - 65].path.size(); j++)
					{
						pathway.push_back(pathway[pos2[i]] + node[int(tempchar) - 65].path[j]);
						dist.push_back(dist[pos2[i]] + node[int(tempchar) - 65].distance[j]);
						pos1.push_back(pathway.size() - 1);
						if (node[int(tempchar) - 65].path[j] == endchar)
						{
							if (node[int(tempchar) - 65].path[j] == endchar)
							{
								if (dist[pathway.size() - 1] <= shortdist || shortdist == 0)
								{
									if (dist[pathway.size() - 1] < shortdist || shortdist == 0)
									{
										posshort.clear();
										shortdist = dist[pathway.size() - 1];
										posshort.push_back(pathway.size() - 1);
									}
									else {
										posshort.push_back(pathway.size() - 1);
									}
								}
							}
						}
						if (dist[pathway.size() - 1] <= shortdist || shortdist == 0)
						{
							found = false;
						}
					}
				}
			}
			pos2.clear();
		}
		for (int i = 0; i < posshort.size(); i++)
		{
			cout << pathway[posshort[i]] << " " << dist[posshort[i]] << endl;
		}
}