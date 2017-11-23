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
    double width = 1280;
    double height = 720;
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
      vidType = getVid1Frame(1).type();
    }
    void setResolution(int nWidth, int nHeight)
    {
      width = nWidth;
      height = nHeight;
    }
    Mat getVid1Frame(int frame);
    Mat getVid2Frame(int frame);
    Mat getWipeFrame(int vid1Frame,int vid2Frame, int dist, bool startLeft);
    void playFrame(Mat frame);
};
