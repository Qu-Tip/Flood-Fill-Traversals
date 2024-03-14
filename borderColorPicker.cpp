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
    if (p.x < borderwidth || p.x >= (img.width() - borderwidth) || p.y < borderwidth || p.y >= (img.height() - borderwidth)) {
        return bordercolor;
    }


    for (int xx = p.x-borderwidth; xx <= p.y+borderwidth; ++xx) {
        for (int yy = p.y-borderwidth; yy <= p.y+borderwidth; ++yy) {
            int nx = p.x + xx;
            int ny = p.y + yy;

        //TODO: account for euclidean radius?? 
        
            if (nx >= 0 && nx < img.width() && ny >= 0 && ny < img.height()) {
                RGBAPixel* pixelColor = img.getPixel(nx, ny);

                if (pixelColor->distanceTo(seedcolor) > tolerance) {
                    return bordercolor; 
                }
            }
        }
    }


    return seedcolor; 
}

/**
 * Add your private BorderColorPicker function implementations below
 */
