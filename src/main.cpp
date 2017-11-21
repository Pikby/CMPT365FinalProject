
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include "headers/main.h"

using namespace cv;

int main()
{
  VideoCapture cap("test.mp4");
  playVideo(cap);
}

void playVideo(VideoCapture video)
{
  double fps = video.get(CV_CAP_PROP_FPS);
  Mat frame;
  namedWindow("Video",1);
  while(video.isOpened())
  {
    video >> frame;
    imshow("Video", frame);
    waitKey(fps);
  }
}
