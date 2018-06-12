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

void SetDrawingObjLine(Mat img, int x, int y, int w, int h)
{
  line(img, Point(w, h), Point(x, y), Scalar(110, 0, 0), 2, 8);
}

void SetLine(Mat imgLine, int left, int down, int heightY, bool right)
{
  int y = 160;
  int x = 140;
  int w = 160;
  int h = 160;

  int sideLine = 20;
  int poseW = 0;

  int size_z = 50;

  //left = left + 150;

  if (right)
  {
    sideLine = 0;
    poseW = -20;
  }
  
  SetDrawingObjLine(imgLine, (x + left), (y + down), (w + left), (h + down));
  SetDrawingObjLine(imgLine, ((x + sideLine) + left), ((y + heightY) + down), ((w + poseW) + left), (h + down));
  SetDrawingObjLine(imgLine, (x + left), ((y + heightY) + down), (w + left), ((h + heightY) + down));
}

void SetDrawingBrackets(Mat imgLine, int left, int down, int heightY, int widthX)
{
  SetLine(imgLine,left, down, heightY, true); // left

  SetLine(imgLine, widthX + left, down, heightY, false); // right
}

static Scalar randomColor(RNG &rng)
{
  int icolor = (unsigned)rng;
  return Scalar(icolor & 255, (icolor >> 8) & 255, (icolor >> 16) & 255);
}

int main(int argc, char **argv)
{

  char wndname[] = "Drawing Demo";
  const int NUMBER = 5000;
  const int DELAY = 5;
  int lineType = LINE_AA; // change it to LINE_8 to see non-antialiased graphics
  int i, width = 1000, height = 700;
  int x1 = -width / 2, x2 = width * 3 / 2, y1 = -height / 2, y2 = height * 3 / 2;
  //const char videoFile[] = argv[1];// "resources/video.avi";

  VideoCapture capture(argv[1]);
  Mat frame;

  Mat image = Mat::zeros(height, width, CV_8UC3);
  Size textsize = getTextSize("OpenCV forever!", FONT_HERSHEY_COMPLEX, 3, 5, 0);
  Point org((width - textsize.width) / 2, (height - textsize.height) / 2);
  RNG rng(0xFFFFFFFF);
  Point pt1, pt2;

  if (!capture.isOpened())
    throw "Error when reading steam_avi";

  for (;;)
  {
    pt1.x = rng.uniform(x1, x2);
    pt1.y = rng.uniform(y1, y2);
    pt2.x = rng.uniform(x1, x2);
    pt2.y = rng.uniform(y1, y2);
    int thickness = rng.uniform(-3, 10);

    capture >> frame;
    if (frame.empty())
      break;
    SetDrawingBrackets(frame, 135, 20, 30, 25);
    imshow("", frame);
    waitKey(1); // waits to display frame
  }

  waitKey();
  return 0;
}