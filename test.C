#include <quaternion.h> 
#include <stdio.h> 
#include <assert.h>

//#################### QUATERNION TESTS  #################################

/*
  Paul Glotfelter
  
  11/03/2014

  Tests for the quaternion implementation.  
*/

//########################################################################

int main(void) {

  printf("BEGINNING TEST\n");

  quaternion q1 = {1.0, 3.0, 4.0, 3.0};
  quaternion q2 = {4.0, 3.9, -1.0, -3.0};

  quaternion result = multq(q1, q2); 

  printf("MULTIPLICATION RESULT: "); printq(result); 

  assert(result.a > 5.29 && result.a < 5.31);
  assert(result.b > 6.89 && result.b < 6.91);
  assert(result.c > 35.69 && result.c < 35.71); 
  assert(result.d > -9.61 && result.d < -9.59);

  printf("MULTIPLICATION SUCCEEDED!\n"); 

  result = inverseq(result);

  printf("INVERSE RESULT: "); printq(result);

  assert((result.a > 0.0036) && (result.a < 0.0037));
  assert((result.b > -0.0048) && (result.b < 0.0047));
  assert((result.c > -0.025) && (result.c < 0.024));
  assert((result.d > 0.0066) && (result.d < 0.0067));

  printf("INVERSION SUCCEEDED!\n");

  printf("%lf \n", phiq(result));
  printf("%lf \n", thetaq(result));
  printf("%lf \n", psiq(result));

  printf("ALL TESTS PASSED!\n");

  return 0;
}
