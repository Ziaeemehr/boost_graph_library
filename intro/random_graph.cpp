#include <random>
#include <utility>
#include <iostream>
#include <chrono>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/erdos_renyi_generator.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/mersenne_twister.hpp>

using std::cout;
using std::endl;

typedef boost::minstd_rand base_generator_type;
typedef boost::adjacency_list<> Graph;
typedef boost::erdos_renyi_iterator<base_generator_type, Graph> ERGenerator;

int main()
{
    // Create graph with "N" nodes and edges with probability "p"
    using namespace std;
    using namespace boost;

    base_generator_type generator;
    unsigned long int seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    generator.seed(seed);
    int N = 10;
    double p = 0.5;
    Graph g(ERGenerator(generator, N, p), ERGenerator(), N);

    typedef graph_traits<Graph>::edge_iterator edge_iterator;
    pair<edge_iterator, edge_iterator> ei = edges(g);

    // cout << "# number of edges :  " << num_edges(g) << endl;

    vector<vector<int>> mat(N, vector<int>(N));
    for (edge_iterator edge_iter = ei.first; edge_iter != ei.second; ++edge_iter)
    {
        int a = source(*edge_iter, g);
        int b = target(*edge_iter, g);
        mat[a][b] = 1;
        mat[b][a] = 1;
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

// for (edge_iterator edge_iter = ei.first; edge_iter != ei.second; ++edge_iter)
// {
//     cout << "(" << source(*edge_iter, g) << ", " << target(*edge_iter, g) << ")\n";
// }
// typedef adjacency_list<vecS, vecS, undirectedS> Graph;