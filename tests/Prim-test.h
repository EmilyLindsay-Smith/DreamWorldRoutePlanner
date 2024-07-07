#include "gtest/gtest.h"
#include "Prim.h"

class PrimTest : public ::testing::Test
{
protected:
    Vertex *v1 = new Vertex(0, "nameOne", "friendOne", 1, 1, placeSmall);
    Vertex *v2 = new Vertex(1, "nameTwo", "friendTwo", 5, 5, placeMedium);
    Vertex *v3 = new Vertex(2, "nameThree", "friendThree", 20, 50, placeMedium);
    Vertex *v4 = new Vertex(3, "nameFour", "friendFour", 20, 20, placeSmall);
};

TEST_F(PrimTest, Test1){
    vector<Vertex*>* vertices = new vector<Vertex*>;
    vertices->push_back(v1);
    vertices->push_back(v2);
    vertices->push_back(v3);
    vertices->push_back(v4);

    Prim* p1 = new Prim(vertices);

    unordered_map<Vertex*, Vertex*> receivedResults = p1->RunPrim();
    //EXPECT_EQ(receivedResults[v1], NULL);
    EXPECT_EQ(receivedResults[v2]->GetName(), v1->GetName());
    EXPECT_EQ(receivedResults[v3]->GetName(), v1->GetName());
    EXPECT_EQ(receivedResults[v4]->GetName(), v2->GetName());
    
    
}