sbit VOICE_PLAY=P1^0;
sbit VOICE_ADD0=P1^1;
sbit VOICE_ADD1=P1^2;
sbit VOICE_ADD2=P1^3;
sbit VOICE_ADD3=P1^4;
sbit VOICE_ADD4=P1^5;


void VOICE_BEGIN(){
	VOICE_PLAY = 1;
	VOICE_ADD0 = 1;
	VOICE_ADD1 = 1;
	VOICE_ADD2 = 1;
	VOICE_ADD3 = 1;
	VOICE_ADD4 = 1;
}

void VOICE_SELECT(char addr){
	VOICE_ADD0  = ~(( addr      ) & 1)& 1;
	VOICE_ADD1  = ~(( addr >> 1 ) & 1)& 1;
	VOICE_ADD2  = ~(( addr >> 2 ) & 1)& 1;
	VOICE_ADD3  = ~(( addr >> 3 ) & 1)& 1;
	VOICE_ADD4  = ~(( addr >> 4 ) & 1)& 1;
	delay(10);
	VOICE_PLAY  = 0;
    delay(50);
    VOICE_PLAY  = 1;
	
	//VOICE_BEGIN();
}