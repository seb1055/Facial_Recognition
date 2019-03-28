#include "opencv2/highgui.hpp"
#include "face_model/FaceDetector.h"

using namespace std;
using namespace cv;


void displayFaces(Mat frame, vector<Face> faces);
void startCapture(VideoCapture capture);


String window_name = "Face Capture";
FaceDetector faceDetector;


int main( int argc, const char** argv )
{
    VideoCapture capture;
    startCapture(capture);
    return 0;
}


void startCapture(VideoCapture capture){
    Mat frame;
    capture.open( 0 );

    int frame_count = 0;

    if ( ! capture.isOpened() ) { printf("--(!)Error opening video capture\n"); exit(-1);}
    while ( capture.read(frame) )
    {
        if( frame.empty() )
        {
            printf(" --(!) No captured frame -- Break!");
            break;
        }


        if (frame_count % 5 == 0) { // only detect every 5 frames
            displayFaces(frame, faceDetector.findFaces(frame));
            frame_count = 0;
        } else {
            displayFaces(frame, faceDetector.findFaces(frame));
        }

        if (waitKey(10) == 27) {
            capture.release();
            break;
        } // escape

    }

    capture.release();

}


void displayFaces(Mat frame, vector<Face> faces) {

    for (auto &face : faces) {

        Rect facebox = face.getFaceBox();
        rectangle(frame, facebox, Scalar(255, 0, 0), 3);
        putText(frame, face.getName(), Point(facebox.x, facebox.y), FONT_HERSHEY_SIMPLEX, 1, Scalar(97, 255, 0), 2);

        for (auto &eye : face.getEyes()) {
            Point eye_center(eye.x + eye.width / 2, eye.y + eye.height / 2);
            int radius = cvRound((eye.width + eye.height) * 0.25);
            circle(frame, eye_center, radius, Scalar(255, 0, 0), 4, 8, 0);
        }
    }
    imshow( window_name, frame );
}