#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/betweenness_centrality.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/property_map/property_map.hpp>
#include <map>
#include <iostream>

int main() {
    // Define the graph using an adjacency list
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;
    typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
    typedef boost::graph_traits<Graph>::edge_descriptor Edge;

    // Creating the graph for the pgRouting Sample Data
    Graph g(17);

    // Adding the edges manually
    add_edge(4, 5, g);
    add_edge(5, 9, g);
    add_edge(9, 14, g);
    add_edge(5, 6, g);
    add_edge(9, 10, g);
    add_edge(0, 2, g);
    add_edge(2, 6, g);
    add_edge(6, 10, g);
    add_edge(10, 15, g);
    add_edge(6, 7, g);
    add_edge(10, 11, g);
    add_edge(7, 11, g);
    add_edge(11, 16, g);
    add_edge(7, 8, g);
    add_edge(15, 16, g);
    add_edge(14, 15, g);
    add_edge(1, 3, g);
    add_edge(12, 13, g);
    // Property map to store the centrality values for each edge
    std::map<Edge, double> edge_centrality_map;
    boost::associative_property_map<std::map<Edge, double>> centrality_map(edge_centrality_map);

    // Compute edge betweenness centrality
    brandes_betweenness_centrality(g, boost::edge_centrality_map(centrality_map).vertex_index_map(get(boost::vertex_index, g)));

    // Number of vertices in the graph
    std::size_t n = num_vertices(g);
    double normalization_factor = (n - 1) * (n - 2) / 2.0;

    // Output the relative centrality values
		double sum = 0;
    BGL_FORALL_EDGES(edge, g, Graph) {
        double relative_centrality = centrality_map[edge] / normalization_factor;
				std::cout << "Edge (" << source(edge, g) << ", " << target(edge, g) << "): " << relative_centrality << std::endl;
    }
    return 0;
}

