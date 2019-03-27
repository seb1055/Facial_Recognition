#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/face.hpp"
#include <opencv2/core_detect.hpp>
#include "face_model/FaceDetector.h"

#define EYE_CASCADE "face_model/haarcascade_eye_tree_eyeglasses.xml"
#define FACE_CASCADE "face_model/haarcascade_frontalface_alt.xml"

using namespace std;
using namespace cv;
using namespace cv::face;


void displayFaces(Mat frame, vector<Face> faces);
void startCapture(VideoCapture capture);

static Mat norm_0_255(InputArray _src);


String window_name = "Face Capture";
FaceDetector faceDetector;
bool skipframe = 0;




int main( int argc, const char** argv )
{
    VideoCapture capture;
    //loadModel("/home/seb/Desktop/seb_faces/faces.csv");
    startCapture(capture);

    return 0;
}


void startCapture(VideoCapture capture){
    Mat frame;
    capture.open( 0 );

    if ( ! capture.isOpened() ) { printf("--(!)Error opening video capture\n"); exit(-1);}
    while ( capture.read(frame) )
    {
        if( frame.empty() )
        {
            printf(" --(!) No captured frame -- Break!");
            break;
        }
        //-- 3. Apply the classifier to the frame
        displayFaces(frame, faceDetector.findFaces(frame));
        skipframe = ~skipframe;
        if( waitKey(10) == 27 ) { break; } // escape

    }

    capture.release();

}

//TODO Error in eye drawing
void displayFaces(Mat frame, vector<Face> faces) {

    for (auto &face : faces) {
        Rect facebox = face.getFaceBox();
        rectangle(frame, facebox, Scalar(255, 0, 0), 3);
        cout << face.getName() << endl;
        putText(frame, face.getName(), Point(facebox.x, facebox.y), FONT_HERSHEY_SIMPLEX, 1, Scalar(97, 255, 0), 2);

        for (auto &eye : face.getEyes()) {

            Point eye_center(facebox.x + eye.x + eye.width / 2,
                             facebox.y + eye.y + eye.height / 2);
            int radius = cvRound((eye.width + eye.height) * 0.25);
            circle(frame, eye_center, radius, Scalar(255, 0, 0), 4, 8, 0);
        }
    }

    //-- Show what you got
    imshow( window_name, frame );

}





static Mat norm_0_255(InputArray _src) {

}