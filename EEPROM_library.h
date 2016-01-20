////////////////////////////
#define EEPROM_DEV_ID 0xA //
#define EEPROM_PID 0x0    //         
////////////////////////////
// 4k - 9bit Adderessing support


char PID_MSBmemoryLoc;

	
void EEPROM_UPLOAD(int memoryLoc,int memoryData){
   
	   PID_MSBmemoryLoc = (EEPROM_PID & 6)|((memoryLoc >> 8) & 1) ;
	   I2C_START();
	   I2C_ADDRESS(EEPROM_DEV_ID,PID_MSBmemoryLoc,WRITE);
	   I2C_WRITE(memoryLoc);
	   I2C_WRITE(memoryData);
	   I2C_STOP();
       I2C_IDLE();
	
}

int EEPROM_DOWNLOAD(int memoryLoc){
	
	   int memoryData;
	
	   PID_MSBmemoryLoc = (EEPROM_PID & 6)|((memoryLoc >> 8) & 1) ;

	   I2C_START();
	   I2C_ADDRESS(EEPROM_DEV_ID,PID_MSBmemoryLoc,WRITE);
	   I2C_WRITE(memoryLoc);
	   I2C_START();
	   I2C_ADDRESS(EEPROM_DEV_ID,PID_MSBmemoryLoc,READ); 
		 memoryData = I2C_READ();
		 I2C_putACK(NACK);
		 I2C_STOP();
	   I2C_IDLE();
	
	   return memoryData;
}