/**
 * @file quarterColorPicker.cpp
 * @description Implements the QuarterColorPicker constructor and () function
 *              for CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "quarterColorPicker.h"

QuarterColorPicker::QuarterColorPicker(PNG& inputimg, unsigned char b_amount)
{
    referenceimg = inputimg;
    brightamount = b_amount;
	
}

/**
 * Picks the color for pixel (x, y).
 *
 * Using the private reference image, scale each dimension by half
 * and tile the smaller image in a 2 x 2 grid over the original dimensions
 * of the image, and return the pixel at the appropriate coordinate from
 * the tiled image, brightened on each R/G/B channel by the required amount.
 * 
 * The value of each pixel in the scaled image will be a bilinear interpolation
 * of a 2x2 pixel region from the original image, with each of the R/G/B/A channels
 * processed individually. Interpolate over the x-axis before the y-axis.
 * Truncate any fractional values on the R/G/B channels. Brighten each color channel
 * as the final step.
 * 
 * @pre referenceimg width and height are both even
 */
RGBAPixel QuarterColorPicker::operator()(PixelPoint p)
{
    // scale each dimension by half
    referenceimg.resize(referenceimg.width() / 2, referenceimg.height() / 2);

    RGBAPixel* par = referenceimg.getPixel(p.x, p.y);
    RGBAPixel* east = referenceimg.getPixel(p.x + 1, p.y);
    RGBAPixel* south = referenceimg.getPixel(p.x, p.y + 1);
    RGBAPixel* southeast = referenceimg.getPixel(p.x + 1, p.y + 1);

    // bilinear interpolation
    int top_red_avg = (par->r + east->r) / 2;
    int top_green_avg = (par->g + east->g) / 2;
    int top_blue_avg = (par->b + east->b) / 2;
    double top_a_avg = (par->a + east->a) / 2;

    int bot_red_avg = (south->r + southeast->r) / 2;
    int bot_green_avg = (south->g + southeast->g) / 2;
    int bot_blue_avg = (south->b + southeast->b) / 2;
    double bot_a_avg = (south->a + southeast->a) / 2;

    int pixel_red_avg = (top_red_avg + bot_red_avg) / 2;
    int pixel_green_avg = (top_green_avg + bot_green_avg) / 2;
    int pixel_blue_avg = (top_blue_avg + bot_blue_avg) / 2;
    double pixel_a_avg = (top_a_avg + bot_a_avg) / 2;

    // brighten pixel
    pixel_red_avg = min(pixel_red_avg + brightamount, 255);
    pixel_green_avg = min(pixel_green_avg + brightamount, 255);
    pixel_blue_avg = min(pixel_blue_avg + brightamount, 255);

    return RGBAPixel(pixel_red_avg, pixel_green_avg, pixel_blue_avg, pixel_a_avg);
}

/**
 * Add your private QuarterColorPicker function implementations below
 */
