
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

Circle createCircle(vector<Point> &);

Circle createCircleFrom2Points(const Point &, const Point &);

bool isEnclosingCircle(const Circle &, const vector<Point> &);

Point findCenter(double, double, double, double);

bool isInside(const Circle &, const Point &);

float distance(const Point &, const Point &);

Circle createCircleFrom3Points(const Point &, const Point &, const Point &);


#endif /* MINCIRCLE_H_ */