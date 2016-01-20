char FP_REPLY[20];

void FP_COMMEND(int CMD_len,...){
	
	va_list CMD_list;
	int i;
	int checkSum=0;
	int TAIL_FRAME_len = 0 ;
	char FP_FRAME_HEAD[7] ={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01};
  
	char FP_CMD_len[2];
	char FP_checkSum[2];
	
	char arg_buf ;
	
	checkSum = 1;
	
	TAIL_FRAME_len = CMD_len + 2;
	
	FP_CMD_len[0] = TAIL_FRAME_len     & 0xFF;
	FP_CMD_len[1] = TAIL_FRAME_len>>8  & 0xFF;	
	
//------------------------------------
	for(i=0;i<7;i++){
		SERIAL_WRITE(FP_FRAME_HEAD[i]);
	}
	
	SERIAL_WRITE(FP_CMD_len[1]);
	SERIAL_WRITE(FP_CMD_len[0]);
	checkSum += TAIL_FRAME_len ;
	
	va_start(CMD_list, CMD_len);
	
  
   for (i = 0; i < CMD_len; i++) {
		  arg_buf = va_arg(CMD_list, char);
		  SERIAL_WRITE(arg_buf);
      checkSum += arg_buf;
   }
	 
   va_end(CMD_list);
	
	 FP_checkSum[0] = checkSum    & 0xFF;
	 FP_checkSum[1] = checkSum>>8 & 0xFF;
	 SERIAL_WRITE(FP_checkSum[1]);
	 SERIAL_WRITE(FP_checkSum[0]);
	 
}

void FP_CLEAR_REPLY(){
   int i;
	SERIAL_AVAILABLE = 0;
	 for(i=0;i<20;i++){
		 FP_REPLY[i] = 0;
	 }
}

void PF_RESPONSE(){
	int pipe;
	pipe = 0;
	if(SERIAL_AVAILABLE>0){
		while(SERIAL_AVAILABLE>0){
			FP_REPLY[pipe] = SERIAL_READ();
			pipe++;
			delay(5);
		}
	}
}

void FP_GenImg(){
	FP_CLEAR_REPLY();
	
	do{
	FP_COMMEND(1,1);
	while(SERIAL_AVAILABLE==0);
  PF_RESPONSE();
	}while(FP_REPLY[9]==0x02);
	
}

void FP_Img2Tz(){
	FP_CLEAR_REPLY();
	
	FP_COMMEND(2,2,1);
	while(SERIAL_AVAILABLE==0);
  PF_RESPONSE();
}

//x1b\x01\x00\x00\x01\x01\

void FP_HiSpeedSearch(){
	FP_CLEAR_REPLY();
	              
	FP_COMMEND(6,0x1b,0x01,0x00,0x00,0x01,0x01);
	while(SERIAL_AVAILABLE==0);
  PF_RESPONSE();
}

char FP_SREARCH(){
  LCD_LOC(1,1);
	LCD_PRINT("FINGER SCAN     ");
	delay(1000);
	FP_GenImg();
	delay(100);
	FP_Img2Tz();
	delay(100);
	FP_HiSpeedSearch();
  delay(100);
	if(FP_REPLY[9]==0x00){
		return FP_REPLY[11];
	} 
		return 0xAA;
		
}
