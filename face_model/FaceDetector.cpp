//
// Created by seb on 3/26/19.
//

#include "FaceDetector.h"

FaceDetector::FaceDetector() {
    face_cascade.load(FACE_CASCADE);
    eyes_cascade.load(EYE_CASCADE);
    read_csv("/home/seb/Desktop/seb_faces/faces.csv", this->images, this->labels, ';');
    model->train(images, labels);
}

vector<Face> FaceDetector::getFaces() {
    return vector<Face>();
}

vector<Face> FaceDetector::findFaces(const Mat &frame) {
    std::vector<Rect> face_boxes;
    std::vector<Rect> eye_boxes;
    std::vector<Face> face_list;

    Mat frame_gray;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);
    //-- Detect face_boxes
    face_cascade.detectMultiScale(frame_gray, face_boxes, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(60, 60));

    for (auto &face : face_boxes) {

        Face detected_face;
        if (!face.empty()) {
            detected_face.setFaceBox(face);
            eyes_cascade.detectMultiScale(frame_gray, eye_boxes, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
            detected_face.setEyeBoxes(eye_boxes);
            detected_face.setName(recognizeFace(frame));
            face_list.push_back(detected_face);
        }
    }
    return face_list;
}

string FaceDetector::recognizeFace(const Mat &frame) {
    Mat test_img = norm_0_255(frame);

    int label = model->predict(test_img);
    switch (label) {
        case 0:
            return "SEB";
        case 1:
            return "CHASE";
        default:
            return "N/A";
    }
}


Mat FaceDetector::norm_0_255(const _InputArray &_src) {
    Mat src = _src.getMat();
    // Create and return normalized image:
    Mat dst;
    Size size(640, 480);
    resize(src, dst, size, 0, 0, INTER_LINEAR);
    cvtColor(dst, dst, COLOR_BGR2GRAY);
    return dst;
}

void FaceDetector::read_csv(const string &filename, vector<Mat> &images, vector<int> &labels, char separator) {
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
        if (!path.empty() && !classlabel.empty()) {
            images.push_back(norm_0_255(imread(path, 1)));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }

}


