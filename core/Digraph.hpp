// Digraph.hpp
//
// ICS 46 Spring 2018
// Project #5: Rock and Roll Stops the Traffic
//
// This header file declares a class template called Digraph, which is
// intended to implement a generic directed graph.  The implementation
// uses the adjacency lists technique, so each vertex stores a linked
// list of its outgoing edges.
//
// Along with the Digraph class template is a class DigraphException
// and a couple of utility structs that aren't generally useful outside
// of this header file.
//
// In general, directed graphs are all the same, except in the sense
// that they store different kinds of information about each vertex and
// about each edge; these two types are the type parameters to the
// Digraph class template.

#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP

#include <exception>
#include <functional>
#include <list>
#include <map>
#include <utility>
#include <vector>
#include <queue>
#include <iterator>
#include <string>
#include <iostream>
#define INF 0x3f3f3f3f



// DigraphExceptions are thrown from some of the member functions in the
// Digraph class template, so that exception is declared here, so it
// will be available to any code that includes this header file.

class DigraphException : public std::runtime_error
{
public:
    DigraphException(const std::string& reason);
};


inline DigraphException::DigraphException(const std::string& reason)
    : std::runtime_error{reason}
{
}



// A DigraphEdge lists a "from vertex" (the number of the vertex from which
// the edge points), a "to vertex" (the number of the vertex to which the
// edge points), and an EdgeInfo object.  Because different kinds of Digraphs
// store different kinds of edge information, DigraphEdge is a struct template.

template <typename EdgeInfo>
struct DigraphEdge
{
    int fromVertex;
    int toVertex;
    EdgeInfo einfo;
};



// A DigraphVertex includes two things: a VertexInfo object and a list of
// its outgoing edges.  Because different kinds of Digraphs store different
// kinds of vertex and edge information, DigraphVertex is a struct template.

template <typename VertexInfo, typename EdgeInfo>
struct DigraphVertex
{
    VertexInfo vinfo;
    std::list<DigraphEdge<EdgeInfo>> edges;
};



// Digraph is a class template that represents a directed graph implemented
// using adjacency lists.  It takes two type parameters:
//
// * VertexInfo, which specifies the kind of object stored for each vertex
// * EdgeInfo, which specifies the kind of object stored for each edge
//
// You'll need to implement the member functions declared here; each has a
// comment detailing how it is intended to work.
//
// Each vertex in a Digraph is identified uniquely by a "vertex number".
// Vertex numbers are not necessarily sequential and they are not necessarily
// zero- or one-based.

template <typename VertexInfo, typename EdgeInfo>
class Digraph
{
public:
    // The default constructor initializes a new, empty Digraph so that
    // contains no vertices and no edges.
    Digraph();

    // The copy constructor initializes a new Digraph to be a deep copy
    // of another one (i.e., any change to the copy will not affect the
    // original).
    Digraph(const Digraph& d);

    // The move constructor initializes a new Digraph from an expiring one.
    Digraph(Digraph&& d) noexcept;

    // The destructor deallocates any memory associated with the Digraph.
    ~Digraph() noexcept;

    // The assignment operator assigns the contents of the given Digraph
    // into "this" Digraph, with "this" Digraph becoming a separate, deep
    // copy of the contents of the given one (i.e., any change made to
    // "this" Digraph afterward will not affect the other).
    Digraph& operator=(const Digraph& d);

    // The move assignment operator assigns the contents of an expiring
    // Digraph into "this" Digraph.
    Digraph& operator=(Digraph&& d) noexcept;

    // vertices() returns a std::vector containing the vertex numbers of
    // every vertex in this Digraph.
    std::vector<int> vertices() const;

    // edges() returns a std::vector of std::pairs, in which each pair
    // contains the "from" and "to" vertex numbers of an edge in this
    // Digraph.  All edges are included in the std::vector.
    std::vector<std::pair<int, int>> edges() const;

    // This overload of edges() returns a std::vector of std::pairs, in
    // which each pair contains the "from" and "to" vertex numbers of an
    // edge in this Digraph.  Only edges outgoing from the given vertex
    // number are included in the std::vector.  If the given vertex does
    // not exist, a DigraphException is thrown instead.
    std::vector<std::pair<int, int>> edges(int vertex) const;

    // vertexInfo() returns the VertexInfo object belonging to the vertex
    // with the given vertex number.  If that vertex does not exist, a
    // DigraphException is thrown instead.
    VertexInfo vertexInfo(int vertex) const;

    // edgeInfo() returns the EdgeInfo object belonging to the edge
    // with the given "from" and "to" vertex numbers.  If either of those
    // vertices does not exist *or* if the edge does not exist, a
    // DigraphException is thrown instead.
    EdgeInfo edgeInfo(int fromVertex, int toVertex) const;

    // addVertex() adds a vertex to the Digraph with the given vertex
    // number and VertexInfo object.  If there is already a vertex in
    // the graph with the given vertex number, a DigraphException is
    // thrown instead.
    void addVertex(int vertex, const VertexInfo& vinfo);

    // addEdge() adds an edge to the Digraph pointing from the given
    // "from" vertex number to the given "to" vertex number, and
    // associates with the given EdgeInfo object with it.  If one
    // of the vertices does not exist *or* if the same edge is already
    // present in the graph, a DigraphException is thrown instead.
    void addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo);

    // removeVertex() removes the vertex (and all of its incoming
    // and outgoing edges) with the given vertex number from the
    // Digraph.  If the vertex does not exist already, a DigraphException
    // is thrown instead.
    void removeVertex(int vertex);

    // removeEdge() removes the edge pointing from the given "from"
    // vertex number to the given "to" vertex number from the Digraph.
    // If either of these vertices does not exist *or* if the edge
    // is not already present in the graph, a DigraphException is
    // thrown instead.
    void removeEdge(int fromVertex, int toVertex);

    // vertexCount() returns the number of vertices in the graph.
    int vertexCount() const noexcept;

    // edgeCount() returns the total number of edges in the graph,
    // counting edges outgoing from all vertices.
    int edgeCount() const noexcept;

    // This overload of edgeCount() returns the number of edges in
    // the graph that are outgoing from the given vertex number.
    // If the given vertex does not exist, a DigraphException is
    // thrown instead.
    int edgeCount(int vertex) const;

    // isStronglyConnected() returns true if the Digraph is strongly
    // connected (i.e., every vertex is reachable from every other),
    // false otherwise.
    bool isStronglyConnected() const;

    // findShortestPaths() takes a start vertex number and a function
    // that takes an EdgeInfo object and determines an edge weight.
    // It uses Dijkstra's Shortest Path Algorithm to determine the
    // shortest paths from the start vertex to every other vertex
    // in the graph.  The result is returned as a std::map<int, int>
    // where the keys are vertex numbers and the value associated
    // with each key k is the precedessor of that vertex chosen by
    // the algorithm.  For any vertex without a predecessor (e.g.,
    // a vertex that was never reached, or the start vertex itself),
    // the value is simply a copy of the key.
    std::map<int, int> findShortestPaths(
        int startVertex,
        std::function<double(const EdgeInfo&)> edgeWeightFunc) const;


private:
    // Add whatever member variables you think you need here.  One
    // possibility is a std::map where the keys are vertex numbers
    // and the values are DigraphVertex<VertexInfo, EdgeInfo> objects.
  std::map<int, DigraphVertex<VertexInfo, EdgeInfo>> obj;
  void connect(int v, std::map<int, bool>& visited, std::vector<int>& visit) const;
    // You can also feel free to add any additional member functions
    // you'd like (public or private), so long as you don't remove or
    // change the signatures of the ones that already exist.
};



// You'll need to implement the member functions below.  There's enough
// code in place to make them compile, but they'll all need to do the
// correct thing instead.

template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph()
{
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph(const Digraph& d)
{
  //for(typename std::map<int, DigraphVertex<VertexInfo, EdgeInfo>>::iterator iter = d.obj.begin(); iter != d.obj.end(); ++iter)
  for(auto& ent: d.obj)
    {
      obj[ent.first] = ent.second;
    }
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph(Digraph&& d) noexcept
{
  std::swap(obj, d.obj);
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::~Digraph() noexcept
{
  //for(auto const &ent: obj)
  // {
  //   ent->second.edges.clear();
  // }
  obj.clear();
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>& Digraph<VertexInfo, EdgeInfo>::operator=(const Digraph& d)
{
    obj.clear();
    //this->obj = d.obj;
    //return *this;
    //for(typename std::map<int, DigraphVertex<VertexInfo, EdgeInfo>>::iterator iter = d.obj.begin(); iter != d.obj.end(); ++iter)
    for(auto& ent: d.obj)
    {
      obj[ent.first] = ent.second;
    }
    return *this;
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>& Digraph<VertexInfo, EdgeInfo>::operator=(Digraph&& d) noexcept
{
    std::swap(obj, d.obj);
    return *this;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<int> Digraph<VertexInfo, EdgeInfo>::vertices() const
{
  //return std::vector<int>{};
  std::vector<int> vtex;
  for(auto& ent: obj)
    {
      vtex.push_back(ent.first);
    }
  return vtex;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges() const
{
  //return std::vector<std::pair<int, int>>{};
  std::vector<std::pair<int, int>> pts;
  for(auto& outer: obj)
    {
      for(auto& inner: outer.second.edges)
        {
          pts.push_back(std::make_pair(inner.fromVertex, inner.toVertex));
        }
    }
  return pts;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges(int vertex) const
{
  //return std::vector<std::pair<int, int>>{};
  std::vector<std::pair<int, int>> pts;
  if(obj.count(vertex))
    {
      for(auto& ent: obj.at(vertex).edges)
        {
          pts.push_back(std::make_pair(ent.fromVertex, ent.toVertex));
          //pts.push_back(std::make_pair(vertex, ent.toVertex));
        }
      return pts;
    }
  else
    {
      throw DigraphException("Vertex does not exist!\n");
    }
}


template <typename VertexInfo, typename EdgeInfo>
VertexInfo Digraph<VertexInfo, EdgeInfo>::vertexInfo(int vertex) const
{
  //return VertexInfo{};
  /*if(obj.count(vertex))
    {
      return obj.at(vertex).vinfo;
    }
  else
    {
      throw DigraphException("Vertex does not exist!\n");
    }*/
  return obj.count(vertex)? obj.at(vertex).vinfo: throw DigraphException("Vertex does not exist!!!!!!\n");
}


template <typename VertexInfo, typename EdgeInfo>
EdgeInfo Digraph<VertexInfo, EdgeInfo>::edgeInfo(int fromVertex, int toVertex) const
{
  //return EdgeInfo{};
  // EdgeInfo einf;
  std::vector<std::pair<int, int>> from = edges(fromVertex);
  std::pair<int, int> coord = std::make_pair(fromVertex, toVertex);
  if(obj.count(fromVertex) && obj.count(toVertex))
    {  
       if(std::find(from.begin(), from.end(), coord) == from.end())
       {
        throw DigraphException("Edge does not exist!\n");
       }
    }
  else
    {
      throw DigraphException("Edge does not exist!\n");
    }
  for(auto& ent: obj.at(fromVertex).edges)
    {
      if(ent.toVertex == toVertex)
        {
          return ent.einfo;
        }
    }
  //return einf;
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addVertex(int vertex, const VertexInfo& vinfo)
{
  if(!(obj.count(vertex)))
    {
      //DigraphVertex<VertexInfo, EdgeInfo> vtex = DigraphVertex<VertexInfo, EdgeInfo>{vinfo};
      DigraphVertex<VertexInfo, EdgeInfo> vtex{vinfo};
      obj.insert(std::pair<int, DigraphVertex<VertexInfo, EdgeInfo>>(vertex, vtex));
    }
  else
    {
      throw DigraphException("Vertex already exists in the graph!\n");
    }
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo)
{
   std::vector<std::pair<int, int>> from = edges(fromVertex);
   std::pair<int, int> coord = std::make_pair(fromVertex, toVertex);
   if(obj.count(fromVertex) && obj.count(toVertex))
    {
      if(std::find(from.begin(), from.end(), coord) != from.end())
       {
        throw DigraphException("Edge already exists in the graph!\n");
       }
    }
  else
    {
      throw DigraphException("Invalid edge!\n");
    }
   DigraphEdge<EdgeInfo> newEdge{fromVertex, toVertex, einfo};
   obj.at(fromVertex).edges.push_back(newEdge);
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeVertex(int vertex)
{
   if(obj.count(vertex))
    {
      obj.erase(vertex);
    }
  else
    {
      throw DigraphException("Vertex does not exist!\n");
    }
   for(auto& outer: obj)
     {
       for(typename std::list<DigraphEdge<EdgeInfo>>::iterator iter = outer.second.edges.begin(); iter != outer.second.edges.end(); ++iter)
         {
           if(iter->toVertex == vertex)
             {
               outer.second.edges.erase(iter);   
             }
         }
       //obj.erase(vertex);
    }
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeEdge(int fromVertex, int toVertex)
{
  std::pair<int, int> coord = std::make_pair(fromVertex, toVertex);
  std::vector<std::pair<int, int>> from = edges(fromVertex);
  if(obj.count(fromVertex) && obj.count(toVertex))
    {
      if(std::find(from.begin(), from.end(), coord) == from.end())
      {
        throw DigraphException("Edge already exists in the graph!\n");
      }
    }
  else
    {
      throw DigraphException("Vertices entered do not exist!\n");
    }
  /* for(auto& ent: obj.at(fromVertex).edges)
    {
      if(ent.toVertex == toVertex)
        {
          ent.toVertex = obj.erase(toVertex);
        }
    }*/
  for(typename std::list<DigraphEdge<EdgeInfo>>::iterator iter = obj.at(fromVertex).edges.begin(); iter != obj.at(fromVertex).edges.end(); ++iter)
    {
      if(iter->toVertex == toVertex)
        {
          obj.at(fromVertex).edges.erase(iter);   
        }
    }
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::vertexCount() const noexcept
{
  //return 0;
  return obj.size();
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount() const noexcept
{
  //return 0;
  int count = 0;
  for(auto& ent: obj)
    {
      count += ent.second.edges.size();
    }
  return count;
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount(int vertex) const
{
  //return 0;
  if(obj.count(vertex) == 0)
    {
      throw DigraphException("Vertex does not exist!\n");
    }
  //int count = 0;
  //for(auto& _: obj.at(vertex).edges)
  //{
  //  count++;
  //}
  //  return count;
  return obj.at(vertex).edges.size();
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::connect(int v, std::map<int, bool>& visited, std::vector<int>& visit) const
{
  visited[v] = true;
  visit.push_back(v);
  for (auto& ent: obj.at(v).edges)
    {
      if (!visited[ent.toVertex])
        connect(ent.toVertex, visited, visit);
    }
}


template <typename VertexInfo, typename EdgeInfo>
bool Digraph<VertexInfo, EdgeInfo>::isStronglyConnected() const
{
  //return false;
  
  for(auto& outer: obj)
    {
      std::vector<int> visit;
      std::map<int, bool> visited;
      for(auto& inner: obj)
        visited[inner.first] = false;
      
      connect(outer.first, visited, visit);
      if (visit.size() != obj.size())
        return false;
    }
  return true;
}


template <typename VertexInfo, typename EdgeInfo>
std::map<int, int> Digraph<VertexInfo, EdgeInfo>::findShortestPaths(
    int startVertex,
    std::function<double(const EdgeInfo&)> edgeWeightFunc) const
{
  //return std::map<int, int>{};
    std::map<int,bool> kv;
    std::map<int,int> pv;
    std::map<int,double> dv;
    
    class V
    {
      public:
        double weight;
        int v;
        V(){};
        V(double weigh, int vtex):
          weight(weigh), v(vtex) {}
    };

    class compare
    {
    public:
      bool operator()(V& lhs, V& rhs)
      {
        return rhs.weight < lhs.weight;
      }
    };
    
    for(auto& ent: obj)
    {
      kv.emplace(ent.first, 0);
      pv.emplace(ent.first, ent.first);
      if(startVertex != ent.first)
        {
          dv.emplace(ent.first, INF);
        }
      else
        {
          dv.emplace(ent.first, 0);
        }
    }
    
    std::priority_queue<V, std::vector<V>, compare> pq;
    pq.push(V{0, startVertex});
    while(pq.size() != 0)
    {
        V ver = pq.top();
        pq.pop();
        if(!kv.at(ver.v))
        {
            kv.at(ver.v) = 1;
            std::vector<std::pair<int, int>> eg = edges(ver.v);
            for(auto& e: eg)
            {
                EdgeInfo einf = edgeInfo(e.first, e.second);
                double tot = dv[ver.v] + edgeWeightFunc(einf);
                double& tidis = dv.at(e.second);
                if(tidis > tot)
                {
                    tidis = tot;
                    pv.at(e.second) = ver.v;
                    pq.push(V{tot, e.second});
                }
            }
        }
    }
    return pv;
}



#endif // DIGRAPH_HPP

