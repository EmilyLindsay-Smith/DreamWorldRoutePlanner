#include "gtest/gtest.h"
#include "PrefixTree.h"

class PrefixTreeTest: public::testing::Test
{
protected:
    string s1 = "emily";
    string s2 = "nick";
    string s3 = "rowan";
    string s4 = "em1ly";
    string s5 = "emma";
    
    Vertex* v1 = new Vertex();
    Vertex* v2 = new Vertex();
    Vertex* v3 = new Vertex();
    Vertex* v4 = new Vertex();
    Vertex* v5 = new Vertex();
    
    PrefixTree*p1 = new PrefixTree();
    
};

TEST_F(PrefixTreeTest, TestInsert){
    EXPECT_EQ(p1->Insert(s1, v1), true);
    EXPECT_EQ(p1->Insert(s1, v1), false); // won't add same name twice
    EXPECT_EQ(p1->Insert(s4, v4), false); // won't add nonalphanumeric key
}

TEST_F(PrefixTreeTest, TestSearch){
    p1->Insert(s1, v1);
    p1->Insert(s2, v2);
    p1->Insert(s3, v3);
    p1->Insert(s4, v4);
    p1->Insert(s5, v5);
    
    EXPECT_EQ(p1->Search(s1)->size(), 1);
    EXPECT_EQ(p1->Search("em")->size(), 2);
    EXPECT_EQ((*p1->Search("em"))[0].queryString, "emily");
    EXPECT_EQ((*p1->Search("em"))[1].queryString, "emma");
    EXPECT_EQ(p1->Search(s4)->size(), 0);  
}

TEST_F(PrefixTreeTest, TestFindAll){
    p1->Insert(s1, v1);
    p1->Insert(s2, v2);
    p1->Insert(s3, v3);
    p1->Insert(s4, v4);
    p1->Insert(s5, v5);

    EXPECT_EQ(p1->FindAllLocations()->size(), 4);
    set<string>* receivedResults = p1->FindAllLocations();

    auto itR = receivedResults->begin(); 
    EXPECT_EQ((*itR++), s1);
    EXPECT_EQ((*itR++), s5);
    EXPECT_EQ((*itR++), s2);
    EXPECT_EQ((*itR), s3);

}

TEST_F(PrefixTreeTest, TestFindAllV){
    p1->Insert(s1, v1);
    p1->Insert(s2, v2);
    p1->Insert(s3, v3);
    p1->Insert(s4, v4);
    p1->Insert(s5, v5);

    EXPECT_EQ(p1->FindAllLocations()->size(), 4);
    vector<RefPair>* receivedResults = p1->FindAllLocationsVerbose();

    auto itR = receivedResults->begin(); 
    EXPECT_EQ((*itR++).queryString, s1);
    EXPECT_EQ((*itR++).queryString, s5);
    EXPECT_EQ((*itR++).queryString, s2);
    EXPECT_EQ((*itR).queryString, s3);
}