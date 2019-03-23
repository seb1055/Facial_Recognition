#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"
#include <stdio.h>
using namespace std;
using namespace cv;
void detectAndDisplay( Mat frame );
void startCapture(VideoCapture capture);

CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;

String window_name = "Capture - Face detection";
int main( int argc, const char** argv )
{
    VideoCapture capture;



    face_cascade.load("/home/seb/Projects/facerec/haarcascade_frontalface_alt.xml");
    eyes_cascade.load("/home/seb/Projects/facerec/haarcascade_eye_tree_eyeglasses.xml");

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
        detectAndDisplay( frame );
        if( waitKey(10) == 27 ) { break; } // escape

    }

}


void detectAndDisplay( Mat frame )
{
    std::vector<Rect> faces;
    Mat frame_gray;
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(60, 60) );
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Point p1(faces[i].x, faces[i].y);
        Point p2(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
        rectangle(frame, p1,p2, Scalar(255,0,255),4 , 8 , 0);

        Mat faceROI = frame_gray( faces[i] );
        std::vector<Rect> eyes;
        //-- In each face, detect eyes
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );
        for ( size_t j = 0; j < eyes.size(); j++ )
        {
            Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
            int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
            circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
        }
    }
    //-- Show what you got
    imshow( window_name, frame );
}