void GSM_BEGIN(){
	SERIAL_PRINT("ATE0");
    SERIAL_WRITE(CARRIAGE_RETRUN);
    delay(100);
    SERIAL_AVAILABLE = 0;
}

char GSM_CONNECTION(){
	SERIAL_PRINT("AT");
    SERIAL_WRITE(CARRIAGE_RETRUN);
    delay(100);
    if(SERIAL_REC[2]=='O' && SERIAL_REC[3]=='K'){
       SERIAL_AVAILABLE = 0;
       return 1;
    }else{
       SERIAL_AVAILABLE = 0;
       return 0;
    } 
}

void GSM_MAKE_CALL(char *mobileNo){
    SERIAL_PRINT("ATD ");
    SERIAL_PRINT(mobileNo);
    SERIAL_PRINT(";");
    SERIAL_WRITE(CARRIAGE_RETRUN);
    delay(100);
    SERIAL_AVAILABLE = 0;
}

void GSM_DETELE_ALL_SMS(){
    SERIAL_PRINT("AT+CMGDA=\"DEL ALL\"");
    SERIAL_WRITE(CARRIAGE_RETRUN);
    delay(1000);
    SERIAL_AVAILABLE = 0;
}

void GSM_SEND_SMS(char *mobileNo,char *massage){
    SERIAL_PRINT("AT+CMGF=1");
    SERIAL_WRITE(CARRIAGE_RETRUN);
    delay(100);
    SERIAL_PRINT("AT+CMGS=\"");
    SERIAL_PRINT(mobileNo);
    SERIAL_PRINT("\"");
    SERIAL_WRITE(CARRIAGE_RETRUN);
    delay(100);
    SERIAL_PRINT(massage);
    SERIAL_WRITE(CARRIAGE_RETRUN);
    SERIAL_WRITE(CTRL_Z);
    delay(500);
    SERIAL_AVAILABLE = 0;
}
