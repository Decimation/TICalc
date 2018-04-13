//
// Created by Decimation on 4/7/2018.
//

#include "Trigonometry.h"
#define TRANSPARENT_COLOR 10
void print_t(char* str, gfx_point_t p)
{
	gfx_PrintStringXY(str,p.x,p.y);
	/*while (*str)
	{
		gfx_Sprite(gfx_GetSpriteChar(*str), p.x, p.y);
		p.x += gfx_GetCharWidth(*str++);
	}*/
}

void clr(int len, gfx_point_t p)
{
	char buf[10];
	strncpy(buf,"\b", len);
	gfx_PrintStringXY(buf, p.x, p.y);
}

/*void clr(int len, gfx_point_t p)
{
	gfx_SetTextTransparentColor(gfx_white);
	gfx_SetTextBGColor(gfx_white);
	gfx_SetTextFGColor(gfx_white);
	while (len--)
	{
		gfx_Sprite(gfx_GetSpriteChar(' '), p.x, p.y);
		p.x += gfx_GetCharWidth(' ');
	}
}*/

void trig_HighlightAngle(char* str, gfx_point_t p)
{
	char buf[20];
	//gfx_SetTextBGColor(gfx_blue);

	clr(3, p);
	sprintf(buf, "[%s]", str);
	print_t(buf,p);


	//gfx_SetTextBGColor(gfx_white);
	//gfx_SetTextTransparentColor(gfx_black);
	//gfx_SetTextFGColor(gfx_black);
}

void trig_SolveRightTriangle()
{

	uint8_t key;
	int     index = 0;

	const gfx_point_t mode = {230, 10};

	/* Triangle coordinates */
	const int verts[6] = {
			30, 10,   /* (x0, y0) */
			30, 129,  /* (x1, y1) */
			189, 129, /* (x2, y2) */
	};

	const gfx_point_t angles[3] = {
			/* verts[2] + X, verts[3] + Y */
			{30 + 5,   129 - 10},   // 90
			{30 + 120, 129 - 10},   // BBB
			{30 + 3,   129 - 98}    // AAA
	};

	const gfx_point_t sides[3] = {
			/* verts[2] + X, verts[3] + Y */
			{30 - 25, 129 - 50},  // bbb
			{30 + 50, 129 + 10},  // aaa
			{30 + 90, 129 - 70}   // ccc
	};


	os_ClrHome();

	gfx_Begin();

	gfx_SetColor(gfx_blue);
	/* Set the transparent text background color */
	//gfx_SetTextBGColor(TRANSPARENT_COLOR);
	//gfx_SetTextTransparentColor(gfx_black);
	gfx_SetTextFGColor(gfx_black);
	//gfx_SetTextBGColor(gfx_white);

	//dbg_sprintf(dbgout, "[DECIMATH] (%d, %d) to (%d, %d)\n", verts[iv-1], verts[iv],verts[iv+1], verts[iv+2]);

	print_t("ANGLE MODE", mode);

	/* Leg a */
	gfx_Line(verts[0], verts[1], verts[2], verts[3]);

	/* Leg b */
	gfx_Line(verts[2], verts[3], verts[4], verts[5]);

	/* Hypotenuse */
	gfx_Line(verts[4], verts[5], verts[0], verts[1]);



	/* Angle C */
	//gfx_PrintStringXY("90", angles[0].x, angles[0].y);
	print_t("90", angles[0]);

	/* Angle B */
	//gfx_PrintStringXY("BBB", angles[1].x, angles[1].y);
	print_t("BBB", angles[1]);

	/* Angle A */
	//gfx_PrintStringXY("AAA", angles[2].x, angles[2].y);
	print_t("AAA", angles[2]);


	/* Leg b */
	//gfx_PrintStringXY("bbb", sides[0].x, sides[0].y);
	print_t("bbb", sides[0]);

	/* Leg a */
	//gfx_PrintStringXY("aaa", sides[1].x, sides[1].y);
	print_t("aaa", sides[1]);

	/* Hypotenuse */
	//gfx_PrintStringXY("ccc", sides[2].x, sides[2].y);
	print_t("ccc", sides[2]);

	while (!os_GetCSC());

	trig_HighlightAngle("90", angles[0]);

	while (!os_GetCSC());

	/*while ((key = os_GetCSC()) != sk_Enter)
	{
		if (key == sk_Left) {

		}
	}*/
	while (!os_GetCSC());
	gfx_ZeroScreen();
	gfx_End();

}