#include "gtest/gtest.h"
#include "Prim.h"

class PrimTest : public ::testing::Test
{
protected:
    Vertex *v1 = new Vertex(0, "nameOne", "friendOne", 1, 1, placeSmall);
    Vertex *v2 = new Vertex(1, "nameTwo", "friendTwo", 5, 5, placeMedium);
    Vertex *v3 = new Vertex(2, "nameThree", "friendThree", 20, 50, placeMedium);
    Vertex *v4 = new Vertex(3, "nameFour", "friendFour", 20, 20, placeSmall);

    Vertex *v5 = new Vertex(0, "nameOne", "friendOne", 0, 0, placeSmall);
    Vertex *v6 = new Vertex(1, "nameTwo", "friendTwo", 0, 0, placeMedium);
    Vertex *v7 = new Vertex(2, "nameThree", "friendThree", 0, 0, placeMedium);
    Vertex *v8 = new Vertex(3, "nameFour", "friendFour", 0, 0, placeSmall);

    Vertex *v9 = new Vertex(0, "nameOne", "friendOne", 1000, 1000, placeSmall);
    Vertex *v10 = new Vertex(1, "nameTwo", "friendTwo", 50, 0, placeMedium);
    Vertex *v11 = new Vertex(2, "nameThree", "friendThree", 0, 1000, placeMedium);
    Vertex *v12 = new Vertex(3, "nameFour", "friendFour", 1000, 0, placeSmall);


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
    EXPECT_EQ(receivedResults.size(), 3); // because v1 has no parent
    EXPECT_EQ(receivedResults[v2]->GetName(), v1->GetName());
    EXPECT_EQ(receivedResults[v3]->GetName(), v1->GetName());
    EXPECT_EQ(receivedResults[v4]->GetName(), v2->GetName());
}

TEST_F(PrimTest, Test2){
    vector<Vertex*>* vertices = new vector<Vertex*>;
    vertices->push_back(v5);
    vertices->push_back(v6);
    vertices->push_back(v7);
    vertices->push_back(v8);

    Prim* p1 = new Prim(vertices);

    unordered_map<Vertex*, Vertex*> receivedResults = p1->RunPrim();
    EXPECT_EQ(receivedResults.size(), 3);
    EXPECT_EQ(receivedResults[v6]->GetName(), v5->GetName());
    EXPECT_EQ(receivedResults[v7]->GetName(), v5->GetName());
    EXPECT_EQ(receivedResults[v8]->GetName(), v5->GetName());
}

TEST_F(PrimTest, Test3){
    vector<Vertex*>* vertices = new vector<Vertex*>;
    vertices->push_back(v9);
    vertices->push_back(v10);
    vertices->push_back(v11);
    vertices->push_back(v12);

    Prim* p1 = new Prim(vertices);

    unordered_map<Vertex*, Vertex*> receivedResults = p1->RunPrim();
 //   EXPECT_EQ(receivedResults[v9]->GetName(), v9->GetName());
    EXPECT_EQ(receivedResults[v10]->GetName(), v9->GetName());
    EXPECT_EQ(receivedResults[v11]->GetName(), v9->GetName());
    EXPECT_EQ(receivedResults[v12]->GetName(), v10->GetName());
}