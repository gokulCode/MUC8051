#include <intrins.h>
#include <stdlib.h> 

#define ON  1
#define OFF 0

#define RELAY_ON  0
#define RELAY_OFF 1

//////////////////////////////////////////
#define OP_FREQ 11059200                //
//////////////////////////////////////////
#define MACHINE_CYCLE OP_FREQ/12        //
#define MS_PERIODE MACHINE_CYCLE/50000  //
//////////////////////////////////////////

// Delay Function
void delay(int periode_MS){
	
	int i,j;
	
	for(j=0;j<periode_MS;j++)
   for(i=0;i<MS_PERIODE;i++){
   _nop_();_nop_();_nop_();
	 _nop_();_nop_();_nop_();
	 _nop_();_nop_();_nop_();
   }
}

void delay_us(int periode_US){
	// not accurate delay 1 us -> 70 us delay
	// 10us -> 200us
	int j;
	
	for(j=0;j<periode_US;j++);
   _nop_();_nop_();_nop_();
}

// Adjestment of variable Range
int map(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/*
// Random Number Generator with in range
unsigned int random(unsigned int min, unsigned int max)
{
    int r;
    const unsigned int range = 1 + max - min;
    const unsigned int buckets = RAND_MAX / range;
    const unsigned int limit = buckets * range;

    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}


// Push Button Switch Latch
int button (int button){
	  static int lastState=0;
	  static int state = 0 ;

	  if ((button==1) & (lastState==0)){
		   state = ~state;
			 delay(10);
    }
		lastState = button;
	  return state ;
}

// Push Button counter
int CounterUPDOWN (int buttonInc,int buttonDec){
	  
	  static int lastStateInc = 0;
	  static int lastStateDec = 0;
	  
	  static int state = 0 ;

	  if ((buttonInc==1) & (lastStateInc==0)){
		   state = state+1;
			 delay(10);
    }
		
		if ((buttonDec==1) & (lastStateDec==0)){
		   state = state-1;
			 delay(10);
    }
		
		lastStateInc = buttonInc;
		lastStateDec = buttonDec;
		
	  return state ;
}



// variable Limiting in Range
int constrain(int value,int minVal, int maxVal){

      int limitRange ;
	
	    if (value < minVal) {
			    limitRange = minVal;
      }
		  else if (value > maxVal) {
			    limitRange = maxVal;
      }
			else {
				  limitRange = value;
			}
		
			return limitRange;

}
*/

int STRING2Number(char a[]) {
  int c, sign, offset, n;
 
  if (a[0] == '-') {  // Handle negative integers
    sign = -1;
  }
 
  if (sign == -1) {  // Set starting position to convert
    offset = 1;
  }
  else {
    offset = 0;
  }
 
  n = 0;
 
  for (c = offset; a[c] != '\0'; c++) {
    n = n * 10 + a[c] - '0';
  }
 
  if (sign == -1) {
    n = -n;
  }
 
  return n;
}

