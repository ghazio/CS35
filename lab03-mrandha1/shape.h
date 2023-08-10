#pragma once

#include "grid.h"

/**
 * A class representing a shape.
 */
class Shape {
  public:
    virtual ~Shape() {
    }

    /**
     * Draws this shape on the provided grid.
     * @param grid The grid onto which to draw the shape.
     */
    virtual void draw(Grid* grid) = 0;
};
