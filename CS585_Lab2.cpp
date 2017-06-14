/*	
*	CS440 Spring 2016 
*	Lab 2
*	--------------
*	This program introduces the following concepts:
*		a) Reading a stream of images from a webcamera, and displaying the video
*		b) Skin color detection
*		c) Background differencing
*		d) Visualizing motion history
*	--------------
*/

#include "stdafx.h"
//opencv libraries
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
//C++ standard libraries
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

//function declarations

/**
	Function that returns the maximum of 3 integers
	@param a first integer
	@param b second integer
	@param c third integer
*/
int myMax(int a, int b, int c);

/**
	Function that returns the minimum of 3 integers
	@param a first integer
	@param b second integer
	@param c third integer
*/
int myMin(int a, int b, int c);

/**
	Function that detects whether a pixel belongs to the skin based on RGB values
	@param src The source color image
	@param dst The destination grayscale image where skin pixels are colored white and the rest are colored black
*/
void mySkinDetect(Mat& src, Mat& dst);

/**
	Function that does frame differencing between the current frame and the previous frame
*/
void myFrameDifferencing();

/**
	Function that accumulates the frame differences for a certain number of pairs of frames
*/
void myMotionEnergy();

int main()
{

//----------------
//a) Reading a stream of images from a webcamera, and displaying the video
//----------------
	// For more information on reading and writing video: http://docs.opencv.org/modules/highgui/doc/reading_and_writing_images_and_video.html
	// open the video camera no. 0
	VideoCapture cap(0); 

	// if not successful, exit program
    if (!cap.isOpened())  
    {
        cout << "Cannot open the video cam" << endl;
        return -1;
    }

	// Mat object to read first frame
	Mat frame0;
	
	// read a new frame from video
	bool bSuccess0 = cap.read(frame0); 

	//if not successful, break loop
    if (!bSuccess0) 
	{
			cout << "Cannot read a frame from video stream" << endl;
	}

	//create a window called "MyVideoFrame0"
	namedWindow("MyVideoFrame0", WINDOW_AUTOSIZE);
	imshow("MyVideoFrame0", frame0);

	//create a window called "MyVideo"
	namedWindow("MyVideo",WINDOW_AUTOSIZE);
	namedWindow("MySkinDetect",WINDOW_AUTOSIZE);

	while (1)
    {
		// read a new frame from video
        Mat frame;
        bool bSuccess = cap.read(frame); 
		//show the frame in "MyVideo" window
		imshow("MyVideo", frame);

		//if not successful, break loop
        if (!bSuccess) 
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }
		
		// destination frame
		Mat frameDest;
		frameDest = Mat::zeros(frame.rows, frame.cols, CV_8UC1); //Returns a zero array of same size as src mat, and of type CV_8UC1
//----------------
//	b) Skin color detection
//----------------
		mySkinDetect(frame, frameDest);
		imshow("MySkinDetect", frameDest);

//----------------
//	c) Background differencing
//----------------
		//TODO: HW1 - EXERCISE 2
//----------------
//  d) Visualizing motion history
//----------------
		//TODO: HW1 - EXERCISE 2

        if (waitKey(30) == 27) 
       {
            cout << "esc key is pressed by user" << endl;
            break; 
       }

    }
	cap.release();
	return 0;
}

//Function that returns the maximum of 3 integers
int myMax(int a, int b, int c) {
	return max(max(a, b), c);
}

//Function that returns the minimum of 3 integers
int myMin(int a, int b, int c) {
	return min(min(a, b), c);
}

//Function that detects whether a pixel belongs to the skin based on RGB values
void mySkinDetect(Mat& src, Mat& dst) {
	//Surveys of skin color modeling and detection techniques:
	//Vezhnevets, Vladimir, Vassili Sazonov, and Alla Andreeva. "A survey on pixel-based skin color detection techniques." Proc. Graphicon. Vol. 3. 2003.
	//Kakumanu, Praveen, Sokratis Makrogiannis, and Nikolaos Bourbakis. "A survey of skin-color modeling and detection methods." Pattern recognition 40.3 (2007): 1106-1122.
	
	//TODO:
	//Use the following test for skin color detection
	//Red > 95 and Blue > 20 and Green > 40, and 
	//max(Red, Green, Blue) - min(Red, Green, Blue) > 15, and
	//abs(Red - Green) > 15, and
	//Red > Green, and
	//Red > Blue
	
	for (int i = 0; i < src.rows; i++){
		for (int j = 0; j < src.cols; j++){

			//For each pixel, compute the average intensity of the 3 color channels
			Vec3b intensity = src.at<Vec3b>(i, j);
			int B = intensity[0]; int G = intensity[1]; int R = intensity[2];

			if ((R > 95 && G > 40 && B > 20) && (myMax(R, G, B) - myMin(R, G, B) > 15) && (abs(R - G) > 15) && (R > G) && (R > B)){
				dst.at<uchar>(i, j) = 255;
			}
		}
	}




}

//Function that does frame differencing between the current frame and the previous frame
void myFrameDifferencing() {
	//TODO: 
}

//Function that accumulates the frame differences for a certain number of pairs of frames
void myMotionEnergy() {
	//TODO:
	
}