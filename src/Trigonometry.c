//
// Created by Decimation on 4/7/2018.
//

#include "Trigonometry.h"
#include "MathLib.h"
#include "TrigMath.h"

/**
 * For non-right triangles
 *
 * todo: Right triangles to come soon
 */

static superpoint_t xangles[3] = {
		{{30,       119 - 10}, "A"},   // AAA
		{{10 + 155, 119 - 10}, "B"},   // BBB
		{{140 - 14, 32},       "C"}   // CCC
};

static superpoint_t xsides[3] = {
		{{10 + 180, 60},  "a"},  // aaa
		{{20,       60},  "b"},  // bbb
		{{140 - 45, 130}, "c"}   // ccc
};

static const char lbl_AngleMode[] = "ANGLE MODE";
static const char lbl_SideMode[]  = "SIDE MODE";
static const char lbl_SSS[]       = "SSS";
static const char lbl_SSA[]       = "SSA (!)";
static const char lbl_SAS[]       = "SAS";
static const char lbl_AAS[]       = "AAS";
static const char lbl_ASA[]       = "ASA";

static triangle_t   triangle;
static trigstatus_t trigstatus;

static superpoint_t       ui_Mode      = {{230, 10}, "ANGLE MODE"};
static superpoint_t       ui_Type      = {{230, 20}, "..."};
static const superpoint_t ui_btn_Mode  = {280, 230, "Mode"};
static const superpoint_t ui_btn_Clear = {215, 230, "Clear"};

static superpoint_t xanglesData[3] = {
		{10, 155, "A = "},
		{10, 175, "B = "},
		{10, 195, "C = "}
};

static superpoint_t xsidesData[3] = {
		{130, 155, "a = "},
		{130, 175, "b = "},
		{130, 195, "c = "}
};

static superpoint_t data_X_ex = {10, 215, "*X = "};

void ClearTrianglePoints()
{
	int index = 0;
	for (; index < 3; index++)
	{
		gfx_Clear(&xangles[index]);
		gfx_Clear(&xsides[index]);
	}
}

void RedrawTriangle()
{
	int index = 0;
	ClearTrianglePoints();
	for (index = 0; index < 3; index++)
	{
		gfx_Print(&xangles[index]);
		gfx_Print(&xsides[index]);

		dbg_sprintf(dbgout, "[%s, %s]\n", xangles[index].label, xsides[index].label);
	}
}

void dbg_printTriangle()
{
	char buf[20];
	os_RealToStr(buf, &triangle.A, 0, 0, -1);
	dbg_sprintf(dbgout, "Angle A: %s | ", buf);
	os_RealToStr(buf, &triangle.a, 0, 0, -1);
	dbg_sprintf(dbgout, "Side a: %s\n", buf);

	os_RealToStr(buf, &triangle.B, 0, 0, -1);
	dbg_sprintf(dbgout, "Angle B: %s | ", buf);
	os_RealToStr(buf, &triangle.b, 0, 0, -1);
	dbg_sprintf(dbgout, "Side b: %s\n", buf);

	os_RealToStr(buf, &triangle.C, 0, 0, -1);
	dbg_sprintf(dbgout, "Angle C: %s | ", buf);
	os_RealToStr(buf, &triangle.c, 0, 0, -1);
	dbg_sprintf(dbgout, "Side c: %s\n", buf);

	dbg_sprintf(dbgout, "Angle availability: [%s, %s, %s]\n", trigstatus.A ? "1" : "0", trigstatus.B ? "1" : "0",
				trigstatus.C ? "1" : "0");
	dbg_sprintf(dbgout, "Side availability: [%s, %s, %s]\n", trigstatus.a ? "1" : "0", trigstatus.b ? "1" : "0",
				trigstatus.c ? "1" : "0");
}

void RoundTriangle(uint8_t places)
{
	int i = 0;
	real_t* mem = (real_t*) &triangle;
	for (; i < 6; i++)
	{
		os_RealRound(&mem[i], places);
		dbg_sprintf(dbgout, "Rounded real_t memory @ 0x%p\n", &mem[i]);
	}
}

void Synchronize()
{
	dbg_sprintf(dbgout, "Synchronizing...\n");
	RoundTriangle(ROUND);
	dbg_sprintf(dbgout, "Rounded\n");

	if (trigstatus.A)
	{
		os_RealToStr(xangles[0].label, &triangle.A, 0, 0, 6);
	}
	if (trigstatus.B)
	{
		os_RealToStr(xangles[1].label, &triangle.B, 0, 0, 6);
	}
	if (trigstatus.C)
	{
		os_RealToStr(xangles[2].label, &triangle.C, 0, 0, 6);
	}
	if (trigstatus.a)
	{
		os_RealToStr(xsides[0].label, &triangle.a, 0, 0, 6);
	}
	if (trigstatus.b)
	{
		os_RealToStr(xsides[1].label, &triangle.b, 0, 0, 6);
	}
	if (trigstatus.c)
	{
		os_RealToStr(xsides[2].label, &triangle.c, 0, 0, 6);
	}

	disp_TriangleData();
	TruncateLabels(DIGIT_THRESHOLD);
	dbg_sprintf(dbgout, "Truncated labels\n");
	RedrawTriangle();
}

void trig_SolveSSS()
{
	real_t buf;
	real_t real180 = os_Int24ToReal(180);
	dbg_sprintf(dbgout, "[DECIMATH] [Trig] Solving SSS triangle\n");
	triangle.A   = loc_AngleA(triangle.b, triangle.c, triangle.a);
	trigstatus.A = true;
	dbg_sprintf(dbgout, "[DECIMATH] [Trig] Solved for angle A\n");

	triangle.B   = loc_AngleB(triangle.c, triangle.a, triangle.b);
	trigstatus.B = true;
	dbg_sprintf(dbgout, "[DECIMATH] [Trig] Solved for angle B\n");

	buf = os_RealAdd(&triangle.A, &triangle.B);
	triangle.C   = os_RealSub(&real180, &buf);
	trigstatus.C = true;
	dbg_sprintf(dbgout, "[DECIMATH] [Trig] Solved for angle C\n");

	Synchronize();
}

void trig_SolveMissingAngle()
{
	const real_t real180 = os_Int24ToReal(180);
	real_t       buf;

	if (trigstatus.A && trigstatus.B)
	{
		buf = os_RealAdd(&triangle.A, &triangle.B);
		triangle.C   = os_RealSub(&real180, &buf);
		trigstatus.C = true;
	}
	else if (trigstatus.A && trigstatus.C)
	{
		buf = os_RealAdd(&triangle.A, &triangle.C);
		triangle.B   = os_RealSub(&real180, &buf);
		trigstatus.B = true;
	}
	else if (trigstatus.B && trigstatus.C)
	{
		buf = os_RealAdd(&triangle.B, &triangle.C);
		triangle.A   = os_RealSub(&real180, &buf);
		trigstatus.A = true;
	}
}

void TruncateLabels(int len)
{
	int i = 0;
	for (; i < 3; i++)
	{
		StrCut(xangles[i].label, len, 20 - len);
	}
	for (i = 0; i < 3; i++)
	{
		StrCut(xsides[i].label, len, 20 - len);
	}
}

void trig_CheckSolvability()
{
	real_t       rbuf;
	char         cbuf[20];
	char cbuf2[20];
	const real_t real180 = os_Int24ToReal(180);
	dbg_sprintf(dbgout, "[DECIMATH] [Trig] Checking solvability...\n");
	disp_TriangleData();

	if (trigstatus.complete) return;

	// SSS
	if (trigstatus.a && trigstatus.b && trigstatus.c)
	{
		dbg_sprintf(dbgout, "SSS detected [%s, %s, %s]\n", xsides[0].label, xsides[1].label, xsides[2].label);
		gfx_Clear(&ui_Type);
		//type.label = "SSS";
		sp_SetLabel(&ui_Type, lbl_SSS);
		gfx_PrintColor(&ui_Type, gfx_green);
		trig_SolveSSS();
		trigstatus.complete = true;
		return;
	}

	// AAS
	// "AAS" is when we know two angles and one side (which is not between the angles).
	if (trigstatus.A && trigstatus.C && trigstatus.c)
	{
		dbg_sprintf(dbgout, "AAS_1 detected [%s, %s, %s]\n", xangles[0].label, xangles[2].label, xsides[2].label);
		gfx_Clear(&ui_Type);
		sp_SetLabel(&ui_Type, lbl_AAS);
		gfx_PrintColor(&ui_Type, gfx_green);

		trig_SolveMissingAngle();
		triangle.a   = los_Side_x(triangle.A, triangle.c, triangle.C);
		trigstatus.a = true;
		triangle.b   = los_Side_x(triangle.B, triangle.a, triangle.A);
		trigstatus.b = true;
		Synchronize();
		trigstatus.complete = true;
		return;
	}
	else if (trigstatus.B && trigstatus.C && trigstatus.b)
	{
		dbg_sprintf(dbgout, "AAS_2 detected [%s, %s, %s]\n", xangles[1].label, xangles[2].label, xsides[1].label);
		gfx_Clear(&ui_Type);
		sp_SetLabel(&ui_Type, lbl_AAS);
		gfx_PrintColor(&ui_Type, gfx_green);

		trig_SolveMissingAngle();

		triangle.c   = los_Side_x(triangle.C, triangle.b, triangle.B);
		trigstatus.c = true;
		triangle.a   = los_Side_x(triangle.A, triangle.c, triangle.C);
		trigstatus.a = true;
		dbg_printTriangle();
		Synchronize();
		trigstatus.complete = true;
		return;
	}
	else if (trigstatus.A && trigstatus.B && trigstatus.b)
	{
		dbg_sprintf(dbgout, "AAS_3 detected [%s, %s, %s]\n", xangles[0].label, xangles[1].label, xsides[1].label);
		gfx_Clear(&ui_Type);
		sp_SetLabel(&ui_Type, lbl_AAS);
		gfx_PrintColor(&ui_Type, gfx_green);

		trig_SolveMissingAngle();
		triangle.c   = los_Side_x(triangle.C, triangle.b, triangle.B);
		trigstatus.c = true;
		triangle.a   = los_Side_x(triangle.A, triangle.b, triangle.B);
		trigstatus.a = true;
		Synchronize();
		trigstatus.complete = true;
		return;
	}

	// ASA
	// "ASA" is when we know two angles and a side between the angles.
	if (trigstatus.A && trigstatus.c && trigstatus.B)
	{
		dbg_sprintf(dbgout, "ASA_1 detected [%s, %s, %s]\n", xangles[0].label, xsides[2].label, xangles[1].label);
		gfx_Clear(&ui_Type);
		sp_SetLabel(&ui_Type, lbl_ASA);
		gfx_PrintColor(&ui_Type, gfx_green);

		trig_SolveMissingAngle();
		triangle.a   = los_Side_x(triangle.A, triangle.c, triangle.C);
		trigstatus.a = true;
		triangle.b   = los_Side_x(triangle.B, triangle.c, triangle.C);
		trigstatus.b = true;
		Synchronize();
		trigstatus.complete = true;
		return;
	}
	else if (trigstatus.A && trigstatus.b && trigstatus.C) //todo: verify
	{
		dbg_sprintf(dbgout, "ASA_2 detected [%s, %s, %s]\n", xangles[0].label, xsides[1].label, xangles[2].label);
		gfx_Clear(&ui_Type);
		sp_SetLabel(&ui_Type, lbl_ASA);
		gfx_PrintColor(&ui_Type, gfx_green);

		trig_SolveMissingAngle();
		triangle.a   = los_Side_x(triangle.A, triangle.b, triangle.B);
		trigstatus.a = true;
		triangle.c   = los_Side_x(triangle.C, triangle.b, triangle.B);
		trigstatus.c = true;
		Synchronize();
		trigstatus.complete = true;
		return;
	}
	else if (trigstatus.B && trigstatus.a && trigstatus.C) //todo: verify
	{
		dbg_sprintf(dbgout, "ASA_3 detected [%s, %s, %s]\n", xangles[1].label, xsides[0].label, xangles[2].label);
		gfx_Clear(&ui_Type);
		sp_SetLabel(&ui_Type, lbl_ASA);
		gfx_PrintColor(&ui_Type, gfx_green);

		trig_SolveMissingAngle();
		triangle.b   = los_Side_x(triangle.B, triangle.a, triangle.A);
		trigstatus.b = true;
		triangle.c   = los_Side_x(triangle.C, triangle.a, triangle.A);
		trigstatus.c = true;
		Synchronize();
		trigstatus.complete = true;
		return;
	}

	// SAS
	// "SAS" is when we know two sides and the angle between them.
	if (trigstatus.b && trigstatus.A && trigstatus.c)
	{
		dbg_sprintf(dbgout, "SAS_1 detected [%s, %s, %s]\n", xsides[1].label, xangles[0].label, xsides[2].label);
		gfx_Clear(&ui_Type);
		sp_SetLabel(&ui_Type, lbl_SAS);
		gfx_PrintColor(&ui_Type, gfx_green);

		triangle.a   = loc_Side_x(triangle.b, triangle.c, triangle.A);
		trigstatus.a = true;

		// todo: need to find the smaller of the two angles
		triangle.B   = los_Angle_x(triangle.b, triangle.A, triangle.a);
		trigstatus.B = true;

		trig_SolveMissingAngle();
		Synchronize();
		trigstatus.complete = true;
		return;
	}
	else if (trigstatus.c && trigstatus.B && trigstatus.a) //todo: verify
	{
		dbg_sprintf(dbgout, "SAS_2 detected [%s, %s, %s]\n", xsides[2].label, xangles[1].label, xsides[0].label);
		gfx_Clear(&ui_Type);
		sp_SetLabel(&ui_Type, lbl_SAS);
		gfx_PrintColor(&ui_Type, gfx_green);

		triangle.b   = loc_Side_x(triangle.a, triangle.c, triangle.B);
		trigstatus.b = true;

		// todo: need to find the smaller of the two angles
		triangle.A   = los_Angle_x(triangle.a, triangle.B, triangle.b);
		trigstatus.A = true;

		trig_SolveMissingAngle();
		Synchronize();
		trigstatus.complete = true;
		return;
	}
	else if (trigstatus.b && trigstatus.C && trigstatus.a)
	{
		dbg_sprintf(dbgout, "SAS_3 detected [%s, %s, %s]\n", xsides[1].label, xangles[2].label, xsides[0].label);
		gfx_Clear(&ui_Type);
		sp_SetLabel(&ui_Type, lbl_SAS);
		gfx_PrintColor(&ui_Type, gfx_green);

		triangle.c   = loc_Side_x(triangle.a, triangle.b, triangle.C);
		trigstatus.c = true;

		// todo: need to find the smaller of the two angles
		triangle.A   = los_Angle_x(triangle.a, triangle.C, triangle.c);
		trigstatus.A = true;

		trig_SolveMissingAngle();
		Synchronize();
		trigstatus.complete = true;
		return;
	}

	// SSA
	// "SSA" is when we know two sides and an angle that is not the angle between the sides.
	// todo: check if it has multiple answers
	if (trigstatus.b && trigstatus.c && trigstatus.B)
	{
		dbg_sprintf(dbgout, "SSA_1 detected [%s, %s, %s]\n", xsides[1].label, xsides[2].label, xangles[1].label);
		gfx_Clear(&ui_Type);
		sp_SetLabel(&ui_Type, lbl_SSA);
		gfx_PrintColor(&ui_Type, gfx_green);
		trigstatus.isSSA = true;

		triangle.C   = los_Angle_x(triangle.c, triangle.B, triangle.b);
		trigstatus.C = true;

		trig_SolveMissingAngle();

		triangle.a   = los_Side_x(triangle.A, triangle.c, triangle.C);
		trigstatus.a = true;

		// other possible answer for C
		rbuf = os_RealSub(&real180, &triangle.C);
		os_RealToStr(cbuf, &rbuf, 0, 0, 6);

		sprintf(cbuf2, "*C = %s", cbuf);
		sp_SetLabel(&data_X_ex, cbuf2);
		gfx_Clear(&data_X_ex);
		gfx_Print(&data_X_ex);
		dbg_sprintf(dbgout, "data_X_ex = %s\n", data_X_ex.label);
		dbg_sprintf(dbgout, "Other possible solution for C = %s\n", cbuf);
		Synchronize();
		trigstatus.complete = true;
		return;
	}
	else if (trigstatus.b && trigstatus.a && trigstatus.B) //todo: verify
	{
		dbg_sprintf(dbgout, "SSA_2 detected [%s, %s, %s]\n", xsides[1].label, xsides[0].label, xangles[1].label);
		gfx_Clear(&ui_Type);
		sp_SetLabel(&ui_Type, lbl_SSA);
		gfx_PrintColor(&ui_Type, gfx_green);
		trigstatus.isSSA = true;

		triangle.C   = los_Angle_x(triangle.c, triangle.B, triangle.b);
		trigstatus.C = true;

		trig_SolveMissingAngle();

		triangle.c   = los_Side_x(triangle.C, triangle.b, triangle.B);
		trigstatus.c = true;

		// other possible answer for C
		rbuf = os_RealSub(&real180, &triangle.C);
		os_RealToStr(cbuf, &rbuf, 0, 0, 6);

		sprintf(cbuf2, "*C = %s", cbuf);
		sp_SetLabel(&data_X_ex, cbuf2);
		gfx_Clear(&data_X_ex);
		gfx_Print(&data_X_ex);
		dbg_sprintf(dbgout, "data_X_ex = %s\n", data_X_ex.label);
		dbg_sprintf(dbgout, "Other possible solution for C = %s\n", cbuf);
		Synchronize();
		trigstatus.complete = true;
		return;
	}
	else if (trigstatus.a && trigstatus.c && trigstatus.C) //todo: verify
	{
		dbg_sprintf(dbgout, "SSA_3 detected [%s, %s, %s]\n", xsides[0].label, xsides[2].label, xangles[2].label);
		gfx_Clear(&ui_Type);
		sp_SetLabel(&ui_Type, lbl_SSA);
		gfx_PrintColor(&ui_Type, gfx_green);
		trigstatus.isSSA = true;

		triangle.B   = los_Angle_x(triangle.a, triangle.C, triangle.c);
		trigstatus.B = true;

		trig_SolveMissingAngle();

		triangle.b   = los_Side_x(triangle.B, triangle.c, triangle.C);
		trigstatus.b = true;

		// other possible answer for B
		rbuf = os_RealSub(&real180, &triangle.B);
		os_RealToStr(cbuf, &rbuf, 0, 0, 6);

		sprintf(cbuf2, "*B = %s", cbuf);
		sp_SetLabel(&data_X_ex, cbuf2);
		gfx_Clear(&data_X_ex);
		gfx_Print(&data_X_ex);
		dbg_sprintf(dbgout, "data_X_ex = %s\n", data_X_ex.label);
		dbg_sprintf(dbgout, "Other possible solution for B = %s\n", cbuf);
		Synchronize();
		trigstatus.complete = true;
		return;
	}
}

void SelectSide()
{
	uint8_t key;
	superpoint_t* currentSelection = &xsides[1]; // start at b
	gfx_HighlightPoint(&xsides[1]);
	RECURSE:
	while ((key = os_GetCSC()) != sk_Enter)
	{
		if (key == sk_Clear)
		{
			return;
		}

		if (key == sk_Trace)
		{
			trig_Reset();
			currentSelection = &xsides[1];
			gfx_HighlightPoint(&xsides[1]);
		}

		if (key == sk_Graph)
		{
			gfx_Clear(&ui_Mode);
			//mode.label = "ANGLE MODE";
			sp_SetLabel(&ui_Mode, lbl_AngleMode);
			gfx_Print(&ui_Mode);
			gfx_ClearHighlight(currentSelection);
			SelectAngle();
			return;
		}

		/* bbb -> aaa */
		if (key == sk_Right && PointEq(*currentSelection, xsides[1]))
		{
			gfx_ClearHighlight(&xsides[1]);
			gfx_HighlightPoint(&xsides[0]);
			currentSelection = &xsides[0];
		}

		/* bbb -> ccc */
		if (key == sk_Down && PointEq(*currentSelection, xsides[1]))
		{
			gfx_ClearHighlight(&xsides[1]);
			gfx_HighlightPoint(&xsides[2]);
			currentSelection = &xsides[2];
		}

		/* ccc -> bbb */
		if ((key == sk_Up || key == sk_Left) && PointEq(*currentSelection, xsides[2]))
		{
			gfx_ClearHighlight(&xsides[2]);
			gfx_HighlightPoint(&xsides[1]);
			currentSelection = &xsides[1];
		}

		/* ccc -> aaa */
		if (key == sk_Right && PointEq(*currentSelection, xsides[2]))
		{
			gfx_ClearHighlight(&xsides[2]);
			gfx_HighlightPoint(&xsides[0]);
			currentSelection = &xsides[0];
		}

		/* aaa -> bbb */
		if (key == sk_Left && PointEq(*currentSelection, xsides[0]))
		{
			gfx_ClearHighlight(&xsides[0]);
			gfx_HighlightPoint(&xsides[1]);
			currentSelection = &xsides[1];
		}

		/* aaa -> ccc */
		if (key == sk_Down && PointEq(*currentSelection, xsides[0]))
		{
			gfx_ClearHighlight(&xsides[0]);
			gfx_HighlightPoint(&xsides[2]);
			currentSelection = &xsides[2];
		}
	}

	if (PointEq(*currentSelection, xsides[0]))
	{
		dbg_sprintf(dbgout, "[DECIMATH] [Trig] User selected side %s\n", xsides[0].label);
		triangle.a   = io_gfx_ReadReal(&xsides[0]);
		trigstatus.a = true;
	}

	if (PointEq(*currentSelection, xsides[1]))
	{
		dbg_sprintf(dbgout, "[DECIMATH] [Trig] User selected side %s\n", xsides[1].label);
		triangle.b   = io_gfx_ReadReal(&xsides[1]);
		trigstatus.b = true;
	}

	if (PointEq(*currentSelection, xsides[2]))
	{
		dbg_sprintf(dbgout, "[DECIMATH] [Trig] User selected side %s\n", xsides[2].label);
		triangle.c   = io_gfx_ReadReal(&xsides[2]);
		trigstatus.c = true;
	}

	trig_CheckSolvability();
	gfx_HighlightPoint(currentSelection);
	goto RECURSE;

}

void trig_Quit()
{
	gfx_ZeroScreen();
	gfx_End();
	dbg_sprintf(dbgout, "[DECIMATH] [Trig] Zeroed screen and ended GFX\n");
}

void trig_Reset()
{
	int   i = 0;
	bool  * bptr = (bool*) &trigstatus;
	real_t* rptr = (real_t*) &triangle;
	for (; i < sizeof(trigstatus) / sizeof(bool); i++)
	{
		bptr[i] = false;
	}
	for (i = 0; i < sizeof(triangle) / sizeof(real_t); i++)
	{
		rptr[i] = os_Int24ToReal(0);
	}
	for (i = 0; i < 3; i++)
	{
		gfx_Clear(&xanglesData[i]);
		mem_Zero(xanglesData[i].label + 4, 16);
	}
	for (i = 0; i < 3; i++)
	{
		gfx_Clear(&xsidesData[i]);
		mem_Zero(xsidesData[i].label + 4, 16);
	}
	gfx_Clear(&ui_Type);
	gfx_Clear(&data_X_ex);
	mem_Zero(data_X_ex.label + 4, 16);

	sp_SetLabel(&xangles[0], "A");
	sp_SetLabel(&xangles[1], "B");
	sp_SetLabel(&xangles[2], "C");
	sp_SetLabel(&xsides[0], "a");
	sp_SetLabel(&xsides[1], "b");
	sp_SetLabel(&xsides[2], "c");
	RedrawTriangle();
	gfx_DrawTriangleSides();
	Synchronize();
}

void gfx_DrawTriangleSides()
{
	int index = 0;

	/* Triangle coordinates */
	const int verts[6] = {
			140, 10,   /* (x0, y0) */
			10, 119,  /* (x1, y1) */
			209, 119, /* (x2, y2) */
	};

	/* Leg a */
	gfx_Line(verts[0], verts[1], verts[2], verts[3]);

	/* Leg b */
	gfx_Line(verts[2], verts[3], verts[4], verts[5]);

	/* Hypotenuse */
	gfx_Line(verts[4], verts[5], verts[0], verts[1]);


	// Angles A, B, C
	RedrawTriangle();

	// Leg a, b, c
	for (index = 0; index < 3; index++)
	{
		gfx_Print(&xsides[index]);
	}
}

void SelectAngle()
{
	uint8_t key;
	superpoint_t* currentSelection = &xangles[0];
	gfx_HighlightPoint(&xangles[0]);
	RECURSE:
	while ((key = os_GetCSC()) != sk_Enter)
	{
		if (key == sk_Clear)
		{
			return;
		}

		if (key == sk_Trace)
		{
			trig_Reset();
			currentSelection = &xangles[0];
			gfx_HighlightPoint(&xangles[0]);
		}

		if (key == sk_Graph)
		{
			gfx_Clear(&ui_Mode);
			//mode.label = "SIDE MODE";
			sp_SetLabel(&ui_Mode, lbl_SideMode);
			gfx_Print(&ui_Mode);
			gfx_ClearHighlight(currentSelection);
			SelectSide();
			return;
		}

		/* AAA -> BBB */
		if (key == sk_Right && PointEq(*currentSelection, xangles[0]))
		{
			gfx_ClearHighlight(&xangles[0]);
			gfx_HighlightPoint(&xangles[1]);
			currentSelection = &xangles[1];
		}

		/* AAA -> CCC */
		if (key == sk_Up && PointEq(*currentSelection, xangles[0]))
		{
			gfx_ClearHighlight(&xangles[0]);
			gfx_HighlightPoint(&xangles[2]);
			currentSelection = &xangles[2];
		}

		/* BBB -> AAA */
		if (key == sk_Left && PointEq(*currentSelection, xangles[1]))
		{
			gfx_ClearHighlight(&xangles[1]);
			gfx_HighlightPoint(&xangles[0]);
			currentSelection = &xangles[0];
		}

		/* BBB -> CCC */
		if (key == sk_Up && PointEq(*currentSelection, xangles[1]))
		{
			gfx_ClearHighlight(&xangles[1]);
			gfx_HighlightPoint(&xangles[2]);
			currentSelection = &xangles[2];
		}

		/* CCC -> AAA */
		if (key == sk_Left && PointEq(*currentSelection, xangles[2]))
		{
			gfx_ClearHighlight(&xangles[2]);
			gfx_HighlightPoint(&xangles[0]);
			currentSelection = &xangles[0];
		}

		/* CCC -> BBB */
		if (key == sk_Down && PointEq(*currentSelection, xangles[2]))
		{
			gfx_ClearHighlight(&xangles[2]);
			gfx_HighlightPoint(&xangles[1]);
			currentSelection = &xangles[1];
		}
	}

	if (PointEq(*currentSelection, xangles[0]))
	{
		dbg_sprintf(dbgout, "[DECIMATH] [Trig] User selected angle %s\n", xangles[0].label);
		triangle.A   = io_gfx_ReadReal(&xangles[0]);
		trigstatus.A = true;
	}

	if (PointEq(*currentSelection, xangles[1]))
	{
		dbg_sprintf(dbgout, "[DECIMATH] [Trig] User selected angle %s\n", xangles[1].label);
		triangle.B   = io_gfx_ReadReal(&xangles[1]);
		trigstatus.B = true;
	}

	if (PointEq(*currentSelection, xangles[2]))
	{
		dbg_sprintf(dbgout, "[DECIMATH] [Trig] User selected angle %s\n", xangles[2].label);
		triangle.C   = io_gfx_ReadReal(&xangles[2]);
		trigstatus.C = true;
	}

	trig_CheckSolvability();
	gfx_HighlightPoint(currentSelection);
	goto RECURSE;
}

void disp_TriangleData()
{


	int i = 0;
	for (; i < 3; i++)
	{
		if (*xsides[i].label == 'a' || *xsides[i].label == 'b' || *xsides[i].label == 'c')
			strcpy(xsidesData[i].label + 4, "?");
		else strcpy(xsidesData[i].label + 4, xsides[i].label);
		gfx_Clear(&xsidesData[i]);
		gfx_Print(&xsidesData[i]);
	}
	for (i = 0; i < 3; i++)
	{
		if (*xangles[i].label == 'A' || *xangles[i].label == 'B' || *xangles[i].label == 'C')
			strcpy(xanglesData[i].label + 4, "?");
		else strcpy(xanglesData[i].label + 4, xangles[i].label);
		gfx_Clear(&xanglesData[i]);
		gfx_Print(&xanglesData[i]);
	}
	if (trigstatus.isSSA) {
		gfx_Clear(&data_X_ex);
		gfx_Print(&data_X_ex);
	}
	else if (!trigstatus.isSSA) {
		gfx_Clear(&data_X_ex);
	}
}

void trig_SolveTriangle()
{
	os_ClrHome();

	gfx_Begin();
	gfx_SetColor(gfx_blue);
	gfx_SetTextFGColor(gfx_black);

	gfx_Print(&ui_Mode);
	gfx_Print(&ui_btn_Mode);
	gfx_Print(&ui_btn_Clear);

	//gfx_DrawTriangleSides();
	trig_Reset();

	SelectAngle();

	trig_Quit();
}