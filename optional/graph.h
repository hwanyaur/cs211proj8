/*graph.h*/

//
// Graph class implemented as ...
// 
//    an adjacency list
// 
// For this implementation of graph, the vertices are 
// VertexT, and the weights are WeightT.  Example:
// 
//   graph  G;
//   G.addVertex("Chicago");
//   G.addVertex("New York");
//   G.addEdge("Chicago", "New York", -999.99);
//
// Yaurie HWang
//
// Northwestern University
// CS 211: Winter 2023
//

#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

template<typename VertexT, typename WeightT>
class graph {

private:
  map<VertexT, vector<pair<VertexT, WeightT>> > Vertices;
  int EdgeCount;
  int VertexCount;
  
  


public:
  
//
// constructor
//
graph()
{
    VertexCount = 0;
    EdgeCount = 0;
}

//
// NumVertices
//
// Returns the # of vertices currently in the graph.
//
int NumVertices() const{
    return VertexCount;
}
 
//
// NumEdges
//
// Returns the # of edges currently in the graph.
//
int NumEdges() const{
    return EdgeCount;
}

//
// addVertex
//
// Adds the vertex v to the graph if there's room, and if so
// returns true.  If the graph is full, or the vertex already
// exists in the graph, then false is returned.
//
bool addVertex(VertexT v) {
    // if not found, add to map
    if (Vertices.find(v) == Vertices.end()) {
        //////// if graph is full, return false /////////
        Vertices.emplace(v, std::vector<std::pair<VertexT, WeightT>>{});
        VertexCount += 1;
        return true;
    }
    // if vertex exists, return false
    return false;

  //NOTE: no check needed to see if graph is full -> map grows dynamically
}

//
  // addEdge
  //
  // Adds the edge (from, to, weight) to the graph, and returns
  // true. If the vertices do not exist then no edge is added
  // and false is returned.
  //
  // NOTE: if the edge already exists, the existing edge weight
  // is overwritten with the new edge weight.
  //
bool addEdge(VertexT from, VertexT to, WeightT weight) {
    if (Vertices.find(from) == Vertices.end()) {
        return false;
    }
    if (Vertices.find(to) == Vertices.end()) {
        return false;
    }
    //vertices exist, add to graph
    // vector<pair<VertexT, WeightT>> list = *Vertices[from].second; // get vector of edges for 'from'
    
    // if 'from' not in Vertices, will create a new one
    auto& edges = Vertices[from];
    for (auto& pair : edges) {
    // iterate though Vertices[from]. If 'to' exists, rewrite it
    if (pair.first == to) {
      pair.second = weight; //overwrite
      return true;
    }
    }
    // 'to' not in Vertices, will push back
    edges.push_back(make_pair(to, weight));
    EdgeCount += 1;
    return true;
  }

//
  // getWeight
  //
  // Returns the weight associated with a given edge.  If 
  // the edge exists, the weight is returned via the reference
  // parameter and true is returned. If the edge does not 
  // exist, the weight parameter is unchanged and false is
  // returned.
  //
bool getWeight(VertexT from, VertexT to, WeightT& weight) const {
  // check if vertices exist.
  // if 'from' is a vertex, fromExists = vector of edges
  // if 'from' doesn't exist, fromExists = end of map
  auto fromExists = Vertices.find(from);
  if (fromExists == Vertices.end()) {
    return false;
  }

  for (auto& pair : fromExists->second) {
    // iterate though Vertices[from]. If 'to' exists, get the weight
    if (pair.first == to) {
      weight = pair.second; //change weight
      return true;
    }
    }
  // edge 'from'->'to' doesn't exist 
  return false;
}

//
  // neighbors
  //
  // Returns a set containing the neighbors of v, i.e. all
  // vertices that can be reached from v along one edge. If
  // v does not exist, an empty set is returned.
  //
set<VertexT> neighbors(VertexT v) const {
  set<VertexT> ans; //will be returned

  // check if vertices exist.
  // if 'from' is a vertex, fromExists = vector of edges
  // if 'from' doesn't exist, fromExists = end of map
  auto fromExists = Vertices.find(v);
  if (fromExists == Vertices.end()) {
    return ans;
  }

  // iterate through all pairs in edges of 'from' and insert into answer set
  for (const auto& pair : fromExists->second) {
    ans.insert(pair.first);
  }
  return ans;
}

  //
  // getVertices
  //
  // Returns a vector containing all the vertices currently in
  // the graph. There is no guaranteed order to the vertices 
  // in the returned vector; the order should be considered 
  // random.
  //
vector<VertexT> getVertices() const{
  vector<VertexT> ans;
  for (auto& v : Vertices) {
    ans.push_back(v.first);
  }
  return ans;
}

  //
  // print
  // 
  // Prints the internal state of the graph to the given 
  // output stream for debugging purposes. The output will
  // contain the # of vertices, the # of edges, the vertices,
  // and the edges. Vertices are output as st rings and the 
  // weights as doub les.
  //
  // Example:
  //    graph G;
  //    ...
  //    G.print(cout);  // print to console
  //
void print(ostream& output) const{
  cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  cout << "Number of Vertices: " << VertexCount << endl;
  cout << "Number of Edges: " << EdgeCount << endl;
  cout << endl;

  // iterate through each vertex
  for (auto& v : Vertices) {
    cout << "Vertex " << v.first << endl;

    // iterate through each edge
    for (auto& pair: v.second) {
      cout << "   ~ Edge " << pair.first << ", Weight " << pair.second << endl;
    }
  }
  cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
}

//
// sizeVertices
// 
// returns the size of Vertices map
int sizeVertices() const{
  return Vertices.size();
}

};
