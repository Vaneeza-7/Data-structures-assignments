#include "pch.h"
#include "../DS-assignment3/Header.h"
#include <gtest/gtest.h>

TEST(Graph, addNodetest) {
    Graph g;
    int** arr = ReadFromFile();//this fuction returns edges and cities in 2d int array. Cities are mapped to int values
    //declared arraycount and V global for ease
    g.makeGraphfromMatrix(arr);
    string s1 = "Sialkot:";
    g.addNode("Sialkot");
    //g.printGraph();

    ASSERT_EQ(0, s1.compare(g.printsingleLink("Sialkot")));
}

TEST(Graph, addEdgetest) {
    Graph g;
    int** arr;
    arr = ReadFromFile();//this fuction returns edges and cities in 2d int array. Cities are mapped to int values
    //declared arraycount and V global for ease
    g.makeGraphfromMatrix(arr);
    string s1 = "Karachi:Sukkur->Peshawar->";
    g.addedge("Karachi", "Peshawar", 200);

    ASSERT_EQ(0, s1.compare(g.printsingleLink("Karachi"))); 
}

TEST(Graph, deleteNodetest) {
    Graph g;
    int** arr;
    arr = ReadFromFile();//this fuction returns edges and cities in 2d int array. Cities are mapped to int values
    //declared arraycount and V global for ease
    g.makeGraphfromMatrix(arr);
    string s1 = "Multan:Jhang->DG Khan->Bahwalpur->";
    g.deleteNode("Lahore");

    ASSERT_EQ(0, s1.compare(g.printsingleLink("Multan")));
}

TEST(Graph, deleteEdgetest) {
    Graph g;
    int** arr;
    arr = ReadFromFile();//this fuction returns edges and cities in 2d int array. Cities are mapped to int values
    //declared arraycount and V global for ease
    g.makeGraphfromMatrix(arr);
    string s1 = "Quetta:";
    g.deleteEdge("Quetta", "Khuzdar");
    g.printGraph();

    ASSERT_EQ(0, s1.compare(g.printsingleLink("Quetta")));
}

TEST(Graph, shorterstPathfromOnetoalltest) {
    Graph* g;
    int** arr;
    arr = ReadFromFile();
    shortestPathfromOnetoall(arr, "Lahore");

    //Print all shortest Path from Lahore to all cities

    //Evaluator will verify your output from terminal

    ASSERT_EQ(0, 0);
}


TEST(Graph, secondshorterstPathfromOnetoalltest) {
    Graph* g;
    int** arr;
    arr = ReadFromFile();
    secondshortestPathfromOnetoall(arr, "Lahore");

    //Print all shortest Path from Lahore to all cities

    //Evaluator will verify your output from terminal

    ASSERT_EQ(0, 0);
}


TEST(Graph, shorterstPathfromalltoonetest) {
    Graph* g;
    int** arr;
    arr = ReadFromFile();
    shortestPathfromalltoone(arr, "Lahore");

    //Print all shortest Path from  all cities to Lahore

    //Evaluator will verify your output from terminal

    ASSERT_EQ(0, 0);
}


TEST(Graph, secondshorterstPathfromalltoonetest) {
    Graph* g;
    int** arr;
    arr = ReadFromFile();
    secondshortestPathfromalltoone(arr, "Lahore");

    //Print all shortest Path from  all cities to Lahore

    //Evaluator will verify your output from terminal

    ASSERT_EQ(0, 0);
}


TEST(Graph, ShortestRoutefrompairtest) {
    Graph* g;
    int** arr;
    arr = ReadFromFile();//this fuction returns edges and cities in 2d int array. Cities are mapped to int values
    //declared arraycount and V global for ease
    string s1 = "Mansehra->Murree->Islamabad->";
    string s2 = ShortestRoutefrompair(arr, "Mansehra", "Islamabad");

    ASSERT_EQ(0, s1.compare(s2));
}


TEST(Graph, secondShortestRoutefrompairtest) {
    Graph* g;
    int** arr;
    arr = ReadFromFile();//this fuction returns edges and cities in 2d int array. Cities are mapped to int values
    //declared arraycount and V global for ease
    string s1 = "Lahore->Gujranwala->Dina->Rawat->Chakwal->Balkasar->Islamabad->Hasan Abdal->Mansehra->";
    string s2 = secondShortestRoutefrompair(arr, "Lahore", "Mansehra");

    ASSERT_EQ(0, s1.compare(s2));
}
