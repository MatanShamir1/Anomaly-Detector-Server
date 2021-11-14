#include <algorithm>
#include <math.h>
#include <vector>
#include "anomaly_detection_util.h"
#include "minCircle.h"

// the function return the min circle that included all the value.
Circle findMinCircle(Point **points, size_t size) {
    vector<Point> copy;
    for (int i = 0; i < size; i++) {
        copy.push_back(*(points[i]));
    }
    vector<Point> R;
    return helpToFind(copy, R, size);
}

Circle helpToFind(vector<Point> &P, vector<Point> R, int currentSizeOfCircle) {
    if (currentSizeOfCircle == 0 || R.size() == 3) {
        return createCircle(R);
    }
    int indx = rand() % currentSizeOfCircle;
    Point p = Point(P[indx].x, P[indx].y);
// changing the location of the point that we want to removed to the last.
    swap(P[indx], P[currentSizeOfCircle - 1]);
    // go recursively to find circle that contain all the other point except the one we removed.
    Circle d = helpToFind(P, R, currentSizeOfCircle - 1);
    // If d contains p, return d
    if (isInside(d, p)) {
        return d;
    }
    // the point isnt in the circle so put her as boundary.
    R.push_back(p);
// return circle that have the point as boundary point.
    return helpToFind(P, R, currentSizeOfCircle - 1);
}

//the function create or return the minimum circle that contain all the points.
Circle createCircle(vector<Point> &P) {
    if (P.empty()) {
        return Circle(Point(0, 0), 0);
    } else if (P.size() == 1) {
        return Circle(P[0], 0);
    } else if (P.size() == 2) {
        return createCircleFrom2Points(P[0], P[1]);
    }
    // check if that we can have circle with two points only.
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            Circle c = createCircleFrom2Points(P[i], P[j]);
            if (isEnclosingCircle(c, P))
                return c;
        }
    }
    return createCircleFrom3Points(P[0], P[1], P[2]);
}

// the function create circle from two points.
Circle createCircleFrom2Points(const Point &A, const Point &B) {
    // Set the center to be the midpoint of A and B
    Point C = Point((A.x + B.x) / 2, (A.y + B.y) / 2);
    // Set the radius to be half the distance AB
    return Circle(C, distance(A, B) / 2);
}

// check if the circle have all the points inside her.
bool isEnclosingCircle(const Circle &c, const vector<Point> &P) {
    // check if indeed all the points are in the circle.
    for (const Point &p: P)
        if (!isInside(c, p))
            return false;
    return true;
}

// calculate distance between two points
float distance(const Point &a, const Point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool isInside(const Circle &c, const Point &p) {
    return distance(c.center, p) <= c.radius;
}

// the function find center two circle that must include three points
Point findCenter(float bx, float by, float cx, float cy) {
    float B = bx * bx + by * by;
    float C = cx * cx + cy * cy;
    float D = bx * cy - by * cx;
    return Point((cy * B - by * C) / (2 * D), (bx * C - cx * B) / (2 * D));
}

// the function create circle from three points .
Circle createCircleFrom3Points(const Point &A, const Point &B, const Point &C) {
    Point I = findCenter(B.x - A.x, B.y - A.y, C.x - A.x, C.y - A.y);
    I.x += A.x;
    I.y += A.y;
    return Circle(I, distance(I, A));
}
