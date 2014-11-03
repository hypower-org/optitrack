#include <stdio.h>
#include <math.h>
#include "quaternion.h"
#include <vrpn/vrpn_Connection.h>
#include <vrpn/vrpn_Tracker.h>
#include <assert.h>

//#################### OPTITRACK DRIVER  #################################

/*
  Paul Glotfelter
  
  10/28/2014

  A driver for OptiTrack.  Utilizes VRPN and a socket client to
  communicate to a Java server.  
*/

//########################################################################




//############################### GLOBALS  ###############################

quaternion fix = {0.70710678, 0.0, 0.0, 0.70710678}; //Fixes incoming
                                                     //axis?  Do I
                                                     //need this for
                                                     //the optitrack
                                                     //stuff? 

quaternion fixi = inverseq(fix); //Inverse of fix! 

const char * TRACKER_NAME = "Tracker0";
int CONNECTION_PORT = vrpn_DEFAULT_LISTEN_PORT_NO;

vrpn_Tracker_Remote * tracker; 
vrpn_Connection * connection; 

//########################################################################


//############################### CALLBACK HANDLERS ###############################

void VRPN_CALLBACK handle_data (void *, const vrpn_TRACKERCB t) {
	
  quaternion received = {t.quat[0], t.quat[1], t.quat[2], t.quat[3]};

  // SEND TO JAVA IN -> X Y Z PHI THETA PSI 
  
  //ASK JP: Do I need to convert from OptiTrack -> Vicon axis? 
  
}

int main (void) {

  return 0;
}
