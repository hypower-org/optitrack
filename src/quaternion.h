#ifndef QUATERNION_H
#define QUATERNION_H

//##################### QUATERNION HEADER #########################

/*

  Paul Glotfelter

  11/03/2014

  Header file for quaternion.C.  
*/

//#################################################################

typedef struct {
  double a;
  double b;
  double c;
  double d;
} quaternion;


//##################### OPERATORS #################################

void printq(quaternion q); 
quaternion multq(quaternion q1, quaternion q2);
quaternion inverseq(quaternion q);
double phiq(quaternion q);
double thetaq(quaternion q);
double psiq(quaternion q); 

#endif
