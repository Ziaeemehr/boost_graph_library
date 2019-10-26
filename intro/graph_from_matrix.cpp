#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <sys/stat.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/erdos_renyi_generator.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/mersenne_twister.hpp>

typedef std::vector<int> dim1I;
typedef std::vector<std::vector<int>> dim2I;

/*------------------------------------------------------------*/
bool fileExists(const std::string &filename)
{
    /*return true if input file exists*/
    struct stat buf;
    if (stat(filename.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}
/*------------------------------------------------------------*/
dim2I read_matrix(std::string filename, int Node)
{
    /*get filename and number of row to read a square matrix 
    intput:
        filename: name of text file to read
        Node: number of rows or cols of square matrix
    return:
        matrix as a 2 dimensional double vector

    example: read_matrix("A.txt", 100);
    */
    std::ifstream ifile(filename);

    /*to check if input file exists*/
    if (fileExists(filename))
    {
        dim2I Cij(Node, dim1I(Node));

        for (int i = 0; i < Node; i++)
        {
            for (int j = 0; j < Node; j++)
            {
                ifile >> Cij[i][j];
            }
        }
        ifile.close();
        return Cij;
    }
    else
    {
        std::cerr << "\n file : " << filename << " not found \n";
        exit(2);
    }
}
/*------------------------------------------------------------*/

int main(int argc, char *argv[])
{
    using namespace boost;
    typedef boost::adjacency_list<vecS, vecS, undirectedS> Graph;

    int N = 10;
    dim2I matrix = read_matrix("matrix.txt", N);
    Graph G(N);

    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = i + 1; j < N; j++)
        {
            if (matrix[i][j] != 0)
                add_edge(i, j, G);
        }
    }

    std::cout << num_edges(G) << std::endl;

    typedef graph_traits<Graph>::edge_iterator edge_iterator;
    std::pair<edge_iterator, edge_iterator> ei = edges(G);
    dim2I mat(N, dim1I(N));
    for (edge_iterator edge_iter = ei.first; edge_iter != ei.second; ++edge_iter)
    {
        int a = source(*edge_iter, G);
        int b = target(*edge_iter, G);
        mat[a][b] = 1;
        mat[b][a] = 1;
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}