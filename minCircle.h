
#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"


using namespace std;


// ------------ DO NOT CHANGE -----------
class Circle {
public:
    Point center;
    float radius;

    Circle(Point c, float r) : center(c), radius(r) {}
};

// --------------------------------------
Circle findMinCircle(Point **points, size_t size);

// you can add here additional methods
Circle helpToFind(vector<Point> &, vector<Point>, int);

Circle min_circle_trivial(vector<Point> &);

Circle circle_from(const Point &, const Point &);

bool is_valid_circle(const Circle &, const vector<Point> &);
Point get_circle_center(double bx, double by,double cx, double cy);
bool is_inside(const Circle& c, const Point& p);
float dist(const Point& a, const Point& b);
Circle circle_from(const Point &, const Point &, const Point &);


#endif /* MINCIRCLE_H_ */