#include "gtest/gtest.h"
#include "Vertex-test.h"
#include "RoutePlannerUtils-test.h"
#include "Graph-test.h"
#include "Dijkstra-test.h"
#include "PrefixTree-test.h"
#include "Prim-test.h"
#include "Generator-test.h"

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS(); //run all tests in all files in this folder
}
