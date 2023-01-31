#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<list>
using namespace std;
int** ReadFromFile()
{

	ifstream csv_file;
	csv_file.open("GraphData.csv");
	string line = "";

	int** arr = new int* [25];
	for (int i = 0; i < 25; i++)
	{
		arr[i] = new int[25];
	}

	getline(csv_file, line, '\n');  //take the whole row or line
	for (int i = 0; i < 25; i++)
	{

		getline(csv_file, line, ',');  //take the first word
		for (int j = 0; j < 25; j++)
		{
			if (j == 24)
			{
				getline(csv_file, line, '\n');//for last city terminator is not comma
				arr[i][j] = stoi(line);
			}
			else
			{
				getline(csv_file, line, ',');
				arr[i][j] = stoi(line);
			}
		}
	}
	for (int i = 0; i < 25; i++)
	{
		//cout << cities[i] << " ";
		for (int j = 0; j < 25; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}

	return arr;

}


//=========================NODE CLASS AND ADJACENCY LIST IMPLEMENTATION OF GRAPH============================//
class Node {
	string value;
public:
	list<Node> adjlist;

	Node()
	{
		value = "";
	}

	Node(string src)
	{
		value = src;
	}
	void setNodeid(string src)
	{
		value = src;
	}
	string getNodeid()
	{
		return value;
	}

	list<Node> getadjlist()
	{
		return adjlist;
	}

	void addedgeTolist(string tovertex)
	{
		Node n(tovertex);
		adjlist.push_back(n);

	}

	bool operator==(const Node& n)
	{
		if (value == n.value)
			return true;

	}

	void printadList()
	{
		for (auto i = adjlist.begin(); i != adjlist.end(); i++)
		{
			cout << i->getNodeid() << "-> ";
		}

	}

	/*void deletefromList(string del)
	{
		for (auto i = adjlist.begin(); i != adjlist.end(); i++)
		{
			if (i->getNodeid() == del)
			{
				adjlist.remove(*i);
			}
		}
	}*/
};

class Graph {

	vector<Node> vertices;
public:
	static int count;

	void addNode(string newnode)
	{
		Node n(newnode);
		vertices.push_back(n);
	}

	//void deletefromadjList(Node n, string del)
	//{
	//	for (auto it = n.adjlist.begin(); it != n.adjlist.end(); it++)
	//	{
	//		if ((*it).getNodeid() == del)
	//		{
	//			n.adjlist.erase(it);
	//		}
	//    }
	//}

	//void deleteNode(string dnode)
	//{
	//	for (auto it = vertices.begin(); it != vertices.end(); it++)
	//	{
	//		//(*it).deletefromList(dnode);
	//		(*it).deletefromList(dnode);

	//		if ((*it).getNodeid() == dnode)
	//		{
	//			vertices.erase(it);
	//			break;
	//		}
	//	}
	//}

	void deleteNode(string v) {
		int index;
		for (int i = 0; i < vertices.size(); i++) {
			if (vertices.at(i).getNodeid() == v) {
				index = i;
			}
		}
		for (int i = 0; i < vertices.size(); i++) {
			for (auto it = vertices.at(i).adjlist.begin(); it != vertices.at(i).adjlist.end(); it++) {
				if (it->getNodeid() == v) {
					vertices.at(i).adjlist.erase(it);
					break;
				}
			}

		}
		vertices.erase(vertices.begin() + index);
	}

	void deleteEdge(string city1, string city2)
	{
		for (int i = 0; i < vertices.size(); i++) {
			if (vertices.at(i).getNodeid() == city1) {
				for (auto it = vertices.at(i).adjlist.begin(); it != vertices.at(i).adjlist.end(); it++) {
					if (it->getNodeid() == city2) {
						vertices.at(i).adjlist.erase(it);
						break;
					}
				}
			}
		}
	}

	bool contains(string vertex)
	{
		bool found = false;
		for (int i = 0; i < vertices.size(); i++)
		{
			if (vertices.at(i).getNodeid() == vertex)
			{
				found = true;
				break;
			}

		}

		return found;
	}

	void addEdge(string fromVertex, string toVertex)//called in main to make graph
	{
		if (contains(fromVertex)) {
			Node n(toVertex);
			for (int i = 0; i < vertices.size(); i++)
			{
				if (vertices.at(i).getNodeid() == fromVertex)
				{
					vertices.at(i).adjlist.push_back(n);
					break;
				}

			}
		}
		else {
			Node n(fromVertex);
			n.addedgeTolist(toVertex);
			vertices.push_back(n);
		}
	}

	void addedge(string fromVertex, string toVertex, int weight)
	{
		if (contains(fromVertex)) {
			Node n(toVertex);
			for (int i = 0; i < vertices.size(); i++)
			{
				if (vertices.at(i).getNodeid() == fromVertex)
				{
					vertices.at(i).adjlist.push_back(n);
					break;
				}

			}
		}
		else {
			Node n(fromVertex);
			n.addedgeTolist(toVertex);
			vertices.push_back(n);
		}
	}

	void makeGraphfromMatrix(int** arr)
	{
		string cities[25] = { "Mansehra","Hasan Abdal", "Peshawar","Attock", "Islamabad", "Murree", "Rawat","Balkasar", "Chakwal", "Mianwali", "Bhera", "Sargoda", "Pindi Bhattian", "Jhang", "Faisalabad", "Lahore", "Dina","Gujranwala", "Multan", "DG Khan", "Bahwalpur", "Sukkur", "Quetta", "Khuzdar", "Karachi" };
		
		for (int i = 0; i < 25; i++)
		{
			addNode(cities[i]);

			for (int j = 0; j < 25; j++)
			{
				if (arr[i][j] != 0)
				{
					addEdge(cities[i], cities[j]);
				}
			}
		}
	}

	
	void printGraph() {
		for (int i = 0; i < vertices.size(); i++) {
			Node temp;
			temp = vertices.at(i);
			cout << temp.getNodeid() << ": --> ";
			temp.printadList();
			cout << endl;
		}
	}

	string printsingleLink(string name)
	{
		string singlelink;
		for (int i = 0; i < vertices.size(); i++)
		{
			Node temp;
			temp = vertices.at(i);
			if (temp == name)
			{
				singlelink = temp.getNodeid() + ":";
				//temp.printadList();
				list<Node> adj = temp.getadjlist();
				for (auto i = adj.begin(); i != adj.end(); i++)
				{
					singlelink=singlelink + i->getNodeid()+ "->";
				}

			}
		}
		cout << singlelink;
		return singlelink;
	}
};

//=====================================================================================================
//class Graph {
//public:
//	int** adjMatrix;
//	int numVertices;
//	// Making Array for mapping
//	string cities[25] = { "Mansehra","Hasan Abdal", "Peshawar","Attock", "Islamabad", "Murree", "Rawat","Balkasar", "Chakwal", "Mianwali", "Bhera", "Sargoda", "Pindi Bhattian", "Jhang", "Faisalabad", "Lahore", "Dina","Gujranwala", "Multan", "DG Khan", "Bahwaplur", "Sukkur", "Quetta", "Khuzdar", "Karachi" };
//
//	Graph(int numvertices) //constructor to set size of matrix
//	{
//		numVertices = numvertices;
//
//		adjMatrix = new int* [numVertices];
//		for (int i = 0; i < numVertices; i++) {
//			adjMatrix[i] = new int[numVertices];
//		}
//		
//	}
//
//	Graph(int** arr, int size)
//	{
//		numVertices = size;
//		adjMatrix = new int* [numVertices];
//		for (int i = 0; i < numVertices; i++) {
//			adjMatrix[i] = new int[numVertices];
//		}
//
//		for (int i = 0; i < numVertices; i++)
//		{
//			for (int j = 0; j < numVertices; j++)
//			{
//				adjMatrix[i][j] = arr[i][j];
//			}
//		}
//
//	}
//
//	string* getCities()
//	{
//		return cities;
//	}
//
//	//void addNode(string cityname)
//	//{
//	//	//int size = 25;
//	//	//size++;
//	//	//string* cities = new string[size];
//	//	//for(int i=0; i<size; i++)
//	//	//numVertices++;
//	//	//adjMatrix[numVertices - 1][numVertices - 1] = 0;
//
//	//}
//
//	/*void addNode(string city)
//	{
//		numVertices++;
//	}*/
//
//	//void addEdge(int i, int j, int weight) //marks the edge true in matrix
//	//{
//	//	adjMatrix[i][j] = weight;
//	//	adjMatrix[j][i] = weight;
//	//}
//
//	void removeEdge(int i, int j) //removes the edge at provided position
//	{
//		adjMatrix[i][j] = 0;
//		adjMatrix[j][i] = 0;
//	}
//	bool isEdge(int i, int j) //checks if edge exits or not, then returns
//	{
//		if (adjMatrix[i][j] == true && adjMatrix[j][i] == true) {
//			return true;
//		}
//		else {
//			return false;
//
//		}
//
//	}
//	void printGraph() // prints the matrix
//	{
//		for (int i = 0; i < numVertices; i++) {
//			for (int j = 0; j < numVertices; j++) {
//
//				cout << adjMatrix[i][j] << " ";
//			}
//			cout << endl;
//		}
//
//	}
//
//	string printsingleLink(string cityname)
//	{
//
//	}
//
//};
//
//Graph* addNode(string cityname)
//{
//	Graph* g;
//	g->numVertices = 26;
//	int** arr = ReadFromFile();
//
//	for (int i = 0; i < 26; i++)
//	{
//		for (int j = 0; j < 26; j++)
//		{
//			if (i == 25 || j == 25)
//			{
//				g->adjMatrix[i][j] = 0;
//			}
//			else
//			g->adjMatrix[i][j] = arr[i][j];
//
//		}
//	}
//	string* cy = g->getCities();
//
//
//	//g->adjMatrix[25] = 0;
//
//}
//Graph* addEdge(string city1, string city2, int weight)
//{
//
//}
//
//Graph* deleteNode(string cityname)
//{
//
//}
//
//Graph* deleteEdge(string city1, string city2)
//{
//
//}

void printPath(int currentVertex, int* parents)
{
	string cities[25] = { "Mansehra","Hasan Abdal", "Peshawar","Attock", "Islamabad", "Murree", "Rawat","Balkasar", "Chakwal", "Mianwali", "Bhera", "Sargoda", "Pindi Bhattian", "Jhang", "Faisalabad", "Lahore", "Dina","Gujranwala", "Multan", "DG Khan", "Bahwalpur", "Sukkur", "Quetta", "Khuzdar", "Karachi" };
	// Base case
	if (currentVertex == -1) {
		return;
	}
	printPath(parents[currentVertex], parents);
	cout << cities[currentVertex] << "->";
}

void printfullPath(int currentVertex, int* parents)
{
	string cities[25] = { "Mansehra","Hasan Abdal", "Peshawar","Attock", "Islamabad", "Murree", "Rawat","Balkasar", "Chakwal", "Mianwali", "Bhera", "Sargoda", "Pindi Bhattian", "Jhang", "Faisalabad", "Lahore", "Dina","Gujranwala", "Multan", "DG Khan", "Bahwalpur", "Sukkur", "Quetta", "Khuzdar", "Karachi" };
	// Base case 
	if (currentVertex == -1) {
		return;
	}
	cout << cities[currentVertex] << "->";
	printfullPath(parents[currentVertex], parents);
	
}

void printPair(int currentVertex, int* parents, string& route)
{
	string cities[25] = { "Mansehra","Hasan Abdal", "Peshawar","Attock", "Islamabad", "Murree", "Rawat","Balkasar", "Chakwal", "Mianwali", "Bhera", "Sargoda", "Pindi Bhattian", "Jhang", "Faisalabad", "Lahore", "Dina","Gujranwala", "Multan", "DG Khan", "Bahwalpur", "Sukkur", "Quetta", "Khuzdar", "Karachi" };
	// Base case
	if (currentVertex == -1) {
		return;
	}
	printPair(parents[currentVertex], parents, route);
	route = route + cities[currentVertex] + "->";
}

int extractMin(int* dis, bool* vis)
{
	int minimum = INT_MAX, min_index;

	for (int i = 0; i < 25; i++)
	{
		if (dis[i] <= minimum && vis[i] == false)
		{
			minimum = dis[i];
			min_index = i;
		}
	}

	return min_index;
}

bool isedge(int** arr, int src, int dest)
{
	bool yes = false;
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			if (arr[src][dest] != 0)
			{		yes = true;
			         break;
		    }
		}
	}
	return yes;
}
void shortestPathfromOnetoall(int** graph, string cityname)
{
	string source;
	int source_index=0;
	Graph g;
	g.makeGraphfromMatrix(graph);

	string cities[25] = { "Mansehra","Hasan Abdal", "Peshawar","Attock", "Islamabad", "Murree", "Rawat","Balkasar", "Chakwal", "Mianwali", "Bhera", "Sargoda", "Pindi Bhattian", "Jhang", "Faisalabad", "Lahore", "Dina","Gujranwala", "Multan", "DG Khan", "Bahwalpur", "Sukkur", "Quetta", "Khuzdar", "Karachi" };
	int distances[25];
	bool isVisited[25];
	int paths[25];  //keeps track of parents[paths]

	for (int i = 0; i < 25; i++)
	{
		distances[i] = INT_MAX;
		isVisited[i] = false;
		if (cityname == cities[i])
		{
			source = cities[i];
			source_index = i;
		}
	}
	distances[source_index] = 0;
	paths[source_index] = -1;

	for (int i = 0; i < 25 - 1; i++) //since source is already zero
	{
		int vertex = extractMin(distances, isVisited);
		isVisited[vertex] = true;

		for (int i = 0; i < 25; i++)
		{
			if (isVisited[i] == false && distances[vertex] != INT_MAX)
			{
				if (isedge(graph, vertex, i)) {
					if (distances[vertex] + graph[vertex][i] <= distances[i])
					{
						distances[i] = distances[vertex] + graph[vertex][i];
						paths[i] = vertex;
					}
				}
			}
		}
	}

	for (int i = 0; i < 25; i++)
	{
		/*cout << "Vertex distance from source" << endl;
		cout << i << "     " << distances[i] << "  " << endl;
		*/if (i == 2 || i == 22 || i==23)
		{
			cout << "No path from "<<source<<" to "<<cities[i]<<"\n\n";
		}
		else
		{
			cout << "Shortest path from " << cityname << " to " << cities[i] << " is: " << endl;
		    printPath(i, paths);
		    cout << endl<<endl;
	    }
	}
}


void shortestPathfromalltoone(int** graph, string cityname)
{
	string source;
	int source_index = 0;
	Graph g;
	g.makeGraphfromMatrix(graph);

	string cities[25] = { "Mansehra","Hasan Abdal", "Peshawar","Attock", "Islamabad", "Murree", "Rawat","Balkasar", "Chakwal", "Mianwali", "Bhera", "Sargoda", "Pindi Bhattian", "Jhang", "Faisalabad", "Lahore", "Dina","Gujranwala", "Multan", "DG Khan", "Bahwalpur", "Sukkur", "Quetta", "Khuzdar", "Karachi" };
	int distances[25];
	bool isVisited[25];
	int paths[25];  //keeps track of parents[paths]

	for (int i = 0; i < 25; i++)
	{
		distances[i] = INT_MAX;
		isVisited[i] = false;
		if (cityname == cities[i])
		{
			source = cities[i];
			source_index = i;
		}
	}
	distances[source_index] = 0;
	paths[source_index] = -1;

	for (int i = 0; i < 25 - 1; i++) //since source is already zero
	{
		int vertex = extractMin(distances, isVisited);
		isVisited[vertex] = true;

		for (int i = 0; i < 25; i++)
		{
			if (isVisited[i] == false && distances[vertex] != INT_MAX)
			{
				if (isedge(graph, vertex, i)) {
					if (distances[vertex] + graph[vertex][i] <= distances[i])
					{
						distances[i] = distances[vertex] + graph[vertex][i];
						paths[i] = vertex;
					}
				}
			}
		}
	}

	for (int i = 0; i < 25; i++)
	{
		/*cout << "Vertex distance from source" << endl;
		cout << i << "     " << distances[i] << "  " << endl;
		*/if (i == 2 || i == 22 || i == 23)
		{
			cout << "No path from " << cities[i] << " to " << source << "\n\n";
		}
		else
		{
			cout << "Shortest path from " << cities[i] << " to " << source << " is: " << endl;
			printfullPath(i, paths);
			cout << endl << endl;
		}
	}
}

string ShortestRoutefrompair(int** graph, string cityname, string city2)
{
	string source, destination, route="";
	int source_index = 0, dest_index = 0;
	Graph g;
	g.makeGraphfromMatrix(graph);

	string cities[25] = { "Mansehra","Hasan Abdal", "Peshawar","Attock", "Islamabad", "Murree", "Rawat","Balkasar", "Chakwal", "Mianwali", "Bhera", "Sargoda", "Pindi Bhattian", "Jhang", "Faisalabad", "Lahore", "Dina","Gujranwala", "Multan", "DG Khan", "Bahwalpur", "Sukkur", "Quetta", "Khuzdar", "Karachi" };
	int distances[25];
	bool isVisited[25];
	int paths[25];  //keeps track of parents[paths]

	for (int i = 0; i < 25; i++)
	{
		distances[i] = INT_MAX;
		isVisited[i] = false;
		if (cityname == cities[i])
		{
			source = cities[i];
			source_index = i;
		}
		if (city2 == cities[i])
		{
			destination = cities[i];
			dest_index = i;
		}
	}
	distances[source_index] = 0;
	paths[source_index] = -1;

	for (int i = 0; i < 25 - 1; i++) //since source is already zero
	{
		int vertex = extractMin(distances, isVisited);
		isVisited[vertex] = true;

		for (int i = 0; i < 25; i++)
		{
			if (isVisited[i] == false && distances[vertex] != INT_MAX)
			{
				if (isedge(graph, vertex, i)) {
					if (distances[vertex] + graph[vertex][i] <= distances[i])
					{
						distances[i] = distances[vertex] + graph[vertex][i];
						paths[i] = vertex;
					}
				}
			}
		}
	}
	for (int i = 0; i < 25; i++)
	{
		if (i == dest_index)
		{
			printPair(i, paths, route);
		}
	}
	//cout << route << endl;
	return route;
}
	

void secondshortestPathfromOnetoall(int** graph, string cityname)
{
	string source;
	int source_index = 0;
	Graph g;
	g.makeGraphfromMatrix(graph);

	string cities[25] = { "Mansehra","Hasan Abdal", "Peshawar","Attock", "Islamabad", "Murree", "Rawat","Balkasar", "Chakwal", "Mianwali", "Bhera", "Sargoda", "Pindi Bhattian", "Jhang", "Faisalabad", "Lahore", "Dina","Gujranwala", "Multan", "DG Khan", "Bahwalpur", "Sukkur", "Quetta", "Khuzdar", "Karachi" };
	int distances[25];
	bool isVisited[25];
	int paths[25];  //keeps track of parents[paths]
	int secPaths[25];
	int PrevDist[25];

	for (int i = 0; i < 25; i++)
	{
		distances[i] = INT_MAX;
		PrevDist[i] = INT_MAX;
		isVisited[i] = false;
		if (cityname == cities[i])
		{
			source = cities[i];
			source_index = i;
		}
	}
	distances[source_index] = 0;
	PrevDist[source_index] = 0;
	secPaths[source_index] = -1;
	paths[source_index] = -1;

	for (int i = 0; i < 25 - 1; i++) //since source is already zero
	{
		int vertex = extractMin(distances, isVisited);
		isVisited[vertex] = true;

		for (int i = 0; i < 25; i++)
		{
			if (isVisited[i] == false && distances[vertex] != INT_MAX)
			{
				if (isedge(graph, vertex, i)) {
					if (distances[vertex] + graph[vertex][i] < distances[i])
					{
						//int prevD = distances[i];
						//PrevDist[i] = distances[i];//save previous data
						//secPaths[i]=
						distances[i] = distances[vertex] + graph[vertex][i]; //update new data
						paths[i] = vertex;
					}
					else if (distances[vertex] + graph[vertex][i] < PrevDist[i])
					{
						PrevDist[i] = distances[vertex] + graph[vertex][i];
						//secPaths[i] = vertex;
						paths[i] = vertex;
					}
				}
			}
		}
	}

	for (int i = 0; i < 25; i++)
	{
		/*cout << "Vertex distance from source" << endl;
		cout << i << "     " << distances[i] << "  " << endl;
		*/if (i == 2 || i == 22 || i == 23)
		{
			cout << "No path from " << source << " to " << cities[i] << "\n\n";
		}
		else
		{
			cout << "Second Shortest path from " << cityname << " to " << cities[i] << " is: " << endl;
			printPath(i, paths);
			cout << endl << endl;
		}
	}

}

void secondshortestPathfromalltoone(int** graph, string cityname)
{
	string source;
	int source_index = 0;
	Graph g;
	g.makeGraphfromMatrix(graph);

	string cities[25] = { "Mansehra","Hasan Abdal", "Peshawar","Attock", "Islamabad", "Murree", "Rawat","Balkasar", "Chakwal", "Mianwali", "Bhera", "Sargoda", "Pindi Bhattian", "Jhang", "Faisalabad", "Lahore", "Dina","Gujranwala", "Multan", "DG Khan", "Bahwalpur", "Sukkur", "Quetta", "Khuzdar", "Karachi" };
	int distances[25];
	bool isVisited[25];
	int paths[25];  //keeps track of parents[paths]
	int PrevDist[25];

	for (int i = 0; i < 25; i++)
	{
		distances[i] = INT_MAX;
		PrevDist[i] = INT_MAX;
		isVisited[i] = false;
		if (cityname == cities[i])
		{
			source = cities[i];
			source_index = i;
		}
	}
	distances[source_index] = 0;
	PrevDist[source_index] = 0;
	paths[source_index] = -1;

	for (int i = 0; i < 25 - 1; i++) //since source is already zero
	{
		int vertex = extractMin(distances, isVisited);
		isVisited[vertex] = true;

		for (int i = 0; i < 25; i++)
		{
			if (isVisited[i] == false && distances[vertex] != INT_MAX)
			{
				if (isedge(graph, vertex, i)) {
					if (distances[vertex] + graph[vertex][i] < distances[i])
					{
						distances[i] = distances[vertex] + graph[vertex][i];
						paths[i] = vertex;
					}
					else if (distances[vertex] + graph[vertex][i] < PrevDist[i])
					{
						PrevDist[i] = distances[vertex] + graph[vertex][i];
						paths[i] = vertex;

					}
				}
			}
		}
	}

	for (int i = 0; i < 25; i++)
	{
		/*cout << "Vertex distance from source" << endl;
		cout << i << "     " << distances[i] << "  " << endl;
		*/if (i == 2 || i == 22 || i == 23)
		{
			cout << "No path from " << cities[i] << " to " << source << "\n\n";
		}
		else
		{
			cout << "Second Shortest path from " << cities[i] << " to " << source << " is: " << endl;
			printfullPath(i, paths);
			cout << endl << endl;
		}
	}
}

string secondShortestRoutefrompair(int** graph, string cityname, string city2)
{
	string source, destination, route = "";
	int source_index = 0, dest_index = 0;
	Graph g;
	g.makeGraphfromMatrix(graph);

	string cities[25] = { "Mansehra","Hasan Abdal", "Peshawar","Attock", "Islamabad", "Murree", "Rawat","Balkasar", "Chakwal", "Mianwali", "Bhera", "Sargoda", "Pindi Bhattian", "Jhang", "Faisalabad", "Lahore", "Dina","Gujranwala", "Multan", "DG Khan", "Bahwalpur", "Sukkur", "Quetta", "Khuzdar", "Karachi" };
	int distances[25];
	bool isVisited[25];
	int paths[25];  //keeps track of parents[paths]
	int PrevDist[25];
	for (int i = 0; i < 25; i++)
	{
		distances[i] = INT_MAX;
		PrevDist[i] = INT_MAX;
		isVisited[i] = false;
		if (cityname == cities[i])
		{
			source = cities[i];
			source_index = i;
		}
		if (city2 == cities[i])
		{
			destination = cities[i];
			dest_index = i;
		}
	}
	distances[source_index] = 0;
	paths[source_index] = -1;

	for (int i = 0; i < 25 - 1; i++) //since source is already zero
	{
		int vertex = extractMin(distances, isVisited);
		isVisited[vertex] = true;

		for (int i = 0; i < 25; i++)
		{
			if (isVisited[i] == false && distances[vertex] != INT_MAX)
			{
				if (isedge(graph, vertex, i)) {
					if (distances[vertex] + graph[vertex][i] <= distances[i])
					{
						distances[i] = distances[vertex] + graph[vertex][i];
						paths[i] = vertex;
					}
					else if (distances[vertex] + graph[vertex][i] < PrevDist[i])
					{
						PrevDist[i] = distances[vertex] + graph[vertex][i];
						//secPaths[i] = vertex;
						paths[i] = vertex;
					}

				}
			}
		}
	}
	for (int i = 0; i < 25; i++)
	{
		if (i == dest_index)
		{
			printPair(i, paths, route);
		}
	}
	//cout << route << endl;
	return route;
}
