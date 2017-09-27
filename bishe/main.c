/*******************************************************************************
*                 
*                 		       ∆’÷–ø∆ºº
--------------------------------------------------------------------------------
*  µ —È √˚		 : 18B20Œ¬∂»œ‘ æ ‘—È
*  µ—ÈÀµ√˜       : LCD1602œ‘ æŒ¬∂»÷µ°£
* ¡¨Ω”∑Ω Ω       : º˚¡¨Ω”Õº
* ◊¢    “‚		 : 
*******************************************************************************/

#include<reg51.h>
#include"lcd.h"
#include"temp.h"
void LcdDisplay(int);
#define uchar unsigned char
#define uint unsigned int

typedef unsigned char  U8;       /* defined for unsigned 8-bits integer variable 	  Œﬁ∑˚∫≈8Œª’˚–Õ±‰¡ø  */
typedef signed   char  S8;       /* defined for signed 8-bits integer variable		  ”–∑˚∫≈8Œª’˚–Õ±‰¡ø  */
typedef unsigned int   U16;      /* defined for unsigned 16-bits integer variable 	  Œﬁ∑˚∫≈16Œª’˚–Õ±‰¡ø */
typedef signed   int   S16;      /* defined for signed 16-bits integer variable 	  ”–∑˚∫≈16Œª’˚–Õ±‰¡ø */
typedef unsigned long  U32;      /* defined for unsigned 32-bits integer variable 	  Œﬁ∑˚∫≈32Œª’˚–Õ±‰¡ø */
typedef signed   long  S32;      /* defined for signed 32-bits integer variable 	  ”–∑˚∫≈32Œª’˚–Õ±‰¡ø */
typedef float          F32;      /* single precision floating point variable (32bits) µ•æ´∂»∏°µ„ ˝£®32Œª≥§∂»£© */
typedef double         F64;      /* double precision floating point variable (64bits) À´æ´∂»∏°µ„ ˝£®64Œª≥§∂»£© */

#define   Data_0_time    4
sbit  test=P1^0;
sbit  P2_0  = P2^0 ;
U8  U8FLAG,k;
U8  U8count,U8temp;
U8  U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;
U8  U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;
U8  U8comdata;
U8  outdata[5];  //∂®“Â∑¢ÀÕµƒ◊÷Ω⁄ ˝	   
U8  indata[5];
U8  count, count_r=0;
U8  str[5]={"RS232"};
U16 U16temp1,U16temp2;
void delay(U16 j)
{      U8 i;
	    for(;j>0;j--)
	  { 	
		for(i=0;i<27;i++);

	  }
}
void  Delay_10us(void)
{
        U8 i;
        i--;
        i--;
        i--;
        i--;
        i--;
        i--;
}
	
void  COM(void)
{
     
	        U8 i;
          
       for(i=0;i<8;i++)	   
	    {
		
	   	    U8FLAG=2;	
	   	while((!P2_0)&&U8FLAG++);
			Delay_10us();
		    Delay_10us();
			Delay_10us();
	  		U8temp=0;
	     if(P2_0)U8temp=1;
		    U8FLAG=2;
		 while((P2_0)&&U8FLAG++);
	   	//≥¨ ±‘ÚÃ¯≥ˆfor—≠ª∑		  
	   	 if(U8FLAG==1)break;
	   	//≈–∂œ ˝æ›Œª «0ªπ «1	 
	   	   
		// »Áπ˚∏ﬂµÁ∆Ω∏ﬂπ˝‘§∂®0∏ﬂµÁ∆Ω÷µ‘Ú ˝æ›ŒªŒ™ 1 
	   	 
		   U8comdata<<=1;
	   	   U8comdata|=U8temp;        //0
	     }//rof
}

	//--------------------------------
	//----- ™∂»∂¡»°◊”≥Ã–Ú ------------
	//--------------------------------
	//----“‘œ¬±‰¡øæ˘Œ™»´æ÷±‰¡ø--------
	//----Œ¬∂»∏ﬂ8Œª== U8T_data_H------
	//----Œ¬∂»µÕ8Œª== U8T_data_L------
	//---- ™∂»∏ﬂ8Œª== U8RH_data_H-----
	//---- ™∂»µÕ8Œª== U8RH_data_L-----
	//----–£—È 8Œª == U8checkdata-----
	//----µ˜”√œ‡πÿ◊”≥Ã–Ú»Áœ¬----------
	//---- Delay();, Delay_10us();,COM(); 
	//--------------------------------
void RH(void)
{
	  //÷˜ª˙¿≠µÕ18ms 
       P2_0=0;
	   delay(180);
	   P2_0=1;
	 //◊‹œﬂ”……œ¿≠µÁ◊Ë¿≠∏ﬂ ÷˜ª˙—” ±20us
	   Delay_10us();
	   Delay_10us();
	   Delay_10us();
	   Delay_10us();
	 //÷˜ª˙…ËŒ™ ‰»Î ≈–∂œ¥”ª˙œÏ”¶–≈∫≈ 
	   P2_0=1;
	 //≈–∂œ¥”ª˙ «∑Ò”–µÕµÁ∆ΩœÏ”¶–≈∫≈ »Á≤ªœÏ”¶‘ÚÃ¯≥ˆ£¨œÏ”¶‘ÚœÚœ¬‘À––	  
	   if(!P2_0)		 //T !	  
	   {
	   U8FLAG=2;
	 //≈–∂œ¥”ª˙ «∑Ò∑¢≥ˆ 80us µƒµÕµÁ∆ΩœÏ”¶–≈∫≈ «∑ÒΩ· ¯	 
	   while((!P2_0)&&U8FLAG++);
	   U8FLAG=2;
	 //≈–∂œ¥”ª˙ «∑Ò∑¢≥ˆ 80us µƒ∏ﬂµÁ∆Ω£¨»Á∑¢≥ˆ‘ÚΩ¯»Î ˝æ›Ω” ’◊¥Ã¨
	   while((P2_0)&&U8FLAG++);
	 // ˝æ›Ω” ’◊¥Ã¨		 
	   COM();
	   U8RH_data_H_temp=U8comdata;
	   COM();
	   U8RH_data_L_temp=U8comdata;
	   COM();
	   U8T_data_H_temp=U8comdata;
	   COM();
	   U8T_data_L_temp=U8comdata;
	   COM();
	   U8checkdata_temp=U8comdata;
	   P2_0=1;
	 // ˝æ›–£—È 
	 
	   U8temp=(U8T_data_H_temp+U8T_data_L_temp+U8RH_data_H_temp+U8RH_data_L_temp);
	   if(U8temp==U8checkdata_temp)
	   {
	   	  U8RH_data_H=U8RH_data_H_temp;
	   	  U8RH_data_L=U8RH_data_L_temp;
		  U8T_data_H=U8T_data_H_temp;
	   	  U8T_data_L=U8T_data_L_temp;
	   	  U8checkdata=U8checkdata_temp;
	   }//fi
	   }//fi

}

/*******************************************************************************
* ∫Ø ˝√˚         : main
* ∫Ø ˝π¶ƒ‹		   : ÷˜∫Ø ˝
*  ‰»Î           : Œﬁ
*  ‰≥ˆ         	 : Œﬁ
*******************************************************************************/

void main()
{
uint temp1,TP1;
	TMOD = 0x20;	  //∂® ±∆˜T1 π”√π§◊˜∑Ω Ω2
	TH1 = 253;        // …Ë÷√≥ı÷µ
	TL1 = 253;
	TR1 = 1;          // ø™ ºº∆ ±
	EA=1;
	LcdInit();			 //≥ı ºªØLCD1602
	LcdWriteCom(0x88);	//–¥µÿ÷∑ 80±Ì æ≥ı ºµÿ÷∑
	LcdWriteData('C'); 
	while(1)
	{ 
		test=0;
		delay(500);
		test=1;
		LcdDisplay(Ds18b20ReadTemp());
		delay(100);
		RH();
	   //¥Æø⁄œ‘ æ≥Ã–Ú 
	   //--------------------------

	  // temp1=(U8RH_data_H<<8)+U8RH_data_L;	//
	   str[1]=U8RH_data_L;
	   temp1=(U8T_data_H<<8)|U8T_data_L;
		TP1=temp1;
	   temp1=TP1*0.0625*100+0.5;
//	   str[3]=U8T_data_L;
	   str[0] = temp1 / 10000;
	   str[1] = temp1 % 10000 / 1000;
	   str[2] = temp1 % 1000 / 100;
       str[3] = temp1 % 100 / 10; 
	   //str[4]=U8checkdata;
		LcdWriteCom(0xc0);		  //–¥µÿ÷∑ C0±Ì æ≥ı ºµÿ÷∑
		LcdWriteData('S');  
			LcdWriteCom(0xc1);		  //–¥µÿ÷∑ c1±Ì æ≥ı ºµÿ÷∑
		LcdWriteData('D');  
			LcdWriteCom(0xc2);	  //–¥µÿ÷∑ c2±Ì æ≥ı ºµÿ÷∑
		LcdWriteData(':');  
			LcdWriteCom(0xc3);		  //–¥µÿ÷∑ c0±Ì æ≥ı ºµÿ÷∑
		LcdWriteData('0'+str[0]); // ÆŒª 
			LcdWriteCom(0xc4);		  //–¥µÿ÷∑ 80±Ì æ≥ı ºµÿ÷∑
		LcdWriteData('0'+str[1]); //∏ˆŒª 
			LcdWriteCom(0xc5);		  //–¥µÿ÷∑ 80±Ì æ≥ı ºµÿ÷∑
		LcdWriteData('.'); // 
			LcdWriteCom(0xc6);		  //–¥µÿ÷∑ 80±Ì æ≥ı ºµÿ÷∑
		LcdWriteData('0'+str[2]); //–° ˝µ„∫Û“ªŒª 
	  		LcdWriteCom(0xc7);		  //–¥µÿ÷∑ 80±Ì æ≥ı ºµÿ÷∑
		LcdWriteData('R'); //∞ŸŒª 
			LcdWriteCom(0xc8);		  //–¥µÿ÷∑ 80±Ì æ≥ı ºµÿ÷∑
		LcdWriteData('H'); //∞ŸŒª 			   
	}
}

/*******************************************************************************
* ∫Ø ˝√˚         : LcdDisplay()
* ∫Ø ˝π¶ƒ‹		   : LCDœ‘ æ∂¡»°µΩµƒŒ¬∂»
*  ‰»Î           : v
*  ‰≥ˆ         	 : Œﬁ
*******************************************************************************/

void LcdDisplay(int temp) 	 //lcdœ‘ æ
{
    
  	unsigned char datas[] = {0, 0, 0, 0, 0}; //∂®“Â ˝◊È
	float tp;  
	if(temp< 0)				//µ±Œ¬∂»÷µŒ™∏∫ ˝
  	{
	  	LcdWriteCom(0x80);		//–¥µÿ÷∑ 80±Ì æ≥ı ºµÿ÷∑
	    LcdWriteData('-');  		//œ‘ æ∏∫
		//“ÚŒ™∂¡»°µƒŒ¬∂» « µº Œ¬∂»µƒ≤π¬Î£¨À˘“‘ºı1£¨‘Ÿ»°∑¥«Û≥ˆ‘≠¬Î
		temp=temp-1;
		temp=~temp;
		tp=temp;
		temp=tp*0.0625*100+0.5;	
		//¡Ù¡Ω∏ˆ–° ˝µ„æÕ*100£¨+0.5 «Àƒ…·ŒÂ»Î£¨“ÚŒ™C”Ô—‘∏°µ„ ˝◊™ªªŒ™’˚–Õµƒ ±∫Ú∞—–° ˝µ„
		//∫Û√Êµƒ ˝◊‘∂Ø»•µÙ£¨≤ªπ‹ «∑Ò¥Û”⁄0.5£¨∂¯+0.5÷Æ∫Û¥Û”⁄0.5µƒæÕ «Ω¯1¡À£¨–°”⁄0.5µƒæÕ
		//À„”…œ0.5£¨ªπ «‘⁄–° ˝µ„∫Û√Ê°£
 
  	}
 	else
  	{			
	  	LcdWriteCom(0x80);		//–¥µÿ÷∑ 80±Ì æ≥ı ºµÿ÷∑
	    LcdWriteData('+'); 		//œ‘ æ’˝
		tp=temp;//“ÚŒ™ ˝æ›¥¶¿Ì”––° ˝µ„À˘“‘Ω´Œ¬∂»∏≥∏¯“ª∏ˆ∏°µ„–Õ±‰¡ø
		//»Áπ˚Œ¬∂» «’˝µƒƒ«√¥£¨ƒ«√¥’˝ ˝µƒ‘≠¬ÎæÕ «≤π¬ÎÀ¸±æ…Ì
		temp=tp*0.0625*100+0.5;	
		//¡Ù¡Ω∏ˆ–° ˝µ„æÕ*100£¨+0.5 «Àƒ…·ŒÂ»Î£¨“ÚŒ™C”Ô—‘∏°µ„ ˝◊™ªªŒ™’˚–Õµƒ ±∫Ú∞—–° ˝µ„
		//∫Û√Êµƒ ˝◊‘∂Ø»•µÙ£¨≤ªπ‹ «∑Ò¥Û”⁄0.5£¨∂¯+0.5÷Æ∫Û¥Û”⁄0.5µƒæÕ «Ω¯1¡À£¨–°”⁄0.5µƒæÕ
		//À„º”…œ0.5£¨ªπ «‘⁄–° ˝µ„∫Û√Ê°£
	}
	datas[0] = temp / 10000;
	datas[1] = temp % 10000 / 1000;
	datas[2] = temp % 1000 / 100;
	datas[3] = temp % 100 / 10;
	datas[4] = temp % 10;
 
	LcdWriteCom(0x82);		  //–¥µÿ÷∑ 80±Ì æ≥ı ºµÿ÷∑
	LcdWriteData('0'+datas[0]); //∞ŸŒª 

	
	LcdWriteCom(0x83);		 //–¥µÿ÷∑ 80±Ì æ≥ı ºµÿ÷∑
	LcdWriteData('0'+datas[1]); // ÆŒª

	LcdWriteCom(0x84);		//–¥µÿ÷∑ 80±Ì æ≥ı ºµÿ÷∑
	LcdWriteData('0'+datas[2]); //∏ˆŒª 

	LcdWriteCom(0x85);		//–¥µÿ÷∑ 80±Ì æ≥ı ºµÿ÷∑
	LcdWriteData('.'); 		//œ‘ æ °Æ.°Ø

	LcdWriteCom(0x86);		 //–¥µÿ÷∑ 80±Ì æ≥ı ºµÿ÷∑
	LcdWriteData('0'+datas[3]); //œ‘ æ–° ˝µ„  

	LcdWriteCom(0x87);		 //–¥µÿ÷∑ 80±Ì æ≥ı ºµÿ÷∑
	LcdWriteData('0'+datas[4]); //œ‘ æ–° ˝µ„  
}

