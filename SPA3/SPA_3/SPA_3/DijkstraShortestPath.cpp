#include "DijkstraShortestPath.h"


int DijkstraShortestPath::get_rnd(double chance_of_1)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    double random_value = dis(gen);

    if (random_value < chance_of_1) {
        return 1;
    }
    else {
        return 0;
    }
}

DijkstraShortestPath::DijkstraShortestPath(int row_a, int column_a, int row_b, int column_b, bool walls)
{
    this->row_a = row_a;
    this->column_a = column_a;
    this->row_b = row_b;
    this->column_b = column_b;
    this->walls = walls;

    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if ((i == row_a - 1 && j == column_a - 1) || (i == row_b - 1 && j == column_b - 1)) {
                map[i][j] = 0; // Empty cell for the positions of A and B
            }
            else if (walls)
            {
                map[i][j] = get_rnd(0.20); 
            }
            else
            {
                map[i][j] = 0;
            }
        }
    }
    adjacency_list_t adjacency_list(rows * columns + 1);  

    // Add edges between cells
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            // Skip walls
            if (map[i][j] == 1) {
                continue;
            }

            
            if (i > 0 && map[i - 1][j] != 1) {
                adjacency_list[i * columns + j].push_back(neighbor((i - 1) * columns + j, 1));  
            }

            if (j > 0 && map[i][j - 1] != 1) {
                adjacency_list[i * columns + j].push_back(neighbor(i * columns + j - 1, 1));  
            }

           
            if (j < columns - 1 && map[i][j + 1] != 1) {
                adjacency_list[i * columns + j].push_back(neighbor(i * columns + j + 1, 1));  
            }

           
            if (i < rows - 1 && map[i + 1][j] != 1) {
                adjacency_list[i * columns + j].push_back(neighbor((i + 1) * columns + j, 1));  // Connect to the below cell
            }
        }
    }
    if (walls)
    {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (map[i][j] == 1) {
                    adjacency_list[rows * columns].push_back(neighbor(i * columns + j, max_weight));  // Connect walls to other vertices with infinite weight
                }
            }
        }
    }

    std::vector<weight_t> min_distance;
    std::vector<vertex_t> previous;
    DijkstraComputePaths((row_a - 1) * columns + column_a - 1, adjacency_list, min_distance, previous);
    std::list<vertex_t> path = DijkstraGetShortestPathTo((row_b - 1) * columns + column_b - 1, previous);

    std::list<vertex_t> adjusted_path = path;

    drawMap(adjusted_path, map, row_a, column_a, row_b, column_b);
    Sleep(100);

    for (const vertex_t& vertex : adjusted_path)
    {
        int row = vertex / columns;
        int column = vertex % columns;
        map[row][column] = 2; 
        drawMap(adjusted_path, map, row_a, column_a, row_b, column_b);
        Sleep(100);
    }
}

void DijkstraShortestPath::DijkstraComputePaths(vertex_t source, const adjacency_list_t& adjacency_list, std::vector<weight_t>& min_distance, std::vector<vertex_t>& previous)
{
    int n = adjacency_list.size();
    min_distance.clear();
    min_distance.resize(n, max_weight);
    min_distance[source] = 0;
    previous.clear();
    previous.resize(n, -1);
    std::set<std::pair<weight_t, vertex_t>> vertex_queue;
    vertex_queue.insert(std::make_pair(min_distance[source], source));

    while (!vertex_queue.empty())
    {
        weight_t dist = vertex_queue.begin()->first;
        vertex_t u = vertex_queue.begin()->second;
        vertex_queue.erase(vertex_queue.begin());

        
        const std::vector<neighbor>& neighbors = adjacency_list[u];
        for (const neighbor& neighbor_iter : neighbors)
        {
            vertex_t v = neighbor_iter.target;
            weight_t weight = neighbor_iter.weight;

           
            if (weight == max_weight)
                continue;

            weight_t distance_through_u = dist + weight;
            if (distance_through_u < min_distance[v])
            {
                vertex_queue.erase(std::make_pair(min_distance[v], v));

                min_distance[v] = distance_through_u;
                previous[v] = u;
                vertex_queue.insert(std::make_pair(min_distance[v], v));
            }
        }
    }
}

std::list<vertex_t> DijkstraShortestPath::DijkstraGetShortestPathTo(vertex_t vertex, const std::vector<vertex_t>& previous)
{
    std::list<vertex_t> path;
    for (; vertex != -1; vertex = previous[vertex])
        path.push_front(vertex);
    return path;
}

void DijkstraShortestPath::drawMap(const std::list<vertex_t>& adjusted_path, int map[20][40], int row_a, int column_a, int row_b, int column_b)
{
    system("cls");
    
    for (int i = 0; i < 20; ++i)
    {
        for (int j = 0; j < 40; ++j)
        {
            if (i == row_a - 1 && j == column_a - 1)
                cout << "A ";
            else if (i == row_b - 1 && j == column_b - 1)
                cout << "B ";
            else if (map[i][j] == 1)
                cout << "# ";
            else if (map[i][j] == 2)
                cout << "* ";
            else
                cout << ". ";
        }
        cout << endl;
    }
}
