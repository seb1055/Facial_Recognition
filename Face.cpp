//
// Created by seb on 3/26/19.
//

#include "Face.h"

string Face::getName() { return this->name; }

Rect Face::getFaceBox() { return this->face_box; }

vector<Rect> Face::getEyes() { return this->eye_boxs; }

void Face::setFaceBox(Rect face) { this->face_box; }

void Face::setEyeBoxs(vector<Rect> eyes) { this->eye_boxs; }

void Face::setName(string name) { this->name; }