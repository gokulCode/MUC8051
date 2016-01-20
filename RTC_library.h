#include "I2C_lib.h"

///////////////////////
#define RTC_ID 0xD   //
#define RTC_PID 0x0  //         // Assign time in 24 hours mode
////////////////////////////////////////////////////////////////////////////////////////////
//char clock[]={ char sec,char min,char hour,char day,char date,char month,char year } ;  //
//                      |        |        |        |        |         |         |        //
  char clock[]={        0,      40,      14,       2,       30,       11,       15 } ;    // 
  unsigned int RTC_TIME[6];    // <= Downloaded time                                      //
  bit PM_AM      ;             // <= PM -> 1   |   AM  -> 0                               //
////////////////////////////////////////////////////////////////////////////////////////////

	
unsigned short int addr_ptr;

char BCDToDecimal (char bcdByte)
{
  return (((bcdByte & 0xF0) >> 4) * 10) + (bcdByte & 0x0F);
}
 
char DecimalToBCD (char decimalByte)
{
  return (((decimalByte / 10) << 4) | (decimalByte % 10));
}
	

	
void RTC_TIME_UPLOAD(unsigned char *clock){

	   I2C_START();
	   I2C_ADDRESS(RTC_ID,RTC_PID,WRITE);  
	   I2C_WRITE(0x00);
	   for(addr_ptr=0;addr_ptr<7;addr_ptr++){
		     I2C_WRITE(DecimalToBCD(clock[addr_ptr]));
		 }
		 I2C_STOP();
	   I2C_IDLE();
}

void RTC_TIME_DOWNLOAD(){
	
	   I2C_START();
	   I2C_ADDRESS(RTC_ID,RTC_PID,WRITE);  
	   I2C_WRITE(0x00);
	   I2C_START();
	   I2C_ADDRESS(RTC_ID,RTC_PID,READ); 
	   for(addr_ptr=0;addr_ptr<7;addr_ptr++){
		     RTC_TIME[addr_ptr]=BCDToDecimal(I2C_READ());
			   I2C_putACK(addr_ptr == 0x06);
		 }
		 I2C_STOP();
	   I2C_IDLE();
		 
		     if (RTC_TIME[2]>=12){
					 if (RTC_TIME[2]>12){
						RTC_TIME[2] = RTC_TIME[2] - 12 ;
					 }
					  PM_AM = 1 ;
         }else{
					  PM_AM = 0 ;
				 }
}


