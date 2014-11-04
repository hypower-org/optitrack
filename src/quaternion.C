#include <src/quaternion.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

//############################## QUATERNION  ############################

/*
  Paul Glotfelter
  
  11/03/2014

  Contains functions for converting from quaternions to Euler coordinates
*/

//#######################################################################




/*

  PRINTQ: Prints out the quaternion 
*/

void printq(quaternion q) {

  printf("a: %lf ", q.a); 
  printf("b: %lf ", q.b); 
  printf("c: %lf ", q.c); 
  printf("d: %lf\n", q.d); 
}

/*
  
  MULTQ: Multiplies two quaternions and returns a quaternion
  representing the result
*/

quaternion multq(quaternion q1, quaternion q2) {

  quaternion result = {0.0, 0.0, 0.0, 0.0};

  double a1 = q1.a; double b1 = q1.b; double c1 = q1.c; double d1 = q1.d;
  double a2 = q2.a; double b2 = q2.b; double c2 = q2.c; double d2 = q2.d; 

  result.a = (a1* a2) - (b1 * b2) - (c1 * c2) - (d1 * d2);
  result.b = (a1 * b2) + (b1 * a2) + (c1 * d2) - (d1 * c2);
  result.c = (a1 * c2) - (b1 * d2) + (c1 * a2) + (d1 * b2);
  result.d = (a1 * d2) + (b1 * c2) - (c1 * b2) + (d1 * a2); 
  
  return result;
}

/*

  INVERSEQ:  Inverses a quaternion and returns a quaternion
  representing the result
*/

quaternion inverseq(quaternion q) {

  quaternion result = {0.0, 0.0, 0.0, 0.0};
  
  double a = q.a; double b = q.b; double c = q.c; double d = q.d;

  double denom = pow(a, 2.0) + pow(b, 2.0) + pow(c, 2.0) + pow(d, 2.0);

  result.a = a / denom;
  result.b = -b / denom;
  result.c = -c / denom;
  result.d = -d / denom;

  return result;
}

/*
  
  PHIQ: Returns the YAW of the quaternion in
  RADIANS
*/

double phiq(quaternion q) {

  double a = q.a; double b = q.b; double c = q.c; double d = q.d;

  return atan2(2 * ((a * b) + (c * d)), pow(a, 2.0) - pow(b, 2.0) - pow(c, 2.0) + pow(d, 2.0));
}

/*
  
  THETAQ: Returns the ROLL of the quaternion in
  RADIANS
*/

double thetaq(quaternion q) {

  return -asin(2 * ((q.b * q.d) - (q.a * q.c)));
}

/*
  
  PSIQ: Returns the PITCH of the quaternion in
  RADIANS
*/

double psiq(quaternion q) {

  double a = q.a; double b = q.b; double c = q.c; double d = q.d; 

  return atan2(2 * ((a * d) + (b * c)), pow(a, 2.0) + pow(b, 2.0) - pow(c, 2.0) - pow(d, 2.0));
}

