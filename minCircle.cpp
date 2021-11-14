#include <algorithm>
#include <assert.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "anomaly_detection_util.h"
#include "minCircle.h"


Circle findMinCircle(Point **points, size_t size) {
    vector<Point> copy;
    for (int i = 0; i < size; i++) {
        copy.push_back(*(points[i]));
    }
    vector<Point> R;
    return helpToFind(copy, R, size);
}

Circle helpToFind(vector<Point> &P, vector<Point> R, int currentSizeOfCircle) {
    // Base case when all points processed or |R| = 3
    if (currentSizeOfCircle == 0 || R.size() == 3) {
        return min_circle_trivial(R);
    }
    // Pick a random point randomly
    int idx = rand() % currentSizeOfCircle;
    Point p = Point(P[idx].x, P[idx].y);
    // Put the picked point at the end of P
    // since it's more efficient than
    // deleting from the middle of the vector
    swap(P[idx], P[currentSizeOfCircle - 1]);
    // Get the MEC circle d from the
    // set of points P - {p}
    Circle d = helpToFind(P, R, currentSizeOfCircle - 1);
    // If d contains p, return d
    if (is_inside(d, p)) {
        return d;
    }
    // Otherwise, must be on the boundary of the MEC
    R.push_back(p);
    // Return the MEC for P - {p} and R U {p}
    return helpToFind(P, R, currentSizeOfCircle - 1);
}

// Function to return the minimum enclosing
// circle for N <= 3
Circle min_circle_trivial(vector<Point> &P) {
    assert(P.size() <= 3);
    if (P.empty()) {
        return Circle(Point(0, 0), 0);
    } else if (P.size() == 1) {
        return Circle(P[0], 0);
    } else if (P.size() == 2) {
        return circle_from(P[0], P[1]);
    }
    // To check if MEC can be determined
    // by 2 points only
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            Circle c = circle_from(P[i], P[j]);
            if (is_valid_circle(c, P))
                return c;
        }
    }
    return circle_from(P[0], P[1], P[2]);
}

// Function to return the smallest circle
// that intersects 2 points
Circle circle_from(const Point &A, const Point &B) {
    // Set the center to be the midpoint of A and B
    Point C = Point((A.x + B.x) / 2.0, (A.y + B.y) / 2.0);
    // Set the radius to be half the distance AB
    return Circle(C, dist(A, B) / 2.0);
}

// Function to check whether a circle
// encloses the given points
bool is_valid_circle(const Circle &c, const vector<Point> &P) {
    // Iterating through all the points
    // to check  whether the points
    // lie inside the circle or not
    for (const Point &p: P)
        if (!is_inside(c, p))
            return false;
    return true;
}

// Function to return the euclidean distance
// between two points
float dist(const Point &a, const Point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// Function to check whether a point lies inside
// or on the boundaries of the circle
bool is_inside(const Circle &c, const Point &p) {
    return dist(c.center, p) <= c.radius;
}

// The following two functions are used
// To find the equation of the circle when
// three points are given.
// Helper method to get a circle defined by 3 points
Point get_circle_center(float bx, float by, float cx, float cy) {
    float B = bx * bx + by * by;
    float C = cx * cx + cy * cy;
    float D = bx * cy - by * cx;
    return Point((cy * B - by * C) / (2 * D), (bx * C - cx * B) / (2 * D));
}

// Function to return a unique circle that
// intersects three points
Circle circle_from(const Point &A, const Point &B, const Point &C) {
    Point I = get_circle_center(B.x - A.x, B.y - A.y, C.x - A.x, C.y - A.y);
    I.x += A.x;
    I.y += A.y;
    return Circle(I, dist(I, A));
}
