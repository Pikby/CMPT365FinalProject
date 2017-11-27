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
    std::string video;

    //Resolution
    int width = 860;
    int height = 420;
    //The captures of the two videos
    VideoCapture vid;
    Mat normalize(Mat frame);

  public:
    FrameObject(std::string vidname, std::string pathtovid)
    {
      videoName = vidname;
      video = pathtovid;

      vid = VideoCapture(pathtovid);



      vidType = getVidFrame(0).type();
    }
    void setResolution(int nWidth, int nHeight)
    {
      width = nWidth;
      height = nHeight;
    }
    void printMat(Mat m);
    Mat getChromacityMat(Mat frame);
    int getL(Mat frame1, Mat frame2);
    Mat getVidFrame(int frame);
    //Mat getWipeFrame(int vid1Frame,int vid2Frame, int dist, bool startLeft);
    //Mat getWipeFrame(Mat vid1mat,Mat vid2mat);
    Mat getVidCopySTI(int frame, int size);
    Mat getVidHistoSTI(int frame, int size);

    void playFrame(Mat frame);
};
