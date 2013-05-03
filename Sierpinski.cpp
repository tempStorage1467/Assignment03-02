/*
 * File: Sierpinski.cpp
 * ----------------------
 * Section: SCPD, Aaron Broder <abroder@stanford.edu>
 * Copyright 2013 Eric Beach <ebeach@google.com>
 * Assignment 3 - Pt. 2 - Sierpinski
 */

#include <iostream>
#include "gwindow.h"
#include "simpio.h"
using namespace std;

/*
 * Calculate half the length of line when given two corresponding
 *   coordinates (i.e., calculate half the length of a line when given
 *   two x-coordinates)
 */
double halfLineLength(double one, double two) {
    return (two - one) / 2.0;
}

/*
 * Draw a Sierpinski triangle with a specific edge legnth and order number.
 */
void drawSierpinskiTriangle(GWindow& window, int orderNum,
                            int edgeLength, double x0, double y0) {
    if (orderNum < 0) {
        // base case: no triangle left to draw
        return;
    } else {
        // recursive case: draw three lines and then
        //   recursively draw triangles from the appropriate points

        // draw three lines to form triangle
        GPoint bRight = window.drawPolarLine(x0,
                                             y0,
                                             edgeLength,
                                             300.0);
        GPoint bLeft = window.drawPolarLine(bRight.getX(),
                                            bRight.getY(),
                                            edgeLength,
                                            180);
        GPoint top = window.drawPolarLine(bLeft.getX(),
                                             bLeft.getY(),
                                             edgeLength,
                                             60);

        // calculate and draw top triangle
        double newTopX = top.getX();
        double newTopY = top.getY();
        drawSierpinskiTriangle(window, orderNum - 1, edgeLength / 2,
                     newTopX, newTopY);

        // calculate and draw left triangle
        double newLeftX = bLeft.getX() +
                          halfLineLength(bLeft.getX(), top.getX());
        double newLeftY = bLeft.getY() +
                          halfLineLength(bLeft.getY(), top.getY());
        drawSierpinskiTriangle(window, orderNum - 1, edgeLength / 2,
                     newLeftX, newLeftY);

        // calculate and draw right triangle
        double newRightX = bRight.getX() +
                           halfLineLength(bRight.getX(), top.getX());
        double newRightY = bRight.getY() +
                           halfLineLength(bRight.getY(), top.getY());
        drawSierpinskiTriangle(window, orderNum - 1, edgeLength / 2,
                     newRightX, newRightY);
    }
}

/*
 * Helper function to seed the drawing of a Sierpinski triangle.
 */
void seedTriangle(int orderNum, int edgeLength) {
    // Step 0: Create a window
    GWindow window = GWindow(400, 400);

    // Step 1: Calculate coordinates of starting triangle
    double x0 = window.getWidth() / 2.0;
    double y0 = window.getHeight() / 4.0;

    // Step 2: Start drawing triangles
    drawSierpinskiTriangle(window, orderNum, edgeLength, x0, y0);
}

/*
 * Get a valid integer from the user.
 */
int getValidInt(string prompt) {
    int n = getInteger(prompt);
    while (n < 0) {
        cout << "Please enter a positive integer" << endl;
        n = getInteger(prompt);
    }
    return n;
}

int main() {
    int edgeLength = getValidInt("Enter an edge length: ");
    int orderNum = getValidInt("Enter a Sierpinski order number: ");

    seedTriangle(orderNum, edgeLength);
    return 0;
}
