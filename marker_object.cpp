#include "marker_object.h"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <stdio.h>
#include <string.h>
#include <iostream>


using namespace cv;

void SetDrawingObj(Mat img, int x, int y, int w, int h){
  Rect transform_R = Rect(x,y,w,h);

  rectangle(img,transform_R,Scalar(255,0,0),3,8,0);
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
    const char videoFile[] = "resources/video.avi";
    VideoCapture capture(videoFile);
    Mat frame;
   
    Mat image = Mat::zeros(height, width, CV_8UC3);
    Size textsize = getTextSize("OpenCV forever!", FONT_HERSHEY_COMPLEX, 3, 5, 0);
    Point org((width - textsize.width)/2, (height - textsize.height)/2);
    RNG rng(0xFFFFFFFF);
    Point pt1, pt2;

    if(!capture.isOpened())
        throw "Error when reading steam_avi";

    namedWindow("Detect Objects", 1);
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
        SetDrawingObj(frame, pt1.x, pt1.y, 100, 100);
        imshow("Detect Objects", frame);
        waitKey(20); // waits to display frame
    }
   
    waitKey();
    return 0;
}