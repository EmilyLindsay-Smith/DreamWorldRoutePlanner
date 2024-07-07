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
    Vertex* v4 = new Vertex();
};

TEST_F(VertexTest, TestName){
    string name1 = "nick";
    string name1_upper = name1;
    name1_upper[0] = toupper(name1_upper[0]);
    string name2 = "emily";
    string name3 = "em1ly";
    
    v1->SetName(name1);
    v2->SetName(name2);
    v3->SetName(name3);

    EXPECT_EQ(v1->GetName(), name1_upper) << "Vertex does not store correct name";
    EXPECT_NE(v1->GetName(), name1) << "Vertex does not store name as sentence case";
    
    EXPECT_NE(v2->GetName(), "") << "Vertex does not store name when assigned";
    
    EXPECT_NE(v3->GetName(), name3) << "Vertex stores names iwth non-alphabetical characters";
    
    EXPECT_EQ(v4->GetName(), "") << "Vertex does not initialise unassigned name correctly";
};

TEST_F(VertexTest, TestID){
    int id1 = 10000;
    int id2 = -2;
    v1->SetID(id1);
    v2->SetID(id2);

    EXPECT_EQ(v1->GetID(), id1) << "Vertex does not store correct ID";
    EXPECT_NE(v1->GetID(), id2) << "Vertex stored negative ID";
    EXPECT_EQ(v2->GetID(), -1) << "Vertex didn't default with negative ID";
    EXPECT_EQ(v3->GetID(), -1) << "Vertex does not initialise unassigned ID correctly";
};

TEST_F(VertexTest, TestSettlement){
    SettlementType sett1 = placeBig;

    v1->SetSettlement(sett1);
    
    EXPECT_EQ(v1->GetSettlement(), sett1) << "Vertex does not store settlement type correctly" << endl;
};

TEST_F(VertexTest, TestFriend){
    string name1 = "nick";
    string name2 = "emily";
    string name3 = "em1ly";
    
    v1->SetFriend(name1);
    v2->SetFriend(name2);
    v3->SetFriend(name3);

    EXPECT_EQ(v1->GetFriend(), name1) << "Vertex does not store friend";
    EXPECT_NE(v2->GetFriend(), "") << "Vertex does not store name when assigned";
    
    EXPECT_NE(v3->GetFriend(), name3) << "Vertex stores friend iwth non-alphabetical characters";
    
    EXPECT_EQ(v4->GetFriend(), "") << "Vertex does not initialise unassigned friend correctly";
};

TEST_F(VertexTest, TestCoordinates){
    int x1 = 1000;
    int x2 = -3;
    int y1 = 10000;
    int y2 = -3;

    v1->SetX(x1);
    v1->SetY(y1);

    v2->SetX(x2);
    v2->SetY(y2);

    v3->SetCoordinates(x1, y1);

    v4->SetCoordinates(x2, y2);

    EXPECT_EQ(v1->GetCoordinates()->x, x1) << "Vertex did not correctly store positive x coord";
    EXPECT_EQ(v1->GetCoordinates()->y, y1) << "Vertex did not correctly store positive y coord";
    
    EXPECT_NE(v2->GetCoordinates()->x, x2) << "Vertex incorrectly stored negative x coord";
    EXPECT_NE(v2->GetCoordinates()->y, y2) << "Vertex incorrectly stored negative y coord";

    EXPECT_EQ(v3->GetCoordinates()->x, x1) << "Vertex did not correctly store positive x coord";
    EXPECT_EQ(v3->GetCoordinates()->y, y1) << "Vertex did not correctly store positive y coord";
    
    EXPECT_NE(v4->GetCoordinates()->x, x2) << "Vertex incorrectly stored negative x coord";
    EXPECT_NE(v4->GetCoordinates()->y, y2) << "Vertex incorrectly stored negative y coord";
}

TEST_F(VertexTest, TestAmenities){
    string amenity1 = "bakery";
    string amenity2 = "b4kery";
    string amenity3 = "grocer";
    string amenity4 = "butcher";

    v1->AddAmenities(amenity1);
    v2->AddAmenities(amenity2);

    v3->AddAmenities(amenity1);
    v3->AddAmenities(amenity2);
    v3->AddAmenities(amenity3);
    v3->AddAmenities(amenity4);
    
    EXPECT_EQ(v1->GetAmenities()->size(), 1)<< "Single amenity not added correctly";
    EXPECT_EQ((*v1->GetAmenities())[0], amenity1) << "Amenity not added correctly";

    EXPECT_NE(v2->GetAmenities()->size(), 1)<< "Non-alphabetic amenity added";
    
    EXPECT_EQ(v3->GetAmenities()->size(), 3)<< "Multiple amenities not added correctly";
    EXPECT_EQ((*v3->GetAmenities())[0], amenity1) << "Amenity not added in order";
    EXPECT_NE((*v3->GetAmenities())[1], amenity2) << "Non-alphabet amenity added";
    EXPECT_EQ((*v3->GetAmenities())[1], amenity3) << "Amenity not added in order";
    EXPECT_EQ((*v3->GetAmenities())[2], amenity4) << "Amenity not added in order";

    EXPECT_EQ(v4->GetAmenities()->size(), 0) << "Amenity vector not defaulting to empty vector";
}

TEST(VertexTest2, FullInstantiation){
    Vertex* newVert = new Vertex(0, "nameOne", "friendOne", 10, 0, placeBig);
    EXPECT_EQ(newVert->GetID(), 0);
    EXPECT_EQ(newVert->GetName(), "NameOne");
    EXPECT_EQ(newVert->GetFriend(), "friendOne");
    EXPECT_EQ(newVert->GetCoordinates()->x, 10);
    EXPECT_EQ(newVert->GetCoordinates()->y, 0);
    EXPECT_EQ(newVert->GetSettlement(), placeBig);  
}