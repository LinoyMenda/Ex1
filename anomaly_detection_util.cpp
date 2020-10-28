/*
 * animaly_detection_util.cpp
 *
 * Author: 313302317 and Linoy Menda
 */

#include <cmath>
#include "anomaly_detection_util.h"

// returns the average of array x
float avg(float* x, int size){
    float sumOfArray = 0; 
    float avg = 0;
	for (int i=0; i < size; i++){
        sumOfArray += *x;
        x++;
    }
    avg = sumOfArray / size;
	return avg;
}

// returns the variance of X and Y
float var(float* x, int size){
	float var = 0; 
	float u = avg(x,size);
	float squares_sum = 0; //  for all 0<=i<=n  the sum of all (Xi^2)
	for (int i=0; i < size; i++){
		squares_sum += pow(*x, 2);
		x++;
	}
	var = (pow(size,-1)*squares_sum)-(pow(u,2));
	return var;
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size){
	float cov = 0;
	float x_after_change[size] = {0}; // new araay to save the changes without chane the original array x
	float y_after_change[size] = {0}; // new araay to save the changes without chane the original array y
	float multiply_the_differences [size] = {0};
	float sum_of_multiply_the_differences = 0;

	float average_x = avg(x,size);
	float average_y = avg (y,size);
	for (int i=0; i < size; i++){
		 x_after_change[i] = *x - average_x;
		 y_after_change[i] = *y - average_y;
		x++ ,y++;
	}
	for (int i=0; i < size; i++){
		multiply_the_differences [i] = (x_after_change[i]*y_after_change[i]);
	}
	for (int i=0; i < size; i++){
		sum_of_multiply_the_differences += multiply_the_differences [i];
	}
	cov = sum_of_multiply_the_differences / size ;
	return cov;
}

// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size){
	float pearson = 0;
	float standard_dev_x = sqrt(var(x,size));
	float standard_dev_y = sqrt(var(y,size));
	pearson = cov(x,y,size) / (standard_dev_x*standard_dev_y);
	return pearson;
}

// performs a linear regression and returns the line equation
// In this section Hananel Hadd helps me to understant why "Point" is pointer to pointer
Line linear_reg(Point** points, int size){
	float save_x [size];
	for (int i=0; i<size; i++){
		save_x [i] = points[i]->x;
	}
		float save_y [size];
	for (int i=0; i<size; i++){
		save_y [i] = points[i]->y;
	}

	float a = cov(save_x,save_y, size) / var(save_x,size);
	float b =  avg(save_y,size) - (a* avg(save_x,size));
	return Line(a,b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){
	Line line = linear_reg(points,size);
	float f_x = line.f(p.x);
	float dev = std:: abs (f_x - p.y);
	return dev;
}

// returns the deviation between point p and the line
float dev(Point p,Line l){
	float f_x = l.f(p.x);
	float dev = std:: abs(f_x - p.y);
	return dev;
}

