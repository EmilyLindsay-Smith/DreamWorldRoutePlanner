#include "gtest/gtest.h"
#include "Dijkstra.h"


class DijkstraTest : public ::testing::Test
{
protected:
    Graph *g1 = new Graph(5);
    Dijkstra *d1 = new Dijkstra(g1);
};

TEST_F(DijkstraTest, Test1){
    EXPECT_EQ("a", "a");
};