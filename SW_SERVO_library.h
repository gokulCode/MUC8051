

sbit servo_pin = p1^0;

void SERVO_MOTOR(int angle){
	int angleToDelay;
	int smooth;
	angleToDelay = map(angle,0,179,0,56);
	for(smooth=0;smooth<30;smooth++){
		servo_pin = 1;              
		delay_us(56);
		delay_us(angleToDelay);
		servo_pin = 0;
		delay(20);
	}
}