#include <iostream>
#include "gtest/gtest.h"
#include "graph.h"
//#include "graph.cpp"

using namespace std;


// test basic graph
TEST(testing, test01)
{
    graph<string, double> G;
    ASSERT_TRUE(G.NumVertices() == 0);
    ASSERT_TRUE(G.NumEdges() == 0);

    // check all 8 vertices
    G.addVertex("a");
    ASSERT_TRUE(G.NumVertices() == 1);
    G.addVertex("b");
    ASSERT_TRUE(G.NumVertices() == 2);
    G.addVertex("c");
    ASSERT_TRUE(G.NumVertices() == 3);
    G.addVertex("d");
    ASSERT_TRUE(G.NumVertices() == 4);
    G.addVertex("e");
    ASSERT_TRUE(G.NumVertices() == 5);
    G.addVertex("f");
    ASSERT_TRUE(G.NumVertices() == 6);
    G.addVertex("g");
    ASSERT_TRUE(G.NumVertices() == 7);
    G.addVertex("h");
    ASSERT_TRUE(G.NumVertices() == 8);

    // check all 12 edges
    G.addEdge("a", "b", 1.0);
    ASSERT_TRUE(G.NumEdges() == 1);
    G.addEdge("a", "c", 1.0);
    ASSERT_TRUE(G.NumEdges() == 2);
    G.addEdge("a", "d", 1.0);
    ASSERT_TRUE(G.NumEdges() == 3);
    G.addEdge("a", "e", 1.0);
    ASSERT_TRUE(G.NumEdges() == 4);
    G.addEdge("a", "f", 1.0);
    ASSERT_TRUE(G.NumEdges() == 5);
    G.addEdge("a", "g", 1.0);
    ASSERT_TRUE(G.NumEdges() == 6);
    G.addEdge("a", "h", 1.0);
    ASSERT_TRUE(G.NumEdges() == 7);
    G.addEdge("a", "a", 1.0);
    ASSERT_TRUE(G.NumEdges() == 8);
    G.addEdge("b", "a", 1.0);
    ASSERT_TRUE(G.NumEdges() == 9);
    G.addEdge("b", "c", 1.0);
    ASSERT_TRUE(G.NumEdges() == 10);
    G.addEdge("b", "d", 1.0);
    ASSERT_TRUE(G.NumEdges() == 11);
    G.addEdge("b", "b", 1.0);
    ASSERT_TRUE(G.NumEdges() == 12);


    // adding vertex return true
    bool add;
    add = G.addVertex ("z");
    ASSERT_TRUE(add == true);


    // edge overwrite
    G.addEdge("a", "b", 2.0);
    double w;
    G.getWeight("a", "b", w);
    ASSERT_TRUE(w == 2.0);

}

// tests returning false
TEST(testing, test02)
{
    graph<string, double> G;
	G.addVertex("a");
    G.addVertex("b");
    G.addVertex("c");
    G.addVertex("d");
    G.addVertex("e");
    G.addVertex("f");
    G.addVertex("g");
    G.addVertex("h");
    ASSERT_TRUE(G.NumVertices() == 8);

    // adding vertices false
    bool add = G.addVertex("a");
    ASSERT_TRUE(add == false);
    add = G.addVertex ("b");
    ASSERT_TRUE(add == false);
    ASSERT_TRUE(G.NumVertices() == 8);
    
    G.addEdge("h", "h", 1.23423);
    G.addEdge("h", "a", 543.7);
    G.addEdge("a", "h", 1.6);

    // no updating wrong edge
    ASSERT_TRUE(G.NumEdges() == 3);

    G.addEdge("a", "b", 87.0);
    G.addEdge("b", "a", 8.7);
    G.addEdge("c", "d", 5.32);
    G.addEdge("e", "e", 3.50);
    G.addEdge("e", "a", 1.00);
    G.addEdge("e", "b", 0.0);
    G.addEdge("h", "c", -3.0);
    G.addEdge("c", "h", -1.1);
    G.addEdge("d", "d", 1.32);
    G.addEdge("d", "a", 0.432);

    // adding edges return false
    add = G.addEdge("z", "y", 2.0);
    ASSERT_TRUE(add == false);
    ASSERT_TRUE(G.NumEdges() == 13);
    add = G.addEdge("z", "a", 2.2);
    ASSERT_TRUE(add == false);
    add = G.addEdge("b", "y", 0.0);
    ASSERT_TRUE(add == false);

    // getting weights return false
    double w = 80.3;
    add = G.getWeight("a", "z", w);
    ASSERT_TRUE(add == false);
    add = G.getWeight("y", "d", w);
    ASSERT_TRUE(add == false);
    ASSERT_TRUE(w == 80.3); // w is unchanged
    ASSERT_TRUE(G.NumVertices() == 8); // num of vertices is unchanged
    ASSERT_TRUE(G.NumEdges() == 13); // num of vertices is unchanged
}

// testing neighbors
TEST(testing, test03) {
    graph<string, double> G;

    // neighbors on an empty graph
    set<string> ans;
    ans = G.neighbors("a");
    ASSERT_TRUE(ans.size() == 0);
    ASSERT_TRUE(G.NumVertices() == 0); 
    ASSERT_TRUE(G.NumEdges() == 0);

	G.addVertex("a");
    G.addVertex("b");
    G.addVertex("c");
    G.addVertex("d");
    G.addVertex("e");
    G.addVertex("f");
    G.addVertex("g");
    G.addVertex("h");

    // neighbors on no edges
    ans = G.neighbors("a");
    ASSERT_TRUE(ans.size() == 0);
    ASSERT_TRUE(G.NumEdges() == 0);

    G.addEdge("a", "a", 1.23423);
    G.addEdge("a", "b", 543.7);
    G.addEdge("a", "c", 1.6);
    G.addEdge("a", "d", 87.0);
    G.addEdge("a", "e", 8.7);
    G.addEdge("a", "f", 5.32);
    G.addEdge("a", "g", 3.50);
    G.addEdge("a", "h", 1.00);
    G.addEdge("b", "a", 0.0);
    G.addEdge("b", "b", -3.0);
    G.addEdge("b", "c", -1.1);
    G.addEdge("b", "d", 1.32);
    G.addEdge("b", "e", 0.432);

    // updated neighbors
    ans = G.neighbors("a");
    ASSERT_TRUE(ans.size() == 8);
    ans = G.neighbors("b");
    ASSERT_TRUE(ans.size() == 5);

    // no unintentional neighbors added in addEdge
    ans = G.neighbors("c");
    ASSERT_TRUE(ans.size() == 0);

}


// mixed bag
TEST(testing, test04) {
    graph<string, double> G;
    bool add;

    // test when vertex doesn't exist
    set<string> nei = G.neighbors("SMQ");
    ASSERT_TRUE(nei.size() == 0);

    G.addVertex("Bobb");
    G.addVertex("Sargent");
    G.addVertex("Elder");
    G.addVertex("Lincoln");

    // test getVertices
    vector<string> v = G.getVertices();
    ASSERT_TRUE(v.size() == 4);

    // test when no neighbors exist
    nei = G.neighbors("Bobb");
    ASSERT_TRUE(nei.size() == 0);

    G.addVertex("Plex");
    G.addVertex("Allison");
    G.addVertex("Willard");
    G.addVertex("SMQ");
    G.addVertex("Shepard");

    // test when vertices exist
    v = G.getVertices();
    ASSERT_TRUE(v.size() == 9);

    // test when neighbors exist
    G.addEdge("Bobb", "Sargent", 1.0);
    nei = G.neighbors("Bobb");
    ASSERT_TRUE(nei.size() == 1);

    G.addEdge("Sargent", "Allison", 13.0);
    G.addEdge("Allison", "Willard", 5.0);
    G.addEdge("Plex", "Lincoln", 15.0);
    G.addEdge("Elder", "Lincoln", 3.0);
    G.addEdge("Bobb", "Willard", 20.0);
    G.addEdge("Willard", "Allison", 5.0);
    G.addEdge("Shepard", "Allison", 1.00);
    G.addEdge("SMQ", "Willard", 3.0);
    G.addEdge("Sargent", "Sargent", 0.0);
    G.addEdge("Elder", "Sargent", 4.0);
    G.addEdge("Lincoln", "Bobb", 3.0);
    G.addEdge("Plex", "SMQ", 4.0);

    // test neighbor growth
    nei = G.neighbors("Bobb");
    ASSERT_TRUE(nei.size() == 2);
    nei = G.neighbors("Sargent");
    ASSERT_TRUE(nei.size() == 2);

    // adding edge successfully returns true
    ASSERT_TRUE(G.NumEdges() == 13);
    add = G.addEdge("Lincoln", "Elder", 3.0);
    ASSERT_TRUE(G.NumEdges() == 14);
    ASSERT_TRUE(add == true);

    //no test to see if graph is full -> map grows dynamically

    // addVertex returns false
    add = G.addVertex("Sargent");
    ASSERT_TRUE(add == false);

    // addVertex returns true
    add = G.addVertex("Jones");
    ASSERT_TRUE(add == true);

    // size of map and numVertices are the same (numVertices check)
    int size = G.sizeVertices();
    ASSERT_TRUE(size == G.NumVertices());

}

// stress test
TEST(testing, test05) {
    graph<string, double> G;
    for (int i = 0; i < 2000000; i++)
{
    G.addVertex( to_string(i) );
    G.addEdge(to_string(i), to_string(i), 1.0);
}

ASSERT_TRUE( G.NumVertices() == 2000000 );
ASSERT_TRUE(G.NumEdges() == 2000000);
ASSERT_TRUE(G.sizeVertices() == 2000000);
double w;
G.getWeight("1", "1", w);
ASSERT_TRUE(w == 1.0);
ASSERT_TRUE(G.neighbors("1").size() == 1);
ASSERT_TRUE(G.neighbors("32489").size() == 1);
ASSERT_TRUE(G.neighbors("3000000").size() == 0);

}

// different type 
TEST(testing, test06){
    graph<long long, int> G;
    bool add;

    // test when vertex doesn't exist
    set<long long> nei = G.neighbors(4); //SMQ
    ASSERT_TRUE(nei.size() == 0);

    G.addVertex(0); //bobb
    G.addVertex(1); //sarg
    G.addVertex(2); //elder
    G.addVertex(3); //lincoln

    // test getVertices
    vector<long long> v = G.getVertices();
    ASSERT_TRUE(v.size() == 4);

    // test when no neighbors exist
    nei = G.neighbors(0);
    ASSERT_TRUE(nei.size() == 0);

    G.addVertex(5); //plex
    G.addVertex(6); //allison
    G.addVertex(7); //willard
    G.addVertex(4);
    G.addVertex(8); //shepard

    // test when vertices exist
    v = G.getVertices();
    ASSERT_TRUE(v.size() == 9);

    // test when neighbors exist
    G.addEdge(0, 1, 1.0);
    nei = G.neighbors(0);
    ASSERT_TRUE(nei.size() == 1);

    G.addEdge(1, 6, 13.0);
    G.addEdge(6, 7, 5.0);
    G.addEdge(5, 3, 15.0);
    G.addEdge(2, 3, 3.0);
    G.addEdge(0, 7, 20.0);
    G.addEdge(7, 6, 5.0);
    G.addEdge(8, 6, 1.00);
    G.addEdge(4, 7, 3.0);
    G.addEdge(1, 1, 0.0);
    G.addEdge(2, 1, 4.0);
    G.addEdge(3, 0, 3.0);
    G.addEdge(5, 4, 4.0);

    // test neighbor growth
    nei = G.neighbors(0);
    ASSERT_TRUE(nei.size() == 2);
    nei = G.neighbors(1);
    ASSERT_TRUE(nei.size() == 2);

    // adding edge successfully returns true
    ASSERT_TRUE(G.NumEdges() == 13);
    add = G.addEdge(3, 2, 3.0);
    ASSERT_TRUE(G.NumEdges() == 14);
    ASSERT_TRUE(add == true);

    //no test to see if graph is full -> map grows dynamically

    // addVertex returns false
    add = G.addVertex(1);
    ASSERT_TRUE(add == false);

    // addVertex returns true
    add = G.addVertex(9); //jones
    ASSERT_TRUE(add == true);

    // size of map and numVertices are the same (numVertices check)
    int size = G.sizeVertices();
    ASSERT_TRUE(size == G.NumVertices());

}

// different type <string string>
TEST(testing, test07) {
    graph<string, string> G;

    G.addVertex("a");
    G.addVertex("b");
    G.addVertex("c");
    G.addVertex("d");
    G.addVertex("e");
    G.addVertex("f");
    G.addVertex("g");
    G.addVertex("h");

    G.addEdge("a", "b", "Y");
    G.addEdge("a", "c", "A");
    G.addEdge("a", "d", "U");
    G.addEdge("a", "e", "R");
    G.addEdge("a", "f", "I");
    G.addEdge("a", "g", "E");
    G.addEdge("a", "h", "H");
    G.addEdge("b", "a", "W");
    G.addEdge("b", "b", "A");
    G.addEdge("b", "c", "N");
    G.addEdge("b", "d", "G");
    G.addEdge("b", "e", "B");
    G.addEdge("b", "f", "A");
    G.addEdge("b", "g", "B");
    G.addEdge("b", "h", "O");

    ASSERT_TRUE(G.NumEdges() == 15);
    ASSERT_TRUE(G.NumVertices() == 8);




}

int main()
{
    ::testing::InitGoogleTest();

    //
    // run all the tests, returns 0 if they
    // all pass and 1 if any fail:
    //
    int result = RUN_ALL_TESTS();

    return result;
}

