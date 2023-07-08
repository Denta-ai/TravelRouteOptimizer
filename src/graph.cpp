#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct Point {
    double x;
    double y;
    int label;
};

void loadEdges(const std::string& flePnts, const std::string& fleEdges) {
    std::ifstream pntsFile("D:/Github-Projects/TravelRouteOptimizer/db/" + flePnts);
    std::ifstream edgesFile("D:/Github-Projects/TravelRouteOptimizer/db/" + fleEdges);

    if (!pntsFile.is_open() || !edgesFile.is_open()) {
        std::cout << "Failed to open the files." << std::endl;
        return;
    }

    std::vector<Point> points;
    std::string line;
    while (std::getline(pntsFile, line)) {
        std::istringstream iss(line);
        Point p;
        if (iss >> p.x >> p.y >> p.label) {
            points.push_back(p);
        }
    }

    std::ofstream outputFile("D:/Github-Projects/TravelRouteOptimizer/db/edges_data.txt");
    std::vector<bool> visited(points.size(), false);
    while (std::getline(edgesFile, line)) {
        std::istringstream iss(line);
        int index1, index2;
        if (iss >> index1 >> index2) {
            if (index1 >= 0 && index1 < points.size() && index2 >= 0 && index2 < points.size()) {
                if (!visited[index1]) {
                    outputFile << points[index1].x << " " << points[index1].y << " " << points[index1].label << "\n";
                    visited[index1] = true;
                }
                if (!visited[index2]) {
                    outputFile << points[index2].x << " " << points[index2].y << " " << points[index2].label << "\n";
                    visited[index2] = true;
                }
                outputFile << "\n";
                outputFile << points[index1].x << " " << points[index1].y << "\n";
                outputFile << points[index2].x << " " << points[index2].y << "\n\n";
            }
        }
    }

    pntsFile.close();
    edgesFile.close();
    outputFile.close();
}


void loadWeights(const std::string& flePnts, const std::string& fleEdges) {
    std::ifstream pntsFile("D:/Github-Projects/TravelRouteOptimizer/db/" + flePnts);
    std::ifstream edgesFile("D:/Github-Projects/TravelRouteOptimizer/db/" + fleEdges);

    if (!pntsFile.is_open() || !edgesFile.is_open()) {
        std::cout << "Failed to open the files." << std::endl;
        return;
    }

    std::vector<Point> points;
    std::string line;
    while (std::getline(pntsFile, line)) {
        std::istringstream iss(line);
        Point p;
        if (iss >> p.x >> p.y) {
            points.push_back(p);
        }
    }

    std::ofstream outputFile("D:/Github-Projects/TravelRouteOptimizer/db/weights_data.txt");
    while (std::getline(edgesFile, line)) {
        std::istringstream iss(line);
        int index1, index2;
        double weight;
        double offsetX, offsetY;
        if (iss >> index1 >> index2 >> weight >> offsetX >> offsetY) {
            if (index1 >= 0 && index1 < points.size() && index2 >= 0 && index2 < points.size()) {
                double averageX = (points[index1].x + points[index2].x) / 2.0 + offsetX;
                double averageY = (points[index1].y + points[index2].y) / 2.0 + offsetY;
                outputFile << averageX << "\t" << averageY << "\t" << weight << "\n";
            }
        }
    }

    pntsFile.close();
    edgesFile.close();
    outputFile.close();
}

void generateGraph() {
    std::string flePnts = "pnts.txt";
    std::string fleEdges = "edges.txt";

    std::ofstream pntsFile("D:/Github-Projects/TravelRouteOptimizer/db/" + flePnts);
    if (!pntsFile.is_open()) {
        std::cout << "Failed to open the pnts.txt file." << std::endl;
        return;
    }

    pntsFile << "50 50 0\n";
    pntsFile << "50 30 1\n";
    pntsFile << "30 50 2\n";
    pntsFile << "50 70 3\n";
    pntsFile << "70 50 4\n";
    pntsFile << "70 75 5\n";
    pntsFile << "70 25 6\n";
    pntsFile << "30 75 7\n";
    pntsFile << "30 25 8\n";
    pntsFile << "45 80 9\n"; // root label 3
    pntsFile << "55 80 10\n";
    pntsFile << "45 20 11\n"; // root label 1
    pntsFile << "55 20 12\n";
    pntsFile << "75 60 13\n"; // root label 4
    pntsFile << "75 40 14\n";
    pntsFile << "25 60 15\n"; // root label 2
    pntsFile << "25 40 16\n";
    pntsFile << "75 90 17\n"; // root label 5
    pntsFile << "80 80 18\n";
    pntsFile << "80 20 19\n"; // root label 6
    pntsFile << "75 12 20\n";
    pntsFile << "25 90 21\n"; // root label 7
    pntsFile << "20 80 22\n";
    pntsFile << "20 20 23\n"; // root label 8
    pntsFile << "25 12 24\n";

    pntsFile.close();

    std::ofstream edgesFile("D:/Github-Projects/TravelRouteOptimizer/db/" + fleEdges);
    if (!edgesFile.is_open()) {
        std::cout << "Failed to open the edges.txt file." << std::endl;
        return;
    }

    edgesFile << "0 1 30 0 0\n";
    edgesFile << "0 2 15 0 0\n";
    edgesFile << "0 3 20 0 0\n";
    edgesFile << "0 4 10 0 0\n";
    edgesFile << "0 5 12 0 0\n";
    edgesFile << "0 6 15 0 0\n";
    edgesFile << "0 7 11 0 0\n";
    edgesFile << "0 8 19 0 0\n";
    edgesFile << "3 9 2 0 0\n";
    edgesFile << "3 10 3 0 0\n";
    edgesFile << "1 11 1 0 0\n";
    edgesFile << "1 12 4 0 0\n";
    edgesFile << "4 13 2 0 0\n";
    edgesFile << "4 14 1 0 0\n";
    edgesFile << "2 15 3 0 0\n";
    edgesFile << "2 16 6 0 0\n";
    edgesFile << "5 17 8 0 0\n";
    edgesFile << "5 18 6 0 0\n";
    edgesFile << "6 19 2 0 0\n";
    edgesFile << "6 20 1 0 0\n";
    edgesFile << "7 21 4 0 0\n";
    edgesFile << "7 22 6 0 0\n";
    edgesFile << "8 23 2 0 0\n";
    edgesFile << "8 24 5 0 0\n";
    edgesFile << "21 9 13 0 0\n";
    edgesFile << "22 15 11 0 0\n";
    edgesFile << "16 23 16 0 0\n";
    edgesFile << "24 11 18 0 0\n";
    edgesFile << "12 20 11 0 0\n";
    edgesFile << "19 14 14 0 0\n";
    edgesFile << "13 18 19 0 0\n";
    edgesFile << "17 10 10 0 0\n";
    edgesFile << "1 8 24 0 0\n";
    edgesFile << "1 6 34 0 0\n";
    edgesFile << "2 8 22 0 0\n";
    edgesFile << "2 7 45 0 0\n";
    edgesFile << "3 7 37 0 0\n";
    edgesFile << "3 5 40 0 0\n";
    edgesFile << "4 5 22 0 0\n";
    edgesFile << "4 6 21 0 0\n";

    edgesFile.close();

    loadEdges(flePnts, fleEdges);
    loadWeights(flePnts, fleEdges);

    FILE* gnuplotPipe = _popen("gnuplot -persist", "w");
    if (!gnuplotPipe) {
        std::cerr << "Error opening Gnuplot pipe." << std::endl;
        return;
    }

    fprintf(gnuplotPipe, "set terminal png\n");
    fprintf(gnuplotPipe, "set output 'D:/Github-Projects/TravelRouteOptimizer/img/graph.png'\n");
    fprintf(gnuplotPipe, "set key off\n");
    fprintf(gnuplotPipe, "set xrange [0:100]\n");
    fprintf(gnuplotPipe, "set yrange [0:100]\n");
    fprintf(gnuplotPipe, "plot 'D:/Github-Projects/TravelRouteOptimizer/db/edges_data.txt' using 1:2:3 with labels font ',8' offset -1,-1 textcolor 'black' point pt 7 ps 2 notitle,'' using 1:2 with linespoint pt 7 ps 2 notitle,'D:/Github-Projects/TravelRouteOptimizer/db/weights_data.txt' using 1:2:3 with labels tc rgb 'red' notitle\n");

    _pclose(gnuplotPipe);

    std::string command = "start D:/Github-Projects/TravelRouteOptimizer/img/graph.png";
    system(command.c_str());

    return;
}