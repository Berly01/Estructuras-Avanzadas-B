#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>

auto euclidean_distance(const std::vector<double>& x, std::vector<double>& y);
auto random_points(const int& d, const int& n);
void save_result(const std::vector<double>& vec_result, const std::string& file_path);
void test_1();

int main() {

    test_1();

    return 0;
}

//Funcion que calcula la distancia euclidiana entre dos puntos de una dimension 'n'
auto euclidean_distance(const std::vector<double>& x, std::vector<double>& y) {

    if (x.size() != y.size())
        throw std::invalid_argument("Los puntos ingresados no son de la misma dimension!");

    double result{ 0 };

    for (auto i{ x.cbegin() }, j{ y.cbegin() }; i != x.cend(); i++, j++)
        result += std::pow(*j - *i, 2);

    return std::sqrt(result);
}

//Genera 'n' puntos de una dimension 'd' con valores aleatorios entre 0 y 1
auto random_points(const int& d, const int& n) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> random_distribution(0.0, 1.0);

    std::vector<double> point;
    std::vector<std::vector<double>> vec_points;

    for (auto i{ 0 }; i < n; i++) {
        for (auto j{ 0 }; j < d; j++) {
            point.push_back(random_distribution(generator));
        }
        vec_points.push_back(point);
        point.clear();
    }

    return vec_points;
}

//Guarda los resultados obtenidos en un archivo txt para luego ser abierto en python para graficarlo
void save_result(const std::vector<double>& vec_result, const std::string& file_path) {

    std::ofstream out_file(file_path, std::ios::out);

    for (const auto& i : vec_result)
        out_file << std::to_string(i) << '\n';

    out_file.close();
}

//Funcion principal
void test_1() {
    const auto DIMENSIONS = { 2, 10, 50, 100, 500, 1000, 2000, 5000 };
    const auto SIZE{ 100 };
    const std::string PATH_FILE{ "results" };
    std::stringstream ss;
    std::vector<std::vector<double>> vec_points;
    std::vector<double> vec_result;

    for (const auto& D : DIMENSIONS) {

        //Se generan 100 puntos aleatorios con una dimension 'D' y se guardan en 'vec_points'
        vec_points = random_points(D, SIZE);

        //Se hace el calculo de la distancia euclidiana con cada punto y se guarda en vec_result
        for (int i = 0; i < vec_points.size() - 1; i++) {
            for (int j = i + 1; j < vec_points.size(); j++)
                vec_result.push_back(euclidean_distance(vec_points[i], vec_points[j]));
        }

        //std::cout << vec_result.size() << '\n'; //Genera 4950 resultados

        ss << PATH_FILE << "_dimension_" << D << ".txt";

        std::cout << "Se creo el archivo: " << ss.str() << '\n';

        //Se guarda los resultados en archivos de texto para luego ser cargados y graficados en python 
        //en el archivo 'generateGraphics.py'
        save_result(vec_result, ss.str());

        //Se borra el contenido de los vectores para poder cargar los demas resultados
        ss.str("");
        vec_points.clear();
        vec_result.clear();
    }
}
