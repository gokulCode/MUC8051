sbit MKP_R0 = P1^0;
sbit MKP_R1 = P1^1;
sbit MKP_R2 = P1^2;
sbit MKP_R3 = P1^3;

sbit MKP_C0 = P1^4;
sbit MKP_C1 = P1^5;
sbit MKP_C2 = P1^6;
sbit MKP_C3 = P1^7;

int Matrix_keyPad(){
	  
	int row,col,i;
	int isPressed=0;
	static int pressedButton=-1;
	char scanLine[4],writeLine[4];
   
	for(row=0;row<4;row++){
	  for(i=0;i<4;i++){             // Clear all
			writeLine[i]=1;
	  }
		writeLine[row]=0;
		
	    ///////////////////////
		MKP_C0 = writeLine[0];
		MKP_C1 = writeLine[1];
		MKP_C2 = writeLine[2];
		MKP_C3 = writeLine[3];
		///////////////////////
		scanLine[0] = MKP_R0; 
	    scanLine[1] = MKP_R1; 
	    scanLine[2] = MKP_R2; 
	    scanLine[3] = MKP_R3; 
		///////////////////////
					
		for(col=0;col<4;col++){
			if(scanLine[col]==0){
				isPressed=1;
				pressedButton=(col*4)+row;
				delay(100);     // debounce time
              }
        }
					
			delay(1);
	} 
			
      if (isPressed==1){
	     return pressedButton;
			    isPressed=0;
			}
			else{
			 return -1;
			}
		}
		