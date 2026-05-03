#include <iostream>
#include <climits>

using namespace std;

const int INF = INT_MAX / 4;

void printAdjacencyMatrix(int** matrix, int n) {
    cout << "The adjacency matrix of G is:" << endl;

    int i;
    int j;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void printOddNodes(int* oddNodes, int oddCount) {
    cout << "The nodes with odd degrees in G are:" << endl;
    cout << "O = { ";

    int i;
    for (i = 0; i < oddCount; i++) {
        cout << oddNodes[i];
        if (i < oddCount - 1) {
            cout << " ";
        }
    }

    cout << " }" << endl;
}

void dijkstra(int** matrix, int n, int start, int* dist, bool* visited) {
    int i;
    int count;

    for (i = 1; i <= n; i++) {
        dist[i] = INF;
        visited[i] = false;
    }

    dist[start] = 0;

    for (count = 1; count <= n; count++) {
        int minDistance = INF;
        int current = -1;

        for (i = 1; i <= n; i++) {
            if (!visited[i] && dist[i] < minDistance) {
                minDistance = dist[i];
                current = i;
            }
        }

        if (current == -1) {
            return;
        }

        visited[current] = true;

        for (i = 1; i <= n; i++) {
            if (!visited[i] && matrix[current][i] > 0) {
                int newDistance = dist[current] + matrix[current][i];
                if (newDistance < dist[i]) {
                    dist[i] = newDistance;
                }
            }
        }
    }
}

void printDistances(int start, int* dist, int n) {
    cout << "The shortest path lengths from Node " << start
         << " to all other nodes are:" << endl;

    int i;
    for (i = 1; i <= n; i++) {
        cout << "  " << i << ": " << dist[i] << endl;
    }
}

int main() {
    int numOfVertices;
    int numOfEdges;

    if (!(cin >> numOfVertices >> numOfEdges)) {
        return 0;
    }

    int** adjacencyMatrix = new int*[numOfVertices + 1];
    int* degree = new int[numOfVertices + 1];

    int i;
    int j;
    for (i = 0; i <= numOfVertices; i++) {
        adjacencyMatrix[i] = new int[numOfVertices + 1];
        degree[i] = 0;
        for (j = 0; j <= numOfVertices; j++) {
            adjacencyMatrix[i][j] = 0;
        }
    }

    for (i = 0; i < numOfEdges; i++) {
        int startVertex;
        int endVertex;
        int weight;

        cin >> startVertex >> endVertex >> weight;

        adjacencyMatrix[startVertex][endVertex] = weight;
        adjacencyMatrix[endVertex][startVertex] = weight;
        degree[startVertex]++;
        degree[endVertex]++;
    }

    int* oddNodes = new int[numOfVertices];
    int oddCount = 0;

    for (i = 1; i <= numOfVertices; i++) {
        if (degree[i] % 2 == 1) {
            oddNodes[oddCount] = i;
            oddCount++;
        }
    }

    printAdjacencyMatrix(adjacencyMatrix, numOfVertices);
    cout << endl;

    printOddNodes(oddNodes, oddCount);
    cout << endl;

    int* dist = new int[numOfVertices + 1];
    bool* visited = new bool[numOfVertices + 1];

    for (i = 0; i < oddCount; i++) {
        dijkstra(adjacencyMatrix, numOfVertices, oddNodes[i], dist, visited);
        printDistances(oddNodes[i], dist, numOfVertices);

        if (i < oddCount - 1) {
            cout << endl;
        }
    }

    delete[] dist;
    delete[] visited;
    delete[] oddNodes;
    delete[] degree;

    for (i = 0; i <= numOfVertices; i++) {
        delete[] adjacencyMatrix[i];
    }
    delete[] adjacencyMatrix;

    return 0;
}
