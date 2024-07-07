#include "gtest/gtest.h"
#include "Vertex.h"


class VertexTest : public ::testing::Test
{
protected:
    // set up
    // tear down
    Vertex* v1 = new Vertex();
    Vertex* v2 = new Vertex();
    Vertex* v3 = new Vertex();
};

TEST_F(VertexTest, TestName){
    string name1 = "nick";
    string name2 = "emily";
    v1->SetName(name1);
    v2->SetName(name2);

    EXPECT_EQ(v1->GetName(), name1) << "Vertex does not store correct name";
    EXPECT_NE(v2->GetName(), "") << "Vertex does not store name when assigned";
    EXPECT_EQ(v3->GetName(), "") << "Vertex does not initialise unassigned name correctly";
}