#include <iostream>  // for std::cout
#include <utility>   // for std::pair
#include <algorithm> // for std::for_each
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

#include <vector>
#include <type_traits>
#include <typeinfo>
#ifndef _MSC_VER
#include <cxxabi.h>
#endif
#include <memory>
#include <string>
#include <cstdlib>

template <class T>
std::string
type_name()
{
    typedef typename std::remove_reference<T>::type TR;
    std::unique_ptr<char, void (*)(void *)> own(
#ifndef _MSC_VER
        abi::__cxa_demangle(typeid(TR).name(), nullptr,
                            nullptr, nullptr),
#else
        nullptr,
#endif
        std::free);
    std::string r = own != nullptr ? own.get() : typeid(TR).name();
    if (std::is_const<TR>::value)
        r += " const";
    if (std::is_volatile<TR>::value)
        r += " volatile";
    if (std::is_lvalue_reference<T>::value)
        r += "&";
    else if (std::is_rvalue_reference<T>::value)
        r += "&&";
    return r;
}

using std::cout;
using std::endl;

//-------------------------------------------------------------------------------------------------

int main(int, char *[])
{
    using namespace boost;
    // create a typedef for the Graph type
    // directedS or bidirectionalS (for directed graphs)
    // undirectedS (for undirected graphs)
    typedef adjacency_list<vecS, vecS, undirectedS> Graph; //bidirectionalS

    // Make convenient labels for the vertices
    enum
    {
        A,
        B,
        C,
        D,
        E,
        N
    };
    const int number_of_vertices = N;
    const char name[] = "ABCDE";

    // writing out the edges in the graph
    typedef std::pair<int, int> Edge;
    Edge edge_array[] =
        {
            Edge(A, B),
            Edge(A, D),
            Edge(C, A),
            Edge(D, C),
            Edge(C, E),
            Edge(B, D),
            Edge(D, E),
        };
    const int number_of_edges = sizeof(edge_array) / sizeof(edge_array[0]);

    // adding edge method 1 -----------------------------------------------------------------------
    // declare a graph object
    Graph g(number_of_vertices);

    // add the edges to the graph object
    for (int i = 0; i < number_of_edges; ++i)
        add_edge(edge_array[i].first, edge_array[i].second, g);
    // adding edge method 2------------------------------------------------------------------------
    // Graph g(edge_array, edge_array + sizeof(edge_array) / sizeof(Edge), num_vertices);

    //Accessing the Vertex Set---------------------------------------------------------------------

    typedef graph_traits<Graph>::vertex_descriptor Vertex;

    // get the property map for vertex indices
    typedef property_map<Graph, vertex_index_t>::type IndexMap;
    IndexMap vertex_id = get(vertex_index, g);

    std::cout << "vertices(g) = ";
    typedef graph_traits<Graph>::vertex_iterator vertex_iter;

    std::pair<vertex_iter, vertex_iter> vp;
    for (vp = vertices(g); vp.first != vp.second; ++vp.first)
    {
        Vertex v = *vp.first;
        std::cout << vertex_id[v] << " ";
        // cout << v << " "; //is equivalent
    }
    std::cout << std::endl;

    // Accessing the Edge Set----------------------------------------------------------------------
    std::cout << "edges(g) = ";
    graph_traits<Graph>::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
        std::cout << "(" << vertex_id[source(*ei, g)]
                  << "," << vertex_id[target(*ei, g)] << ") ";
    std::cout << std::endl;

    // Write out all adjacent vertices ------------------------------------------------------------
    std::cout << "adjacent vertices: \n";
    typename graph_traits<Graph>::adjacency_iterator ai, ai_end;
    for (vp = vertices(g); vp.first != vp.second; ++vp.first)
    {
        Vertex v = *vp.first;
        std::cout << name[vertex_id[v]] << " : ";
        for (boost::tie(ai, ai_end) = adjacent_vertices(v, g); ai != ai_end; ++ai)
            std::cout << name[get(vertex_id, *ai)] << " ";
        std::cout << std::endl;
    }

    // Write out all in-edges----------------------------------------------------------------------
    std::cout << "in-edges : \n";
    typename graph_traits<Graph>::edge_descriptor e;
    typename graph_traits<Graph>::in_edge_iterator in_i, in_end;
    for (vp = vertices(g); vp.first != vp.second; ++vp.first)
    {
        Vertex v = *vp.first;
        std::cout << name[vertex_id[v]] << " : ";
        for (boost::tie(in_i, in_end) = in_edges(v, g); in_i != in_end; ++in_i)
        {
            e = *in_i;
            Vertex src = source(e, g);
            Vertex targ = target(e, g);
            std::cout << "(" << name[get(vertex_id, src)]
                      << "," << name[get(vertex_id, targ)] << ") ";
        }
        cout << endl;
    }

    // Write out all out-edges----------------------------------------------------------------------
    std::cout << "out-edges : \n";
    // typename graph_traits<Graph>::edge_descriptor e;
    typename graph_traits<Graph>::out_edge_iterator out_i, out_end;
    for (vp = vertices(g); vp.first != vp.second; ++vp.first)
    {
        Vertex v = *vp.first;
        std::cout << name[vertex_id[v]] << " : ";
        for (boost::tie(out_i, out_end) = out_edges(v, g); out_i != out_end; ++out_i)
        {
            e = *out_i;
            Vertex src = source(e, g);
            Vertex targ = target(e, g);
            std::cout << "(" << name[get(vertex_id, src)]
                      << "," << name[get(vertex_id, targ)] << ") ";
        }
        cout << endl;
    }
    auto nv = num_vertices(g);
    cout << "number of edges : " << num_edges(g) << endl;
    cout << "number of vertixes : " << num_vertices(g) << endl;

    // std::cout << type_name<decltype(nv)>() << '\n';

        return 0;
}