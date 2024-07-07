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

    Graph* g1 = new Graph(10);
    Graph* g2 = new Graph(10);
    Graph* g3 = new Graph(10);
};

TEST_F(GraphTest, TestDefaultValues){
    EXPECT_EQ(g1->GetNumberVertices(), 0);
    EXPECT_EQ(g1->GetNumberRoads(), 0);
    EXPECT_EQ(g1->GetVertices()->size(), 10);
}

TEST_F(GraphTest, TestAddVertex){

}