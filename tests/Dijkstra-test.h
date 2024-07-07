#include "gtest/gtest.h"

#include "Dijkstra.h"


class DijkstraTest : public ::testing::Test
{
protected:
    Vertex *v1 = new Vertex(0, "nameOne", "friendOne", 1, 1, placeSmall);
    Vertex *v2 = new Vertex(1, "nameTwo", "friendTwo", 5, 5, placeMedium);
    Vertex *v3 = new Vertex(2, "nameThree", "friendThree", 50, 20, placeMedium);
    Vertex *v4 = new Vertex(3, "nameFour", "friendFour", 20, 20, placeSmall);
    Graph *g1 = new Graph(5);
};

TEST_F(DijkstraTest, TestGetPaths_TimeCost){
    g1->AddVertex(v1);
    g1->AddVertex(v2);
    g1->AddVertex(v3);
    g1->AddVertex(v4);

    g1->AddEdge(v1, v2);
    g1->AddEdge(v2, v3);
    g1->AddEdge(v3, v4);
    g1->AddEdge(v1, v4);

    float cost1to1 = 0;
    float cost1to2 = (float) ((float)sqrt(pow((v1->GetCoordinates()->x - v2->GetCoordinates()->x),2) + pow((v1->GetCoordinates()->y - v2->GetCoordinates()->y),2)))/5;
    float cost2to3 = (float) ((float)sqrt(pow((v2->GetCoordinates()->x - v3->GetCoordinates()->x),2) + pow((v2->GetCoordinates()->y - v3->GetCoordinates()->y),2)))/10;
    float cost3to4 = (float) ((float)sqrt(pow((v3->GetCoordinates()->x - v4->GetCoordinates()->x),2) + pow((v3->GetCoordinates()->y - v4->GetCoordinates()->y),2)))/5;
    float cost1to4 = (float) ((float)sqrt(pow((v1->GetCoordinates()->x - v4->GetCoordinates()->x),2) + pow((v1->GetCoordinates()->y - v4->GetCoordinates()->y),2)))/5;
    float cost1to3 = cost1to4 + cost3to4;
    Dijkstra *d1 = new Dijkstra(g1);

    vector<float>* receivedResults = d1->GetPaths(v1, "Time");

    EXPECT_EQ((*receivedResults)[0],cost1to1 );
    EXPECT_EQ((*receivedResults)[1],cost1to2 );
    EXPECT_EQ((*receivedResults)[2],cost1to3 );
    EXPECT_EQ((*receivedResults)[3],cost1to4);

 };

TEST_F(DijkstraTest, TestGetPaths_DistCost){
    g1->AddVertex(v1);
    g1->AddVertex(v2);
    g1->AddVertex(v3);
    g1->AddVertex(v4);
    g1->AddEdge(v1, v2);
    g1->AddEdge(v2, v3);
    g1->AddEdge(v3, v4);
    g1->AddEdge(v1, v4);

    float cost1to1 = 0;
    float cost1to2 = (float) sqrt(pow((v1->GetCoordinates()->x - v2->GetCoordinates()->x),2) + pow((v1->GetCoordinates()->y - v2->GetCoordinates()->y),2));
    float cost2to3 = (float) sqrt(pow((v2->GetCoordinates()->x - v3->GetCoordinates()->x),2) + pow((v2->GetCoordinates()->y - v3->GetCoordinates()->y),2));
    float cost3to4 = (float) sqrt(pow((v3->GetCoordinates()->x - v4->GetCoordinates()->x),2) + pow((v3->GetCoordinates()->y - v4->GetCoordinates()->y),2));
    float cost1to4 = (float) sqrt(pow((v1->GetCoordinates()->x - v4->GetCoordinates()->x),2) + pow((v1->GetCoordinates()->y - v4->GetCoordinates()->y),2));
    float cost1to3 = cost1to4 + cost3to4;
    Dijkstra *d1 = new Dijkstra(g1);

    vector<float>* receivedResults = d1->GetPaths(v1, "Dist");
    EXPECT_EQ((*receivedResults)[0],cost1to1 );
    EXPECT_EQ((*receivedResults)[1],cost1to2 );
    EXPECT_EQ((*receivedResults)[2],cost1to3);

    EXPECT_EQ((*receivedResults)[3],cost1to4);
    };

TEST_F(DijkstraTest, TestReconstructPaths_TimeCost){
    g1->AddVertex(v1);
    g1->AddVertex(v2);
    g1->AddVertex(v3);
    g1->AddVertex(v4);
    g1->AddEdge(v1, v2);
    g1->AddEdge(v2, v3);
    g1->AddEdge(v3, v4);
    g1->AddEdge(v1, v4);
    Dijkstra *d1 = new Dijkstra(g1);

    stack<Vertex*> receivedResults = d1->ReconstructPath(v1, v3, "Time");
    stack<Vertex*> expectedResults;
    expectedResults.push(v3);
    expectedResults.push(v4);
    expectedResults.push(v1);
   
    EXPECT_EQ(receivedResults.size(), expectedResults.size());

    while (!receivedResults.empty() && !expectedResults.empty()){
        Vertex* vertExpected = expectedResults.top();
        expectedResults.pop();
        Vertex* vertReceived = receivedResults.top();
        receivedResults.pop();
        EXPECT_EQ(vertExpected, vertReceived);
    }
}

TEST_F(DijkstraTest, TestReconstructPaths_DistCost){
    g1->AddVertex(v1);
    g1->AddVertex(v2);
    g1->AddVertex(v3);
    g1->AddVertex(v4);
    g1->AddEdge(v1, v2);
    g1->AddEdge(v2, v3);
    g1->AddEdge(v3, v4);
    g1->AddEdge(v1, v4);
    Dijkstra *d1 = new Dijkstra(g1);

    stack<Vertex*> receivedResults = d1->ReconstructPath(v1, v3, "Dist");
    stack<Vertex*> expectedResults;
    expectedResults.push(v3);
    expectedResults.push(v4);
    expectedResults.push(v1);
   
    EXPECT_EQ(receivedResults.size(), expectedResults.size());

    while (!receivedResults.empty() && !expectedResults.empty()){
        Vertex* vertExpected = expectedResults.top();
        expectedResults.pop();
        Vertex* vertReceived = receivedResults.top();
        receivedResults.pop();
        EXPECT_EQ(vertExpected, vertReceived);
    }
}