/*******************************************************************************
*                 
*                 		       ���пƼ�
--------------------------------------------------------------------------------
* ʵ �� ��		 : 18B20�¶���ʾ����
* ʵ��˵��       : LCD1602��ʾ�¶�ֵ��
* ���ӷ�ʽ       : ������ͼ
* ע    ��		 : 
*******************************************************************************/

#include<reg51.h>
#include"lcd.h"
#include"temp.h"
void LcdDisplay(int);
#define uchar unsigned char
#define uint unsigned int

typedef unsigned char  U8;       /* defined for unsigned 8-bits integer variable 	  �޷���8λ���ͱ���  */
typedef signed   char  S8;       /* defined for signed 8-bits integer variable		  �з���8λ���ͱ���  */
typedef unsigned int   U16;      /* defined for unsigned 16-bits integer variable 	  �޷���16λ���ͱ��� */
typedef signed   int   S16;      /* defined for signed 16-bits integer variable 	  �з���16λ���ͱ��� */
typedef unsigned long  U32;      /* defined for unsigned 32-bits integer variable 	  �޷���32λ���ͱ��� */
typedef signed   long  S32;      /* defined for signed 32-bits integer variable 	  �з���32λ���ͱ��� */
typedef float          F32;      /* single precision floating point variable (32bits) �����ȸ�������32λ���ȣ� */
typedef double         F64;      /* double precision floating point variable (64bits) ˫���ȸ�������64λ���ȣ� */

#define   Data_0_time    4
sbit  test=P1^0;
sbit  P2_0  = P2^0 ;
U8  U8FLAG,k;
U8  U8count,U8temp;
U8  U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;
U8  U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;
U8  U8comdata;
U8  outdata[5];  //���巢�͵��ֽ���	   
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
	   	//��ʱ������forѭ��		  
	   	 if(U8FLAG==1)break;
	   	//�ж�����λ��0����1	 
	   	   
		// ����ߵ�ƽ�߹�Ԥ��0�ߵ�ƽֵ������λΪ 1 
	   	 
		   U8comdata<<=1;
	   	   U8comdata|=U8temp;        //0
	     }//rof
}

	//--------------------------------
	//-----ʪ�ȶ�ȡ�ӳ��� ------------
	//--------------------------------
	//----���±�����Ϊȫ�ֱ���--------
	//----�¶ȸ�8λ== U8T_data_H------
	//----�¶ȵ�8λ== U8T_data_L------
	//----ʪ�ȸ�8λ== U8RH_data_H-----
	//----ʪ�ȵ�8λ== U8RH_data_L-----
	//----У�� 8λ == U8checkdata-----
	//----��������ӳ�������----------
	//---- Delay();, Delay_10us();,COM(); 
	//--------------------------------
void RH(void)
{
	  //��������18ms 
       P2_0=0;
	   delay(180);
	   P2_0=1;
	 //������������������ ������ʱ20us
	   Delay_10us();
	   Delay_10us();
	   Delay_10us();
	   Delay_10us();
	 //������Ϊ���� �жϴӻ���Ӧ�ź� 
	   P2_0=1;
	 //�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������	  
	   if(!P2_0)		 //T !	  
	   {
	   U8FLAG=2;
	 //�жϴӻ��Ƿ񷢳� 80us �ĵ͵�ƽ��Ӧ�ź��Ƿ����	 
	   while((!P2_0)&&U8FLAG++);
	   U8FLAG=2;
	 //�жϴӻ��Ƿ񷢳� 80us �ĸߵ�ƽ���緢����������ݽ���״̬
	   while((P2_0)&&U8FLAG++);
	 //���ݽ���״̬		 
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
	 //����У�� 
	 
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
* ������         : main
* ��������		   : ������
* ����           : ��
* ���         	 : ��
*******************************************************************************/

void main()
{
uint temp1,TP1;
	TMOD = 0x20;	  //��ʱ��T1ʹ�ù�����ʽ2
	TH1 = 253;        // ���ó�ֵ
	TL1 = 253;
	TR1 = 1;          // ��ʼ��ʱ
	EA=1;
	LcdInit();			 //��ʼ��LCD1602
	LcdWriteCom(0x88);	//д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('C'); 
	while(1)
	{ 
		test=0;
		delay(500);
		test=1;
		LcdDisplay(Ds18b20ReadTemp());
		delay(100);
		RH();
	   //������ʾ���� 
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
		LcdWriteCom(0xc0);		  //д��ַ C0��ʾ��ʼ��ַ
		LcdWriteData('S');  
			LcdWriteCom(0xc1);		  //д��ַ c1��ʾ��ʼ��ַ
		LcdWriteData('D');  
			LcdWriteCom(0xc2);	  //д��ַ c2��ʾ��ʼ��ַ
		LcdWriteData(':');  
			LcdWriteCom(0xc3);		  //д��ַ c0��ʾ��ʼ��ַ
		LcdWriteData('0'+str[0]); //ʮλ 
			LcdWriteCom(0xc4);		  //д��ַ 80��ʾ��ʼ��ַ
		LcdWriteData('0'+str[1]); //��λ 
			LcdWriteCom(0xc5);		  //д��ַ 80��ʾ��ʼ��ַ
		LcdWriteData('.'); // 
			LcdWriteCom(0xc6);		  //д��ַ 80��ʾ��ʼ��ַ
		LcdWriteData('0'+str[2]); //С�����һλ 
	  		LcdWriteCom(0xc7);		  //д��ַ 80��ʾ��ʼ��ַ
		LcdWriteData('R'); //��λ 
			LcdWriteCom(0xc8);		  //д��ַ 80��ʾ��ʼ��ַ
		LcdWriteData('H'); //��λ 			   
	}
}

/*******************************************************************************
* ������         : LcdDisplay()
* ��������		   : LCD��ʾ��ȡ�����¶�
* ����           : v
* ���         	 : ��
*******************************************************************************/

void LcdDisplay(int temp) 	 //lcd��ʾ
{
    
  	unsigned char datas[] = {0, 0, 0, 0, 0}; //��������
	float tp;  
	if(temp< 0)				//���¶�ֵΪ����
  	{
	  	LcdWriteCom(0x80);		//д��ַ 80��ʾ��ʼ��ַ
	    LcdWriteData('-');  		//��ʾ��
		//��Ϊ��ȡ���¶���ʵ���¶ȵĲ��룬���Լ�1����ȡ�����ԭ��
		temp=temp-1;
		temp=~temp;
		tp=temp;
		temp=tp*0.0625*100+0.5;	
		//������С�����*100��+0.5���������룬��ΪC���Ը�����ת��Ϊ���͵�ʱ���С����
		//��������Զ�ȥ���������Ƿ����0.5����+0.5֮�����0.5�ľ��ǽ�1�ˣ�С��0.5�ľ�
		//�����0.5��������С������档
 
  	}
 	else
  	{			
	  	LcdWriteCom(0x80);		//д��ַ 80��ʾ��ʼ��ַ
	    LcdWriteData('+'); 		//��ʾ��
		tp=temp;//��Ϊ���ݴ�����С�������Խ��¶ȸ���һ�������ͱ���
		//����¶���������ô����ô������ԭ����ǲ���������
		temp=tp*0.0625*100+0.5;	
		//������С�����*100��+0.5���������룬��ΪC���Ը�����ת��Ϊ���͵�ʱ���С����
		//��������Զ�ȥ���������Ƿ����0.5����+0.5֮�����0.5�ľ��ǽ�1�ˣ�С��0.5�ľ�
		//�����0.5��������С������档
	}
	datas[0] = temp / 10000;
	datas[1] = temp % 10000 / 1000;
	datas[2] = temp % 1000 / 100;
	datas[3] = temp % 100 / 10;
	datas[4] = temp % 10;
 
	LcdWriteCom(0x82);		  //д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('0'+datas[0]); //��λ 

	
	LcdWriteCom(0x83);		 //д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('0'+datas[1]); //ʮλ

	LcdWriteCom(0x84);		//д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('0'+datas[2]); //��λ 

	LcdWriteCom(0x85);		//д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('.'); 		//��ʾ ��.��

	LcdWriteCom(0x86);		 //д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('0'+datas[3]); //��ʾС����  

	LcdWriteCom(0x87);		 //д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('0'+datas[4]); //��ʾС����  
}

