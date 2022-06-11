#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
/*�˵��ṹ����*/
struct MenuItem
{
	short MenuCount;//�ṹ�������Ԫ�ظ���
	u8 *DisplayString;//��ǰLCD��ʾ����Ϣ
	int MenuClass;//�ṹ��ڼ���ĵڼ�����Ŀ
	void(*Subs)();//ִ�еĺ�����ָ��. 
	struct MenuItem *ChildrenMenus;//ָ���ӽڵ��ָ��
	struct MenuItem *ParentMenus;//ָ�򸸽ڵ��ָ�� 
};

//��������
void Mp3Player(void);        //���ֲ�����
void Timeshow(void);        //ʱ��
void Calendar(void);       //����
void Drawing_Ellipses(void);              //ʸ������ͼ
void Snake(void);               //̰����
void jingziChess(void);          //������
void display(struct MenuItem * MenuPoint,short selectItem);  //�˵���ʾ�ĺ���

//�ṹ������
//�������˵�
struct MenuItem MainMenu[4] = {
		{ 4,"T&Cһһһһһ",1,NULL,NULL,NULL },
    { 4,"Gamesһһһһ",2,NULL,NULL,NULL },
    { 4,"Drawwingһһһ",3,(*Drawing_Ellipses),NULL,NULL },
		{ 4,"MP3playerһһһ",4,(*Mp3Player),NULL,NULL }
};
//����T&Cҳ��Ĳ˵�
struct MenuItem Setmenu1[2]={
		{ 2,"Timeһһһһһһ",1,(*Timeshow),NULL,MainMenu },
		{ 2,"Calendarһһһһ",2,(*Calendar),NULL,MainMenu }
};
//������Ϸҳ��˵�
struct MenuItem Setmenu2[3] = {
    { 2,"Snakeһһһһһ",1,(*Snake),NULL,MainMenu },
    { 2,"jinziCHESSһһ",2,(*jingziChess),NULL,MainMenu } 
};
//������ָ��
struct MenuItem* MenuPoint = MainMenu;
//����һ�����ڻ��еı���
short selectItem;
void Mp3Player(void)                   //���ֲ�����
{
	
}
void Timeshow(void)                    //ʱ��
{
	
}
void Calendar(void)                    //����
{
	
}
void Drawing_Ellipses(void)            //ʸ������ͼ
{
	
}
void Snake(void)                       //̰����
{
	
}
void jingziChess(void)                 //������
{
  
}

void display(struct MenuItem * MenuPoint,short selectItem)     //�˵���ʾ����
{
       int i;
       int j;
       u16 x=30;
       u16 y=30;
        for ( i = 0; i < (selectItem-1); i++)
        {
            LCD_ShowString(x,y,200,16,16,MenuPoint[i].DisplayString);
            y+=30;
        }
        POINT_COLOR=BLACK;
        LCD_DrawRectangle(x-5,y-10,x+60,y+20);
        LCD_ShowString(x,y,200,16,16,MenuPoint[selectItem-1].DisplayString);
        y+=30;
        for ( j= selectItem; j < MenuPoint->MenuCount; j++)
        {
            LCD_ShowString(x,y,200,16,16,MenuPoint[j].DisplayString);
            y+=30;
				}
}


int main(void)
 {	 
  int key=0;
	delay_init();	    	 //��ʱ������ʼ��	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	POINT_COLOR=BLACK;//������ɫ
	 	MainMenu[0].ChildrenMenus = Setmenu1;   //�����Ӽ��˵�
		MainMenu[1].ChildrenMenus = Setmenu2; 	
    selectItem =1;         //����ֵ���˵����1��ʼ
  display(MenuPoint,selectItem);    //�����˵���һ�п�ʼ��ʾ
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();					//��ʼ������
	LCD_Init();			   		//��ʼ��LCD      
  while(1)
    {
       key=KEY_Scan(0);		//�õ���ֵ
       delay_ms(10);
							 //LCD_Clear(WHITE);   //����
		  //�������л��˵� 
			switch(key)
       {
				 
				 //��
				 case KEY0_PRES:{
				 LCD_Clear(WHITE);   //����
         if(selectItem == MenuPoint->MenuCount) selectItem = 1;
         else selectItem++;
				  display(MenuPoint, selectItem);
          key=0;
        };
				 break;
				
				 //ȷ��
				 case WKUP_PRES:{
            if (MenuPoint[selectItem - 1].ChildrenMenus != NULL)
                {
                     LCD_Clear(WHITE);
									   MenuPoint = MenuPoint[selectItem - 1].ChildrenMenus;
                     selectItem = 1;									
										 display(MenuPoint, selectItem);
								}
								else if (MenuPoint[selectItem - 1].Subs !=NULL )
							{
									(*MenuPoint[selectItem - 1].Subs)(MenuPoint);
							}	
          key=0;
        };
				 break;
				
				 //����
				case KEY1_PRES:{
						if (MenuPoint[selectItem - 1].ParentMenus != NULL)
                {
                     LCD_Clear(WHITE);
									   MenuPoint = MenuPoint[selectItem - 1].ParentMenus;
                     selectItem = 1;
										display(MenuPoint, selectItem);
								}
          key=0;
        };
				break; 
			}
		delay_ms(10);
		}
		    	 						    
}
 

