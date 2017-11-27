
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <math.h>
#include "headers/main.h"

using namespace cv;

int main(int argc, char** argv)
{
  std::string video1f = "";
  std::string video2f = "";

  //Check for two input arguments and gets their file path
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



  Mat frame1 = mainFrame.getVidHistoSTI(360,400,2);

  //Mat frame2 = mainFrame.getVidCopySTI(0,1280,1);

  mainFrame.playFrame(frame1);
  //mainFrame.playFrame(mainFrame.getWipeFrame(frame1,frame2));


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
    *curVid >> tempMat;
    resize(tempMat,finalMat,finalMat.size(),(double)width/curWidth, (double)height/curHeight);
    return finalMat;
}

Mat FrameObject::getVidHistoSTI(int frame, int size, int vidNumb)
{
  VideoCapture* curVid = NULL;
  if(vidNumb == 1)
  {
    curVid = &vid1;
  }
  else curVid = &vid2;
  int totFrames = curVid->get(CAP_PROP_FRAME_COUNT);

  if(frame+size >= totFrames) size = totFrames-frame-1;

  Mat finalFrame(width,size,CV_32FC1);



  for(int i = 0;i<size;i++)
  {
    Mat frame1 = getVidFrame(frame,vidNumb);
    Mat frame2 = getVidFrame(frame+1,vidNumb);
    for(int j = 0; j<width;j++)
    {

      Mat hist1 = getChromacityMat(frame1.col(j));
      Mat hist2 = getChromacityMat(frame2.col(j));


      float L = getL(hist1,hist2)/(float)width;
      //std::cout << "L=" << L << "\n";
      finalFrame.at<float>(j,i) = L;
    }
    std::cout << "finished frame: " << i << "\n";
    frame++;
  }

  return finalFrame;

}

Mat FrameObject::getChromacityMat(Mat frame)
{
  int width = frame.cols;
  int height = frame.rows;
  int numbofbins = floor(1+log2(height));

  Mat outputFrame(numbofbins,numbofbins,CV_32SC1,double(0));



  int totalpixels = 0;
  for(int i = 0; i<width; i++)
  {
    for(int j = 0; j<height; j++)
    {
      totalpixels++;
      Vec3b pixelColor = frame.at<Vec3b>(j,i);
      uchar b = pixelColor.val[0];
      uchar g = pixelColor.val[1];
      uchar r = pixelColor.val[2];



      float finr,fing;
      if(b+g+r == 0)
      {
        finr = 1;
        fing = 1;
      }
      else
      {
        finr = r/(float)(r+g+b);
        fing = g/(float)(r+g+b);
      }


      int rIndex = finr*numbofbins;
      int gIndex = fing*numbofbins;
      if(rIndex == numbofbins) rIndex--;
      if(gIndex == numbofbins) gIndex--;

      outputFrame.at<int>(rIndex,gIndex)++;
    }
  }
  return outputFrame;
}

Mat FrameObject::normalize(Mat frame)
{
  int width = frame.cols;
  int height = frame.rows;

  Mat outputFrame(height,width,CV_32FC1);
  int total = width*height;
  for(int i = 0; i<width;i++)
  {
    for(int j = 0; j<height; j++)
    {
      outputFrame.at<float>(j,i) = (float)frame.at<int>(j,i)/(float)total;
    }
  }


  return outputFrame;

}

int FrameObject::getL(Mat frame1, Mat frame2)
{
  int size = frame1.rows;
  int L = 0;

  //std::cout << frame1.rows << frame1.cols << frame2.rows << frame2.cols << "\n";
  for(int i =0; i < size;i++)
  {
    for(int j=0; j < size;j++)
    {
      L += min(frame1.at<int>(i,j), frame2.at<int>(i,j));
    }

  }
  return L;
};

Mat FrameObject::getVidCopySTI(int frame, int size, int vidNumb)
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

void FrameObject::printMat(Mat m)
{
  int total = 0;
  for(int i = 0 ; i < m.rows; i++)
  {
    for(int j = 0; j < m.cols; j++)
    {
      total += m.at<int>(j,i);
      std::cout << m.at<int>(j,i) << " ";
    }
    std::cout << "\n";
  }
  std::cout << "total: " << total << "\n";
}

//Plays the current frame
void FrameObject::playFrame(Mat frame)
{
  imshow(videoName, frame);
  waitKey(100*10000);
}
