// CSCE 2110.003
// Kai Gu (kg0909, 11797431)
// Nov 23, 2025
// TA: Yongshuo Liu

#include <iostream>
#include <fstream>
#include <unordered_map>
// Using a set for ease of implementation
#include <unordered_set>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

// adjacency list
unordered_map<string, vector<string>> graph;

// =============================================
// Teaching Function: Print the graph structure
// =============================================
void printGraph() {
    cout << "\n=== Loaded City Graph ===\n";
    for (auto &p : graph) {
        cout << p.first << " -> ";
        for (auto &dest : p.second) {
            cout << dest << " ";
        }
        cout << endl;
    }
}

// =============================================
// Load graph data from file (complete & working)
// =============================================
void loadData(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "File not found: " << filename << endl;
        return;
    }
    string city, nextCity;
    int count;
    while (file >> city >> count) {
        vector<string> neighbors;
        for (int i = 0; i < count; i++) {
            file >> nextCity;
            neighbors.push_back(nextCity);
        }
        graph[city] = neighbors;
    }
    file.close();
}


// Task 1: Route Discovery using BFS

// My reasoning: BFS is chosen for route discovery because it explores
// nodes level by level, guaranteeing the shortest path in terms of
// number of edges (cities). This is ideal for navigation systems where
// we want to minimize the number of stops between cities.

void studentSolveRoute() {
    string start, destination;
    cout << "\nEnter start city: ";
    cin >> start;
    cout << "Enter destination city: ";
    cin >> destination;

    // Check if cities exist in graph
    if (graph.find(start) == graph.end()) {
        cout << "Start city not found in graph.\n";
        return;
    }

    // BFS
    queue<string> q;
    unordered_set<string> visited;
    unordered_map<string, string> parent; // To track the path

    q.push(start);
    visited.insert(start);
    parent[start] = "";

    bool found = false;

    while (!q.empty() && !found) {
        string current = q.front();
        q.pop();

        if (current == destination) {
            found = true;
            break;
        }

        // Explore neighbors
        if (graph.find(current) != graph.end()) {
            for (const string& neighbor : graph[current]) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    parent[neighbor] = current;
                    q.push(neighbor);
                }
            }
        }
    }

    // Display results
    if (found) {
        vector<string> path;
        string current = destination;
        while (current != "") {
            path.push_back(current);
            current = parent[current];
        }

        cout << "Visited: ";
        for (int i = path.size() - 1; i >= 0; i--) {
            cout << path[i];
            if (i > 0) cout << " -> ";
        }
        cout << "\nRoute Found!\n";
    } else {
        cout << "No route found from " << start << " to " << destination << "\n";
    }
}

// Task 2: Reachability using DFS

// My reasoning: Here, DFS is chosen for finding all reachable cities because
// it explores as far as possible along each branch before backtracking.
// This is memory-efficient for exploring all possible connections and
// doesn't require storing level information like BFS. Since we need ALL
// reachable cities (and not shortest paths), DFS is simpler and effective, and thus the
// better choice here.

void studentSolveConnectivity() {
    string start;
    cout << "\nEnter start city: ";
    cin >> start;

    // Check if city exists in graph
    if (graph.find(start) == graph.end()) {
        cout << "City not found in graph.\n";
        return;
    }

    // DFS using stack
    stack<string> s;
    unordered_set<string> visited;
    vector<string> reachable;

    s.push(start);
    visited.insert(start);

    while (!s.empty()) {
        string current = s.top();
        s.pop();

        // Explore neighbors
        if (graph.find(current) != graph.end()) {
            for (const string& neighbor : graph[current]) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    reachable.push_back(neighbor);
                    s.push(neighbor);
                }
            }
        }
    }

    // Display results
    cout << "Reachable cities:\n";
    if (reachable.empty()) {
        cout << "No cities reachable from " << start << "\n";
    } else {
        for (const string& city : reachable) {
            cout << city << "\n";
        }
    }
}

// =============================================
// Teaching Function: How to use this template
// =============================================
void helpStudentsUnderstand() {
    cout << "\n===== How to Use This Template =====\n";
    cout << "Our graph is stored as an adjacency list:\n";
    cout << "unordered_map<string, vector<string>> graph;\n";
    cout << "\nWhere:\n";
    cout << "- Key: a city name (string)\n";
    cout << "- Value: list of cities it has direct roads to\n\n";

    cout << "Example of accessing neighbors:\n";
    cout << "--------------------------------------\n";
    cout << "for (auto city : graph[\"Houston\"]) {\n";
    cout << "    cout << city;\n";
    cout << "}\n";
    cout << "--------------------------------------\n";

    cout << "\nMeaning: from Houston, we iterate all directly reachable cities.\n";

    cout << "\n=====================================\n";
    cout << "Tasks you must complete:\n";
    cout << "-------------------------------------\n";
    cout << "[Task 1] Find a Route between 2 cities\n";
    cout << "→ You choose BFS or DFS based on logic\n";
    cout << "\n[Task 2] List all reachable cities\n";
    cout << "→ You choose BFS or DFS based on logic\n";
    cout << "=====================================\n";

    cout << "\nIMPORTANT: You must decide which algorithm fits better.\n";
    cout << "- BFS → Good for shortest route in navigation\n";
    cout << "- DFS → Good to explore all possible deep connections\n";

    cout << "\nFill your BFS/DFS code ONLY inside:\n";
    cout << "- studentSolveRoute()\n";
    cout << "- studentSolveConnectivity()\n";

    cout << "\nYou can modify:\n";
    cout << "- loadData()\n";
    cout << "- graph structure\n";
    cout << "- menu system\n";

    cout << "\n=====================================\n";
    cout << "Use printGraph() to see real data!\n";
    cout << "=====================================\n";
}

// ====================================================
// Menu
// ====================================================
void menu() {
    int option;
    do {
        helpStudentsUnderstand();
        cout << "\n===== Texas Route Navigation =====\n";
        cout << "1. View Graph\n";
        cout << "2. Task 1: Find Route\n";
        cout << "3. Task 2: Connectivity\n";
        cout << "0. Exit\n";
        cout << "Select: ";
        cin >> option;

        switch(option) {
        case 1:
            printGraph();
            break;
        case 2:
            studentSolveRoute();
            break;
        case 3:
            studentSolveConnectivity();
            break;
        case 0:
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid option\n";
        }
    } while(option != 0);
}

int main() {
    loadData("graph.txt");
    menu();
    return 0;
}
