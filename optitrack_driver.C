#include <stdio.h>
#include <math.h>
#include <quaternion.h>
#include <vrpn/vrpn_Connection.h>
#include <vrpn/vrpn_Tracker.h>
#include <assert.h>
#include <socket_client.h>
#include <string.h>

//#################### OPTITRACK DRIVER  #################################

/*
  Paul Glotfelter
  
  10/28/2014

  A driver for OptiTrack.  Utilizes VRPN and a socket client to
  communicate to a Java server.  
*/

//########################################################################




//############################### GLOBALS  ###############################

//Quaternions for realligning axis

static quaternion fix = {0.70710678, 0.0, 0.0, 0.70710678}; //Fixes incoming
                                                     //axis?  Do I
                                                     //need this for
                                                     //the optitrack
                                                     //stuff? 

static quaternion fixi = inverseq(fix); //Inverse of fix! 

//Socket for communications to Java server

static int socketfd = conn("localhost", 8999);
static char buffer[500];

//Set up socket connection to local Java server.  This code is messy.

//########################################################################


//############################### CALLBACK HANDLERS#######################

  void VRPN_CALLBACK handle_data (void *, const vrpn_TRACKERCB t) {
	
    quaternion received = {t.quat[0], t.quat[1], t.quat[2], t.quat[3]};

    //TODO: Do something with quaternion...align axis? ASK JP: Do I need to convert from OptiTrack -> Vicon axis? 

    bzero(buffer, 500);
    sprintf(buffer, "%lf | %lf | %lf | %lf | %lf | %lf | %lf |", received.a, received.b, received.c,
            received.d, phiq(received), thetaq(received), psiq(received));
    send(socketfd, buffer);
  }

//########################################################################

int main (int argc, char * argv[]) {

  if (argc != 3) {
    fprintf(stderr, "Usage: %s hostname port\n", argv[0]);
    return -1;
  }

  char * hostname = argv[1];
  char * port = argv[2];
  int length = strlen(hostname) + strlen(port) + 1; //+ 1 for ':' 

  char result[length];
  bzero(result, length);

  strcpy(result, hostname);
  strcat(result, ":");
  strcat(result, port);

  const char * TRACKER_NAME = "Tracker0";
  int CONNECTION_PORT = vrpn_DEFAULT_LISTEN_PORT_NO;

  vrpn_Connection * connection = vrpn_get_connection_by_name(result);
  
  //create a dummy server
  vrpn_Tracker_NULL * null_tracker = new vrpn_Tracker_NULL(TRACKER_NAME, connection, 1, 60.0);

  vrpn_Tracker_Remote * tracker = new vrpn_Tracker_Remote(TRACKER_NAME, connection); 

  tracker->register_change_handler(NULL, handle_data);

  while (1) {

    null_tracker->mainloop();
    tracker->mainloop();
    connection->mainloop();
    vrpn_SleepMsecs(1000);
  }

  disconn(socketfd);

  return 0;
}
