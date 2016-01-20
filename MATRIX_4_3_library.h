sbit MKP_R0 = P3^5;
sbit MKP_R1 = P3^4;
sbit MKP_R2 = P3^3;

sbit MKP_C0 = P3^6;
sbit MKP_C1 = P3^0;
sbit MKP_C2 = P3^1;
sbit MKP_C3 = P3^2;


char number2keyPad(int num){

	char sym;
	
    if((0<=num) && (num<=8)){
	      sym = num + 0x31;
	}
	else if(num == 9){
	      sym = '*';
	}
	else if(num == 10){
	      sym = '0';
	}
	else if(num == 11){
	      sym = '#';
	}
	else{
		    sym = num ;
	}
	
	return sym;
	
}

int Matrix_keyPad(){
	  
	int row,col,i;
	int isPressed=0;
	static int pressedButton=-1;
	char scanLine[4],writeLine[3];
   
    for(row=0;row<3;row++){
	   for(i=0;i<3;i++){             // Clear all
			writeLine[i]=1;
	    }
          writeLine[row]=0;
		/////////////////////////
		 MKP_R0 = writeLine[0];
		 MKP_R1 = writeLine[1];
		 MKP_R2 = writeLine[2];
	    /////////////////////////
		 scanLine[0] = MKP_C0; 
	     scanLine[1] = MKP_C1; 
	     scanLine[2] = MKP_C2; 
	     scanLine[3] = MKP_C3; 
		/////////////////////////
					
	    for(col=0;col<4;col++){
		   if(scanLine[col]==0){
			   isPressed=1;
			   pressedButton=(col*3)+row;
			   delay(100);     // debounce time
             }
          }
            delay(1);
		} 
			
    if (isPressed==1){
	     return pressedButton;
			    isPressed=0;
	}else{
		 return -1;
	}
}

char keyPad_4_3(){

   return number2keyPad(Matrix_keyPad());

}