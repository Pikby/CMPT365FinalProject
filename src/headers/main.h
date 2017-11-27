using namespace cv;

//The frame object
class FrameObject
{
  private:
    //The name of the new window or video
    std::string videoName;

    double fps=5;
    //The video type for new matrices
    int vidType;
    //Path to the first video
    std::string video1;
    //Path to the second video
    std::string video2;
    //Resolution
    int width = 100;
    int height = 100;
    //The captures of the two videos
    VideoCapture vid1;
    VideoCapture vid2;
    Mat normalize(Mat frame);

  public:
    FrameObject(std::string vidname, std::string pathtovid1, std::string pathtovid2)
    {
      videoName = vidname;
      video1 = pathtovid1;
      video2 = pathtovid2;
      vid1 = VideoCapture(pathtovid1);
      vid2 = VideoCapture(pathtovid2);
      vidType = getVidFrame(1,1).type();
    }
    void setResolution(int nWidth, int nHeight)
    {
      width = nWidth;
      height = nHeight;
    }
    void printMat(Mat m);
    Mat getChromacityMat(Mat frame);
    int getL(Mat frame1, Mat frame2);
    Mat getVidFrame(int frame, int vidNumb);
    Mat getWipeFrame(int vid1Frame,int vid2Frame, int dist, bool startLeft);
    Mat getWipeFrame(Mat vid1mat,Mat vid2mat);
    Mat getVidCopySTI(int frame, int size, int vidNumb);
    Mat getVidHistoSTI(int frame, int size, int vidNumb);

    void playFrame(Mat frame);
};
