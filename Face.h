//
// Created by seb on 3/26/19.
//

#ifndef GREETER_OPENFACE_FACE_H
#define GREETER_OPENFACE_FACE_H

#include "opencv2/core.hpp"

using namespace std;
using namespace cv;

class Face {
public:
    Face();

    void setFaceBox(Rect face);

    void setEyeBoxs(vector<Rect> eyes);

    void setName(string name);

    string getName();

    Rect getFaceBox();

    vector<Rect> getEyes();

private:
    Rect face_box;
    vector<Rect> eye_boxs;
    string name;
};


#endif //GREETER_OPENFACE_FACE_H
