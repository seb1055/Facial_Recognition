//
// Created by seb on 3/26/19.
//
#include "opencv2/objdetect.hpp"
#include "opencv2/face.hpp"
#include <opencv2/core_detect.hpp>

#include "Face.h"
#include <iostream>
#include <fstream>

#define EYE_CASCADE "face_model/haarcascade_eye_tree_eyeglasses.xml"
#define FACE_CASCADE "face_model/haarcascade_frontalface_alt.xml"


#ifndef GREETER_OPENFACE_FACEDETECTOR_H
#define GREETER_OPENFACE_FACEDETECTOR_H


using namespace std;
using namespace cv;
using namespace cv::face;


class FaceDetector {


public:
    FaceDetector();

    vector<Face> findFaces(const Mat &mat);

    string recognizeFace(const Mat &mat);
    vector<Face> getFaces();

private:
    static Mat norm_0_255(InputArray _src);

    static void read_csv(const string &filename, vector<Mat> &images, vector<int> &labels, char separator);
    CascadeClassifier face_cascade;
    CascadeClassifier eyes_cascade;
    vector<Mat> images;
    vector<int> labels;
    Ptr<EigenFaceRecognizer> model = EigenFaceRecognizer::create();

};


#endif //GREETER_OPENFACE_FACEDETECTOR_H
