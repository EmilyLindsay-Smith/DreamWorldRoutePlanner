#include "gtest/gtest.h"

#include "Generator.h"


class GeneratorTest : public ::testing::Test
{
protected:
    int numSettlements = 10;
    Graph *g1 = new Graph(numSettlements);
    PrefixTree *pt1 = new PrefixTree();
    vector<string> stA = {"aOne", "aTwo", "aThree"};
    vector<string>* standardAmenities = &stA;
    vector<string> spA = {"aFour", "aFive", "aSix"};
    vector<string>* specialAmenities = &spA;
    bool verbose = false;

    Generator *gen = new Generator(numSettlements, g1, pt1, standardAmenities, specialAmenities, verbose);
};

TEST_F(GeneratorTest, TestNumSettlements){

    gen->Run();

    EXPECT_EQ(gen->GetNumPlaceBigs(), numSettlements*.2) << "20% should be placeBigs ";
    EXPECT_EQ(gen->GetNumPlaceMediums(), numSettlements*.3) << "30% should be placeMediums ";
    EXPECT_EQ(gen->GetNumPlaceSmalls(), numSettlements*.5) << "50% should be placeSmalls ";
    
}

TEST_F(GeneratorTest, TestNumRoads){
    gen->Run();
    EXPECT_EQ(g1->GetNumberRoads(), 12) << "Didn't create the right number of roads";
}

TEST_F(GeneratorTest, TestPlaceAttributes){
    gen->Run();
    
    Vertex* v = g1->GetVertexPointer(0);

    EXPECT_NE(v->GetName(), "");
    EXPECT_NE(v->GetFriend(), "");
    EXPECT_NE(v->GetFriendSurname(), "");
    EXPECT_GE(v->GetCoordinates()->x, 0);
    EXPECT_LE(v->GetCoordinates()->x, gen->GetMaxX());
    EXPECT_GE(v->GetCoordinates()->y, 0);
    EXPECT_LE(v->GetCoordinates()->y, gen->GetMaxY());
    
    EXPECT_GE(v->GetSettlement(), 0);
    EXPECT_LE(v->GetSettlement(), 2);

    switch(v->GetSettlement()){
        case 0 : EXPECT_NE((*v->GetAmenities())[3], "")<<"Should be able to access the 4th amenity";break;
        case 1 : EXPECT_NE((*v->GetAmenities())[2], "")<<"Should be able to access the 3rd amenity";break;
        case 2 : EXPECT_NE((*v->GetAmenities())[1], "")<<"Should be able to access the 2nd amenity";break;
        default: EXPECT_NE(1, 1) << "No settlement type detected" ;
    };

};


