#include <iostream>
#include <vector>
#include <algorithm>

/*
 * Алгоритм Дейкстры. Нахождение кратчайшего пути в графе.
 * Входные данные: матрица смежности графа, номер начальной вершины, номер конечной вершины.
 * Выходные данные: кратчайший путь от начальной вершины до конечной и его длина.
 */
std::pair<std::vector<int>, int> dijkstra(std::vector<std::vector<int>> graph, int start, int stop) {
    std::vector<int> dist(graph.size(), INT_MAX);  // расстояние от старта до вершины i
    std::vector<int> prev(graph.size(), -1);  // предыдущая вершина в кратчайшем пути
    std::vector<bool> visited(graph.size(), false);  // посещена ли вершина
    dist[start] = 0;
    for (int i = 0; i < graph.size(); i++) {
        int min = INT_MAX;
        int min_index = -1;
        for (int j = 0; j < graph.size(); j++) {
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                min_index = j;
            }
        }
        if (min_index == -1) {
            // нет пути (вершина была удалена)
            continue;
        }
        visited[min_index] = true;
        for (int j = 0; j < graph.size(); j++) {
            if (!visited[j] && graph[min_index][j] && dist[min_index] != INT_MAX && dist[min_index] + graph[min_index][j] < dist[j]) {
                dist[j] = dist[min_index] + graph[min_index][j];
                prev[j] = min_index;
            }
        }
    }
    std::vector<int> path;
    int current = stop;
    while (current != -1) {
        path.push_back(current);
        current = prev[current];
    }
    std::reverse(path.begin(), path.end());  // восстанавливаем путь
    return std::make_pair(path, dist[stop]);
}


/*
 * Алгоритм Йена. Нахождение k кратчайших путей в графе.
 * Входные данные: матрица смежности графа, номер начальной вершины, номер конечной вершины, количество путей.
 * Выходные данные: k кратчайших путей от начальной вершины до конечной и их длины.
 */
std::vector<std::pair<std::vector<int>, int>> yens_algorithm(std::vector<std::vector<int>> graph, int start, int stop, int K) {
    std::vector<std::pair<std::vector<int>, int>> paths;  // найденные пути

    std::pair<std::vector<int>, int> first_path = dijkstra(graph, start, stop);
    paths.push_back(first_path);

    std::vector<std::pair<std::vector<int>, int>> candidates;  // кандидаты на следующий кратчайший путь
    for (int k = 1; k < K; k++) {
        std::vector<std::vector<int>> new_graph = graph;  // копируем граф для изменения

        for (int i = 0; i < paths[k - 1].first.size() - 1; i++) {  // для каждой вершины в (k-1)-м кратчайшем пути
            int spur_node = paths[k - 1].first[i];  // вершина ветвления
            std::vector<int> root_path = std::vector<int>(paths[k - 1].first.begin(), paths[k - 1].first.begin() + i + 1);  // путь до вершины ветвления

            for (auto path : paths) {
                if (std::equal(root_path.begin(), root_path.end(), path.first.begin())) {
                    // удаляем все связи, являющиеся частью предыдущих кратчайших путей
                    new_graph[path.first[i]][path.first[i + 1]] = 0;
                    new_graph[path.first[i + 1]][path.first[i]] = 0;  // если граф неориентированный
                }
            }

            for (int v = 0; v < root_path.size() - 1; v++) {
                if (root_path[v] != spur_node) {
                    for (int w = 0; w < graph.size(); w++) {
                        new_graph[root_path[v]][w] = 0;
                        new_graph[w][root_path[v]] = 0;  // если граф неориентированный
                    }
                }
            }

            std::pair<std::vector<int>, int> spur_path = dijkstra(new_graph, spur_node, stop);  // находим кратчайший путь ветвления
            if (spur_path.second != INT_MAX) {
                // собираем путь как путь до вершины ветвления + путь ветвления
                std::vector<int> total_path = root_path;
                total_path.insert(total_path.end(), spur_path.first.begin() + 1, spur_path.first.end());

                int new_cost = 0;
                for (int j = 0; j < total_path.size() - 1; j++) {
                    new_cost += graph[total_path[j]][total_path[j + 1]];
                }
                candidates.emplace_back(total_path, new_cost);  // добавляем путь и его длину в кандидаты
            }
        }
        if (candidates.empty()) {
            break;
        }
        // выбираем из кандидатов путь с минимальной длиной
        std::sort(candidates.begin(), candidates.end(),
                  [](const std::pair<std::vector<int>, int>& a,
                          const std::pair<std::vector<int>, int>& b) { return a.second < b.second; });
        paths.push_back(candidates[0]);
        candidates.clear();
    }
    return paths;
}

int main() {
    int v;  // количество вершин
    std::cout << "Введите количество вершин графа: ";
    std::cin >> v;
    std::vector<std::vector<int>> adj(v, std::vector<int>(v, 0));  // матрица смежности
    std::cout << "Введите тройки (начало, конец, вес) для каждого ребра, -1 для остановки ввода: " << std::endl;
    int from, to, weight;
    while (true) {
        std::cin >> from;
        if (from == -1) break;
        from--;  // индексация с 0
        std::cin >> to >> weight;
        to--;  // индексация с 0
        adj[from][to] = weight;
        adj[to][from] = weight;  // если граф неориентированный
    }

    int start, stop, k;
    std::cout << "Введите начальную вершину, конечную и количество кратчайших маршрутов для поиска: ";
    std::cin >> start >> stop >> k;
    start--;  // индексация с 0
    stop--;  // индексация с 0
    std::vector<std::pair<std::vector<int>, int>> paths = yens_algorithm(adj, start, stop, k);
    for (int i = 0; i < paths.size(); i++) {
        std::cout << "Путь " << i + 1 << ": ";
        for (int j = 0; j < paths[i].first.size(); j++) {
            std::cout << paths[i].first[j] + 1 << " ";  // индексация с 0, выводим с 1
        }
        std::cout << "(длина " << paths[i].second << ")" << std::endl;
    }
}
