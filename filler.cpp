/**
 * @file        filler.cpp
 * @description Implementation of functions in the filler namespace.
 *
 *              SUBMIT THIS FILE WITH YOUR MODIFICATIONS
 */

/**
 * Performs a flood fill using breadth first search.
 *
 * @param config FillerConfig struct to setup the fill
 * @return animation object illustrating progression of flood fill algorithm
 */
animation filler::FillBFS(FillerConfig& config) {
	return Fill<Queue>(config); 
}

/**
 * Performs a flood fill using depth first search.
 *
 * @param  config - FillerConfig struct to setup the fill
 * @return animation object illustrating progression of flood fill algorithm
 */
animation filler::FillDFS(FillerConfig& config) {
	return Fill<Stack>(config); 
}

/**
 * Run a flood fill on an image starting at the seed point
 *
 * @param config FillerConfig struct with data for flood fill of image
 * @return animation object illustrating progression of flood fill algorithm
 */
template <template <class T> class OrderingStructure> animation filler::Fill(FillerConfig& config)
{
	/**
	 * You need to implement this function!
	 *
	 * This is the basic description of a flood-fill algorithm: Every fill
	 * algorithm requires an ordering structure, which is passed to this
	 * function via its template parameter. For a breadth-first-search
	 * fill, that structure is a Queue, for a depth-first-search, that
	 * structure is a Stack. To begin the algorithm, you simply place the
	 * given point in the ordering structure, marking it processed
	 * (the way you mark it is a design decision you'll make yourself).
	 * We have a choice to either change the color, if appropriate, when we
	 * add the point to the OS, or when we take it off. In our test cases,
	 * we have assumed that you will change the color when a point is removed
	 * from the structure.
	 * Until the structure is empty, you do the following:
	 *
	 * 1.     Remove a point from the ordering structure, and then...
	 *
	 *        1.1.  add its unprocessed neighbors (up/down/left/right) whose color values are
	 *              within (or equal to) tolerance distance from the seed point,
	 *              to the ordering structure, and
	 *              mark them as processed.
	 *        1.2.  if it is an appropriate frame, send the current PNG to the
	 *              animation (as described below).
	 *
	 * 2.     When implementing your breadth-first-search and
	 *        depth-first-search fills, you will need to explore neighboring
	 *        pixels (up/down/left/right) in some order.
	 *
	 *        While the order in which you examine neighbors does not matter
	 *        for a proper fill, you must use the same order as we do for
	 *        your animations to come out like ours! The order you should put
	 *        neighboring pixels **ONTO** the queue or stack is as follows:
	 *        2.1. northern neighbour (up)
	 *        2.2. eastern neighbour (right)
	 *        2.3. southern neighbour (down)
	 *        2.4. western neighbour (left)
	 * 
	 *        If you process the neighbours in a different order, your fill may
	 *        still work correctly, but your animations will be different
	 *        from the grading scripts!
	 *
	 * 3.     For every k pixels filled, **starting at the kth pixel**, you
	 *        must add a frame to the animation, where k = frameFreq.
	 *
	 *        For example, if frameFreq is 4, then after the 4th pixel has
	 *        been filled you should add a frame to the animation, then again
	 *        after the 8th pixel, etc.  You must only add frames for the
	 *        number of pixels that have been filled, not the number that
	 *        have been checked. So if frameFreq is set to 1, a pixel should
	 *        be filled every frame.
	 *
	 * 4.     Finally, as you leave the function, send one last frame to the
	 *        animation. This frame will be the final result of the fill, and
	 *        it will be the one we test against.
	 *
	 */

/*
	int framecount = 0; // increment after processing one pixel; used for producing animation frames (step 3 above)
	animation anim;
	OrderingStructure<PixelPoint> os;

	// initialize structure to keep track of visited pixels
	vector <vector<int>> visited;
	for (unsigned i = 0; i < config.img.width(); i++) {
		visited.emplace_back();
		for (unsigned j = 0; j < config.img.height(); j++) {
			visited[i].push_back(0);
		}
	}
	anim.addFrame(config.img);
	os.Add(config.seedpoint);

	while (!os.IsEmpty()) {
		PixelPoint curr = os.Remove();														// remove point from ordering structure
		visited[curr.x][curr.y] = 1;

		if (isInTolerance(curr, config)) {
			
			RGBAPixel* pixel = config.img.getPixel(curr.x, curr.y);
			*pixel = config.picker->operator()(curr);

			// Part 3:
			framecount++;
			if (framecount % config.frameFreq == 0) {
				anim.addFrame(config.img);
			}

			// Part 2:
			if (visited[curr.x][curr.y - 1] != 1 && (curr.y - 1) >= 0) { 					// up
				os.Add(PixelPoint(curr.x, curr.y - 1));
			}

			if (visited[curr.x + 1][curr.y] != 1 && (curr.x + 1) < config.img.width()) {	// right
				os.Add(PixelPoint(curr.x + 1, curr.y));
			}

			if (visited[curr.x][curr.y + 1] != 1 && (curr.y + 1) < config.img.height()) {	// down
				os.Add(PixelPoint(curr.x, curr.y + 1));
			}

			if (visited[curr.x - 1][curr.y] != 1 && (curr.x - 1) >= 0) {					// left
				os.Add(PixelPoint(curr.x - 1, curr.y));
			}
		}

	}
	
	// Part 4:
	anim.addFrame(config.img);
	return anim;

	*/

animation anim;
OrderingStructure<PixelPoint> os;

bool** visited = new bool*[config.img.height()];
for (int i = 0; i < config.img.height(); i++) {
    visited[i] = new bool[config.img.width()];
    for (int j = 0; j < config.img.width(); j++) {
        visited[i][j] = false; 
    }
}

os.Add(PixelPoint(config.seedpoint.x, config.seedpoint.y, config.seedpoint.color));
visited[config.seedpoint.y][config.seedpoint.x] = true;

int pixelsFilled = 0;
anim.addFrame(config.img);

while (!os.IsEmpty()) {
    PixelPoint current = os.Remove();

    if (isInTolerance(current, config)) {
        config.img.getPixel(current.x, current.y)->r = config.picker->operator()(current).r;
        config.img.getPixel(current.x, current.y)->g = config.picker->operator()(current).g;
        config.img.getPixel(current.x, current.y)->b = config.picker->operator()(current).b;
        pixelsFilled++;

        if (pixelsFilled % config.frameFreq == 0) {
            anim.addFrame(config.img);
        }

        int dx[] = {0, 1, 0, -1};
        int dy[] = {-1, 0, 1, 0};
        for (int k = 0; k < 4; k++) {
            int nx = current.x + dx[k];
            int ny = current.y + dy[k];


            if (nx >= 0 && nx < config.img.width() && ny >= 0 && ny < config.img.height() && !visited[ny][nx]) {
                RGBAPixel* pixel = config.img.getPixel(nx, ny);
				os.Add(PixelPoint(nx, ny, *pixel));
                visited[ny][nx] = true;
            }
        }
    }
}

for (int i = 0; i < config.img.height(); i++) {
    delete[] visited[i];
}
delete[] visited;

anim.addFrame(config.img);
return anim;

}


bool filler::isInTolerance(PixelPoint curr, FillerConfig& config) {
    // Obtain a const reference to the current pixel's color.
    const RGBAPixel& currPixelColor = *config.img.getPixel(curr.x, curr.y);
    // Make a non-const copy of the seed color.
    RGBAPixel seedColorCopy = config.seedpoint.color;

    // Compare the current pixel's color to the seed color using the distanceTo method.
    // This should be valid as seedColorCopy is non-const and distanceTo is being called on it.
    return seedColorCopy.distanceTo(currPixelColor) <= config.tolerance;
}




