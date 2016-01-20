#include <REGX51.H>
#include <math.h>
#include <string.h>
#include "utility.h"
#include "LCD_library.h"

sbit LED  = P1^0;

void main(){
	
	
	LCD_BEGIN();
    
	LCD_LOC(1,1); LCD_PRINT("    PROJECT     ");
	LCD_LOC(2,1); LCD_PRINT("     TITLE      ");
	delay(1000);

	while(1){
		 
		
	}
}