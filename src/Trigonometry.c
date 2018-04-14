//
// Created by Decimation on 4/7/2018.
//

#include "Trigonometry.h"
#include "../../../../../CEdev/include/graphx.h"

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

void trig_ClearAngle(char* str, gfx_point_t p)
{
	gfx_SetTextFGColor(gfx_black);
	print_t(str,p);

}

void White(char* str, gfx_point_t p)
{
	gfx_FillRectangle(p.x, p.y, gfx_GetStringWidth(str), 3);
	//print_t(str,p);
}

void trig_HighlightAngle(char* str, gfx_point_t p)
{
	gfx_SetTextFGColor(gfx_red);
	print_t(str,p);

}

bool PointEq(gfx_point_t a, gfx_point_t b) {
	return a.x == b.x && a.y == b.y;
}

void trig_SolveRightTriangle()
{

	uint8_t key;
	int     index = 0;
	gfx_point_t currentSelection;

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

	char* szAngles[3] = {
			"90",   // 90
			"BBB",   // BBB
			"AAA"    // AAA
	};

	const gfx_point_t sides[3] = {
			/* verts[2] + X, verts[3] + Y */
			{30 - 25, 129 - 50},  // bbb
			{30 + 50, 129 + 10},  // aaa
			{30 + 90, 129 - 70}   // ccc
	};

	char* szSides[3] = {
			"bbb",
			"aaa",
			"ccc"
	};


	os_ClrHome();

	gfx_Begin();

	gfx_SetColor(gfx_blue);
	gfx_SetTextFGColor(gfx_black);

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
	print_t(szAngles[0], angles[0]);

	/* Angle B */
	//gfx_PrintStringXY("BBB", angles[1].x, angles[1].y);
	print_t(szAngles[1], angles[1]);

	/* Angle A */
	//gfx_PrintStringXY("AAA", angles[2].x, angles[2].y);
	print_t(szAngles[2], angles[2]);


	/* Leg b */
	//gfx_PrintStringXY("bbb", sides[0].x, sides[0].y);
	print_t(szSides[0], sides[0]);

	/* Leg a */
	//gfx_PrintStringXY("aaa", sides[1].x, sides[1].y);
	print_t(szSides[1], sides[1]);

	/* Hypotenuse */
	//gfx_PrintStringXY("ccc", sides[2].x, sides[2].y);
	print_t(szSides[2], sides[2]);

	SELECT_ANGLE:
	currentSelection = angles[0];
	while ((key = os_GetCSC()) != sk_Enter)
	{
		/**
		 * const gfx_point_t angles[3] =
		 * [0] = 90
		 * [1] = BBB
		 * [2] = AAA
		 */

		/* 90 -> BBB */
		if (key == sk_Right && PointEq(currentSelection, angles[0])) {
			trig_ClearAngle(szAngles[0], angles[0]);

			trig_HighlightAngle(szAngles[1], angles[1]);
			currentSelection = angles[1];
		}

		/* 90 -> AAA */
		if (key == sk_Up && PointEq(currentSelection, angles[0])) {
			trig_ClearAngle(szAngles[0], angles[0]);

			trig_HighlightAngle(szAngles[2], angles[2]);
			currentSelection = angles[2];
		}

		/* AAA -> 90 */
		if (key == sk_Down && PointEq(currentSelection, angles[2])) {
			trig_ClearAngle(szAngles[2], angles[2]);

			trig_HighlightAngle(szAngles[0], angles[0]);
			currentSelection = angles[0];
		}

		/* AAA -> BBB */
		if (key == sk_Right && PointEq(currentSelection, angles[2])) {
			trig_ClearAngle(szAngles[2], angles[2]);

			trig_HighlightAngle(szAngles[1], angles[1]);
			currentSelection = angles[1];
		}

		/* BBB -> 90 */
		if (key == sk_Left && PointEq(currentSelection, angles[1])) {
			trig_ClearAngle(szAngles[1], angles[1]);

			trig_HighlightAngle(szAngles[0], angles[0]);
			currentSelection = angles[0];
		}

		/* BBB -> AAA */
		if (key == sk_Up && PointEq(currentSelection, angles[1])) {
			trig_ClearAngle(szAngles[1], angles[1]);

			trig_HighlightAngle(szAngles[2], angles[2]);
			currentSelection = angles[2];
		}
	}

	if (PointEq(currentSelection, angles[0])) {
		dbg_sprintf(dbgout, "[DECIMATH] [Trig] User selected angle 90, returning to angle selection\n");
		goto SELECT_ANGLE;
	}



	while (!os_GetCSC());
	gfx_ZeroScreen();
	gfx_End();

}