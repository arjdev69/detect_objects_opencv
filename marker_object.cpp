#include "marker_object.h"
#include "opencv2/core.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/video.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videostab.hpp"
#include <stdexcept>    
#include "opencv2/opencv_modules.hpp"
#include <stdio.h>
#include <string.h>
#include <iostream>


using namespace cv;

void SetDrawingObjLine(Mat img, int x, int y, int w, int h){
  line(img, Point(w, h), Point(x,y), Scalar( 110, 0, 0 ),2,8);
}

void SetLine(Mat imgLineLeft, int x, int y, int w, int h, bool right){
  int poseY = 100;  int poseX = 20; 
  int poseYu = 100; int poseW = 0;
  int poseHu = 100;

  if(right){
    //std::cout<<"Entrou 2 vezes ? "<< right <<std::endl;
    poseX = 0;
    poseW = -20;
  }

  SetDrawingObjLine(imgLineLeft, x, y, w, h);
  SetDrawingObjLine(imgLineLeft, x + poseX, y + poseY, w + poseW, h);
  SetDrawingObjLine(imgLineLeft, x, y + poseYu, w, h + poseHu);
}

static Scalar randomColor(RNG& rng)
{
    int icolor = (unsigned)rng;
    return Scalar(icolor&255, (icolor>>8)&255, (icolor>>16)&255);
}

int main(int argc, char** argv)
{

    char wndname[] = "Drawing Demo";
    const int NUMBER = 5000;
    const int DELAY = 5;
    int lineType = LINE_AA; // change it to LINE_8 to see non-antialiased graphics
    int i, width = 1000, height = 700;
    int x1 = -width/2, x2 = width*3/2, y1 = -height/2, y2 = height*3/2;
    //const char videoFile[] = argv[1];// "resources/video.avi";

    VideoCapture capture(argv[1]);
    Mat frame;
   
    Mat image = Mat::zeros(height, width, CV_8UC3);
    Size textsize = getTextSize("OpenCV forever!", FONT_HERSHEY_COMPLEX, 3, 5, 0);
    Point org((width - textsize.width)/2, (height - textsize.height)/2);
    RNG rng(0xFFFFFFFF);
    Point pt1, pt2;

    if(!capture.isOpened())
        throw "Error when reading steam_avi";

    for( ; ; )
    {
      pt1.x = rng.uniform(x1, x2);
      pt1.y = rng.uniform(y1, y2);
      pt2.x = rng.uniform(x1, x2);
      pt2.y = rng.uniform(y1, y2);
      int thickness = rng.uniform(-3, 10);

      capture >> frame;
      if(frame.empty())
        break;
        SetLine(frame, 140, 160, 160, 160, true);

        SetLine(frame, 180, 160, 200, 160, false);
        imshow("", frame);
        waitKey(20); // waits to display frame   
    }
   
    waitKey();
    return 0;
}