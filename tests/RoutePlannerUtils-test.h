#include "gtest/gtest.h"
#include "RoutePlannerUtils.h"

using namespace RoutePlannerUtils;

TEST(RoutePlannerUtilsTest, GetRandomNumber){
    int val1 = 1;
    int val2 = 10000;
    EXPECT_EQ(GetRandomNumber(val1), 0) << "Result should be 0 if range 0-0" ;
    EXPECT_LT(GetRandomNumber(val2), val2) << "Result should be less than upper bound";
    EXPECT_GE(GetRandomNumber(val2), 0) << "Results should be greater than or equal to 0";
};

TEST(RoutePlannerUtilsTest, MinToHour){
    float val1 = 0.0f;
    float val2 = -3.9f;
    float val3 = 90.0f;
    float val4 = 100.5f;
    float val5 = 100.4f;
    float val6 = 923.7f;

    EXPECT_EQ(MinToHour(val1), "0 hours 0 minutes");
    EXPECT_EQ(MinToHour(val2), "0 hours 0 minutes");
    EXPECT_EQ(MinToHour(val3), "1 hour 30 minutes");
    EXPECT_EQ(MinToHour(val4), "1 hour 41 minutes");
    EXPECT_EQ(MinToHour(val5), "1 hour 40 minutes");
    EXPECT_EQ(MinToHour(val6), "15 hours 24 minutes");
}

TEST(RoutePlannerUtilsTest, CharToIndex){
    char c1 = 'a';
    char c2 = 'A';
    char c3 = 'z';
    char c4 = 'Z';

    EXPECT_EQ(CharToIndex(c1), 0);
    EXPECT_EQ(CharToIndex(c2), 0);
    EXPECT_EQ(CharToIndex(c3), 25);
    EXPECT_EQ(CharToIndex(c4), 25);
}

TEST(RoutePlannerUtilsTest, IndexToChar){
    int val1= 0;
    int val2= 25;
    int val3= 70;
    EXPECT_EQ(IndexToChar(val1), 'a');
    EXPECT_EQ(IndexToChar(val2), 'z');
    EXPECT_THROW(IndexToChar(val3), runtime_error) << "Doesn't accept indexes above 25";
}

TEST(RoutePlannerUtilsTest, enum2Str){
    SettlementType sett1 = placeBig;
    SettlementType sett2 = placeMedium;
    SettlementType sett3 = placeSmall;
    
    EXPECT_EQ(enum2Str(sett1), "citadel");
    EXPECT_EQ(enum2Str(sett2), "town");
    EXPECT_EQ(enum2Str(sett3), "hamlet"); 
}

TEST(RoutePlannerUtilsTest, ContainsNonAlpha){
    string s1 = "emily";
    string s2 = "em1ly";
    string s3 = "190!23";
    string s4 = "em!ly";
    EXPECT_EQ(ContainsNonAlpha(s1), false);
    EXPECT_EQ(ContainsNonAlpha(s2), true);
    EXPECT_EQ(ContainsNonAlpha(s3), true);
    EXPECT_EQ(ContainsNonAlpha(s4), true);  
}


TEST(RoutePlannerUtilsTest, MakeLowerCase){
    string s1 = "Emily";
    string s1_lower = "emily";

    string s2 = "emilY";
    string s2_lower = "emily";

    string s3 = "EMILY";
    string s3_lower = "emily";

    EXPECT_EQ(MakeLowerCase(s1), s1_lower);
    EXPECT_EQ(MakeLowerCase(s2), s2_lower);
    EXPECT_EQ(MakeLowerCase(s3), s3_lower);
}

TEST(RoutePlannerUtilsTest, MakeSentenceCase){
    string s1 = "emily";
    string s1_sc = "Emily";

    string s2 = "emilY";
    string s2_sc = "EmilY";

    string s3 = "EMILY";
    string s3_sc = "EMILY";

    EXPECT_EQ(MakeSentenceCase(s1), s1_sc);
    EXPECT_EQ(MakeSentenceCase(s2), s2_sc);
    EXPECT_EQ(MakeSentenceCase(s3), s3_sc);
}