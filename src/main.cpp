
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


  int curFrame = 320;
  int dist = 0;
  //Goes through frame by frame and makes the transition

  Mat frame1 = mainFrame.getVidSTI(0,1280,2);
  Mat frame2 = mainFrame.getVidSTI(0,1280,1);

  mainFrame.playFrame(mainFrame.getWipeFrame(frame1,frame2));

}

//Returns the current framewipe with given parameter
Mat FrameObject::getWipeFrame(int vid1Frame,int vid2Frame, int dist, bool startLeft)
{

  Mat vid1mat;
  Mat vid2mat;
  //Extract both the frames
  vid1mat = getVidFrame(vid1Frame,1);
  vid2mat = getVidFrame(vid2Frame,2);

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

// Returns a frame wipe between two defined matrices

Mat FrameObject::getWipeFrame(Mat vid1mat,Mat vid2mat)
{
  Mat finalFrame(height,width,vidType);
  //Iterates through and calculates the new frame

  for(int i = 0; i<width; i++)
  {
    for(int j = 0; j<height; j++)
    {
      if(i<width/2)
      {
        finalFrame.at<Vec3b>(j,i) = vid2mat.at<Vec3b>(j,i);
      }
      else finalFrame.at<Vec3b>(j,i) = vid1mat.at<Vec3b>(j,i);
    }
  }

  return finalFrame;
}
//Returns the frame at a given time and makes sure its in the right resolution
Mat FrameObject::getVidFrame(int frame, int vidNum)
{
    VideoCapture* curVid = NULL;
    if(vidNum == 1)
    {
      curVid = &vid1;
    }
    else curVid = &vid2;
    if(frame>=curVid->get(CAP_PROP_FRAME_COUNT))
    {
      return Mat(height,width,0, Scalar(0,0,0));
    }
    curVid->set(CAP_PROP_POS_FRAMES, frame);
    int curWidth = curVid->get(CAP_PROP_FRAME_WIDTH);
    int curHeight = curVid->get(CAP_PROP_FRAME_HEIGHT);
    Mat tempMat,finalMat;
    vid1 >> tempMat;
    resize(tempMat,finalMat,finalMat.size(),(double)curWidth/width, (double)curHeight/height);
    return finalMat;
}

Mat FrameObject::getVidSTI(int frame, int size, int vidNumb)
{
  VideoCapture* curVid = NULL;
  if(vidNumb == 1)
  {
    curVid = &vid1;
  }
  else curVid = &vid2;
  int totFrames = curVid->get(CAP_PROP_FRAME_COUNT);
  if(frame+size >= totFrames) size = totFrames-frame-1;
  Mat finalFrame(height,size,vidType);
  curVid->set(CAP_PROP_POS_FRAMES,frame);

  for(int i = 0; i< size;i++)
  {
    std::cout << i << "\n";
    Mat tempFrame;
    *curVid >> tempFrame;
    for(int j = 0; j<height;j++)
    {
      finalFrame.at<Vec3b>(j,i) = tempFrame.at<Vec3b>(j,width/2);
    }
  }
  return finalFrame;

}

//Plays the current frame
void FrameObject::playFrame(Mat frame)
{
  imshow(videoName, frame);
  waitKey(100*100);
}
