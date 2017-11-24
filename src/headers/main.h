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
    int width = 1280;
    int height = 720;
    //The captures of the two videos
    VideoCapture vid1;
    VideoCapture vid2;
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
    Mat getVidFrame(int frame, int vidNumb);
    Mat getWipeFrame(int vid1Frame,int vid2Frame, int dist, bool startLeft);
    Mat getVidSTI(int frame, int size, int vidNumb);

    Mat getWipeFrame(Mat vid1mat,Mat vid2mat);

    void playFrame(Mat frame);
};
