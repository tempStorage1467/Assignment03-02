/*
 * File: Sierpinski.cpp
 * ----------------------
 * Section: SCPD, Aaron Broder <abroder@stanford.edu>
 * Copyright 2013 Eric Beach <ebeach@google.com>
 * Assignment 3 - Pt. 2 - Sierpinski
 *
 */

#include <iostream>
#include "gwindow.h"
#include "simpio.h"
using namespace std;

double halfLinePosition(double one, double two) {
    return (two - one) / 2.0;
}

void drawTriangle(GWindow& window, int orderNum,
                  int edgeLength, double x0, double y0) {
    if (orderNum < 0) {
        // base case: no triangle left to draw
        return;
    } else {
        // recursive case: draw three lines and then
        //   recursively draw triangles from the appropriate ending points

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
        drawTriangle(window, orderNum - 1, edgeLength / 2,
                     newTopX, newTopY);

        // calculate and draw left triangle
        double newLeftX = bLeft.getX() +
                          halfLinePosition(bLeft.getX(), top.getX());
        double newLeftY = bLeft.getY() +
                          halfLinePosition(bLeft.getY(), top.getY());
        drawTriangle(window, orderNum - 1, edgeLength / 2,
                     newLeftX, newLeftY);

        // calculate and draw right triangle
        double newRightX = bRight.getX() +
                           halfLinePosition(bRight.getX(), top.getX());
        double newRightY = bRight.getY() +
                           halfLinePosition(bRight.getY(), top.getY());
        drawTriangle(window, orderNum - 1, edgeLength / 2,
                     newRightX, newRightY);
    }
}

void seedTriangle(int orderNum, int edgeLength) {
    // Step 0: Create a window
    GWindow window = GWindow(400, 400);

    // Step 1: Calculate starting triangle coordinates
    double x0 = window.getWidth() / 2.0;
    double y0 = window.getHeight() / 4.0;

    // Step 2: Start drawing triangles
    drawTriangle(window, orderNum, edgeLength, x0, y0);
}

int main() {
    int edgeLength = getInteger("Enter an edge length: ");
    int orderNum = getInteger("Enter a Sierpinski order number: ");

    seedTriangle(orderNum, edgeLength);
    return 0;
}
