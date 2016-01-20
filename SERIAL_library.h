#define BUFFER_SIZE 20
#define SERIAL_TIMEOUT 0

#define NEW_LINE        0x0A
#define CARRIAGE_RETRUN 0x0D
#define HARZ_TAB        0x09
#define VERT_TAB        0x0B
#define BACKSPACE       0x08
#define CTRL_Z          0x1A

#define ENABLE  1
#define DISABLE 0
int fifo=0;

void SERIAL_RECEIVER(int en_dis){
	EA = en_dis;
}

void SERIAL_BEGIN(){
     SCON = 0x50;
	
	   TMOD = (TMOD & 0x0F ) | 0x20;
       TH1  = 0xFD;
       TR1  = 1;

         EA = 1;
	     ES = 1;
      	
	     TI = 0;
	     RI = 0;
}
/*
void SERIAL_PRINT(char *STRING){
     	
	     int i;
	 for(i=0;STRING[i]!='\0';i++){
	      SBUF = STRING[i];
		      while(!TI);
        			TI=0;
	 }
	 
}
*/
///*
void SERIAL_WRITE(char CMD){
     	
	        SBUF = CMD;
		      while(!TI);
        			TI=0;
	        ES=1;	
	     
}
//*/
/*
void SERIAL_PRINT_Number(int num){
	
	int i;
	char BCD[5];
	unsigned int len;
	
  if (num>=0){ 
		  len = log10(num);
	    for(i=0;i<=len;i++){
			  BCD[i] = num%10;
				num = num/10;
      }	
       for(i=0;i<=len;i++){
	      SBUF = BCD[len-i]+0x30;
		      while(!TI);
        			TI=0;
	     }			
    }
	else if(num<0){
		   num = abs(num);
			 len = log10(num);
	    for(i=0;i<=len;i++){
			  BCD[i] = num%10;
				num = num/10;
      }	
			SERIAL_PRINT("-");
       for(i=0;i<=len;i++){
	      SBUF = BCD[len-i]+0x30;
		      while(!TI);
        			TI=0;
	     }				
		 }  
        ES=1;		 
    }
*/
/*
char* SERIAL_READ_REQ(int requied){
  
	int i;
	//char *recData = malloc(sizeof(char) * requied);
	static char recData[5];
	RI = 0;
	for(fifo=0;fifo<requied;fifo++){
	       while(!RI);
		     recData[fifo]=SBUF;
		     RI = 0 ;
		     
	}

		return recData;
}
*/
static char SERIAL_REC[BUFFER_SIZE];
short int SERIAL_AVAILABLE = 0 ;
short int SERIAL_STACK_POP = 0 ;

void serialInterrupt() interrupt 4
{
	

	ES = 1;
	
	if (SERIAL_AVAILABLE<=0){
  for(fifo=0;fifo<BUFFER_SIZE;fifo++){
     SERIAL_REC[fifo]=0;
  }
}

	if(RI==1){
		do{
			while(!RI);
	    SERIAL_REC[SERIAL_AVAILABLE]=SBUF;
		  RI=0;
			SERIAL_AVAILABLE ++ ;
		//	delay(SERIAL_TIMEOUT);
     }while(RI==1);
		 //while(SERIAL_REC[i-1]!=13);

	ES = 1;
 }
}

char SERIAL_READ(){
	
  char popData;
	
	while(SERIAL_AVAILABLE == 0);
	
	popData = SERIAL_REC[0];

	for(fifo=0;fifo<SERIAL_AVAILABLE;fifo++){
		SERIAL_REC[fifo-1] = SERIAL_REC[fifo];
	}
	
	SERIAL_AVAILABLE-- ;
	if (SERIAL_AVAILABLE<=0){
		  SERIAL_AVAILABLE=0;
  }
	
	return popData;
}

/* Document
   
   Function :
   
   1.SERIAL_BEGIN()               // initialize serial communication
   2.SERIAL_WRITE(char CMD)       // send single char
   3.SERIAL_PRINT(char *STRING)   // send char array (string)
   4.SERIAL_PRINT_Number(int num) // send signed number  
   5.SERIAL_READ_REQ(int requied) // requied-no.of requst char | return char array 
   6.SERIAL_READ()                // return last serial buffer value(single char)
   7.SERIAL_AVAILABLE             // no.of serial received stack buffer size 
   8.BUFFER_SIZE                  // serial buffer size
   9.SERIAL_RECEIVER(enable)      // Enabling serial receiver 

*/

