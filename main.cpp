 /*C++ program to print DFS, BFS traversal from
a given vertex in a  given GraphDFS
Scripts  taken from: 
https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/
https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/ 
https://www.geeksforgeeks.org/iterative-deepening-searchids-iterative-deepening-depth-first-searchiddfs/
  */

#include <bits/stdc++.h>
using namespace std;
#include<iostream>
#include <list>

// GraphDFS class represents a directed GraphDFS
// using adjacency list representation

//*******************************DFS*********************************
class GraphDFS {
public:
    map<int, bool> visited;
    map<int, list<int> > adj;
 
    // function to add an edge to GraphDFS
    void addEdgeDFS(int v, int w);
 
    // DFS traversal of the vertices
    // reachable from v
    void DFS(int v);
};
 
void GraphDFS::addEdgeDFS(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}
 
void GraphDFS::DFS(int v)
{
    // Mark the current node as visited and
    // print it
    visited[v] = true;
    cout << v << " ";
 
    // Recur for all the vertices adjacent
    // to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFS(*i);
}
//*******************************BFS*********************************
class GraphBFS
{
    int V;    // No. of vertices
 
    // Pointer to an array containing adjacency
    // lists
    list<int> *adj;  
public:
    GraphBFS(int V);  // Constructor
 
    // function to add an edge to GraphBFS
    void addEdgeBFS(int v, int w);
 
    // prints BFS traversal from a given source s
    void BFS(int s); 
};
 
GraphBFS::GraphBFS(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
void GraphBFS::addEdgeBFS(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}
 
void GraphBFS::BFS(int s)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;
 
    // Create a queue for BFS
    list<int> queue;
 
    // Mark the current node as visited and enqueue it
    visited[s] = true;
    queue.push_back(s);
 
    // 'i' will be used to get all adjacent
    // vertices of a vertex
    list<int>::iterator i;
 
    while(!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        s = queue.front();
        cout << s << " ";
        queue.pop_front();
 
        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        for (i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if (!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
}

//*******************************IDS*********************************
class GraphIDS
{
    int V;    // No. of vertices
  
    // Pointer to an array containing
    // adjacency lists
    list<int> *adj;
    vector<int> visited;
  
    // A function used by IDDFS
    bool DLS(int v, int destiny, int limit);
  
public:
    GraphIDS(int V);   // Constructor
    void addEdgeIDS(int v, int w);
  
    // IDDFS traversal of the vertices reachable from v
    bool IDDFS(int v, int destiny, int max_depth);
};

GraphIDS::GraphIDS(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
  
void GraphIDS::addEdgeIDS(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}

// IDDFS to search if destiny is reachable from v.
// It uses recursive DFSUtil().
bool GraphIDS::IDDFS(int source, int destiny, int max_depth)
{
    // Repeatedly depth-limit search till the
    // maximum depth.
    for (int i = 0; i <= max_depth; i++)
      if (DLS(source, destiny, i) == true)
        return true;
  
    return false;
}

bool GraphIDS::DLS(int source, int destiny, int limit)
{
    if (source == destiny)
        return true;
  
    // If reached the maximum depth, stop recursing.
    if (limit <= 0)
        return false;

    // Recur for all the vertices adjacent to source vertex
    for (auto i = adj[source].begin(); i != adj[source].end(); ++i){
      if (!(std::find(visited.begin(), visited.end(), *i) != visited.end())) {
        visited.push_back(*i);
        cout << *i << " ";
      }
      if (DLS(*i, destiny, limit-1) == true)
          return true;
      }
     return false;
}

//******************DFS source-destination*****************
class GraphDFS_SD {
    int V; // No. of vertices in graph
    list<int>* adj; // Pointer to an array containing adjacency lists
 
    // A recursive function used by printAllPaths()
    void printAllPathsUtilDFS_SD(int, int, bool[], int[], int&);
 
public:
    GraphDFS_SD(int V); // Constructor
    void addEdgeDFS_SD(int u, int v);
    void printAllPathsDFS_SD(int s, int d);
};
 
GraphDFS_SD::GraphDFS_SD(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
void GraphDFS_SD::addEdgeDFS_SD(int u, int v)
{
    adj[u].push_back(v); // Add v to u’s list.
}
 
// Prints all paths from 's' to 'd'
void GraphDFS_SD::printAllPathsDFS_SD(int s, int d)
{
    // Mark all the vertices as not visited
    bool* visited = new bool[V];
 
    // Create an array to store paths
    int* path = new int[V];
    int path_index = 0; // Initialize path[] as empty
 
    // Initialize all vertices as not visited
    for (int i = 0; i < V; i++)
        visited[i] = false;
 
    // Call the recursive helper function to print all paths
    printAllPathsUtilDFS_SD(s, d, visited, path, path_index);
}
 
// A recursive function to print all paths from 'u' to 'd'.
// visited[] keeps track of vertices in current path.
// path[] stores actual vertices and path_index is current
// index in path[]
void GraphDFS_SD::printAllPathsUtilDFS_SD(int u, int d, bool visited[],
                              int path[], int& path_index)
{
    // Mark the current node and store it in path[]
    visited[u] = true;
    path[path_index] = u;
    path_index++;
 
    // If current vertex is same as destination, then print
    // current path[]
    if (u == d) {
        for (int i = 0; i < path_index; i++)
            cout << path[i] << " ";
        cout << endl;
    }
    else // If current vertex is not destination
    {
        // Recur for all the vertices adjacent to current vertex
        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (!visited[*i])
                printAllPathsUtilDFS_SD(*i, d, visited, path, path_index);
    }
 
    // Remove current vertex from path[] and mark it as unvisited
    path_index--;
    visited[u] = false;
}

// Driver code
int main()
{
  int initial_node = 0;
  int nodes = 6;
   // Create a GraphDFS and GrapfhBFS given in the above diagram
    GraphDFS g;
    GraphBFS h(nodes);
    GraphIDS i(nodes);
    GraphDFS_SD j(nodes);
    int maxDepth = 2, source = 2, destiny =3;
    std::ifstream ifs{ "graph.txt" };
    // read line by line
    std::string line;
    while(std::getline(ifs, line)) {
      std::istringstream iss{ line }; // make a stream on the line
      auto values = std::make_pair<int, int>(0, 0);
      if(iss >> values.first >> values.second) {   
        g.addEdgeDFS(values.first, values.second);
        h.addEdgeBFS(values.first, values.second);
        i.addEdgeIDS(values.first, values.second);
        j.addEdgeDFS_SD(values.first, values.second);
      } else {
        throw std::runtime_error{ "bad data" };
      }
    }
  
    cout << "\nFollowing is Depth First Traversal"
            " (starting from vertex "<<initial_node<<") \n";
    //Initial node
    g.DFS(initial_node);
  cout << "\nFollowing is Breadth First Traversal"
            " (starting from vertex "<<initial_node<<") \n";
    h.BFS(initial_node);

  cout << "\nFollowing is Iterative Deepening Search Traversal";
  if (i.IDDFS(source, destiny, maxDepth) == true)
        cout << "destiny is reachable from source "
                "within max depth";
    else
        cout << "destiny is NOT reachable from source "
                "within max depth";

  cout << "\nFollowing are DFS from source " << source << " to destiny " << destiny << endl;
    j.printAllPathsDFS_SD(source, destiny);
    return 0;
}
 
// improved by Vishnudev C0 1