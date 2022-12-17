#include <iostream>
#include <chrono>

void bruteForceMethod(int m, const int* Z, const int* C, int* min_cost, int* min_city, int* min_direction) {
    for (int i = 0; i < m; i++) {
        // Изначально считаем, что минимальная стоимость заправки в городе i - это заправка в самом городе
        min_cost[i] = Z[i];
        min_city[i] = i;
        min_direction[i] = 0;
    }
    for (int i = 0; i < m; i++) {
        int road_cost_0 = 0;  // стоимость проезда по часовой стрелке
        int road_cost_1 = 0;  // стоимость проезда против часовой стрелки
        for (int j = 1; j < m; j++) {
            road_cost_0 += C[(i + j - 1) % m];
            road_cost_1 += C[(i - j + m) % m];
            if (road_cost_0 + Z[(i + j) % m] < min_cost[i]) {  // едем по часовой стрелке
                min_cost[i] = road_cost_0 + Z[(i + j) % m];
                min_city[i] = (i + j) % m;
                min_direction[i] = 0;
            }
            if (road_cost_1 + Z[(i - j + m) % m] < min_cost[i]) {  // едем против часовой стрелки
                min_cost[i] = road_cost_1 + Z[(i - j + m) % m];
                min_city[i] = (i - j + m) % m;
                min_direction[i] = 1;
            }
        }
    }
}

void branchAndBoundMethod(int m, const int* Z, const int* C, int* min_cost, int* min_city, int* min_direction) {
    for (int i = 0; i < m; i++) {
        // Изначально считаем, что минимальная стоимость заправки в городе i - это заправка в самом городе
        min_cost[i] = Z[i];
        min_city[i] = i;
        min_direction[i] = 0;
    }
    int road_cost;
    for (int i = 0; i < m; i++) {
        // Обходим все города по часовой стрелке
        road_cost = 0;
        for (int j = 1; j < m; j++) {
            road_cost += C[(i + j - 1) % m];
            if (road_cost >= Z[i]) {  // Граница, дальше которой не имеет смысла идти
                break;
            }
            if (road_cost + Z[(i + j) % m] < min_cost[i]) {
                min_cost[i] = road_cost + Z[(i + j) % m];
                min_city[i] = (i + j) % m;
                min_direction[i] = 0;
            }
        }

        // Обходим все города против часовой стрелки
        road_cost = 0;
        for (int j = 1; j < m; j++) {
            road_cost += C[(i - j + m) % m];
            if (road_cost >= Z[i]) {  // Граница, дальше которой не имеет смысла идти
                break;
            }
            if (road_cost + Z[(i - j + m) % m] < min_cost[i]) {
                min_cost[i] = road_cost + Z[(i - j + m) % m];
                min_city[i] = (i - j + m) % m;
                min_direction[i] = 1;
            }
        }
    }
}

int main() {
    int m; // количество городов
    std::cout << "Введите количество городов: ";
    std::cin >> m;

    int* Z = new int[m]; // стоимость заправки в городе i
    int* C = new int[m]; // стоимость проезда по дороге из i в i + 1 город

    std::cout << "Введите стоимость заправки в городах: ";
    for (int i = 0; i < m; i++) {
        std::cin >> Z[i];
    }

    std::cout << "Введите стоимость проезда по дорогам: ";
    for (int i = 0; i < m; i++) {
        std::cin >> C[i];
    }

    int* min_cost = new int[m];  // минимальная стоимость заправки в городе
    int* min_city = new int[m];  // город, в который необходимо съездить, чтобы заправиться самым дешевым образом
    int* min_direction = new int[m];  // направление - «по часовой стрелке» (0) или «против часовой стрелки» (1)

    auto start = std::chrono::high_resolution_clock::now();
//    bruteForceMethod(m, Z, C, min_cost, min_city, min_direction);
    branchAndBoundMethod(m, Z, C, min_cost, min_city, min_direction);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "\nВремя выполнения: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns\n\n";

    for (int i = 0; i < m; i++) {
        std::cout << "Для города " << i << ": ";
        if (i == min_city[i]) {
            std::cout << "заправляться в этом городе. ";
        } else {
            std::cout << "съездить в город " << min_city[i]
                 << (min_direction[i] == 0 ? " по часовой стрелке. " : " против часовой стрелки. ");
        }
        std::cout << "Стоимость: " << min_cost[i] << std::endl;
    }
    return 0;
}