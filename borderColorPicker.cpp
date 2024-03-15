/**
 * @file borderColorPicker.cpp
 * @description Implements the BorderColorPicker constructor and () function
 *              for CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "borderColorPicker.h"

/**
 * Constructs a new BorderColorPicker.
 *
 * @param width        Number of pixels to color around border.
 * @param inputimage   Image for referencing original image colors.
 * @param bcolor       Color to be used for painting the fill border.
 * @param tol          Tolerance used to determine the border of the fill.
 */
BorderColorPicker::BorderColorPicker(unsigned int width, PNG& inputimage, RGBAPixel scolor, RGBAPixel bcolor, double tol)
{
    borderwidth = width;
    img = inputimage;
    seedcolor = scolor;
    bordercolor = bcolor;
    tolerance = tol;
}

/**
 * Picks the color for pixel at point. If the x or y coordinate is
 * at or within an Euclidean radius of borderwidth pixels from the border of
 * the fill region, it will be colored with the required border color.
 * Otherwise, its color will not be changed.
 *
 * @param p   The point for which you're picking a color.
 * @return    The color chosen for (p).
 */
RGBAPixel BorderColorPicker::operator()(PixelPoint p)
{
    // check if original pixel is within tolerance of seedcolor; if not, return original color of pixel
    if (img.getPixel(p.x, p.y)->distanceTo(seedcolor) > tolerance) {
        return *img.getPixel(p.x, p.y);
    }

    for (int xx = -borderwidth; xx <= (int) borderwidth; xx++) {
        for (int yy = -borderwidth; yy <= (int) borderwidth; yy++) {
            
            // check if pixel is within distance of the edge of the PNG
            if (((p.x + xx) > (img.width() - 1) || (p.x + xx) < 0 || (p.y + yy) > (img.height() - 1) || (p.y + yy) < 0) 
            && ((xx * xx + yy * yy) <= (int) (borderwidth * borderwidth))) {
                return bordercolor;
            } else {
                // pixel is within distance of any border pixel (not within tolerance of seed colour)
                if (img.getPixel(p.x + xx, p.y + xx)->distanceTo(seedcolor) > tolerance) {
                    return bordercolor;
                }
            }
        }
    }

    return *img.getPixel(p.x, p.y);
}


/**
 * Add your private BorderColorPicker function implementations below
 */
