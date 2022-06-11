#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
/*菜单结构定义*/
struct MenuItem
{
	short MenuCount;//结构体数组的元素个数
	u8 *DisplayString;//当前LCD显示的信息
	int MenuClass;//结构体第几层的第几个项目
	void(*Subs)();//执行的函数的指针. 
	struct MenuItem *ChildrenMenus;//指向子节点的指针
	struct MenuItem *ParentMenus;//指向父节点的指针 
};

//函数声明
void Mp3Player(void);        //音乐播放器
void Timeshow(void);        //时间
void Calendar(void);       //日历
void Drawing_Ellipses(void);              //矢量画椭图
void Snake(void);               //贪吃蛇
void jingziChess(void);          //井字棋
void display(struct MenuItem * MenuPoint,short selectItem);  //菜单显示的函数

//结构体声明
//这是主菜单
struct MenuItem MainMenu[4] = {
		{ 4,"T&C一一一一一",1,NULL,NULL,NULL },
    { 4,"Games一一一一",2,NULL,NULL,NULL },
    { 4,"Drawwing一一一",3,(*Drawing_Ellipses),NULL,NULL },
		{ 4,"MP3player一一一",4,(*Mp3Player),NULL,NULL }
};
//这是T&C页面的菜单
struct MenuItem Setmenu1[2]={
		{ 2,"Time一一一一一一",1,(*Timeshow),NULL,MainMenu },
		{ 2,"Calendar一一一一",2,(*Calendar),NULL,MainMenu }
};
//这是游戏页面菜单
struct MenuItem Setmenu2[3] = {
    { 2,"Snake一一一一一",1,(*Snake),NULL,MainMenu },
    { 2,"jinziCHESS一一",2,(*jingziChess),NULL,MainMenu } 
};
//声明子指针
struct MenuItem* MenuPoint = MainMenu;
//定义一个用于换行的变量
short selectItem;
void Mp3Player(void)                   //音乐播放器
{
	
}
void Timeshow(void)                    //时间
{
	
}
void Calendar(void)                    //日历
{
	
}
void Drawing_Ellipses(void)            //矢量画椭图
{
	
}
void Snake(void)                       //贪吃蛇
{
	
}
void jingziChess(void)                 //井字棋
{
  
}

void display(struct MenuItem * MenuPoint,short selectItem)     //菜单显示函数
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
	delay_init();	    	 //延时函数初始化	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	POINT_COLOR=BLACK;//画笔颜色
	 	MainMenu[0].ChildrenMenus = Setmenu1;   //声明子级菜单
		MainMenu[1].ChildrenMenus = Setmenu2; 	
    selectItem =1;         //赋初值，菜单框从1开始
  display(MenuPoint,selectItem);    //从主菜单第一行开始显示
	uart_init(115200);	 	//串口初始化为115200
 	LED_Init();		  			//初始化与LED连接的硬件接口
	KEY_Init();					//初始化按键
	LCD_Init();			   		//初始化LCD      
  while(1)
    {
       key=KEY_Scan(0);		//得到键值
       delay_ms(10);
							 //LCD_Clear(WHITE);   //清屏
		  //按键来切换菜单 
			switch(key)
       {
				 
				 //下
				 case KEY0_PRES:{
				 LCD_Clear(WHITE);   //清屏
         if(selectItem == MenuPoint->MenuCount) selectItem = 1;
         else selectItem++;
				  display(MenuPoint, selectItem);
          key=0;
        };
				 break;
				
				 //确认
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
				
				 //返回
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
 

