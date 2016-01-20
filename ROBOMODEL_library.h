#define FORWARD 0
#define REVERSE 1
#define STOP    2
#define LEFT    3
#define RIGHT   4

/////////////////////////////
sbit LEFT_MOTOR_P  = P3^0; //
sbit LEFT_MOTOR_N  = P3^1; //
sbit RIGHT_MOTOR_P = P3^2; //
sbit RIGHT_MOTOR_N = P3^3; //
/////////////////////////////

/* FUNCTIONS

   1.MOTOR_OPERATION(int side,int oper);
   2.ROBOT_DIRECETION(int dir);


*/


void MOTOR_OPERATION(int side,int oper){
	if (side == RIGHT) {
		if (oper == FORWARD){
			RIGHT_MOTOR_P = 1;
			RIGHT_MOTOR_N = 0;
		}else if (oper == REVERSE){
			RIGHT_MOTOR_P = 0;
			RIGHT_MOTOR_N = 1;
		}else{
			RIGHT_MOTOR_P = 0;
			RIGHT_MOTOR_N = 0;
		}	
	}else{
	    if (oper == FORWARD){
			LEFT_MOTOR_P = 1;
			LEFT_MOTOR_N = 0;
		}else if (oper == REVERSE){
			LEFT_MOTOR_P = 0;
			LEFT_MOTOR_N = 1;
		}else{
			LEFT_MOTOR_P = 0;
			LEFT_MOTOR_N = 0;
		}	
	}
}

void ROBOT_DIRECETION(int dir){
	if(dir == LEFT){
		MOTOR_OPERATION(LEFT,STOP);
		MOTOR_OPERATION(RIGHT,FORWARD);
	}
	if(dir == RIGHT){
		MOTOR_OPERATION(LEFT,FORWARD);
		MOTOR_OPERATION(RIGHT,STOP);
	}
	if(dir == FORWARD){
		MOTOR_OPERATION(LEFT,FORWARD);
		MOTOR_OPERATION(RIGHT,FORWARD);
	}
	if(dir == REVERSE){
		MOTOR_OPERATION(LEFT,REVERSE);
		MOTOR_OPERATION(RIGHT,REVERSE);
	}
	if(dir == STOP){
		MOTOR_OPERATION(LEFT,STOP);
		MOTOR_OPERATION(RIGHT,STOP);
	}
}