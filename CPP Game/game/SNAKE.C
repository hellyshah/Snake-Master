#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>
#include<bios.h>
#include<stdio.h>
void main()
{
	void  *snake,*food;
	do{
	int  x=75,y=225,size,a=19712,m=30,n=225,c=300,d=225,b=0,s=0;
	char score[20],level[20],lvl;
	int gd=DETECT,gm,w,h;


	clrscr();

	initgraph(&gd,&gm,"c:\\tc\\bgi");

	setcolor(1);

	clearviewport();

	setcolor(15);
	bar(60,225,74,239);
       //	size=imagesize(60,225,74,239);
       //	snake=malloc(size);
	getimage(60,225,74,239,snake);
	putimage(45,225,snake,COPY_PUT);
	putimage(30,225,snake,COPY_PUT);
	circle(307,232,3);
	setfillstyle(LINE_FILL,5);//sets fill patterns and color
	floodfill(307,232,15);
       //	size=imagesize(300,225,314,239);
       //	food=malloc(size);
	getimage(300,225,314,239,food);
	setcolor(5);
	printf("  \t");
	outtextxy(0,3,"Score");
	outtextxy(520,3,"Level");

	rectangle(0,18,getmaxx(),getmaxy());
	setcolor(9);
	rectangle(3,21,getmaxx()-3,getmaxy()-3);
	outtextxy(238,3,"Ravi");
	outtextxy(307,3,"and");
	outtextxy(355,3,"jatin");
	getche();
	while(a!=283 && x>0 && x<625 && y>15 && y<465 && getpixel(x,y)!=15)   //determines boundaries
	{
		if(bioskey(1)!=0)
		a=bioskey(0);
		putimage(x,y,snake,COPY_PUT);
		if (s>=0 && s<25)
		{
			lvl='A';
			delay(300);
		}
		if (s>=25 && s<50)
		{
			lvl='B';
			delay(240);
		}
		if (s>=50 && s<70)
		{
			lvl='C';
			delay(170);
		}
		if (s>=70 && s<85)
		{
			lvl='D';
			delay(100);
		}
		if (s>=85 && s<=95)
		{
			lvl='E';
			delay(80);
		}
		if (s>95)
		{
			setcolor(5);
			rectangle(250,210,353,267);
			setcolor(9);
			rectangle(255,215,347,262);
			outtextxy(275,235,"YouWon");
		     //delay(1000);
			sound(100);
			delay(500);
			nosound();
			sound(200);
			delay(500);
			nosound();
			sound(300);
			delay(500);
			nosound();
		}
	       //-------------------------------------------------
		if (a==19712) //right
		 { 	if(b!=19200)
			{
				x=x+15;
				b=a;
			}
			else
			{
				x=x-15;
			}
		 }
		if(a==20480) //down
			if(b!=18432)
			{
				y=y+15;
				b=a;
			}
		else
			y=y-15;
		if(a==19200)   //left
			if(b!=19712)
			{
				x=x-15;
				b=a;
			}
		else
			x=x+15;
		if(a==18432) //up
			if(b!=20480)
			{
				y=y-15;
				b=a;
			}
		else
			y=y+15;

		//-----------------------------------------------
		if(getpixel(x+7,y+7)!=5)
		{
		       //	putimage(m,n,snake,XOR_PUT);
		       putimage(m,n,snake,NOT_PUT);
			if(getpixel(m+15,n)==15)
			{
				m=m+15;    }
			else
				if(getpixel(m-1,n)==15)
				 {
					m=m-15;}
				else
					if(getpixel(m,n+15)==15)
						n=n+15;
					else
						if(getpixel(m,n-1)==15)
							n=n-15;
		}
		else
		{
			sound(300);
			delay(1000/(s+1));
			nosound();
			s=s+5;

			printf("\b\b%d",s);

		      //	sprintf(ch,"%d",s);
		      //	putimage(50,0,snake,NOT_PUT);
			putimage(65,0,snake,NOT_PUT);
			//outtextxy(100,0,ch);
			sprintf(level,"%c",lvl);
			putimage(590,0,snake,NOT_PUT);
			putimage(600,0,snake,NOT_PUT);
			outtextxy(590,3,level);
			putimage(c,d,food,XOR_PUT);
			do
			{
				do
				{
					c=random(600);
				}while(c%15!=0||c<15||c>610);
				do
				{
					d=random(400);
				}while(d%15!=0||d<30||d>450);
			}while(getpixel(c+7,d+7)!=0);
			putimage(c,d,food,COPY_PUT);
		}
	}
	free(snake);
	free(food);
	outtextxy(256,410,"Press Space + Shift To Restart");
	outtextxy(256,440,"Press Esc To Exit");
      //	if(bioskey(2)==0x01){ goto start;}
	}while(bioskey(0)!=283);{}
	clearviewport();
	closegraph();
}