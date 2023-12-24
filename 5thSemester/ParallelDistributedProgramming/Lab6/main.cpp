#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>

using namespace std;

atomic<bool> isHamiltonian(false);
mutex mtx;

void addEdge(vector<vector<int>>& graph, int u, int v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
}

vector<vector<int>> createHamiltonianCycleGraph(int numNodes) {
    vector<vector<int>> graph(numNodes);

    for (int i = 0; i < numNodes - 1; ++i) {
        addEdge(graph, i, i + 1);
    }
    addEdge(graph, 0, numNodes - 1); // Closing the cycle

    return graph;
}

bool isValidMove(int v, vector<int>& path, vector<vector<int>>& graph, int pos) {

    if (graph[path[pos - 1]][v] == 0)
        return false;

    for (int i = 0; i < pos; ++i)
        if (path[i] == v)
            return false;

    return true;
}

void printPath(const vector<int>& path) {
    cout << "Hamiltonian cycle found: ";
    for (int node : path) {
        cout << node << " ";
    }
    cout << path[0] << endl;
}

void printGraph(const vector<vector<int>>& graph) {
    cout << "Entered graph adjacency matrix: " << endl;
    for (const auto& row : graph) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

void hamiltonianCycleUtil(vector<vector<int>>& graph, vector<int>& path, int pos, int numNodes) {
    if (pos == numNodes) {
        if (graph[path[pos - 1]][path[0]] == 1) {
            lock_guard<mutex> guard(mtx);
            isHamiltonian = true;
            printPath(path);
        }
        return;
    }

    for (int v = 1; v < numNodes; ++v) {
        if (isHamiltonian) return;

        if (isValidMove(v, path, graph, pos)) {
            path[pos] = v;

            hamiltonianCycleUtil(graph, path, pos + 1, numNodes);

            path[pos] = -1;
        }
    }
}

bool isHamiltonianCycle(vector<vector<int>>& graph) {
    int numNodes = graph.size();
    vector<int> path(numNodes, -1);
    path[0] = 2;

    vector<thread> threads;

    for (int i = 1; i < numNodes; ++i) {
        path[1] = i;
        threads.emplace_back(hamiltonianCycleUtil, ref(graph), ref(path), 2, numNodes);
    }

    for (auto& t : threads) {
        t.join();
    }

    return isHamiltonian;
}

int main() {
    int numNodes = 75;

    vector<vector<int>> graph = createHamiltonianCycleGraph(numNodes);

    bool result = isHamiltonianCycle(graph);

    if (result) {
        cout << "The graph contains a Hamiltonian cycle." << endl;
    } else {
        cout << "The graph does not contain a Hamiltonian cycle." << endl;
    }

    return 0;
}
