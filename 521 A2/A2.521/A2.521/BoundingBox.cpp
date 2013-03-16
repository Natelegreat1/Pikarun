//#include "BoundingBox.h"
//#include "Define.h"
//#include "A2.h"
//
//using namespace std;
//
//BoundingBox::BoundingBox(){ }
//
//BoundingBox::~BoundingBox(){ }
//
//void BoundingBox::setAll(double x, double y, double height, double width){
//	HEIGHT = height;
//	WIDTH = width;
//	top_left = {x, y};
//	top_right = {x+width-1, y};
//	bottom_left = {x, y+height-1};
//	bottom_right = {x+width-1, y+height-1};
//}
//
//void BoundingBox::updateX(double newX){
//	top_left.at(0) = newX;
//	top_right.at(0) = newX + WIDTH - 1;
//	bottom_left.at(0) = newX;
//	bottom_right.at(0) = newX + WIDTH - 1;
//}
//
//void BoundingBox::updateY(double newY){
//	top_left.at(1) = newY;
//	top_right.at(1) = newY;
//	bottom_left.at(1) = newY + HEIGHT - 1;
//	bottom_right.at(1) = newY + HEIGHT - 1;
//}
//
//vector<double> BoundingBox::get_top_left(){
//	return top_left;
//}
//
//vector<double> BoundingBox::get_top_right(){
//	return top_right;
//}
//
//vector<double> BoundingBox::get_bottom_right(){
//	return bottom_right;
//}
//
//vector<double> BoundingBox::get_bottom_left(){
//	return bottom_left;
//}
//
//double BoundingBox::getLeft(){
//	return top_left.at(0);
//}
//
//double BoundingBox::getRight(){
//	return top_right.at(0);
//}
//
//double BoundingBox::getTop(){
//	return top_left.at(1);
//}
//
//double BoundingBox::getBottom(){
//	return bottom_left.at(1);
//}
//
//bool BoundingBox::isColliding(BoundingBox * A, BoundingBox * B){
//	if (A->getLeft() < B->getRight() && A->getRight() > B->getLeft() &&
//		A->getBottom() < B->getBottom() && A->getBottom() > B->getBottom()){
//		cout<<"Touching\n";
//		return true;
//	}else{
//		cout<<"NOT\n";
//		
//		return false;
//	}
//}
//
//bool BoundingBox::isColliding(BoundingBox * B){
//	if (this->getLeft() < B->getRight() && this->getRight() > B->getLeft() &&
//		this->getBottom() < B->getBottom() && this->getBottom() > B->getBottom()){
//		cout<<"Touching\n";
//		return true;
//	}else{
//		cout<<"NOT\n";
//		return false;
//	}
//}