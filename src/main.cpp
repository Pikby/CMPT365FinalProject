
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <math.h>
#include "headers/main.h"

using namespace cv;

int main(int argc, char** argv)
{
  std::string video1f = "";
  std::string pathtoimage = "STI";
  int type = -1;
  int startFrame = -1;
  int length = -1;
  char savetofile = 0;
  int width = 1040;
  int height = 720;

  for(int curArg = 1; curArg < argc; curArg++)
  {
    switch(curArg)
    {
      case(1): video1f = argv[curArg]; break;
      case(2): width = std::stoi(argv[curArg]); break;
      case(3): height = std::stoi(argv[curArg]); break;
      case(4): type = std::stoi(argv[curArg]); break;
      case(5): startFrame = std::stoi(argv[curArg]); break;
      case(6): length = std::stoi(argv[curArg]); break;
      case(7): pathtoimage = argv[curArg];
              savetofile = 'y'; break;
    }

  }


  FrameObject mainFrame("Project", "test1.mp4");
  while(true)
  {

    if(video1f == "")
    {
      std::cout << "Please input a path to file \n";
      std::cin >> video1f;
      mainFrame = FrameObject("Project", video1f);
    }
    else
    {
      mainFrame = FrameObject("Project", video1f);
    }
    if(type == -1)
    {

      std::cout << "Enter type: (0 for CopySti or 1 for HistogramSti)\n";
      std::cin >> type;
    }

    if(length == -1)
    {
      std::cout << "Enter length of STI (in terms of number of frames)\n";
      std::cin >> length;
    }

    if(startFrame == -1)
    {
      std::cout << "Enter the frame of the video you would like to start from\n";
      std::cin >> startFrame;
    }

    Mat frame;
    std::cout << "Loading STI, depending on resolution this might take a while\n";
    mainFrame.setResolution(width,height);
    switch(type)
    {
      case 0:
        frame = mainFrame.getVidCopySTI(startFrame,length);
        break;
      case 1:
        frame = mainFrame.getVidHistoSTI(startFrame,length);
        break;
      default:
        std::cout << "Invalid Type! \n";
        continue;
    }

    std::cout << "STI loaded! Press 'q' to close the image\n";
    mainFrame.playFrame(frame);

    if(savetofile == 0)
    {
      std::cout << "Save STI to file? (y/n)\n";
      std::cin >> savetofile;
      if(savetofile == 'y')
      {
        std::cout << "Enter the filename\n";
        std::cin >> pathtoimage;
      }

      if(savetofile != 'y' || savetofile != 'n') savetofile = 0;
    }

    if(savetofile == 'y')
    {
      imwrite(pathtoimage,frame);

    }
    return 1;
  }


}


//Returns the frame at a given time and makes sure its in the right resolution
Mat FrameObject::getVidFrame(int frame)
{

    if(frame>=vid.get(CAP_PROP_FRAME_COUNT))
    {
      return Mat(height,width,0, Scalar(0,0,0));
    }
    vid.set(CAP_PROP_POS_FRAMES, frame);
    int curWidth = vid.get(CAP_PROP_FRAME_WIDTH);
    int curHeight = vid.get(CAP_PROP_FRAME_HEIGHT);
    Mat tempMat,finalMat;
    vid >> tempMat;
    resize(tempMat,finalMat,finalMat.size(),(double)width/curWidth, (double)height/curHeight);
    return finalMat;
}

Mat FrameObject::getVidHistoSTI(int frame, int size)
{

  int totFrames = vid.get(CAP_PROP_FRAME_COUNT);

  if(frame+size >= totFrames) size = totFrames-frame-1;

  Mat finalFrame(width,size,CV_8UC1);



  for(int i = 0;i<size;i++)
  {
    Mat frame1 = getVidFrame(frame);
    Mat frame2 = getVidFrame(frame+1);
    for(int j = 0; j<width;j++)
    {

      Mat hist1 = getChromacityMat(frame1.col(j));
      Mat hist2 = getChromacityMat(frame2.col(j));


      float L = getL(hist1,hist2)/(float)width;
      //std::cout << "L=" << L << "\n";
      finalFrame.at<uchar>(j,i) = L*255;
    }

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
Mat FrameObject::getDifferenceSTI(int frame, int size)
{
  int totFrames = vid.get(CAP_PROP_FRAME_COUNT);

  if(frame+size >= totFrames) size = totFrames-frame-1;

  Mat finalFrame(width,size,CV_8UC1);
  for(int i = 0;i<size;i++)
  {
    Mat frame1 = getVidFrame(frame);
    Mat frame2 = getVidFrame(frame+1);
    for(int j = 0; j<width;j++)
    {

      Mat hist1 = getChromacityMat(frame1.col(j));
      Mat hist2 = getChromacityMat(frame2.col(j));

      hist1 = hist1.reshape(0,1);
      hist2 = hist2.reshape(0,1);

      Mat z = hist2-hist1;
      double D = getD(z)/(float)width;
      finalFrame.at<uchar>(j,i) = D*255;
    }

    frame++;
  }
  return finalFrame;
}

Mat FrameObject::toLongVector(Mat frame)
{
  std::cout << "calculating long vector \n";
  int width = frame.cols;
  int height = frame.rows;

  Mat finalFrame(width*height,1,frame.type());
  for(int i = 0; i<width;i++)
  {
    for(int j = 0; j<height;j++)
    {
      finalFrame.at<uchar>(j+i*width,0) = frame.at<uchar>(j,i);
    }
  }
  //std::cout << finalFrame << "\n";
  return finalFrame;
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

int FrameObject::getD(Mat frame)
{
  int size = frame.cols;
  int D = 0;
  for(int i = 0; i<size;i++)
  {
    D += pow(frame.at<uchar>(i,0),2);
  }

  return D;
}

Mat FrameObject::getVidCopySTI(int frame, int size)
{

  int totFrames = vid.get(CAP_PROP_FRAME_COUNT);

  if(frame+size >= totFrames) size = totFrames-frame-1;

  Mat finalFrame(height,size,vidType);
  vid.set(CAP_PROP_POS_FRAMES,frame);

  for(int i = 0; i< size;i++)
  {
    Mat tempFrame;
    vid >> tempFrame;
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
  char key = 0;
  while(true)
  {
    key = waitKey(30);
    if( key == 'q') break;
  }
  destroyAllWindows();
}
