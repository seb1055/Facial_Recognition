#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/face.hpp"
#include <opencv2/core_detect.hpp>


#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;
using namespace cv::face;


void detectAndDisplay( Mat frame );
void startCapture(VideoCapture capture);

void loadModel(string filepath);
static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';');

string reconizeFace(Mat frame);
static Mat norm_0_255(InputArray _src);

CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;

String window_name = "Face Capture";
vector<Mat> images;
vector<int> labels;
Ptr<EigenFaceRecognizer> model = EigenFaceRecognizer::create();



int main( int argc, const char** argv )
{
    VideoCapture capture;

    //use for facial rec
    face_cascade.load("/home/seb/Projects/Greeter_OpenFace/haarcascade_frontalface_alt.xml");
    eyes_cascade.load("/home/seb/Projects/Greeter_OpenFace/haarcascade_eye_tree_eyeglasses.xml");
    loadModel("/home/seb/Desktop/seb_faces/faces.csv");


    startCapture(capture);

    return 0;
}

void loadModel(const string filepath) {
    read_csv(filepath, images, labels);
    model->train(images, labels);
    cout << "Model Trained" << endl;
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
        detectAndDisplay(frame);
        if( waitKey(10) == 27 ) { break; } // escape

    }

}


void detectAndDisplay( Mat frame )
{
    std::vector<Rect> faces;
    Mat frame_gray;
    Mat frame_zoom = frame;
    string person_name;

    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(60, 60) );
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Point p1(faces[i].x, faces[i].y);
        Point p2(faces[i].x + faces[i].width, faces[i].y + faces[i].height);



        //NOT GOOD PRAC FIND BETTER
        if(faces[i].width > 0 ) {
            frame_zoom = frame(Rect2d(faces[i].x, faces[i].y, faces[i].width, faces[i].height));

            frame_zoom.copyTo(frame(Rect(0, 0, frame_zoom.rows, frame_zoom.cols)));
            person_name = reconizeFace(frame);
        }

        rectangle(frame, p1,p2, Scalar(255,0,255),4 , 8 , 0);
        putText(frame, person_name, p1, FONT_HERSHEY_SIMPLEX, 1, Scalar(97, 255, 0), 2);


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

string reconizeFace(Mat frame) {


    Mat testimg = norm_0_255(frame);


    int predictedlabel = model->predict(testimg);

    switch (predictedlabel) {
        case 0:
            return "SEB";

        case 1:
            return "CHASE";


        default:
            return "N/A";

    }
}


static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator ) {
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        cout << error_message;
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            images.push_back(norm_0_255(imread(path, 1)));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}


static Mat norm_0_255(InputArray _src) {
    Mat src = _src.getMat();
    // Create and return normalized image:
    Mat dst;
    Size size(640, 480);
    resize(src, dst, size);
    cvtColor(_src, dst, COLOR_BGR2GRAY);
    return dst;
}