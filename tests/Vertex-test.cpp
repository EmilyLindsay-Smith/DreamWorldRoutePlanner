#include "gtest/gtest.h"
#include "Vertex.h"


class VertexTest : public ::testing::Test
{
protected:
    // set up
    // tear down
    Vertex v1;
    Vertex v2;
};

TEST_F(VertexTest, TestName){
    string name1 = "nick";
    string name2 = "emily";
    v1.SetName(name1);
    v2.SetName(name2);

    EXPECT_EQ(v1.GetName(), name1);
    EXPECT_EQ(v2.GetName(), name2);
}