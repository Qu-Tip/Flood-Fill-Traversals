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

    unsigned int tiledX = p.x % (referenceimg.width() / 2);
    unsigned int tiledY = p.y % (referenceimg.height() / 2);

    tiledX *= 2;
    tiledY *= 2;

    if (tiledX >= referenceimg.width() - 1) {
        tiledX = referenceimg.width() - 2;
    }

    if (tiledY >= referenceimg.height() - 1) {
        tiledY = referenceimg.height() - 2;
    }

    RGBAPixel* par = referenceimg.getPixel(tiledX, tiledY);
    RGBAPixel* east = referenceimg.getPixel(tiledX + 1, tiledY);
    RGBAPixel* south = referenceimg.getPixel(tiledX, tiledY + 1);
    RGBAPixel* southeast = referenceimg.getPixel(tiledX + 1, tiledY + 1);

    unsigned char avgR = (par->r + east->r + south->r + southeast->r) / 4;
    unsigned char avgG = (par->g + east->g + south->g + southeast->g) / 4;
    unsigned char avgB = (par->b + east->b + south->b + southeast->b) / 4;

    unsigned char newR = min(avgR + brightamount, 255);
    unsigned char newG = min(avgG + brightamount, 255);
    unsigned char newB = min(avgB + brightamount, 255);

    return RGBAPixel(newR, newG, newB, par->a);


// AATTEMPT 1
    /*
    PNG tiled_img = bilinear_Int(referenceimg);
    RGBAPixel* pixel = tiled_img.getPixel(p.x/2, p.y/2);

    pixel->r = min(pixel->r + brightamount, 255);
    pixel->g = min(pixel->g + brightamount, 255);
    pixel->b = min(pixel->b + brightamount, 255);

    return *pixel;
    */
}

/**
 * Add your private QuarterColorPicker function implementations below
 */

 PNG QuarterColorPicker::bilinear_Int(PNG& refimg) 
 {
    PNG tiled_img = refimg;
    tiled_img.resize(refimg.width() / 2, refimg.height() / 2);

    for (int i = 0; i < refimg.width(); i += 2) {
        for (int j = 0; j < refimg.height(); j += 2) {

            // get the pixel and its neighbours (2 x 2)
            RGBAPixel* par = refimg.getPixel(i, j);
            RGBAPixel* east = refimg.getPixel(i + 1, j);
            RGBAPixel* south = refimg.getPixel(i, j + 1);
            RGBAPixel* southeast = refimg.getPixel(i + 1, j + 1);

            // bilinear interpolation
            int pixel_red_avg = (((par->r + east->r) / 2) + ((south->r + southeast->r) / 2)) / 2;
            int pixel_green_avg = (((par->g + east->g) / 2) + ((south->g + southeast->g) / 2)) / 2;
            int pixel_blue_avg = (((par->b + east->b) / 2) + ((south->b + southeast->b) / 2)) / 2;
            double pixel_a_avg = (((par->a + east->a) / 2) + ((south->a + southeast->a) / 2)) / 2;

            RGBAPixel* tiled = tiled_img.getPixel(i/2, j/2);
            *tiled = RGBAPixel(pixel_red_avg, pixel_green_avg, pixel_blue_avg, pixel_a_avg);
        }
    }
    return tiled_img;
 }
