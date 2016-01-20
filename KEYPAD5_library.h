sbit SET_PIN = P1^2;
sbit MOV_PIN = P1^3;
sbit INC_PIN = P1^4;
sbit DEC_PIN = P1^5;
sbit ENT_PIN = P1^6;

#define FILL_DIGITS 2

char KP5_ENT = 0 ;
char KP5_SET = 0 ;
int  KP5_MOV = 0 ;
int  KP5_INC_DEC_COUNT = 0 ;
char KP5_FILL[FILL_DIGITS+1];

char KEYPAD5_AVAILABILE = 0;

void KEYPAD5_BEGIN(){
	int i;
	for(i=0;i<FILL_DIGITS;i++){
		KP5_FILL[i]='0';
	}
	 KP5_FILL[FILL_DIGITS]=0;
}

char setButton (char button){
	  static char lastState=0;
	  static char state = 0 ;

	  if ((button==1) & (lastState==0)){
		   state = ~state;
			 delay(10);
    }
		lastState = button;
	  return state ;
}

char movCounter (char button){
	  static char lastState=0;
	  static char state = -1 ;

	  if ((button==1) & (lastState==0)){
		   state = state + 1;
			 delay(10);
      }

      if (state >= FILL_DIGITS){
          state = 0;
      }
		lastState = button;
   
	  return state ;
}

char INC_DEC_Counter (char buttonInc,char buttonDec){
	  
	  static char lastStateInc = 0;
	  static char lastStateDec = 0;
	  
	  static int state = 1 ;

	  	if ((buttonInc==1) & (lastStateInc==0)){
		   state = state+1;
			 delay(10);
    	}
		
		if ((buttonDec==1) & (lastStateDec==0)){
		   state = state-1;
			 delay(10);
    	}
		
        if(state>9){
           state = 0;
        }
        if(state<0){
           state = 9;
		}

		lastStateInc = buttonInc;
		lastStateDec = buttonDec;
		
	  return state ;
}

void KEYPAD5(){
 	KP5_ENT = ~ ENT_PIN && 1;
 	KP5_SET = ~ (setButton(SET_PIN) && 1);
    KP5_MOV = movCounter(MOV_PIN) ;
 	KP5_INC_DEC_COUNT = INC_DEC_Counter(INC_PIN,DEC_PIN);
	KP5_FILL[KP5_MOV] = KP5_INC_DEC_COUNT + 0x30;
}
