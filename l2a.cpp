#include <iostream>
#include <vector>
#include <string>

class Point {
public:
    int x;
    int y;
    Point(int x, int y) : x(x), y(y) {}
};

class PointsInField {
private:
    int n;
    std::vector<Point> points;

public:
    PointsInField(int n) : n(n) {
        int x, y;
        for (int i = 0; i < n; i++) {
            std::cin >> x >> y;
            Point p(x, y);
            points.push_back(p);
        }
    }
    void printPoints() const {
        for (int i = 0; i < n; i++) {
            std::cout << points[i].x << " " << points[i].y << std::endl;
        }
    }
    void printResult() const {
        int minX, minY, maxX, maxY;
        minX = points[0].x;
        maxX = points[0].x;
        minY = points[0].y;
        maxY = points[0].y;
        for (int i = 1; i < n; i++) {
            minX = (points[i].x < minX) ? points[i].x : minX;
            maxX = (points[i].x > maxX) ? points[i].x : maxX;
            //std::cout << "i = " << i << " " << maxX << std::endl;
            minY = (points[i].y < minY) ? points[i].y : minY;
            maxY = (points[i].y > maxY) ? points[i].y : maxY;
        }
        std::cout << minX << " " << minY << " " << maxX << " " << maxY << std::endl;
    }
};

int main() {
    int n;
    std::cin >> n;
    
    PointsInField field(n);
    field.printResult();
    //field.printPoints();

    return 0;
}
