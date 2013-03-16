
/*
 #ifndef __A2_521__BoundingBox__
#define __A2_521__BoundingBox__

#include <iostream>
#include <vector>

using namespace std;

class BoundingBox{
	
	private:
		double HEIGHT;
		double WIDTH;
		vector<double> top_left;
		vector<double> top_right;
		vector<double> bottom_left;
		vector<double> bottom_right;
	
	public:
		BoundingBox();
		virtual ~BoundingBox();
		void setAll(double x, double y, double height, double width);
		void updateX(double newX);
		void updateY(double newY);

		vector<double> get_top_left();
		vector<double> get_top_right();
		vector<double> get_bottom_right();
		vector<double> get_bottom_left();
	
		double getLeft();
		double getRight();
		double getTop();
		double getBottom();
	
		bool isColliding(BoundingBox * A, BoundingBox * B);
		bool isColliding(BoundingBox * B);
};

#endif

*/
