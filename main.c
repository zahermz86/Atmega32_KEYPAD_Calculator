#include "STD_TYPES.h"
#include <util/delay.h>
#include "PORT_interface.h"
#include "CHAR_LCD_interface.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "KEYPAD_interface.h"


void main(void)

{

    PORT_voidInt();

	CHAR_LCD_viodInit();
	uint8 Local_Reading;
	static uint8 NUM[16]={0};
	static uint32 NUM1=0,NUM2=0;
	uint16 Div_Remainder;
	uint32 Local_Final_Value;
	uint8 Sum_Op_Counter=0;
	uint8 Sub_Op_Counter=0;
	uint8 Mult_Op_Counter=0;
	uint8 Div_Op_Counter=0;
    uint8 PressedNum1_Count=0;
	uint8 PressedNum2_Count=0;
	while(1)
	{
		Local_Reading=KEYPAD_u8GetPressedKey();

		if(Local_Reading != 0xff && Local_Reading<=9)
		{
			if(Sum_Op_Counter==0 && Sub_Op_Counter==0 && Mult_Op_Counter==0 && Div_Op_Counter==0)
			{_delay_ms(200);
			 NUM[PressedNum1_Count]=Local_Reading;
			 CHAR_LCD_viodSendData(Local_Reading+'0');
			 PressedNum1_Count=PressedNum1_Count+1;}


		    if(Sum_Op_Counter>0)
			{_delay_ms(200);
		    NUM[PressedNum2_Count+5]=Local_Reading;
			CHAR_LCD_viodSendData(Local_Reading+'0');
			PressedNum2_Count=PressedNum2_Count+1;}

		    if(Sub_Op_Counter>0)
		    {_delay_ms(200);
		    NUM[PressedNum2_Count+5]=Local_Reading;
		    CHAR_LCD_viodSendData(Local_Reading+'0');
		    PressedNum2_Count=PressedNum2_Count+1;}

		    if(Mult_Op_Counter>0)
		    {_delay_ms(200);
		    NUM[PressedNum2_Count+5]=Local_Reading;
		    CHAR_LCD_viodSendData(Local_Reading+'0');
		    PressedNum2_Count=PressedNum2_Count+1;}

		    if(Div_Op_Counter>0)
		    {_delay_ms(200);
		    NUM[PressedNum2_Count+5]=Local_Reading;
		    CHAR_LCD_viodSendData(Local_Reading+'0');
		    PressedNum2_Count=PressedNum2_Count+1;}


			while( PressedNum1_Count==6 )
		      {   CHAR_LCD_viodGoToXY(7,1);
		      CHAR_LCD_viodSendString("Max 5 Num");
		      PressedNum1_Count--;
		      _delay_ms(1000);
		      CHAR_LCD_viodGoToXY(5,0);
		      CHAR_LCD_viodSendData(' ');
		      for(int i=7;i<16;i++)
		      {_delay_ms(100);
		    	  CHAR_LCD_viodGoToXY(i,1);
		      CHAR_LCD_viodSendData(' ');}}

			while(PressedNum2_Count==6 )
			 {   CHAR_LCD_viodGoToXY(7,1);
			     CHAR_LCD_viodSendString("Max 5 Num");
				PressedNum2_Count--;
				_delay_ms(1000);
				CHAR_LCD_viodGoToXY((PressedNum1_Count+6),0);
			    CHAR_LCD_viodSendData(' ');
			 for(int i=7;i<16;i++)
			 {CHAR_LCD_viodGoToXY(i,1);
			 CHAR_LCD_viodSendData(' ');}}


		}
        if(Local_Reading != 0xff && Local_Reading=='=')
      {_delay_ms(200);
        	CHAR_LCD_viodSendData('=');
        if(PressedNum1_Count==1)
        	 NUM1=NUM[0];
         if(PressedNum1_Count==2)
        	 NUM1=NUM[0]*10+NUM[1];
         if(PressedNum1_Count==3)
             NUM1=(NUM[0]*10+NUM[1])*10+NUM[2];
         if(PressedNum1_Count==4)
             NUM1=((NUM[0]*10+NUM[1])*10+NUM[2])*10+NUM[3];
         if(PressedNum1_Count==5)
             NUM1=(((NUM[0]*10+NUM[1])*10+NUM[2])*10+NUM[3])*10+NUM[4];




        	 if(PressedNum2_Count==1 && (Sum_Op_Counter>0||Sub_Op_Counter>0||Mult_Op_Counter>0||Div_Op_Counter>0))
        		 NUM2=NUM[5];
        	 if(PressedNum2_Count==2 && (Sum_Op_Counter>0||Sub_Op_Counter>0||Mult_Op_Counter>0||Div_Op_Counter>0))
        		 NUM2=NUM[5]*10+NUM[6];
        	 if(PressedNum2_Count==3 && (Sum_Op_Counter>0||Sub_Op_Counter>0||Mult_Op_Counter>0||Div_Op_Counter>0))
        		 NUM2=(NUM[5]*10+NUM[6])*10+NUM[7];
        	 if(PressedNum2_Count==4 && (Sum_Op_Counter>0||Sub_Op_Counter>0||Mult_Op_Counter>0||Div_Op_Counter>0))
        		 NUM2=((NUM[5]*10+NUM[6])*10+NUM[7])*10+NUM[8];
        	 if(PressedNum2_Count==5 && (Sum_Op_Counter>0||Sub_Op_Counter>0||Mult_Op_Counter>0||Div_Op_Counter>0))
        		 NUM2=(((NUM[5]*10+NUM[6])*10+NUM[7])*10+NUM[8])*10+NUM[9];


         if(Sum_Op_Counter==0)
         { CHAR_LCD_viodGoToXY(0,1);
           CHAR_LCD_viodSendNumber(NUM1);}

         if(Sum_Op_Counter>0)
           { CHAR_LCD_viodGoToXY(0,1);
             CHAR_LCD_viodSendNumber(NUM1+NUM2);}

         if(Sub_Op_Counter>0)
         {
        	 if(NUM2>NUM1)
        	 {
        		 CHAR_LCD_viodGoToXY(0,1);
        		 CHAR_LCD_viodSendData('-');
        		 CHAR_LCD_viodGoToXY(1,1);
        		 CHAR_LCD_viodSendNumber((NUM2-NUM1));
        	 }
        	 else
        	 {
        		 CHAR_LCD_viodGoToXY(0,1);
        		 CHAR_LCD_viodSendNumber((NUM1-NUM2));
        	 }
         }

         if(Mult_Op_Counter>0)
         { CHAR_LCD_viodGoToXY(0,1);
         CHAR_LCD_viodSendNumber(NUM1*NUM2);}

         if(Div_Op_Counter>0)
         {

        	 if(NUM2>NUM1)
        	 {
        		 CHAR_LCD_viodGoToXY(0,1);
        		 CHAR_LCD_viodSendData('0');
        		 CHAR_LCD_viodSendData('.');
        		 CHAR_LCD_viodGoToXY(2,1);
        		 CHAR_LCD_viodSendNumber(((NUM1*10000)/NUM2));
        	 }

        	 if(NUM1>=NUM2 && NUM2 !=0)

        	 {Div_Remainder=((NUM1*1000)/NUM2)%1000;
        	 CHAR_LCD_viodGoToXY(0,1);
        	 CHAR_LCD_viodSendNumber((NUM1/NUM2));
        	 CHAR_LCD_viodSendData('.');
        	 CHAR_LCD_viodSendNumber(Div_Remainder);}

        	 else
        	    { if(NUM2==0)
        		 {
        	    	CHAR_LCD_viodGoToXY(0,1);
        	     CHAR_LCD_viodSendString("Invalid Prs Rst");
        	     }
        	    }

             }
      }



         if(Local_Reading=='+')
         {_delay_ms(200);
        	 CHAR_LCD_viodSendData('+');
        	 Sum_Op_Counter=Sum_Op_Counter+1;

         }

         if(Local_Reading=='-')
         {_delay_ms(200);
        	 CHAR_LCD_viodSendData('-');
        	 Sub_Op_Counter=Sub_Op_Counter+1;

         }

         if(Local_Reading=='x')
         {_delay_ms(200);
         CHAR_LCD_viodSendData('x');
         Mult_Op_Counter=Mult_Op_Counter+1;

         }
         if(Local_Reading=='/')
         {_delay_ms(200);
         CHAR_LCD_viodSendData('/');
         Div_Op_Counter=Div_Op_Counter+1;

         }


            if(Local_Reading != 0xff && Local_Reading=='c')
            {CHAR_LCD_voidClr();
             Sum_Op_Counter=0;
             Sub_Op_Counter=0;
             Div_Op_Counter=0;
             Mult_Op_Counter=0;
             PressedNum1_Count=0;
             PressedNum2_Count=0;}
       }

}