#include "gtest/gtest.h"
#include "Graph.h"

class GraphTest : public ::testing::Test
{
protected:
    // set up
    // tear down
    Vertex* v1 = new Vertex(0, "nameOne", "friendOne", 10, 0, city);
    Vertex* v2 = new Vertex(1, "nameTwo", "friendTwo", 11, 5, town);
    Vertex* v3 = new Vertex(2, "nameThree", "friendThree", 12, 10, village);
    Vertex* v4 = new Vertex(3, "nameFour", "friendFour", 13, 0, city);
    Vertex* v5 = new Vertex(4, "nameFive", "friendFive", 14, 5, town);
    Vertex* v6 = new Vertex(5, "nameSix", "friendSix", 15, 10, village);
    Vertex* v7 = new Vertex(6, "nameSeven", "friendSeven", 16, 0, city);
    Vertex* v8 = new Vertex(7, "nameEight", "friendEight", 17, 5, town);
    Vertex* v9 = new Vertex(8, "nameNine", "friendNine", 18, 10, village);
    Vertex* v10 = new Vertex(9, "nameTen", "friendTen", 19, 15, city);

    Graph* g1 = new Graph(3);
    Graph* g2 = new Graph(5);
    Graph* g3 = new Graph(10);
};

TEST_F(GraphTest, TestDefaultValues){
    EXPECT_EQ(g1->GetNumberVertices(), 0);
    EXPECT_EQ(g1->GetNumberRoads(), 0);
    EXPECT_EQ(g1->GetVertices()->size(),3);
}

TEST_F(GraphTest, TestAddVertex){
    g1->AddVertex(v1);
    g1->AddVertex(v2);
    g1->AddVertex(v3);

    EXPECT_EQ(g1->GetNumberVertices(), 3);
    EXPECT_EQ((*g1->GetVertices())[0], v1);
    EXPECT_EQ((*g1->GetVertices())[1], v2);
    EXPECT_EQ((*g1->GetVertices())[2], v3);
}

TEST_F(GraphTest, TestAddVertex2){
    g1->AddVertex(v1);
    g1->AddVertex(v2);
    g1->AddVertex(v3);
    g1->AddVertex(v4);

    EXPECT_NE(g1->GetNumberVertices(), 4) << "Added more vertices than max size";
    EXPECT_EQ((*g1->GetVertices())[0], v1);
    EXPECT_EQ((*g1->GetVertices())[1], v2);
    EXPECT_EQ((*g1->GetVertices())[2], v3);
}

TEST_F(GraphTest, GetVertexPointer){
    g1->AddVertex(v1);
    g1->AddVertex(v2);
    g1->AddVertex(v3);

    EXPECT_EQ(g1->GetVertexPointer(0), v1);
    EXPECT_EQ(g1->GetVertexPointer(1), v2);
    EXPECT_EQ(g1->GetVertexPointer(2), v3);

}

TEST_F(GraphTest, AddEdge){
    g1->AddVertex(v1);
    g1->AddVertex(v2);
    g1->AddVertex(v3);
    
    g1->AddEdge(0, 1);
    EXPECT_EQ(g1->GetNumberRoads(), 1);

    g1->AddEdge(v2, v3);
    EXPECT_EQ(g1->GetNumberRoads(), 2);

}

TEST_F(GraphTest, AddEdges){
    g1->AddVertex(v1);
    g1->AddVertex(v2);
    g1->AddVertex(v3);
    EXPECT_EQ(g1->GetNumberVertices(), 3);
    unordered_map<Vertex*, Vertex*> edgesMST;
    edgesMST.insert(make_pair(v1, v2));
    edgesMST.insert(make_pair(v2, v3));
    edgesMST.insert(make_pair(v3, v1));

    EXPECT_EQ(edgesMST.size(), 3);
    g1->AddEdges(edgesMST);
    EXPECT_EQ(g1->GetNumberRoads(), 3);
}

TEST_F(GraphTest, GetCost){
    g1->AddVertex(v1);
    g1->AddVertex(v2);
    g1->AddEdge(v1,v2); 
    float distCost = (float) sqrt(pow((10 - 11),2) + pow((0 - 5),2));
    float timeCost = distCost / 10;

    EXPECT_EQ(g1->GetCost(v1, v2, "Dist"), distCost);
    EXPECT_EQ(g1->GetCost(v1, v2, "Time"), timeCost);
    EXPECT_EQ(g1->GetCost(0, 1, "Dist"), distCost);
    EXPECT_EQ(g1->GetCost(0, 1, "Time"), timeCost);    
}

TEST_F(GraphTest, GetAdjacentVert1){
    g2->AddVertex(v1);
    g2->AddVertex(v2);
    g2->AddVertex(v3);
    g2->AddVertex(v4);
    g2->AddVertex(v5);

    g2->AddEdge(v1, v2);
    g2->AddEdge(v1, v3);

    EXPECT_EQ(g2->GetNumberVertices(), 5);
    EXPECT_EQ(g2->GetNumberRoads(), 2);
    EXPECT_EQ(g2->GetAdjacentVertices(v1).size(), 2);
    EXPECT_EQ(g2->GetAdjacentVertices(v1)[0], v2);
    EXPECT_EQ(g2->GetAdjacentVertices(v1)[1], v3);

}


TEST_F(GraphTest, GetAdjacentVert2){
    g2->AddVertex(v1);
    g2->AddVertex(v2);
    g2->AddVertex(v3);
    g2->AddVertex(v4);
    g2->AddVertex(v5);

    g2->AddEdge(v1, v2);
    g2->AddEdge(v1, v3);

    EXPECT_EQ(g2->GetNumberVertices(), 5);
    EXPECT_EQ(g2->GetNumberRoads(), 2);
    EXPECT_EQ(g2->GetAdjacentVerticesByID(v1).size(), 2);
    EXPECT_EQ(g2->GetAdjacentVerticesByID(v1)[0], 1);
    EXPECT_EQ(g2->GetAdjacentVerticesByID(v1)[1], 2);
}

TEST_F(GraphTest, GetAdjacentVert3){
    g2->AddVertex(v1);
    g2->AddVertex(v2);
    g2->AddVertex(v3);
    g2->AddVertex(v4);
    g2->AddVertex(v5);

    g2->AddEdge(v1, v2);
    g2->AddEdge(v1, v3);

    EXPECT_EQ(g2->GetNumberVertices(), 5);
    EXPECT_EQ(g2->GetNumberRoads(), 2);
    EXPECT_EQ(g2->GetAdjacentVerticesByID(0).size(), 2);
    EXPECT_EQ(g2->GetAdjacentVerticesByID(0)[0], 1);
    EXPECT_EQ(g2->GetAdjacentVerticesByID(0)[1], 2);
}

TEST_F(GraphTest, GetAdjacentVert4){
    g2->AddVertex(v1);
    g2->AddVertex(v2);
    g2->AddVertex(v3);
    g2->AddVertex(v4);
    g2->AddVertex(v5);

    g2->AddEdge(v1, v2);
    g2->AddEdge(v1, v3);

    EXPECT_EQ(g2->GetNumberVertices(), 5);
    EXPECT_EQ(g2->GetNumberRoads(), 2);
    EXPECT_EQ(g2->GetAdjacentVerticesByID(v2).size(), 1);
    EXPECT_EQ(g2->GetAdjacentVerticesByID(v2)[0], 0);
    EXPECT_EQ(g2->GetAdjacentVerticesByID(v4).size(), 0);

}