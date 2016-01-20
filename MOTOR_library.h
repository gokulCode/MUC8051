#define OPEN    1
#define CLOSE   0


#define FORWARD 0
#define REVERSE 1
#define STOP    2
#define LEFT    3
#define RIGHT   4


sbit MOTOR_P = P1^6;
sbit MOTOR_N = P1^7;

void MOTOR_OPERATION(int oper){
		if (oper == FORWARD){
			  MOTOR_P = 0;
			  MOTOR_N = 1;
		}else if (oper == REVERSE){
			  MOTOR_P = 1;
			  MOTOR_N = 0;
		}else{
			  MOTOR_P = 1;
			  MOTOR_N = 1;
	  }	
}

