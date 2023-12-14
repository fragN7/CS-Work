#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <random>

using namespace std;

auto start_time = std::chrono::high_resolution_clock::now();

mutex mtx; // Mutex for synchronization
atomic<bool> cycleFound(false); // Atomic flag to signal cycle found

// Function to generate a random directed graph
vector<vector<int>> generateRandomGraph(int V) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 1);

    vector<vector<int>> graph(V, vector<int>(V, 0));

    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i != j) {
                // Assigning random edge values (0 or 1) to represent the existence of edges
                graph[i][j] = dis(gen);
            }
        }
    }

    return graph;
}

// A utility function to check if the current path is a Hamiltonian cycle
bool isHamiltonianCycle(const vector<int>& path, vector<vector<int>>& graph) {
    int V = graph.size();
    // Check if all vertices are included and there is an edge from the last vertex to the starting vertex
    if (path.size() == V && graph[path.back()][path[0]])
        return true;
    else
        return false;
}

// Function to explore paths in parallel using threads
void explorePaths(vector<vector<int>>& graph, vector<int>& path, vector<bool>& visited) {
    int V = graph.size();
    if (path.size() == V) {
        if (isHamiltonianCycle(path, graph)) {
            lock_guard<mutex> lock(mtx);
            cycleFound = true;
            cout << "Hamiltonian Cycle Found: ";
            for (int i : path) {
                cout << i << " ";
            }
            cout << path[0] << endl;

            auto end_time = std::chrono::high_resolution_clock::now(); // Stop measuring time
            std::chrono::duration<double> time = end_time - start_time;

            cout << "Time taken: " << time.count() << " seconds" << endl;
            exit(0);
        }
        return;
    }

    int current = path.back();

    for (int i = 0; i < V; ++i) {
        if (!visited[i] && graph[current][i]) {
            path.push_back(i);
            visited[i] = true;

            explorePaths(graph, path, visited);

            path.pop_back();
            visited[i] = false;

            if (cycleFound) // If cycle found by another thread, stop exploring
                return;
        }
    }
}

// Function to find the first Hamiltonian cycle in the graph using multiple threads
void findFirstHamiltonianCycle(vector<vector<int>>& graph, int start) {
    int V = graph.size();

    vector<int> path;
    path.push_back(start);
    vector<bool> visited(V, false);
    visited[start] = true;

    vector<thread> threads;

    for (int i = 0; i < V; ++i) {
        if (graph[start][i]) {
            path.push_back(i);
            visited[i] = true;

            threads.emplace_back(explorePaths, ref(graph), ref(path), ref(visited));

            path.pop_back();
            visited[i] = false;
        }
    }

    for (auto& t : threads) {
        t.join();
    }

    if (!cycleFound) {
        cout << "No Hamiltonian Cycle Found" << endl;
    }
}

int main() {
    int V = 120;

    vector<vector<int>> graph = generateRandomGraph(V);
    int startVertex = 5;


    start_time = std::chrono::high_resolution_clock::now();

    findFirstHamiltonianCycle(graph, startVertex);

    return 0;
}
