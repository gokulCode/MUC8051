#define OPEN    1
#define CLOSE   0

#ifndef FORWARD
#define FORWARD 0
#define REVERSE 1
#define STOP    2
#define LEFT    3
#define RIGHT   4
#endif

sbit GATE_MOTOR_P = P1^1;
sbit GATE_MOTOR_N = P1^1;

sbit GATE_TOP_LIMIT    = P1^5;
sbit GATE_BUTTOM_LIMIT = P1^6;


void GATE_MOTOR_OPERATION(int oper){
		if (oper == FORWARD){
			GATE_MOTOR_P = 0;
			GATE_MOTOR_N = 1;
		}else if (oper == REVERSE){
			GATE_MOTOR_P = 1;
			GATE_MOTOR_N = 0;
		}else{
			GATE_MOTOR_P = 1;
			GATE_MOTOR_N = 1;
	  }	
}

void GATE_OPERATION(int oper){
	  if(oper == OPEN){
			GATE_MOTOR_OPERATION(FORWARD);
			while(GATE_TOP_LIMIT == 1);
			GATE_MOTOR_OPERATION(STOP);
		}else{
			GATE_MOTOR_OPERATION(REVERSE);
			while(GATE_BUTTOM_LIMIT == 1);
			GATE_MOTOR_OPERATION(STOP);
		}
}
