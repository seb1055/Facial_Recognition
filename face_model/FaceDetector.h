//
// Created by seb on 3/26/19.
//
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"
#include "opencv2/face.hpp"
#include <opencv2/core_detect.hpp>
#include "Face.h"


#ifndef GREETER_OPENFACE_FACEDETECTOR_H
#define GREETER_OPENFACE_FACEDETECTOR_H


using namespace std;
using namespace cv;
using namespace cv::face;


class FaceDetector {


public:
    FaceDetector(string face_casecade, string eye_cascade, string csv, vector<Mat> training_img, vector<int> labels);

    vector<Face> getFaces();

private:

    CascadeClassifier face_cascade;
    CascadeClassifier eyes_cascade;
    vector<Mat> images;
    vector<int> labels;
    Ptr<EigenFaceRecognizer> model = EigenFaceRecognizer::create();

};


#endif //GREETER_OPENFACE_FACEDETECTOR_H
