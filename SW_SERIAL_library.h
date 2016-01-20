// WARNING ! DON'T USE THIS library for continue receiving minimum data time gap ***us 
// RECEIVER interrupt enabled in this library it can work in delay function execute

#define SW_BUFFER_SIZE 50

sbit SW_TX = P1^0; 
sbit SW_RX = P3^2; // DON'T CHANGE

int sw_fifo; 

void SW_SERIAL_delay(int periode_US){ //104us 9600
	do{
	_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();
	_nop_();_nop_();
	}while(periode_US--);
}


void SW_SERIAL_BEGIN(){
      
	    SW_RX = 1 ;
	    SW_TX = 1 ;
      
	    EA  = 1 ;
	    IE0 = 1 ;
	    IT0 = 1 ;
	    EX0 = 1 ;
}

void SW_SERIAL_WRITE(char CMD){

	    char DATA[8];
	    int i;
	
	    EA = 0 ;   
	    
	    for(i=0;i<8;i++){
				DATA[i] = (CMD >> i) & 1;
		}
	    SW_TX = 0;
	    SW_SERIAL_delay(4);
	    SW_TX = DATA[0];
		SW_SERIAL_delay(4);
		SW_TX = DATA[1];
		SW_SERIAL_delay(4);
		SW_TX = DATA[2];
		SW_SERIAL_delay(4);
		SW_TX = DATA[3];
		SW_SERIAL_delay(4);
		SW_TX = DATA[4];
		SW_SERIAL_delay(4);
		SW_TX = DATA[5];
		SW_SERIAL_delay(4);
		SW_TX = DATA[6];
		SW_SERIAL_delay(4);
		SW_TX = DATA[7];
		SW_SERIAL_delay(4);
		SW_TX = 1;
		SW_SERIAL_delay(4);
			
		EA = 1 ; 
}

char SW_SBUF(){

	   	char DATA[8];
	    char CMD = 0;
	    register i;
	
	    EA = 0 ; 

	    //SW_SERIAL_delay(4);
		DATA[0] = SW_RX;
		SW_SERIAL_delay(4);
	    DATA[1] = SW_RX;
		SW_SERIAL_delay(4);
	    DATA[2] = SW_RX;
		SW_SERIAL_delay(4);
	    DATA[3] = SW_RX;
		SW_SERIAL_delay(4);
	    DATA[4] = SW_RX;
		SW_SERIAL_delay(4);
	    DATA[5] = SW_RX;
	  	SW_SERIAL_delay(4);
	    DATA[6] = SW_RX;
		SW_SERIAL_delay(4);
	    DATA[7] = SW_RX;
		SW_SERIAL_delay(4);
		if(SW_RX == 1){  }
      
		for(i=0;i<8;i++){
		    CMD |= ((DATA[i]&1) << i);
		}

			return CMD & 0x7F;
}

void SW_SERIAL_PRINT(char *STRING){
     	
	     int i;
	 for(i=0;STRING[i]!='\0';i++){
	    SW_SERIAL_WRITE(STRING[i]);
	 }
	 
}


static char SW_SERIAL_REC[SW_BUFFER_SIZE];
short int SW_SERIAL_AVAILABLE = 0 ;
short int SW_SERIAL_STACK_POP = 0 ;


void sw_serialInterrupt() interrupt 0
{
	  char SW_BUF_reg;
	  
	
  	if (SW_SERIAL_AVAILABLE<=0){	
      for(sw_fifo=0;sw_fifo<SW_BUFFER_SIZE;sw_fifo++){
         SW_SERIAL_REC[sw_fifo]=0;
      }
	  } else {
			SW_SERIAL_delay(4);
		}
		
	 SW_BUF_reg = SW_SBUF();

	 SW_SERIAL_REC[SW_SERIAL_AVAILABLE]=SW_BUF_reg;
	 SW_SERIAL_AVAILABLE ++ ;
	
	 	EA = 1 ; 
}

char SW_SERIAL_READ(){
	
  char popData;
	
	popData = SW_SERIAL_REC[0];

	for(sw_fifo=0;sw_fifo<SW_SERIAL_AVAILABLE;sw_fifo++){
		SW_SERIAL_REC[sw_fifo-1] = SW_SERIAL_REC[sw_fifo];
	}
	
	SW_SERIAL_AVAILABLE-- ;
	
	if (SW_SERIAL_AVAILABLE<=0){
		  SW_SERIAL_AVAILABLE=0;
  }
	
	return popData;
}