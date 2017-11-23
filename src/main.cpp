
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include "headers/main.h"

using namespace cv;

int main(int argc, char** argv)
{
  std::string video1f = "";
  std::string video2f = "";

  //Check for two input arguments and gets there file path
  if(argc > 1)
  {
    video1f = argv[1];
  }

  if(argc > 2)
  {
    video2f = argv[2];
  }
  //Create the frame class in order to calculate the wipe;
  FrameObject mainFrame("Project", video1f, video2f);


  int curFrame = 0;
  int dist = 0;
  //Goes through frame by frame and makes the transition
  while(dist< 1280)
  {
      std::cout << curFrame << "\n";
      mainFrame.playFrame(mainFrame.getWipeFrame(curFrame,curFrame,dist,true));
      std::cout << "Played frame\n";
      curFrame++;
      dist++;

  }

}

//Returns the current framewipe with given parameter
Mat FrameObject::getWipeFrame(int vid1Frame,int vid2Frame, int dist, bool startLeft)
{

  Mat vid1mat;
  Mat vid2mat;
  //Extract both the frames
  vid1mat = getVid1Frame(vid1Frame);
  vid2mat = getVid2Frame(vid2Frame);

  if(dist >= width) dist = width-1;
  if(dist <0) dist = 0;


  Mat finalFrame(height,width,vidType);
  //Iterates through and calculates the new frame
  if(startLeft)
  {
    for(int i = 0; i<width; i++)
    {
      for(int j = 0; j<height; j++)
      {
        if(i<dist)
        {
          finalFrame.at<Vec3b>(j,i) = vid2mat.at<Vec3b>(j,i);
        }
        else finalFrame.at<Vec3b>(j,i) = vid1mat.at<Vec3b>(j,i);
      }
    }
  }
  return finalFrame;
}

//Returns the frame at a given time and makes sure its in the right resolution
Mat FrameObject::getVid1Frame(int frame)
{
    if(frame>=vid1.get(CAP_PROP_FRAME_COUNT))
    {
      return Mat(height,width,0);
    }
    vid1.set(CAP_PROP_POS_FRAMES, frame);
    int curWidth = vid1.get(CAP_PROP_FRAME_WIDTH);
    int curHeight = vid1.get(CAP_PROP_FRAME_HEIGHT);
    Mat tempMat,finalMat;
    vid1 >> tempMat;
    resize(tempMat,finalMat,finalMat.size(),(double)curWidth/width, (double)curHeight/height);
    return finalMat;
}

Mat FrameObject::getVid2Frame(int frame)
{
    if(frame>=vid2.get(CAP_PROP_FRAME_COUNT))
    {
      return Mat(height,width,0);
    }
    vid2.set(CAP_PROP_POS_FRAMES, frame);
    int curWidth = vid2.get(CAP_PROP_FRAME_WIDTH);
    int curHeight = vid2.get(CAP_PROP_FRAME_HEIGHT);
    Mat tempMat,finalMat;
    vid2 >> tempMat;
    resize(tempMat,finalMat,finalMat.size(),(double)curWidth/width, (double)curHeight/height);
    return finalMat;
}
//Plays the current frame
void FrameObject::playFrame(Mat frame)
{
  imshow(videoName, frame);
  waitKey(1);
}
