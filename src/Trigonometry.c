//
// Created by Decimation on 4/7/2018.
//

#include "Trigonometry.h"

real_t io_gfx_ReadReal(superpoint_t vBuffer)
{
	bool        isNeg    = false;
	uint8_t     key, i   = 0;
	real_t      rbuffer;
	static char lchars[] = "\0\0\0\0\0\0\0\0\0\0\"-RMH\0\0?[69LG\0\0.258KFC\0 147JEB\0\0XSNIDA\0\0\0\0\0\0\0\0";
	Zero(vBuffer.label, INPUT_SIZE);
	lchars[33] = '0';
	lchars[18] = '3';

	while ((key = os_GetCSC()) != sk_Enter)
	{

		if (key == sk_Del)
		{
			vBuffer.label[--i] = '\0';
			//io_ClearFirstLine();
			Clear(vBuffer);
			xprint(vBuffer);
		}

		if (key == 0x11)
		{
			dbg_sprintf(dbgout, "[DECIMATH] Negative sign keypress detected\n");
			rbuffer = os_StrToReal(vBuffer.label, NULL);
			rbuffer = os_RealNeg(&rbuffer);
			os_RealToStr(vBuffer.label, &rbuffer, 0, 0, -1);
			//io_ClearFirstLine();
			Clear(vBuffer);
			xprint(vBuffer);
			isNeg = true;
		}

		else if (lchars[key])
		{
			/*for (; x < sizeof(chars) -1; x++) {
				if (chars[key] == chars[x]) {
					sprintf(buffer, "%c | %d", chars[key], x);
					io_print(buffer,0,1);
				}
			}*/
			vBuffer.label[i++] = lchars[key];
			dbg_sprintf(dbgout, "[DECIMATH] [RAW_INPUT] [KEYCODE] 0x%X (%d) \n", key, key);
		}


		xprint(vBuffer);

	}
	if (isNeg)
	{
		return rbuffer;
	}
	else
	{
		return os_StrToReal(vBuffer.label, NULL);
	}
}

void xprint_col(superpoint_t p, uint8_t color)
{
	gfx_SetTextFGColor(color);
	gfx_PrintStringXY(p.label, p.point.x, p.point.y);
	gfx_SetTextFGColor(gfx_black);
}

void xprint(superpoint_t p)
{
	gfx_PrintStringXY(p.label, p.point.x, p.point.y);
}

void trig_ClearAngleX(superpoint_t p)
{
	//gfx_SetTextFGColor(gfx_black);
	xprint_col(p, gfx_black);
}

void Clear(superpoint_t p)
{
	gfx_SetColor(gfx_white);
	gfx_FillRectangle(p.point.x, p.point.y, gfx_GetStringWidth(p.label), 9);
	gfx_SetColor(gfx_blue);
}

void trig_HighlightAngleX(superpoint_t p)
{
	//gfx_SetTextFGColor(gfx_red);
	xprint_col(p, gfx_red);
}

bool PointEq(superpoint_t a, superpoint_t b)
{
	return a.point.x == b.point.x && a.point.y == b.point.y;
}

void sohcahtoa_DrawAAA(superpoint_t xsides_oah[3])
{
	int index = 0;
	// When angle AAA is selected
	xsides_oah[0].label = "ADJ"; // bbb
	xsides_oah[1].label = "OPP"; // aaa
	xsides_oah[2].label = "HYP"; // ccc

	for (index = 0; index < 3; index++)
	{
		xprint_col(xsides_oah[index], gfx_green);
	}
}

void sohcahtoa_DrawBBB(superpoint_t xsides_oah[3])
{
	int index = 0;
	// When angle BBB is selected
	xsides_oah[0].label = "OPP"; // bbb
	xsides_oah[1].label = "ADJ"; // aaa
	xsides_oah[2].label = "HYP"; // ccc

	for (index = 0; index < 3; index++)
	{
		xprint_col(xsides_oah[index], gfx_green);
	}
}

void RedrawAngles(const superpoint_t xangles[3])
{
	int index = 0;
	for (; index < 3; index++)
	{
		Clear(xangles[index]);
	}
	for (index = 0; index < 3; index++)
	{
		xprint(xangles[index]);
	}
}

void sohcahtoa_DrawNull(superpoint_t xsides_oah[3])
{
	int index = 0;
	// Draw nothing when 90 is selected
	xsides_oah[0].label = "BBB"; // bbb
	xsides_oah[1].label = "AAA"; // aaa
	xsides_oah[2].label = "CCC"; // ccc

	for (index = 0; index < 3; index++)
	{
		//xprint_col(xsides_oah[index], gfx_green);
		Clear(xsides_oah[index]);
	}
}

/**
 * todo: - add support for angle C ("90")
 *       - add support for sides
 */
void trig_SolveRightTriangle()
{
	real_t             buffer, buffer2;
	const real_t       real90 = os_Int24ToReal(90);
	uint8_t            key;
	int                index  = 0;
	superpoint_t       currentSelection;
	const superpoint_t mode   = {{230, 10}, "ANGLE MODE"};

	/* Triangle coordinates */
	const int verts[6] = {
			30, 10,   /* (x0, y0) */
			30, 129,  /* (x1, y1) */
			189, 129, /* (x2, y2) */
	};

	const superpoint_t xangles[3] = {
			/* verts[2] + X, verts[3] + Y */
			{{30 + 5,   129 - 10}, "90"},   // 90
			{{30 + 120, 129 - 10}, "BBB"},   // BBB
			{{30 + 3,   129 - 98}, "AAA"}   // AAA
	};

	const superpoint_t xsides[3] = {
			/* verts[2] + X, verts[3] + Y */
			{{30 - 25, 129 - 50}, "bbb"},  // bbb
			{{30 + 50, 129 + 10}, "aaa"},  // aaa
			{{30 + 90, 129 - 70}, "ccc"}   // ccc
	};

	superpoint_t xsides_oah[3] = {
			/* verts[2] + X, verts[3] + Y */
			{{30 - 25, 129 - 40}, "..."},  // bbb
			{{30 + 50, 129 + 20}, "..."},  // aaa
			{{30 + 90, 129 - 60}, "..."}   // ccc
	};


	os_ClrHome();

	gfx_Begin();

	gfx_SetColor(gfx_blue);
	gfx_SetTextFGColor(gfx_black);

	//dbg_sprintf(dbgout, "[DECIMATH] (%d, %d) to (%d, %d)\n", verts[iv-1], verts[iv],verts[iv+1], verts[iv+2]);

	xprint(mode);

	/* Leg a */
	gfx_Line(verts[0], verts[1], verts[2], verts[3]);

	/* Leg b */
	gfx_Line(verts[2], verts[3], verts[4], verts[5]);

	/* Hypotenuse */
	gfx_Line(verts[4], verts[5], verts[0], verts[1]);


	// Angles C, B, A
	RedrawAngles(xangles);

	// Leg b, a, c
	for (index = 0; index < 3; index++)
	{
		xprint(xsides[index]);
	}


	SELECT_ANGLE:
	currentSelection = xangles[0];
	trig_HighlightAngleX(xangles[0]);
	sohcahtoa_DrawNull(xsides_oah);
	while ((key = os_GetCSC()) != sk_Enter)
	{
		/**
		 * const gfx_point_t angles[3] =
		 * [0] = 90
		 * [1] = BBB
		 * [2] = AAA
		 */

		/**
		 * superpoint_t xsides_oah[3] =
		 * [0] = bbb
		 * [1] = aaa
		 * [2] = ccc
		 */

		/* 90 -> BBB */
		if (key == sk_Right && PointEq(currentSelection, xangles[0]))
		{
			trig_ClearAngleX(xangles[0]);
			trig_HighlightAngleX(xangles[1]);
			currentSelection = xangles[1];

			sohcahtoa_DrawBBB(xsides_oah);
		}

		/* 90 -> AAA */
		if (key == sk_Up && PointEq(currentSelection, xangles[0]))
		{
			trig_ClearAngleX(xangles[0]);
			trig_HighlightAngleX(xangles[2]);
			currentSelection = xangles[2];

			sohcahtoa_DrawAAA(xsides_oah);
		}

		/* AAA -> 90 */
		if (key == sk_Down && PointEq(currentSelection, xangles[2]))
		{
			trig_ClearAngleX(xangles[2]);
			trig_HighlightAngleX(xangles[0]);
			currentSelection = xangles[0];

			sohcahtoa_DrawNull(xsides_oah);
		}

		/* AAA -> BBB */
		if (key == sk_Right && PointEq(currentSelection, xangles[2]))
		{
			trig_ClearAngleX(xangles[2]);
			trig_HighlightAngleX(xangles[1]);
			currentSelection = xangles[1];

			sohcahtoa_DrawBBB(xsides_oah);
		}

		/* BBB -> 90 */
		if (key == sk_Left && PointEq(currentSelection, xangles[1]))
		{
			trig_ClearAngleX(xangles[1]);
			trig_HighlightAngleX(xangles[0]);
			currentSelection = xangles[0];

			sohcahtoa_DrawNull(xsides_oah);
		}

		/* BBB -> AAA */
		if (key == sk_Up && PointEq(currentSelection, xangles[1]))
		{
			trig_ClearAngleX(xangles[1]);
			trig_HighlightAngleX(xangles[2]);
			currentSelection = xangles[2];

			sohcahtoa_DrawAAA(xsides_oah);
		}
	}

	if (PointEq(currentSelection, xangles[0]))
	{
		dbg_sprintf(dbgout, "[DECIMATH] [Trig] User selected angle 90, returning to angle selection\n");
		goto SELECT_ANGLE;
	}

	if (PointEq(currentSelection, xangles[1]))
	{
		dbg_sprintf(dbgout, "[DECIMATH] [Trig] User selected angle %s\n", xangles[1].label);

		/* Solve for angle AAA */
		Clear(xangles[1]);
		Clear(xangles[2]);

		buffer = io_gfx_ReadReal(xangles[1]);
		os_RealToStr(xangles[1].label, &buffer, 0, 0, -1);

		buffer2 = os_RealSub(&real90, &buffer);
		os_RealToStr(xangles[2].label, &buffer2, 0, 0, -1);

		RedrawAngles(xangles);
	}

	if (PointEq(currentSelection, xangles[2]))
	{
		dbg_sprintf(dbgout, "[DECIMATH] [Trig] User selected angle %s\n", xangles[2].label);

		/* Solve for angle BBB */
		Clear(xangles[1]);
		Clear(xangles[2]);

		buffer = io_gfx_ReadReal(xangles[2]);
		os_RealToStr(xangles[2].label, &buffer, 0, 0, -1);

		buffer2 = os_RealSub(&real90, &buffer);
		os_RealToStr(xangles[1].label, &buffer2, 0, 0, -1);

		RedrawAngles(xangles);
	}


	while (!os_GetCSC());
	gfx_ZeroScreen();
	gfx_End();
	dbg_sprintf(dbgout, "[DECIMATH] [Trig] Zeroed screen and ended GFX\n");
}