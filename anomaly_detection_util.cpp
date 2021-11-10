/*
 * animaly_detection_util.cpp
 *
 * Authors : Matan Shamir 206960239 , Itamar Bachar 318781630.
 */

#include <math.h>
#include "anomaly_detection_util.h"

//a simple check for an average of size elements stored in an array of floats.
float avg(float *x, int size) {
    //check if the size isnt 0 to be able to divide by it later.
    if (size < 1) {
        return 0;
    }
    float sum = 0;
    //go through the array and add to sum, eventually return the result of the division.
    for (int i = 0; i < size; i++) {
        sum = sum + x[i];
    }
    return sum / size;
}

// returns the variance of X and Y: simply put, a calculation of the average distance from the average point.
float var(float *x, int size) {
    //again, we can't divide by zero.
    if (size < 1) {
        return 0;
    }
    // calculate the average point to know where to measure the distance from.
    float u = avg(x, size);
    float sum = 0;
    //sum up all of the sqaure x values.
    for (int i = 0; i < size; i++) {
        sum += x[i] * x[i];
    }
    sum = sum / size;
    //return the distance from the squared average value.
    return sum - (u * u);
}

// returns the covariance of X and Y: a relational variance, generaly telling if the two move in the same direction.
float cov(float *x, float *y, int size) {
    if (size < 1) {
        return 0;
    }
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum = sum + (x[i] - avg(x, size)) * (y[i] - avg(y, size));
    }
    return (sum / size);
}


// returns the Pearson correlation coefficient of X and Y.
float pearson(float *x, float *y, int size) {
    if (size < 1) {
        return 0;
    }
    return cov(x,y,size)/(sqrt(var(x,size))*sqrt(var(y,size)));
//    float covariance = cov(x, y, size);
//    float varianceX = var(x, size);
//    float varianceY = var(y, size);
//    float mulitplyXY = sqrt(varianceX) * sqrt(varianceY);
//    return (float) (covariance / mulitplyXY);
}

// performs a linear regression and returns the line equation
Line linear_reg(Point **points, int size) {
    //if the size is smaller then 1, we cant divide by it in the end- termination condition.
    if (size < 1) {
        return Line(0, 0);
    }
    float arrX[size], arrY[size];
    //put the x and y values of the points in two different arrays.
    for (int i = 0; i < size; i++) {
        arrX[i] = points[i]->x;
        arrY[i] = points[i]->y;
    }
    //calculate the covariance of the x values with the y values, and return the line of the linear regression.
    float a = cov(arrX, arrY, size) / var(arrX, size);
    float b = avg(arrY, size) - a * avg(arrX, size);
    return Line(a, b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p, Point **points, int size) {
    if (size < 1) {
        return 0;
    }
    return dev(p, linear_reg(points, size));
}

// returns the deviation between point p and the line
float dev(Point p, Line l) {
    float distance = p.y - l.f(p.x);
    if (distance < 0) {
        return -distance;
    }
    return distance;
}
