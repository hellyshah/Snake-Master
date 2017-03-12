#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <math.h>
#include<string.h>


#define MIN_X 83
#define MAX_X 629
#define MIN_Y 30
#define MAX_Y 409
#define MAX_BUTTONS 22
#define MAX_COLPAT 28


#define CLEAR      0
#define MARK_OP    8      //mark
#define CLIP_OP    10    //clip
#define TRANS_OP   11   //translate
#define LOAD_OP   12    //open
#define SAVE_OP   13    //save

typedef struct button_desc
{
 int xmin,ymin,xmax,ymax;
 int button_no;
 char* desc;
}button;

button buttons[MAX_BUTTONS];

typedef struct color_button
{
  int xmin,ymin,xmax,ymax;
  int color;
  int colflag;
}color_but;

color_but colorbuttons[28];

/*/ structure to mark an area      */
struct
{
 int top,left,bottom,right;
}marker;

int marked=0; /*/ to store whether marked or not*/

char FileName[40]="Untitled";
int  saved=1;/*/to store if file has been saved or not*/
int  LeftButtonPressed;
int  RightButtonPressed;
int  mousex,mousey;
int  prevx,prevy;
int  Current_Color=BLACK; /*/ to  Store the current color           */
int  Current_Button=0;/*/ to store the current button pressed*/
int  Prev_Button=1;/*/ to store the previous button              */

void init(); //174
void init_button(int,int,int,int,int,char*); //319
void init_color_button(int,int,int,int,int,int); //296
void New_ico(int x1, int y1);//389
void Open_ico(int x1, int y1);//405
void Save_ico(int x1, int y1);//431
void Line_ico(int x1, int y1); //464
void Rectangle_ico(int x1, int y1);//469
void Circle_ico(int x1, int y1);//474
void Ellipse_ico(int x1,int y1);//499
//void Sphere_ico(int x1, int y1); this button is not defined
void Spiral_ico(int x1,int y1); //479
void Brush_ico(int x1, int y1);//504  free hand
void Erase_ico(int x1, int y1);//542
void Alphabet_ico(int x, int y);//564 text
void Mark_ico(int x1, int y1); //576 marking tool
void Clip_ico(int x1, int y1);   //585 clip works with mark
void Translate_ico(int x, int y);//596
void Bucket_ico(int x,int y); //620
void Cube_ico(int x, int y); //532
void color_ico(int x1, int y1, int c);//612
void draw_button_border(int );   //336
void undraw_button_border(int no);//350
void draw_color_button_border(int,int);//364
void start_up(); //640

void check_if_exit(); //839
int check_mouse_on(int,int,int,int);  //825
int check_if_button_pressed();  //849
int check_if_color(); //934

void disp_filename();    //703  dos-paint
void disp_coord();        //719
void ShowStatus(char*);  //957
void ClearStatus();          //968
char* readline(char*);     //1572

void showmouse();//749
void hidemouse();//756
void wheremouse(int *, int *);//772
int buttclicked(); //763
void reset();   //737
void getxy();   //781
void startmouse(int,int);//802
void restrictmouse(int,int,int,int);//811

void Diagram(); //974
void freehand();//1011
void drawline();//1028
void drawrectangle();//1054
void erase();  //1076
void beep();  //1091
void drawtext(); //1098
void plotellipsepoints(int,int,int,int); //1364
void algoellipse(int,int,float,float);    //1322
void algospiral(int,int,float,float);  //1375
void drawellipse(); //1282
void drawspiral();   //1392
void drawcircle();   //1453
void Bucket(); //1185
void Cube();  //1239
void insert(int,int); //1172
void ffill(int,int,int,int);//1200


void save(); //1515
void Load();//1632

void clip();  //1904
void mark(); //1690
void unmark();//1748
void translate();//1761

void main()
{
	int i,j,gd=DETECT,gm;
	initgraph(&gd,&gm,"c:\\tc\\bgi");
	setcolor(RED);
	if(graphresult())
	{
		printf("\n Could not initialise graphics \n");
		exit(0);
	}
	reset();
	start_up();
	showmouse();
	startmouse(300,300);//initial position of mouse
	disp_filename();

	init();
	undraw_button_border(Current_Button);
	while(1)
	{
		getxy();
		disp_coord();
		if(LeftButtonPressed)
		{
			if(check_if_button_pressed()>=0);
			else if(check_if_color())
				ClearStatus();
			else if(check_mouse_on(MIN_X+2,MIN_Y+2,MAX_X-2,MAX_Y-2))
			{
				ClearStatus();
				saved=0;/* file has been altered; */
				Diagram();
			}
			else check_if_exit();
		}
		else check_if_button_pressed();
	}
}

void init()// Buttons 
{
	int x1=10,y1=30,x2=44,y2=MAX_Y+28,ywidth=30,xwidth=30;
	int butt=0,i,j;


	New_ico(x1,y1);
	init_button(butt,x1,y1,xwidth,ywidth,"New File");
	draw_button_border(butt);
	butt++;

	Line_ico(x2,y1);
	init_button(butt,x2,y1,xwidth,ywidth,"Line Drawing Tool");
	draw_button_border(butt);
	butt++;


	y1=y1+ywidth;
	Rectangle_ico(x1,y1);
	init_button(butt,x1,y1,xwidth,ywidth,"Rectangle Drawing Tool");
	draw_button_border(butt);
	butt++;

	Circle_ico(x2,y1);
	init_button(butt,x2,y1,xwidth,ywidth,"Circle Drawing Tool");
	draw_button_border(butt);
	butt++;

	y1=y1+ywidth;
	Ellipse_ico(x1,y1);
	init_button(butt,x1,y1,xwidth,ywidth,"Ellipse Drawing Tool");
	draw_button_border(butt);
	butt++;


	Spiral_ico(x2,y1);
	init_button(butt,x2,y1,xwidth,ywidth,"Spiral Drawing Tool");
	draw_button_border(butt);
	butt++;


	y1=y1+ywidth;
	Brush_ico(x1,y1);
	init_button(butt,x1,y1,xwidth,ywidth,"Free Hand");
	draw_button_border(butt);
	butt++;

	Erase_ico(x2,y1);
	init_button(butt,x2,y1,xwidth,ywidth,"Eraser");
	draw_button_border(butt);
	butt++;

	y1=y1+ywidth;
	Mark_ico(x1,y1);
	init_button(butt,x1,y1,xwidth,ywidth,"Marking Tool");
	draw_button_border(butt);
	butt++;

	Alphabet_ico(x2,y1);
	init_button(butt,x2,y1,xwidth,ywidth,"Text");
	draw_button_border(butt);
	butt++;

	y1=y1+ywidth;
	Clip_ico(x1,y1);
	init_button(butt,x1,y1,xwidth,ywidth,"Clipping (Works with Mark)");
	draw_button_border(butt);
	butt++;

	Translate_ico(x2,y1);
	init_button(butt,x2,y1,xwidth,ywidth,"Translate (Works with Mark)");
	draw_button_border(butt);
	butt++;

	y1=y1+ywidth;
	Open_ico(x1,y1);
	init_button(butt,x1,y1,xwidth,ywidth,"Open File");
	draw_button_border(butt);
	butt++;

	Save_ico(x2,y1);
	init_button(butt,x2,y1,xwidth,ywidth,"Save File");
	draw_button_border(butt);
	butt++;

	y1=y1+ywidth;
	Cube_ico(x1,y1);
	init_button(butt,x1,y1,xwidth,ywidth,"Cuboid Drawing Tool");
	draw_button_border(butt);
	butt++;

	Bucket_ico(x2,y1);
	init_button(butt,x2,y1,xwidth,ywidth,"Bucket Fill");
	draw_button_border(butt);
	butt++;

////////////////////////All Icon Construction Over Now /////////////////////////

	butt=0;
	x1=MIN_X+8;
	y1=MAX_Y+9;
	xwidth=19;ywidth=15;
	for(i=0;i<8;i++)
	{
		init_color_button(butt,x1,y1,xwidth,ywidth,1);
		draw_color_button_border(butt,1);
		butt++;

		init_color_button(butt,x1,y2,xwidth,ywidth,1);
		draw_color_button_border(butt,1);
		butt++;

		x1=x1+xwidth;
	}
	butt=0;
	x1=x1+25;
	bar(20,MAX_Y+7,65,MAX_Y+7+35);
	setcolor(BLACK);
	rectangle(20,MAX_Y+7,65,MAX_Y+7+35);
	setcolor(Current_Color);
}

void init_color_button(int color,int xmin,int ymin,int xwidth,int ywidth,int colflag)
{
	int xgap=4;
	if (colflag)
	{
		colorbuttons[color].xmin=xmin;
		colorbuttons[color].xmax=xmin+xwidth-xgap;
		colorbuttons[color].ymin=ymin;
		colorbuttons[color].ymax=ymin+ywidth;
		colorbuttons[color].color=color;
		colorbuttons[color].colflag=colflag;
	}
	else
	{
		colorbuttons[color+16].xmin=xmin;
		colorbuttons[color+16].xmax=xmin+xwidth-xgap;
		colorbuttons[color+16].ymin=ymin;
		colorbuttons[color+16].ymax=ymin+ywidth;
		colorbuttons[color+16].color=color;
		colorbuttons[color+16].colflag=colflag;
	}
}

void init_button(int no,int xmin,int ymin,int xwidth,int ywidth,char* desc)
{
	int ygap=4;
	buttons[no].xmin=xmin;
	buttons[no].ymin=ymin;
	buttons[no].xmax=xmin+xwidth;
	buttons[no].ymax=ymin+ywidth-ygap;
	buttons[no].desc=(char *) malloc(strlen(desc)+1);
	if(buttons[no].desc==NULL)
	{
		cleardevice();
		printf("\n No MEMORY ");
	}
	strcpy(buttons[no].desc,desc);
}


void draw_button_border(int no)
{
	int color=getcolor();
	hidemouse();
	setcolor(WHITE);
	line(buttons[no].xmin,buttons[no].ymin,buttons[no].xmax,buttons[no].ymin);
	line(buttons[no].xmin,buttons[no].ymin,buttons[no].xmin,buttons[no].ymax);
	setcolor(DARKGRAY);
	line(buttons[no].xmax,buttons[no].ymax,buttons[no].xmax,buttons[no].ymin);
	line(buttons[no].xmax,buttons[no].ymax,buttons[no].xmin,buttons[no].ymax);
	setcolor(color);
	showmouse();
}

void undraw_button_border(int no)
{
	int color=getcolor();
	hidemouse();
	setcolor(0);
	line(buttons[no].xmin,buttons[no].ymin,buttons[no].xmax,buttons[no].ymin);
	line(buttons[no].xmin,buttons[no].ymin,buttons[no].xmin,buttons[no].ymax);
	setcolor(CYAN);
	line(buttons[no].xmax,buttons[no].ymax,buttons[no].xmax,buttons[no].ymin);
	line(buttons[no].xmax,buttons[no].ymax,buttons[no].xmin,buttons[no].ymax);
	setcolor(color);
	showmouse();
}

void draw_color_button_border(int no,int colflag)
{
	int color=getcolor();
	setcolor(BLACK);
	if (colflag)
	{
		line(colorbuttons[no].xmin,colorbuttons[no].ymin,colorbuttons[no].xmax,colorbuttons[no].ymin);
		line(colorbuttons[no].xmin,colorbuttons[no].ymin,colorbuttons[no].xmin,colorbuttons[no].ymax);
		line(colorbuttons[no].xmax,colorbuttons[no].ymax,colorbuttons[no].xmax,colorbuttons[no].ymin);
		line(colorbuttons[no].xmax,colorbuttons[no].ymax,colorbuttons[no].xmin,colorbuttons[no].ymax);
		setfillstyle(1,no);
		floodfill(colorbuttons[no].xmin+1,colorbuttons[no].ymin+1,BLACK);
	}
	else
	{
		line(colorbuttons[no+16].xmin,colorbuttons[no+16].ymin,colorbuttons[no+16].xmax,colorbuttons[no+16].ymin);
		line(colorbuttons[no+16].xmin,colorbuttons[no+16].ymin,colorbuttons[no+16].xmin,colorbuttons[no+16].ymax);
		line(colorbuttons[no+16].xmax,colorbuttons[no+16].ymax,colorbuttons[no+16].xmax,colorbuttons[no+16].ymin);
		line(colorbuttons[no+16].xmax,colorbuttons[no+16].ymax,colorbuttons[no+16].xmin,colorbuttons[no+16].ymax);
		setfillstyle(no,LIGHTBLUE);
		floodfill(colorbuttons[no+16].xmin+1,colorbuttons[no+16].ymin+1,BLACK);
	}
	setcolor(color);
}

void New_ico(int x1, int y1)
{
	setlinestyle(0, 1, 1);
	setcolor(BLACK);
	line(9+x1, 4+y1, 9+x1, 20+y1);
	line(9+x1, 20+y1, 21+x1, 20+y1);
	line(21+x1, 20+y1, 21+x1, 8+y1);
	line(9+x1, 4+y1, 17+x1, 4+y1);
	line(17+x1, 4+y1, 17+x1, 8+y1);
	line(17+x1, 8+y1, 21+x1, 8+y1);
	line(21+x1, 8+y1, 17+x1, 4+y1);

	setfillstyle(1, WHITE);
	floodfill(10+x1, 9+y1, BLACK);
}

void Open_ico(int x1, int y1)
{
	setlinestyle(0, 1, 1);
	setcolor(BLACK);
	line(5+x1, 20+y1, 17+x1, 20+y1);
	line(17+x1, 20+y1, 24+x1, 15+y1);
	line(24+x1, 15+y1, 12+x1, 15+y1);
	line(12+x1, 15+y1, 5+x1, 20+y1);
	setfillstyle(1, DARKGRAY);
	floodfill(10+x1, 18+y1, BLACK);

	line(5+x1, 20+y1, 5+x1, 10+y1);
	line(5+x1, 10+y1, 6+x1, 8+y1);
	line(6+x1, 8+y1, 8+x1, 8+y1);
	line(8+x1, 8+y1, 9+x1, 10+y1);
	line(9+x1, 10+y1, 17+x1, 10+y1);
	line(17+x1, 10+y1, 17+x1, 15+y1);
	setfillstyle(1, BLUE);
	floodfill(6+x1, 12+y1, BLACK);
	line(15+x1, 7+y1, 17+x1, 5+y1);
	line(17+x1, 5+y1, 22+x1, 7+y1);
	line(22+x1, 7+y1, 24+x1, 12+y1);
	line(24+x1, 12+y1, 20+x1, 10+y1);
	line(24+x1, 12+y1, 26+x1, 9+y1);
}

void Save_ico(int x1, int y1)
{
	setlinestyle(0, 1, 1);
	setcolor(BLACK);
	line(6+x1, 4+y1, 24+x1, 4+y1);
	line(24+x1, 4+y1, 24+x1, 20+y1);
	line(24+x1, 20+y1, 8+x1, 20+y1);
	line(8+x1, 20+y1, 6+x1, 18+y1);
	line(6+x1, 18+y1, 6+x1, 4+y1);

	line(9+x1, 4+y1, 9+x1, 12+y1);
	line(9+x1, 12+y1, 21+x1, 12+y1);
	line(21+x1, 12+y1, 21+x1, 4+y1);

	line(10+x1, 20+y1, 10+x1, 15+y1);
	line(10+x1, 15+y1, 20+x1, 15+y1);
	line(20+x1, 15+y1, 20+x1, 20+y1);

	line(17+x1, 15+y1, 17+x1, 20+y1);

	line(21+x1, 7+y1, 24+x1, 7+y1);

	setfillstyle(1, WHITE);
	floodfill(10+x1, 5+y1, BLACK);

	setfillstyle(1, LIGHTBLUE);
	floodfill(7+x1, 5+y1, BLACK);

	setfillstyle(1, DARKGRAY);
	floodfill(11+x1, 19+y1, BLACK);
}


void Line_ico(int x1, int y1)
{
	line(8+x1, 5+y1, 22+x1, 19+y1);
}

void Rectangle_ico(int x1, int y1)
{
	rectangle(8+x1, 5+y1, 22+x1, 19+y1);
}

void Circle_ico(int x1, int y1)
{
	circle(15+x1, 12+y1, 8);
}

void Spiral_ico(int x1, int y1)
{
	int xrad=3,yrad=1;
	int i;
	x1=15+x1;
	y1=14+y1;
	for( i = 1; i <=4; ++i )
	{
		ellipse( x1, y1, 90, 270, xrad, yrad );
		xrad += 1;
		yrad += 1;
		y1 -= 1;
		ellipse( x1, y1, 270, 90, xrad, yrad );
		xrad += 1;
		yrad += 1;
		y1 += 1;
	}
}


void Ellipse_ico(int x1,int y1)
{
	ellipse(15+x1, 13+y1, 0, 360, 8, 6);
}

void Brush_ico(int x1, int y1)
{
	setcolor(BLACK);
	setlinestyle(0, 1, 3);
	line(19+x1, 21+y1, 10+x1, 9+y1);
	setlinestyle(0, 1, 1);
	line(11+x1, 9+y1, 11+x1, 6+y1);
	line(11+x1, 6+y1, 6+x1, 4+y1);
	line(6+x1, 4+y1, 7+x1, 9+y1);
	line(7+x1, 9+y1, 11+x1, 9+y1);
}

void Fill_ico(int x1, int y1)
{
	setlinestyle(0, 1, 1);
	setcolor(BLACK);
	line(10+x1, 11+y1, 16+x1, 19+y1);
	line(16+x1, 19+y1, 25+x1, 12+y1);
	line(25+x1, 12+y1, 20+x1, 5+y1);

	line(10+x1, 11+y1, 24+x1, 11+y1);
	setfillstyle(1, RED);
	floodfill( 12+x1, 12+y1, BLACK);
	setcolor(RED);
	line(10+x1, 11+y1, 8+x1, 14+y1);
	line(8+x1, 14+y1, 8+x1, 16+y1);
}

void Cube_ico(int x, int y)
{
	rectangle(8+x, 5+y, 24+x, 17+y);
	rectangle(5+x, 9+y, 21+x, 21+y);
	line(5+x, 9+y, 8+x, 5+y);
	line(21+x, 21+y, 24+x, 17+y);
	line(21+x, 9+y, 24+x, 5+y);
	line(5+x, 21+y, 8+x, 17+y);
}

void Erase_ico(int x1, int y1)
{
	setlinestyle(0, 1, 1);
	setcolor(BLACK);
	line(14+x1, 20+y1, 25+x1, 7+y1);
	line(25+x1, 7+y1, 23+x1, 4+y1);
	line(23+x1, 4+y1, 12+x1, 17+y1);
	line(12+x1, 17+y1, 14+x1, 20+y1);

	line(14+x1, 20+y1, 5+x1, 20+y1);
	line(5+x1, 20+y1, 5+x1, 17+y1);
	line(5+x1, 17+y1, 12+x1, 17+y1);

	line(5+x1, 17+y1, 16+x1, 4+y1);
	line(16+x1, 4+y1, 23+x1, 4+y1);

	setfillstyle(1, DARKGRAY);
	floodfill(14+x1, 18+y1, BLACK);
	setfillstyle(1, WHITE);
	floodfill(16+x1, 5+y1, BLACK);
}

void Alphabet_ico(int x, int y)
{
	setcolor(BLACK);
	setlinestyle(0, 1, 3);
	line(8+x, 20+y, 18+x, 4+y);
	line(18+x, 4+y, 18+x, 20+y);
	setlinestyle(0, 1, 1);
	line(12+x, 14+y, 19+x, 14+y);
	line(6+x, 20+y, 12+x, 20+y);
	line(15+x, 20+y, 21+x, 20+y);
}

void Mark_ico(int x1, int y1)
{
	setlinestyle(0, 1, 1);
	setcolor(BLACK);
	setlinestyle(3, 1, 1);
	rectangle(5+x1, 5+y1, 25+x1, 19+y1);
	setlinestyle(0, 1, 1);
}

void Clip_ico(int x1, int y1)
{
	setlinestyle(0, 1, 1);
	setcolor(BLACK);
	rectangle(5+x1, 5+y1, 25+x1, 19+y1);
	setfillstyle(1, WHITE);
	floodfill(15+x1, 12+y1, BLACK);
	setfillstyle(1,BLACK);
	bar(12+x1, 10+y1, 23+x1, 17+y1);
}

void Translate_ico(int x, int y)
{
	setcolor(BLACK);
	line(6+x, 3+y, 20+x, 3+y);
	line(20+x, 3+y, 20+x, 8+y);
	line(6+x, 3+y, 6+x, 16+y);
	line(6+x, 16+y, 12+x, 16+y);

	line(25+x, 8+y, 12+x, 8+y);
	line(12+x, 8+y, 12+x, 20+y);
	line(12+x, 20+y, 25+x, 20+y);
	line(25+x, 20+y, 25+x, 8+y);
	setfillstyle(1, BLUE);
	floodfill(8+x, 5+y, BLACK);
	floodfill(20+x, 18+y, BLACK);
}
void color_ico(int x1, int y1, int c)
{
	setcolor(BLACK);
	rectangle(x1, y1, x1+9, y1+8);
	setfillstyle(1, c);
	floodfill(x1+1, y1+1, BLACK);
}

void Bucket_ico(int x, int y)
{
	setlinestyle(0, 1, 1);
	setcolor(BLACK);
	line(7+x, 8+y, 11+x, 20+y);
	line(11+x, 20+y, 21+x, 16+y);
	line(21+x, 16+y, 17+x, 4+y);
	line(7+x, 8+y, 17+x, 4+y);
	line(17+x, 4+y, 7+x, 8+y);

	line(3+x, 12+y, 7+x, 8+y);
	line(3+x, 12+y, 5+x, 15+y);
	line(5+x, 15+y, 7+x, 8+y);

	setfillstyle(1, BLUE);
	floodfill(10+x, 9+y, BLACK);

	setfillstyle(1, YELLOW);
	floodfill(5+x, 13+y, BLACK);
}
void start_up()
{
	setfillstyle(1, LIGHTBLUE);
	floodfill(200, 200, 1);
	/* FOR MAIN WINDOW */
	setcolor(4);
	line(0, 0, 639, 0);
	line(0, 0+1, 639-1, 0+1);
	line(0, 0, 0, 479-1);
	line(0+1, 0, 0+1, 479-2);
	setcolor(4);
	line(639, 0+1, 639, 479);
	line(639-1, 0+2, 639-1, 479-1);
	line(639, 479, 0, 479);
	line(639, 479-1, 0+1, 479-1);

	/* for drawing window */
	setcolor(WHITE);
	rectangle(MIN_X, MIN_Y, MAX_X, MAX_Y);   // 83   30   629  409
	setfillstyle(1, WHITE);
	floodfill(300, 300, WHITE);

	setcolor(4);
	line(MIN_X, MIN_Y, MAX_X, MIN_Y);
	line(MIN_X, MIN_Y+1, MAX_X-1, MIN_Y+1);
	line(MIN_X, MIN_Y, MIN_X, MAX_Y-1);
	line(MIN_X+1, MIN_Y, MIN_X+1, MAX_Y-2);
	setcolor(4);
	line(MAX_X, MIN_Y+1, MAX_X, MAX_Y);
	line(MAX_X-1, MIN_Y+2, MAX_X-1, MAX_Y-1);
	line(MAX_X, MAX_Y, MIN_X, MAX_Y);
	line(MAX_X, MAX_Y-1, MIN_X+1, MAX_Y-1);

	/* for status bar */
	setcolor(LIGHTGRAY);
	line(10, 460, 629, 460);
	line(10, 460, 10, 479 - 5-1);
	setcolor(4);
	line(629, 460 , 629, 479 - 5);
	line(629, 479 - 5, 10, 479 - 5);

	/*/ For color*/
	setcolor(15);
	line(MIN_X, MAX_Y+4, 251, MAX_Y+4);
	line(MIN_X, MAX_Y+4, MIN_X,MAX_Y+47);
	setcolor(0);
	line(251, MAX_Y+47 , MIN_X, MAX_Y+47);
	line(251, MAX_Y+47, 251, MAX_Y+4);

	/* For College And Creators Details */
	setcolor(15);
	line(270, MAX_Y+4, 630, MAX_Y+4);
	line(270, MAX_Y+4, 270,MAX_Y+47);
	setcolor(0);
	line(630, MAX_Y+47 , 270, MAX_Y+47);
	line(630, MAX_Y+47, 630, MAX_Y+4);
	setcolor(BLACK);
	settextstyle(SMALL_FONT,HORIZ_DIR,4);
	outtextxy(280,MAX_Y+5,"Developed At :");
	outtextxy(280,MAX_Y+20,"Faculty Of Technology and Engineering, M. S. U. Baroda");
	outtextxy(280,MAX_Y+35,"Developed By :-Jatin Suvaliya and Ravi Katara. ");
	settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
}
void disp_filename()
{
	char name[60];
	int  xpos;
	setfillstyle(SOLID_FILL,BLUE);
	bar(10,5,629,18);
	strcpy(name,"RASTER GRAPHICS EDITOR ");
	strcat(name,FileName);
	xpos=(getmaxx()-textwidth(name))/2;
	setcolor(BLACK);
	outtextxy(xpos,8,name);
	setfillstyle(SOLID_FILL,BLUE);
	bar(614,6,628,17);
	outtextxy(620,8,"X");
}

void disp_coord()
{
	char xy[25];
	int color;
	if(prevx!=mousex||prevy!=mousey)
	if( (mousex>MIN_X+1)&&(mousex<MAX_X-1)&&(mousey>MIN_Y+1)&&(mousey<MAX_Y-1))
	{
		sprintf(xy," x : %d  y : %d",mousex-MIN_X-2,mousey-MIN_Y-2);
		color=getcolor();
		setcolor(LIGHTBLUE);
		outtextxy(475,464,"лллллллллллллллллллллллл   " );/* ALT 219*/
		setcolor(0);
		outtextxy(475,464,xy);
		setcolor(color);
	}

}

void reset()
{
	union REGS regs;
	regs.x.ax=0;
	int86(0x33,&regs,&regs);
	if(regs.x.ax==0)
	{
		printf("\n No Mouse Drivers ");
		exit(0);
	}
}

void showmouse()
{
	union REGS regs;
	regs.x.ax=1;
	int86(0x33,&regs,&regs);
}

void hidemouse()
{
	union REGS regs;
	regs.x.ax=2;
	int86(0x33,&regs,&regs);
}

int buttclicked()
{
union REGS regs;
regs.x.ax=3;
int86(0x33,&regs,&regs);

return regs.x.bx;
}

void wheremouse(int *x,int*y)
{
union REGS regs;
regs.x.ax=3;
int86(0x33,&regs,&regs);
*x=regs.x.cx;
*y=regs.x.dx;
}

void getxy()
{
	union REGS regs;
	regs.x.ax=3;
	int86(0x33,&regs,&regs);

	prevx=mousex;
	prevy=mousey;
	if(regs.x.bx&1)
		LeftButtonPressed=1;
	else
		LeftButtonPressed=0;
	if(regs.x.bx&2)
		RightButtonPressed=1;
	else
		RightButtonPressed=0;

	mousex=regs.x.cx;
	mousey=regs.x.dx;
}

void startmouse(int x,int y)
{
	union REGS regs;
	regs.x.ax=4;
	regs.x.cx=x;
	regs.x.dx=y;
	int86(0x33,&regs,&regs);
}

void restrictmouse(int minx,int miny,int maxx,int maxy)
{
	union REGS regs;

	regs.x.cx=minx;
	regs.x.dx=maxx;
	regs.x.ax=0x7;
	int86(0x33,&regs,&regs);
	regs.x.cx=miny;
	regs.x.dx=maxy;
	regs.x.ax=0x8;
	int86(0x33,&regs,&regs);
}

int check_mouse_on(int minx,int miny,int maxx,int maxy)
{
	if(mousex<minx)
		return 0;
	if(mousex>maxx)
		return 0;
	if(mousey<miny)
		return 0;
	if(mousey>maxy)
		return 0;

	return 1;
}

void check_if_exit()
{
	if( (check_mouse_on(614,6,628,17))&&LeftButtonPressed)
	{
		flushall();
		closegraph();
		exit(0);
	}
}

int check_if_button_pressed()
{
	int ret_value=-1;
	int i;
	char ch;

	for(i=0;i<MAX_BUTTONS;++i)
	{
	   if(check_mouse_on(buttons[i].xmin,buttons[i].ymin,buttons[i].xmax,buttons[i].ymax))
	   {
	    if(LeftButtonPressed && i!=Current_Button)
	    {
		 ret_value=i;
		 draw_button_border(Current_Button);
		 Prev_Button=Current_Button;
		 undraw_button_border(i);
		 Current_Button=i;

		 switch(Current_Button)
		 {
			case CLEAR : if(marked) unmark();
				     hidemouse();

				     if(!saved)
				     {
					ShowStatus("Save Changes ? ");
					ch=getch();

					if(ch=='y'||ch=='Y')
					save();
				     }
				     strcpy(FileName,"Untitled");
				     disp_filename();
				     setfillstyle(SOLID_FILL,WHITE);
				     bar(MIN_X+2,MIN_Y+2,MAX_X-2,MAX_Y-2);
				     draw_button_border(Current_Button);
				     undraw_button_border(Prev_Button);
				     Current_Button=Prev_Button;
				     showmouse();
				     break;

			  case LOAD_OP: if(marked) unmark();
				       hidemouse();
				      Load();
				      draw_button_border(Current_Button);
				      undraw_button_border(Prev_Button);
				      Current_Button=Prev_Button;
				      showmouse();
				      break;

			 case SAVE_OP:if(marked) unmark();
				       hidemouse();
				      save();
				      draw_button_border(Current_Button);
				      undraw_button_border(Prev_Button);
				      Current_Button=Prev_Button;
				      showmouse();
				      break;


		      case CLIP_OP:
				 hidemouse();
				 clip();
				 draw_button_border(Current_Button);
				 undraw_button_border(Prev_Button);
				 Current_Button=Prev_Button;
				 showmouse();
				 break;
				}
		      if(Current_Button!=MARK_OP&&Current_Button!=TRANS_OP)
		      {
			if(marked) unmark();
		       }
		     }

		 if(prevx!=mousex||prevy!=mousey)
		    ShowStatus(buttons[i].desc);
		    return ret_value;
		}
	}

	ClearStatus();
	return ret_value;
}

int check_if_color()
{
	int i=0;
	for(i=0;i<MAX_COLPAT;i++)
	{
		if(check_mouse_on(colorbuttons[i].xmin,colorbuttons[i].ymin,colorbuttons[i].xmax,colorbuttons[i].ymax))
		{
		  if(colorbuttons[i].colflag)
		  {
			Current_Color=colorbuttons[i].color;
		  }
			setfillstyle(SOLID_FILL,Current_Color);
		  bar(20,MAX_Y+7,65,MAX_Y+7+35);
		  setcolor(BLACK);
		  rectangle(20,MAX_Y+7,65,MAX_Y+7+35);
		  setcolor(Current_Color);
		  return 1;
		}
		}
	return 0;

}

void ShowStatus(char* str)
{
int color=getcolor();
int i;

	ClearStatus();
	setcolor(BLACK);
	outtextxy(12,464,str);
	setcolor(color);
}

void ClearStatus()
{
   setcolor(LIGHTBLUE);
   outtextxy(12,464,"ллллллллллллллллллллллллллллллллллллллллллллллллллл" );/* ALT 219*/
}

void Diagram()
{
    restrictmouse(MIN_X+2,MIN_Y+2,MAX_X-2,MAX_Y-2);
    hidemouse();

    switch(Current_Button)
    {
    case 1: drawline();
	break;
    case 2: drawrectangle();
	break;
    case 3: drawcircle();
	break;
    case 4: drawellipse();
	break;
    case 5: drawspiral();
	break;
    case 6: freehand();
	break;
    case 7: erase();
	break;
    case MARK_OP:
	mark();
	break;
    case 9: drawtext();
	break;
    case TRANS_OP:
	translate();
	break;
    case 14: Cube();
	 break;
    case 15: Bucket();
	 break;
	}
showmouse();
restrictmouse(0,0,639,479);
}
void freehand()
{
	setcolor(Current_Color);
	if(prevx<MIN_X+2||prevx>MAX_X-2||prevy>MAX_Y-2||prevy<MIN_Y+2)
		return;

	while(LeftButtonPressed)
	{

		disp_coord();

		line(mousex,mousey,prevx,prevy);
		getxy();

	}
}

void drawline()
{
	int color=15-Current_Color;
	int x,y;
	setcolor(color);
	setwritemode(XOR_PUT);

	x=mousex;
	y=mousey;

	if(x<MIN_X+2||x>MAX_X-2||y>MAX_Y-2||y<MIN_Y+2)
		return;

	while(LeftButtonPressed)
	{
		disp_coord();
		line(x,y,mousex,mousey);
		getxy();
		line(x,y,mousex,mousey);
	}
	setwritemode(COPY_PUT);
	setcolor(Current_Color);
	line(x,y,mousex,mousey);

}

void drawrectangle()
{
	int color=15-Current_Color;
	int x,y;
	setcolor(color);
	setwritemode(XOR_PUT);

	x=mousex;
	y=mousey;

	while(LeftButtonPressed)
	{
		disp_coord();
		rectangle(x,y,mousex,mousey);
		getxy();
		rectangle(x,y,mousex,mousey);
	}
	setwritemode(COPY_PUT);
	setcolor(Current_Color);
		rectangle(x,y,mousex,mousey);
}

void erase()
{
	int i,j;
	while(LeftButtonPressed)
	{

		disp_coord();
		for(i=mousex;i<mousex+10&&i<=MAX_X-2;++i)
			for(j=mousey;j<mousey+10&&j<=MAX_Y-2;++j)
				putpixel(i,j,WHITE);
		getxy();

	}
}

void beep()
{
	sound(7);
	delay(1000);
	nosound();
}

void drawtext()
{
	int size=0,max_char,i=0;
	char ch;
	char str[68]; /*/ ( (MAX_X-2)-(MIN_X+2) )/8 ,8 being width & height of a char*/
	char blank[68]; /*/ to write blank*/

	max_char=(MAX_X-2-mousex)/8;
	if((MAX_Y-2-mousey<9) || (max_char<1))
	{
		ShowStatus(" Not Enough Space to Write ");
		beep();
		ClearStatus();
		return;
	}

	ShowStatus("Press <Enter> or <Esc> to exit");
	fflush(stdin);
	str[0]='\0';

	ch=getch();

	while(ch!=13 && ch!=27)
	{
		if (ch==8)
		{
			if(size<1)
				beep();
			else
			{
				setcolor(WHITE);
				strcpy(blank,"");
				for(i=0;i<size;++i)
					blank[i]='?';
				blank[size]='\0';
				outtextxy(mousex,mousey,blank);

				setcolor(Current_Color);
				size--;
				str[size]='\0';
				outtextxy(mousex,mousey,str);
			}
		}
		else if(size==max_char)
		{
			beep();
		}
		else
		{
			size++;
			setcolor(WHITE);
			strcpy(blank,"");
			for(i=0;i<size;++i)
				blank[i]='?';
			blank[size]='\0';
			outtextxy(mousex,mousey,blank);

			str[size-1]=ch;
			setcolor(Current_Color);
			str[size]='\0';
			outtextxy(mousex,mousey,str);
		}
		ch=getch();
	}
	ClearStatus();
}

struct node1
{
	int x,y;
	struct node1* next;
};
struct node1 *last1,*root1,*p1;

void insert(int x,int y)
{
	struct node1 *new1;
	new1=(struct node1*)malloc(sizeof(struct node1));
	new1->x=x;
	new1->y=y;
	new1->next=NULL;
	last1->next=new1;
	last1=new1;
	return;
}


void Bucket()
{
	int x,y,bgcolor;
	while(LeftButtonPressed)
	{
		disp_coord();
		getxy();
	}
	setwritemode(COPY_PUT);
	x=mousex;
	y=mousey;
	bgcolor=getpixel(x,y);
	ffill(x,y,bgcolor,Current_Color);
}

void ffill(int x,int y,int backColor,int fill_color)
{
	if(backColor==fill_color)
		return;
	last1=root1=(struct node1*)malloc(sizeof(struct node1));
	root1->x=x;
	root1->y=y;
	root1->next=NULL;
	while(root1!=NULL)
	{
		putpixel(x,y,fill_color);
		if(getpixel(x,y-1)==backColor)
		{
			putpixel(x,y-1,fill_color);
			insert(x,y-1);
		}
		if(getpixel(x+1,y)==backColor)
		{
			putpixel(x+1,y,fill_color);
			insert(x+1,y);
		}
		if(getpixel(x,y+1)==backColor)
		{
			putpixel(x,y+1,fill_color);
			insert(x,y+1);
		}
		if(getpixel(x-1,y)==backColor)
		{
			putpixel(x-1,y,fill_color);
			insert(x-1,y);
		}
		p1=root1;
		root1=root1->next;
		free(p1);
		x=root1->x;
		y=root1->y;
	}
}

void Cube()
{
	int color=15-Current_Color;
	int temp,x,y,mousex1,mousey1;
	restrictmouse((MIN_X+5),(MIN_Y+5),(MAX_X-30),(MAX_Y-30));
	setcolor(color);
	setwritemode(XOR_PUT);

	x=mousex;
	y=mousey;

	while(LeftButtonPressed)
	{
		disp_coord();
/*		rectangle(x,y,mousex,mousey); */
		getxy();
/*		rectangle(x,y,mousex,mousey); */
	}
	setwritemode(COPY_PUT);
	mousex1=mousex;
	mousey1=mousey;
	if(mousex1<x || mousey1<y)
	{
		temp=x;
		x=mousex1;
		mousex1=temp;
		temp=y;
		y=mousey1;
		mousey1=temp;
	}
	if(mousex1-x>1 && mousey1-y>1)
	{
			setcolor(Current_Color);
			rectangle(x,y,mousex1,mousey1);
			rectangle(x+25, y+25, mousex1+25, mousey1+25);
			line(x,y,x+25,y+25);
			line(mousex1,mousey1,mousex1+25,mousey1+25);
			line(x,mousey1,x+25,mousey1+25);
			line(mousex1,y,mousex1+25,y+25);
	}
	restrictmouse(0,0,640,480);
}

void drawellipse()
{
	int x1,y1,x2,y2,color,xmid,ymid;
	float radx,rady;
	x1 = mousex;
	y1 = mousey;
	setwritemode(XOR_PUT);
	while(LeftButtonPressed)
	{
		disp_coord();
		x2 = mousex;
		y2 = mousey;
		xmid = (x1 + x2)/2;
		ymid = (y1 + y2)/2;
		radx = abs((x2 - x1)/2);
		rady = abs((y2 - y1)/2);
		if (radx < 1)
			radx = 1;
		if (rady < 1)
			rady = 1;
		color = 15 - Current_Color;
		setcolor(color);
		algoellipse(xmid,ymid,radx,rady);
		delay(20);
		getxy();
		algoellipse(xmid,ymid,radx,rady);
	}
	setwritemode(COPY_PUT);
	setcolor(Current_Color);
	x2 = mousex;
	y2 = mousey;
	xmid = (x1 + x2)/2;
	ymid = (y1 + y2)/2;
	radx = abs((x2 - x1)/2);
	rady = abs((y2 - y1)/2);
	algoellipse(xmid,ymid,radx,rady);

}


void algoellipse(int xcen,int ycen,float radx,float rady)
{
	float p,px,py,x,y,ry,rx,tworx,twory;
	ry = rady * rady;
	rx = radx * radx;
	twory = 2 * ry;
	tworx = 2 * rx;
	x = 0;
	y = rady;
	plotellipsepoints(xcen,ycen,x,y);
	p = (ry - rx*rady + (0.25 * rx));
	px = 0;
	py = tworx * y;
	while (px < py)
	{       x++;
		px = px + twory;
		if (p >= 0)
		{       y--;
			py = py - tworx;
		}
		if (p < 0)
			p = p + ry + px;
		else
			p = p + ry + px - py;
		plotellipsepoints(xcen,ycen,x,y);
	}
	p = (ry * (x + 0.5) * (x + 0.5) + rx * (y-1) * (y-1) - rx * ry);
	while (y > 0)
	{       y--;
		py = py - tworx;
		if (p <= 0)
		{       x++;
			px = px + twory;
		}
		if (p > 0)
			p = p + rx - py;
		else
			p = p + rx - py + px;
		plotellipsepoints(xcen,ycen,x,y);
	}
}

void plotellipsepoints(int xcen,int ycen,int x,int y)
{
	if (xcen+x >= MIN_X && xcen+x <= MAX_X && ycen+y >= MIN_Y && ycen+y <= MAX_Y)
	   line(xcen+x,ycen+y,xcen+x,ycen+y);
	if (xcen-x >= MIN_X && xcen-x <= MAX_X && ycen+y >= MIN_Y && ycen+y <= MAX_Y)
		line(xcen-x,ycen+y,xcen-x,ycen+y);
	if (xcen+x >= MIN_X && xcen+x <= MAX_X && ycen-y >= MIN_Y && ycen-y <= MAX_Y)
		line(xcen+x,ycen-y,xcen+x,ycen-y);
	if (xcen-x >= MIN_X && xcen-x <= MAX_X && ycen-y >= MIN_Y && ycen-y <= MAX_Y)
		line(xcen-x,ycen-y,xcen-x,ycen-y);
}
void algospiral(int xcen,int ycen,float radx,float rady)
{
	float rx=5,ry=5;
	/* while(rx<=(MAX_X-xcen) || ry<=(MAX_Y-ycen) || rx<=(xcen-MIN_X) || ry<=(ycen-MIN_Y)) */
	while(rx<radx || ry<rady)
	{
		ellipse( xcen, ycen, 90, 270, rx, ry );
		rx += 5;
		ry += 5;
		ycen -= 5;
		ellipse( xcen, ycen, 270, 90, rx, ry );
		rx += 5;
		ry += 5;
		ycen += 5;
	}
}

void drawspiral()
{
int x1,y1,x2,y2,color,xmid,ymid;
float radx;
	x1 = mousex;
	y1 = mousey;
	setwritemode(XOR_PUT);
	while(LeftButtonPressed)
	{
		disp_coord();
		x2 = mousex;
		y2 = mousey;
		xmid = (x1 + x2)/2;
		ymid = (y1 + y2)/2;
		radx = abs((x2 - x1)/2);
		if (radx < 1)
			radx = 1;
		color = 15 - Current_Color;
		setcolor(color);
		if((xmid+radx)>(MAX_X-2))
			radx=(MAX_X-2)-xmid;
		if((xmid-radx)<(MIN_X+2))
			radx=xmid-(MIN_X+2);
		if((ymid+radx)>(MAX_Y-2))
			radx=(MAX_Y-2)-ymid;
		if((ymid-radx)<(MIN_Y+8))
			radx=ymid-(MIN_Y+8);
		algoellipse(xmid,ymid,radx,radx);
/*		circle(xmid,ymid,radx);           */
		delay(20);
		getxy();
		if((xmid+radx)>(MAX_X-2))
			radx=(MAX_X-2)-xmid;
		if((xmid-radx)<(MIN_X+2))
			radx=xmid-(MIN_X+2);
		if((ymid+radx)>(MAX_Y-2))
			radx=(MAX_Y-2)-ymid;
		if((ymid-radx)<(MIN_Y+8))
			radx=ymid-(MIN_Y+8);
		algoellipse(xmid,ymid,radx,radx);
	}
	setwritemode(COPY_PUT);
	setcolor(Current_Color);
	x2 = mousex;
	y2 = mousey;
	xmid = (x1 + x2)/2;
	ymid = (y1 + y2)/2;
	radx = abs((x2 - x1)/2);
	if((xmid+radx)>(MAX_X-2))
		radx=(MAX_X-2)-xmid;
	if((xmid-radx)<(MIN_X+2))
		radx=xmid-(MIN_X+2);
	if((ymid+radx)>(MAX_Y-2))
		radx=(MAX_Y-2)-ymid;
	if((ymid-radx)<(MIN_Y+8))
		radx=ymid-(MIN_Y+8);
	/*circle(xmid,ymid,radx);*/
	algospiral(xmid,ymid,radx,radx);
}


void drawcircle()
{
	int x1,y1,x2,y2,color,xmid,ymid;
	float radx;
	x1 = mousex;
	y1 = mousey;
	setwritemode(XOR_PUT);
	while(LeftButtonPressed)
	{
		disp_coord();
		x2 = mousex;
		y2 = mousey;
		xmid = (x1 + x2)/2;
		ymid = (y1 + y2)/2;
		radx = abs((x2 - x1)/2);
		if (radx < 1)
			radx = 1;
		color = 15 - Current_Color;
		setcolor(color);
		if((xmid+radx)>(MAX_X-2))
			radx=(MAX_X-2)-xmid;
		if((xmid-radx)<(MIN_X+2))
			radx=xmid-(MIN_X+2);
		if((ymid+radx)>(MAX_Y-2))
			radx=(MAX_Y-2)-ymid;
		if((ymid-radx)<(MIN_Y+2))
			radx=ymid-(MIN_Y+2);
		algoellipse(xmid,ymid,radx,radx);
/*		circle(xmid,ymid,radx);           */
		delay(20);
		getxy();
		if((xmid+radx)>(MAX_X-2))
			radx=(MAX_X-2)-xmid;
		if((xmid-radx)<(MIN_X+2))
			radx=xmid-(MIN_X+2);
		if((ymid+radx)>(MAX_Y-2))
			radx=(MAX_Y-2)-ymid;
		if((ymid-radx)<(MIN_Y+2))
			radx=ymid-(MIN_Y+2);
		algoellipse(xmid,ymid,radx,radx);
/*		circle(xmid,ymid,radx); */
	}
	setwritemode(COPY_PUT);
	setcolor(Current_Color);
	x2 = mousex;
	y2 = mousey;
	xmid = (x1 + x2)/2;
	ymid = (y1 + y2)/2;
	radx = abs((x2 - x1)/2);

		if((xmid+radx)>(MAX_X-2))
			radx=(MAX_X-2)-xmid;
		if((xmid-radx)<(MIN_X+2))
			radx=xmid-(MIN_X+2);
		if((ymid+radx)>(MAX_Y-2))
			radx=(MAX_Y-2)-ymid;
		if((ymid-radx)<(MIN_Y+2))
			radx=ymid-(MIN_Y+2);
		/*circle(xmid,ymid,radx);*/
		algoellipse(xmid,ymid,radx,radx);
}

void save()
{
	char* name;
	FILE* out;
	char ch;
	int  row,col;
	int  byte;

	if(strcmp(FileName,"Untitled")==0)
	{
		name=readline("Save File As  : ");
		if(name==NULL) return;
	}
	else
	{	name=(char*)malloc(strlen(FileName)+1);
		strcpy(name,FileName);
	}

	out=fopen(name,"w");
	if(out==NULL)
	{
		ShowStatus(" Error Opening File !");
		delay(1000);
		ClearStatus();
		return;
	}

	ShowStatus(" Saving File...... ");

	for(row=MIN_Y+2;row<=MAX_Y-2;++row)
	{
		for(col=MIN_X+2;col<=MAX_X-2;)
		{
			byte=getpixel(col,row);
			byte=byte<<4;
			col++;
			byte+=getpixel(col,row);
			col++;
			if(fputc(byte,out)==EOF)
			{
				ShowStatus("Error Writing FIle ! ");
				delay(1000);
				ClearStatus();
				free(name);
				fclose(out);
			}
		}
	}
	ClearStatus();
	strcpy(FileName,name);
	disp_filename();
	free(name);
	fclose(out);
	saved=1;

}

char* readline(char* msg)
{
	char* Line;
	char  temp[40];
	char  Disp_Line[60];
	char ch;
	int i=0,length=0;
	int max=((475-12)-strlen(msg)*8)/8;/*/ find maximum number of characters*/

	ClearStatus();
	setcolor(BLACK);
	outtextxy(12,464,msg);
	strcpy(Disp_Line,msg);

	ch=getch();
	while( (ch!=27)&& (ch!=13))
	{
		switch (ch)
		{
		case '\b'  : if(i==0)
				beep();
			  else
			  {
				i--;
				ClearStatus();
				length=strlen(Disp_Line);
				Disp_Line[length-1]='\0';
				setcolor(BLACK);
				outtextxy(12,464,Disp_Line);

			  }

			  break;
		default : if(i > max)
				beep();
			  else
			  {
				length=strlen(Disp_Line);
				Disp_Line[length]=ch;
				Disp_Line[length+1]='\0';
				outtextxy(12,464,Disp_Line);
				temp[i++]=ch;
			  }
			  break;
		}
		ch=getch();
	}

	temp[i]='\0';
	ClearStatus();
	if(ch==27)
		return NULL;
	else
	{
		Line=(char*)malloc(strlen(temp)+1);
		strcpy(Line,temp);
	}
	return Line;
}

void Load()
{
	FILE* in;
	char* name;
	char ch;
	int byte;
	int row,col;
	int temp;

	if(!saved)
	{
		ShowStatus(" Save Current File ? ");
		ch=getch();
		if(ch=='y'||ch=='Y')
		{
			save();
		}
	}

	name=readline(" Enter File To Load : ");
	if(name==NULL)
		return;

	in=fopen(name,"r");
	if(fopen==NULL)
	{
		ShowStatus(" Error Opening File ");
		delay(1000);
		ClearStatus();
		return;
	}

	byte=fgetc(in);

	for(row=MIN_Y+2;row<=MAX_Y-2;row++)
	{
		for(col=MIN_X+2;col<=MAX_X-2;)
		{
			temp=(byte&0xf0)>>4;
			putpixel(col,row,temp);
			col++;
			temp=(byte&0x0f);
			putpixel(col,row,temp);
			col++;
			byte=fgetc(in);
			if(byte==EOF)
			{
				ClearStatus();
				return;
			}
		}
	}
	strcpy(FileName,name);
	disp_filename();
	free(name);
	fclose(in);
	saved=1;
}
void mark()
{
	int color=15-BLACK;
	int x,y;

	if(marked)
		unmark();

	setcolor(color);
	setwritemode(XOR_PUT);

	x=mousex;
	y=mousey;

	setlinestyle(DOTTED_LINE,1,1);
	while(LeftButtonPressed)
	{
		disp_coord();
		rectangle(x,y,mousex,mousey);
		getxy();
		rectangle(x,y,mousex,mousey);
	}
	setlinestyle(SOLID_LINE,1,1);

	if(x<mousex)
	{
		marker.left=x;
		marker.right=mousex;
		if(y<mousey)
		{
			marker.top=y;
			marker.bottom=mousey;
		}
		else
		{
			marker.top=mousey;
			marker.bottom=y;
		}
	}
	else
	{
		marker.left=mousex;
		marker.right=x;
		if(y<mousey)
		{
			marker.top=y;
			marker.bottom=mousey;
		}
		else
		{
			marker.top=mousey;
			marker.bottom=y;
		}
	}
	marked=1;
	setwritemode(COPY_PUT);
}

void unmark()
{
	int color=15-BLACK;
	setcolor(color);
	setwritemode(XOR_PUT);
	setlinestyle(DOTTED_LINE,1,1);
	rectangle(marker.left,marker.top,marker.right,marker.bottom);
	setlinestyle(SOLID_LINE,1,1);
	setwritemode(COPY_PUT);
	marked=0;

}

void translate()
{
	int left,right,bottom,top;
	int diffx,diffy;
	int color=15-BLACK;
	char* image;
	int   size;


	if(!marked) return;
	if(check_mouse_on(marker.left,marker.top,marker.right,marker.bottom))
	{
		setwritemode(XOR_PUT);
		setcolor(color);
		setlinestyle(DOTTED_LINE,1,1);

		left=marker.left;
		right=marker.right;
		top=marker.top;
		bottom=marker.bottom;

		while(LeftButtonPressed)
		{
			rectangle(left,top,right,bottom);
			getxy();
			diffx=prevx-mousex;
			diffy=prevy-mousey;
			left=left-diffx;
			right=right-diffx;
			bottom=bottom-diffy;
			top=top-diffy;
			if( (left<MIN_X+2)||(right>MAX_X-2)||(top<MIN_Y+2)||(bottom>MAX_Y-2) )
			{
				left=left+diffx;
				right=right+diffx;
				bottom=bottom+diffy;
				top=top+diffy;
			}
			rectangle(left,top,right,bottom);
		}

		marked=0;
		setwritemode(COPY_PUT);
		size=imagesize(marker.left,marker.top,marker.right,marker.bottom);
		if(size!=-1)
		{
			image=(char*)malloc(size);
			if(image!=NULL)
			{
				getimage(marker.left,marker.top,marker.right,marker.bottom,image);
				setfillstyle(SOLID_FILL,WHITE);
				bar(marker.left,marker.top,marker.right,marker.bottom);
				putimage(left,top,image,COPY_PUT);
				free(image);
			}
			else
			{
				ShowStatus(" No Memory! ");
				delay(1000);
				ClearStatus();
			}
		}
		else
		{
			ShowStatus(" No Memory! ");
			delay(1000);
			ClearStatus();
		}
		setlinestyle(SOLID_LINE,1,1);
	}
}
void rotate()
{
	char* charangle;
	int angle;
	float rad;
	int x,y;
	int xf=marker.left;/*/(marker.left-marker.right)/2+marker.left;*/
	int yf=marker.bottom;/*/(marker.bottom-marker.top)/2+marker.top;  */
	int row,col;
	int pixel;
	FILE* temp; /* added code*/

	if(!marked) return;

	charangle=readline(" Enter The Angle Of Rotation (?90,?180,?270) : ");
	if(charangle==NULL) return;
	angle=atoi(charangle);
	temp=fopen("work","w");
		if(temp==NULL)
		{
			ShowStatus("Cannot Proceed!");
			delay(1000);
			ClearStatus();
			return;
		}

		for(row=marker.top+1;row<marker.bottom;++row)
		{
			for(col=marker.left+1;col<marker.right;++col)
			{
				pixel=getpixel(col,row);
				fputc(pixel,temp);
			}
		}
		fclose(temp);

		temp=fopen("work","r");
		if(temp==NULL)
		{
			ShowStatus(" Cannot Proceed ! ");
			delay(1000);
			ClearStatus();
			return;
		}
/*	 added code ends */
	rad=angle*M_PI/180.0;

	unmark();
	setwritemode(COPY_PUT);
	for(row=marker.top;row<=marker.bottom;++row)
		for(col=marker.left;col<=marker.right;++col)
			putpixel(col,row,WHITE);
	for(row=marker.top+1;row<marker.bottom;++row)
	{
		for(col=marker.left+1;col<marker.right;++col)
		{
			pixel=fgetc(temp);
			x=ceil((1-cos(rad))*(xf)+sin(rad)*(yf)+col*cos(rad)-row*sin(rad));
			y=ceil((1-cos(rad))*(yf)-sin(rad)*(xf)+col*sin(rad)+row*cos(rad));
			if(x>=MIN_X+2&&x<=MAX_X-2&&y>=MIN_Y+2&&y<=MAX_Y-2)
			{
				putpixel(x,y,pixel);
				putpixel(x+1,y,pixel);
				putpixel(x,y+1,pixel);
				putpixel(x,y-1,pixel);
				putpixel(x-1,y,pixel);
			}

		 }
	}

}
void clip()
{
	int i,j;
	if(!marked) return;

	unmark();
	for(j=MIN_Y+2;j<=MAX_Y-2;++j)
	{
		for(i=MIN_X+2;i<=MAX_X-2;++i)
		{
			if( (i>=marker.left&&i<=marker.right) &&( j>=marker.top && j<=marker.bottom ) )
			{
			}
			else
			putpixel(i,j,WHITE);
		}
	}
}
int over(int x,int y,int w,int h)
{
int x1,y1;

  x1=x+w;
  y1=y+h;
wheremouse(&mousex,&mousey);

	if( (mousex>x) && (mousex<x1) && (mousey>y) && (mousey <y1) )
		return 1;
	else
		return 0;
}