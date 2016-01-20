#define WRITE 0
#define READ  1

#define ACK   0
#define NACK  1

sbit SDA = P3^6;
sbit SCL = P3^7;

int i;

void I2C_IDLE(){
	  SDA = 1 ;
	  SCL = 1 ;
}

void I2C_START(){
	  SDA = 1 ;
	  SCL = 1 ;
	  SDA = 0 ;
	  SCL = 0 ;
}

void I2C_STOP(){
		SDA = 0 ;
	  SCL = 1 ;
	  SDA = 1 ;
}

void I2C_CLK(){
	  SCL = 1 ;
	  delay(1);
	  SCL = 0 ;
	  delay(1);
}

void I2C_putACK(bit ack){ 

	   SDA = ack ;
	   I2C_CLK();

		 
}

void I2C_WRITE(char frame){
	 
	do{
	  for(i=7;i>=0;i--){
			SDA = ( frame >> i ) & 1;
			I2C_CLK();
		}
//// ACK CHECK ////////
		  SDA = 1 ;  //
		  SCL = 1 ;  //
	    delay(1);    //
	}while(SDA == 1);//
    	SCL = 0 ;    //
	    delay(1);    //
///////////////////////
}

char I2C_READ(){
	
	static char frame = 0 ;
	SDA = 1 ;
	frame = 0 ;
	
		for(i=7;i>=0;i--){
	
     			SCL = 1 ;      
	        delay(1);       
			
				if (SDA == 1){                 
					frame = frame | ( 1 << i );   
				}                              
				                               
  				SCL = 0 ;      
			  	delay(1);  
		}
		
		return frame;
}

void I2C_ADDRESS(char DEVICE_ADDR ,char SPECIFIC_ADDR,bit WR) {
		
		char addr_frame;

    addr_frame = ( DEVICE_ADDR << 4 ) | ( SPECIFIC_ADDR << 1) | WR ;
		
	  I2C_WRITE(addr_frame);
}