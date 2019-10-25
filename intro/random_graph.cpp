#include <random>
#include <utility>
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/erdos_renyi_generator.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/mersenne_twister.hpp>

using std::cout;
using std::endl;

typedef boost::adjacency_list<> Graph;
// typedef adjacency_list<vecS, vecS, undirectedS> Graph;
typedef boost::erdos_renyi_iterator<boost::minstd_rand, Graph> ERGen;
// typedef boost::erdos_renyi_iterator<boost::mt19937, Graph> ERGen;

int main()
{
    using namespace std;
    using namespace boost;
    boost::minstd_rand gen;
    // Create graph with 10 nodes and edges with probability 0.5
    int N = 10;
    double p = 0.2;
    Graph g(ERGen(gen, N, p), ERGen(), N);

    typedef graph_traits<Graph>::edge_iterator edge_iterator;
    pair<edge_iterator, edge_iterator> ei = edges(g);

    // for (edge_iterator edge_iter = ei.first; edge_iter != ei.second; ++edge_iter)
    // {
    //     cout << "(" << source(*edge_iter, g) << ", " << target(*edge_iter, g) << ")\n";
    // }
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