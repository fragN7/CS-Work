#include <iostream>
#include <vector>
#include <future>
#include <mutex>

const int V = 1000;

std::mutex mtx;

// Function to check if the vertex can be included in the path
bool isSafe(int v, bool graph[V][V], const std::vector<int> &path, int pos) {
    if (!graph[path[pos - 1]][v]) // check if the vertex is adjacent to the previous vertex
        return false;
    for (int i = 0; i < pos; i++) // check if the vertex has already been included
        if (path[i] == v)
            return false;
    return true;
}

// Recursive function to find the Hamiltonian Cycle
std::vector<int> hamCycleUtil(bool graph[V][V], std::vector<int> path, int pos) {
    if (pos == V) {
        if (graph[path[pos - 1]][path[0]]) // check if the last vertex is adjacent to the first vertex
            return path;
        else
            return {}; // return empty vector
    }

    // create a vector of futures to store the results of the recursive calls
    // this is done to avoid the overhead of creating threads for each recursive call
    std::vector<std::future<std::vector<int>>> futures;

    for (int v = 1; v < V; v++) {
        if (isSafe(v, graph, path, pos)) { // check if the vertex can be included

            std::vector<int> newPath = path; // create a new path
            newPath[pos] = v; // add the vertex to the path
            futures.push_back(std::async(std::launch::async, hamCycleUtil, graph, newPath, pos + 1)); // call the function recursively
        }
    }

    for (auto &future: futures) {
        std::vector<int> result = future.get(); // get the result from the future
        if (!result.empty()) // if the result is not empty, return it
            return result;
    }

    return {}; // return empty vector
}

// Function to find the Hamiltonian Cycle
void findHamiltonianCycle(bool graph[V][V], int start_vertex) {
    std::vector<int> path(V, -1); // create a path vector
    path[0] = start_vertex; // add the start vertex to the path

    std::vector<int> resultPath = hamCycleUtil(graph, path, 1); // call the recursive function
    std::lock_guard<std::mutex> lock(mtx); // lock the mutex
    if (resultPath.empty()) {
        std::cout << "No Hamiltonian Cycle found." << std::endl;
    } else {
        std::cout << "Hamiltonian Cycle found starting from vertex " << start_vertex << ": ";
        for (int vertex: resultPath)
            std::cout << vertex << " ";
        std::cout << resultPath[0] << std::endl;
    }
}

int main() {

    bool graph[V][V];
    for (auto & i : graph) {
        for (bool & j : i) {
            j = false;
        }
    }

    for (int i = 0; i < V - 1; ++i) {
        graph[i][i+1] = true;
    }

    graph[V-1][0] = true;

    auto start_time = std::chrono::high_resolution_clock::now();
    findHamiltonianCycle(graph, 0);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time1 = end_time - start_time;
    std::cout << elapsed_time1.count() << " seconds" << std::endl;
    std::cout << std::endl;

    return 0;
}