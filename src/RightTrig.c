//
// Created by Decimation on 4/14/2018.
//

#include "RightTrig.h"
#include "GraphicsExt.h"
#include "Simplifiers.h"
#include "MathLib.h"

static superpoint_t xangles[3] = {
		/* verts[2] + X, verts[3] + Y */
		{{30 + 5,   129 - 10}, "90"},   // 90
		{{30 + 120, 129 - 10}, "BBB"},  // BBB
		{{30 + 3,   129 - 98}, "AAA"}   // AAA
};

static superpoint_t xsides[3] = {
		/* verts[2] + X, verts[3] + Y */
		{{30 - 25, 129 - 50}, "bbb"},  // bbb
		{{30 + 50, 129 + 10}, "aaa"},  // aaa
		{{30 + 90, 129 - 70}, "ccc"}   // ccc
};

static superpoint_t xsides_oah[3] = {
		/* verts[2] + X, verts[3] + Y */
		{{30 - 25, 129 - 40}, "..."},  // bbb
		{{30 + 50, 129 + 20}, "..."},  // aaa
		{{30 + 90, 129 - 60}, "..."}   // ccc
};

#define side_a xsides[1]
#define side_b xsides[0]
#define side_c xsides[2]

#define angle_A xangles[2]
#define angle_B xangles[1]
#define angle_C xangles[0]

static const superpoint_t ui_btn_Mode           = {280, 230, "Mode"};
static const superpoint_t ui_btn_Clear          = {215, 230, "Clear"};
static const superpoint_t ui_btn_EnableSimpRoot = {150, 230, "Root"};

static const char   ui_FuncFmt[] = "%s / %s";
static bool         ui_dispSimpRoot;
static superpoint_t ui_Wait      = {{230, 40}, "Processing..."};
static superpoint_t ui_Root      = {{230, 25}, "..."};
static superpoint_t ui_Mode      = {{230, 10}, "ANGLE MODE"};

static const char lbl_AngleMode[] = "ANGLE MODE";
static const char lbl_SideMode[]  = "SIDE MODE";
static const char lbl_ADJ[]       = "ADJ";
static const char lbl_HYP[]       = "HYP";
static const char lbl_OPP[]       = "OPP";

static triangle_t   triangle;
static trigstatus_t trigstatus;

static superpoint_t funcData[3] = {
		{10, 165, "sin = "},
		{10, 185, "cos = "},
		{10, 205, "tan = "}
};

static superpoint_t funcData2[3] = {
		{145, 165, "cot = "},
		{145, 185, "sec = "},
		{145, 205, "csc = "}
};


/**
 * xangles[0] = 90
 * xangles[1] = B
 * xangles[2] = A
 */

/**
 * xsides[0] = b
 * xsides[1] = a
 * xsides[2] = c
 */

void right_Sync()
{
	dbg_sprintf(dbgout, "Synchronizing right triangle...\n");
	right_RoundTriangle(2);
	if (trigstatus.A)
	{
		os_RealToStr(xangles[2].label, &triangle.A, 0, 0, 6);
	}
	if (trigstatus.B)
	{
		os_RealToStr(xangles[1].label, &triangle.B, 0, 0, 6);
	}
	if (trigstatus.a)
	{
		os_RealToStr(side_a.label, &triangle.a, 0, 0, 6);
	}
	if (trigstatus.b)
	{
		os_RealToStr(side_b.label, &triangle.b, 0, 0, 6);
	}
	if (trigstatus.c)
	{
		os_RealToStr(side_c.label, &triangle.c, 0, 0, 6);
	}


	right_TruncateLabels(4);
	Redraw();
}

void right_TruncateLabels(int len)
{
	int i = 0;
	for (; i < 3; i++)
	{
		StrCut(xangles[i].label, len, 20 - len);
		StrCut(xsides[i].label, len, 20 - len);
	}
}

void pythag_CheckSolvability()
{
	real_t       apow, bpow, cpow;
	const real_t real2 = os_Int24ToReal(2);


	if (trigstatus.a && trigstatus.b && !trigstatus.c)
	{
		//a^2 + b^2 = c^2
		apow = os_RealPow(&triangle.a, &real2);
		bpow = os_RealPow(&triangle.b, &real2);
		cpow = os_RealAdd(&apow, &bpow);
		triangle.c   = os_RealSqrt(&cpow);
		trigstatus.c = true;

		return;
	}
	else if (!trigstatus.a && trigstatus.b && trigstatus.c)
	{
		//a^2 + b^2 = c^2

		bpow = os_RealPow(&triangle.b, &real2);
		cpow = os_RealPow(&triangle.c, &real2);
		apow = os_RealSub(&cpow, &bpow);
		triangle.a   = os_RealSqrt(&apow);
		trigstatus.a = true;
		return;
	}
	else if (trigstatus.a && !trigstatus.b && trigstatus.c)
	{
		//a^2 + b^2 = c^2

		apow = os_RealPow(&triangle.a, &real2);
		cpow = os_RealPow(&triangle.c, &real2);
		bpow = os_RealSub(&cpow, &apow);
		triangle.b   = os_RealSqrt(&bpow);
		trigstatus.b = true;
		return;
	}


}

void sp_SetFuncData2Label(real_t sideX, real_t sideY, int i)
{
	const uint8_t MaxSide = 4;
	char          x[15];
	char          y[15];
	char          buf[30];
	os_RealToStr(x, &sideX, 0, 0, 6);
	os_RealToStr(y, &sideY, 0, 0, 6);
	StrCut(x, MaxSide, 10 - MaxSide);
	StrCut(y, MaxSide, 10 - MaxSide);
	sprintf(buf, ui_FuncFmt, x, y);
	strcat(funcData2[i].label, buf);
}

void sp_SetFuncDataLabel(real_t sideX, real_t sideY, int i)
{
	const uint8_t MaxSide = 4;
	char          x[15];
	char          y[15];
	char          buf[30];
	os_RealToStr(x, &sideX, 0, 0, 6);
	os_RealToStr(y, &sideY, 0, 0, 6);
	StrCut(x, MaxSide, 10 - MaxSide);
	StrCut(y, MaxSide, 10 - MaxSide);
	sprintf(buf, ui_FuncFmt, x, y);
	strcat(funcData[i].label, buf);
}

void CheckForInt(char* in, char* possibleSrc)
{
	if (in[strlen(in) - 2] == '1')
	{
		dbg_sprintf(dbgout, "Int detected: %s\n", in);
		strcpy(in, possibleSrc);
	}
	else if (in[strlen(in) - 2] == '0')
	{
		strcpy(in, "0");
	}
}

void sohcahtoa_DrawAAA()
{
	char x[15];
	char y[15];
	char buf[30];
	int  index = 0;


	for (index = 0; index < 3; index++)
	{
		gfx_Clear(&funcData[index]);
		mem_Zero(funcData[index].label + 6, 14);
		gfx_Clear(&funcData2[index]);
		mem_Zero(funcData2[index].label + 6, 14);
	}

	// When angle AAA is selected
	sp_SetLabel(&xsides_oah[0], lbl_ADJ); // bbb = adj
	sp_SetLabel(&xsides_oah[1], lbl_OPP); // aaa = opp
	sp_SetLabel(&xsides_oah[2], lbl_HYP); // ccc = hyp


	gfx_PrintColor(&ui_Wait, gfx_red);
	if (!ui_dispSimpRoot)
	{
		// SOH
		sp_SetFuncDataLabel(triangle.a, triangle.c, 0);

		// CAH
		sp_SetFuncDataLabel(triangle.b, triangle.c, 1);

		// TOA
		sp_SetFuncDataLabel(triangle.a, triangle.b, 2);

		// cot = adj/opp
		sp_SetFuncData2Label(triangle.b, triangle.a, 0);

		// sec = hyp/adj
		sp_SetFuncData2Label(triangle.c, triangle.b, 1);

		// csc = hyp/opp
		sp_SetFuncData2Label(triangle.c, triangle.a, 2);
	}
	else
	{
		// SOH
		SimplifyRadicalStrFromDecimal(triangle.a, x);
		SimplifyRadicalStrFromDecimal(triangle.c, y);
		CheckForInt(x, side_a.label);
		CheckForInt(y, side_c.label);
		sprintf(buf, ui_FuncFmt, x, y);
		strcat(funcData[0].label, buf);


		// CAH
		SimplifyRadicalStrFromDecimal(triangle.b, x);
		SimplifyRadicalStrFromDecimal(triangle.c, y);
		CheckForInt(x, side_b.label);
		CheckForInt(y, side_c.label);
		sprintf(buf, ui_FuncFmt, x, y);
		strcat(funcData[1].label, buf);


		// TOA
		SimplifyRadicalStrFromDecimal(triangle.a, x);
		SimplifyRadicalStrFromDecimal(triangle.b, y);
		CheckForInt(x, side_a.label);
		CheckForInt(y, side_b.label);
		sprintf(buf, ui_FuncFmt, x, y);
		strcat(funcData[2].label, buf);


		// cot = adj/opp
		SimplifyRadicalStrFromDecimal(triangle.b, x);
		SimplifyRadicalStrFromDecimal(triangle.a, y);
		CheckForInt(x, side_b.label);
		CheckForInt(y, side_a.label);
		sprintf(buf, ui_FuncFmt, x, y);
		strcat(funcData2[0].label, buf);


		// sec = hyp/adj
		SimplifyRadicalStrFromDecimal(triangle.c, x);
		SimplifyRadicalStrFromDecimal(triangle.b, y);
		CheckForInt(x, side_c.label);
		CheckForInt(y, side_b.label);
		sprintf(buf, ui_FuncFmt, x, y);
		strcat(funcData2[1].label, buf);


		// csc = hyp/opp
		SimplifyRadicalStrFromDecimal(triangle.c, x);
		SimplifyRadicalStrFromDecimal(triangle.a, y);
		CheckForInt(x, side_c.label);
		CheckForInt(y, side_a.label);
		sprintf(buf, ui_FuncFmt, x, y);
		strcat(funcData2[2].label, buf);
	}
	gfx_Clear(&ui_Wait);

	for (index = 0; index < 3; index++)
	{
		gfx_PrintColor(&xsides_oah[index], gfx_green);
		gfx_PrintColor(&funcData[index], gfx_blue);
		gfx_PrintColor(&funcData2[index], gfx_blue);
	}


}

void sohcahtoa_DrawBBB()
{
	char x[15];
	char y[15];
	char buf[30];
	int  index = 0;
	for (index = 0; index < 3; index++)
	{
		gfx_Clear(&funcData[index]);
		mem_Zero(funcData[index].label + 6, 14);
		gfx_Clear(&funcData2[index]);
		mem_Zero(funcData2[index].label + 6, 14);
	}
	// When angle BBB is selected
	sp_SetLabel(&xsides_oah[0], lbl_OPP); // bbb = opp
	sp_SetLabel(&xsides_oah[1], lbl_ADJ); // aaa = adj
	sp_SetLabel(&xsides_oah[2], lbl_HYP); // ccc = hyp

	gfx_PrintColor(&ui_Wait, gfx_red);
	if (!ui_dispSimpRoot)
	{
		// SOH
		sp_SetFuncDataLabel(triangle.b, triangle.c, 0);

		// CAH
		sp_SetFuncDataLabel(triangle.a, triangle.c, 1);

		// TOA
		sp_SetFuncDataLabel(triangle.b, triangle.a, 2);

		// cot = adj/opp
		sp_SetFuncData2Label(triangle.a, triangle.b, 0);

		// sec = hyp/adj
		sp_SetFuncData2Label(triangle.c, triangle.a, 1);

		// csc = hyp/opp
		sp_SetFuncData2Label(triangle.c, triangle.b, 2);
	}
	else
	{
		// SOH
		SimplifyRadicalStrFromDecimal(triangle.b, x);
		SimplifyRadicalStrFromDecimal(triangle.c, y);
		CheckForInt(x, side_b.label);
		CheckForInt(y, side_c.label);
		sprintf(buf, ui_FuncFmt, x, y);
		strcat(funcData[0].label, buf);

		// CAH
		SimplifyRadicalStrFromDecimal(triangle.a, x);
		SimplifyRadicalStrFromDecimal(triangle.c, y);
		CheckForInt(x, side_a.label);
		CheckForInt(y, side_c.label);
		sprintf(buf, ui_FuncFmt, x, y);
		strcat(funcData[1].label, buf);

		// TOA
		SimplifyRadicalStrFromDecimal(triangle.b, x);
		SimplifyRadicalStrFromDecimal(triangle.a, y);
		CheckForInt(x, side_b.label);
		CheckForInt(y, side_a.label);
		sprintf(buf, ui_FuncFmt, x, y);
		strcat(funcData[2].label, buf);

		// cot = adj/opp
		SimplifyRadicalStrFromDecimal(triangle.a, x);
		SimplifyRadicalStrFromDecimal(triangle.b, y);
		CheckForInt(x, side_a.label);
		CheckForInt(y, side_b.label);
		sprintf(buf, ui_FuncFmt, x, y);
		strcat(funcData2[0].label, buf);

		// sec = hyp/adj
		SimplifyRadicalStrFromDecimal(triangle.c, x);
		SimplifyRadicalStrFromDecimal(triangle.a, y);
		CheckForInt(x, side_c.label);
		CheckForInt(y, side_a.label);
		sprintf(buf, ui_FuncFmt, x, y);
		strcat(funcData2[1].label, buf);

		// csc = hyp/opp
		SimplifyRadicalStrFromDecimal(triangle.c, x);
		SimplifyRadicalStrFromDecimal(triangle.b, y);
		CheckForInt(x, side_c.label);
		CheckForInt(y, side_b.label);
		sprintf(buf, ui_FuncFmt, x, y);
		strcat(funcData2[2].label, buf);
	}

	gfx_Clear(&ui_Wait);

	for (index = 0; index < 3; index++)
	{
		gfx_PrintColor(&xsides_oah[index], gfx_green);
		gfx_PrintColor(&funcData[index], gfx_blue);
		gfx_PrintColor(&funcData2[index], gfx_blue);
	}
}

void Redraw()
{

	int index = 0;

	for (; index < 3; index++)
	{
		gfx_Clear(&xangles[index]);
		gfx_Print(&xangles[index]);

		gfx_Clear(&xsides[index]);
		gfx_Print(&xsides[index]);

		//gfx_Clear(&funcData[index]);
		//gfx_Print(&funcData[index]);
	}
}

void sohcahtoa_DrawNull()
{
	int index = 0;
	// Draw nothing when 90 is selected
	sp_SetLabel(&xsides_oah[0], "BBB"); // bbb
	sp_SetLabel(&xsides_oah[1], "AAA"); // aaa
	sp_SetLabel(&xsides_oah[2], "CCC"); // ccc

	for (index = 0; index < 3; index++)
	{
		gfx_Clear(&xsides_oah[index]);
		gfx_Clear(&funcData[index]);
		gfx_Clear(&funcData2[index]);
	}
}

void right_RoundTriangle(uint8_t places)
{
	int i = 0;
	real_t* mem = (real_t*) &triangle;
	for (; i < 6; i++)
	{
		os_RealRound(&mem[i], places);
		dbg_sprintf(dbgout, "Rounded real_t memory @ 0x%p\n", &mem[i]);
	}
}

void disp_Simplified(real_t* r)
{
	real_t inroot;
	char   buf[20];

	if (!ui_dispSimpRoot)
	{
		return;
	}
	gfx_PrintColor(&ui_Wait, gfx_red);
	dbg_sprintf(dbgout, "Converting decimal to root...");
	inroot = os_FloatToReal(DecimalToRoot(os_RealToFloat(r)));
	os_RealToStr(buf, &inroot, 0, 0, 6);
	dbg_sprintf(dbgout, " = %s\n", buf);
	mem_Zero(buf, 20);

	dbg_sprintf(dbgout, "Simplifying radical...");
	SimplifyRadicalStr(os_RealToInt24(&inroot), buf);
	dbg_sprintf(dbgout, " = %s\n", buf);

	sp_SetLabel(&ui_Root, buf);
	gfx_Clear(&ui_Root);
	gfx_Print(&ui_Root);
	gfx_Clear(&ui_Wait);
}

void right_SelectSide()
{
	uint8_t key;
	superpoint_t* currentSelection;


	currentSelection = &xsides[0];
	gfx_HighlightPoint(&xsides[0]);
	sohcahtoa_DrawNull();
	RECURSE:
	while ((key = os_GetCSC()) != sk_Enter)
	{

		if (key == sk_Clear)
		{
			return;
		}

		if (key == sk_Zoom)
		{
			if (ui_dispSimpRoot)
			{
				gfx_Clear(&ui_Root);
				ui_dispSimpRoot = false;
			}
			else if (!ui_dispSimpRoot)
			{
				gfx_Print(&ui_Root);
				ui_dispSimpRoot = true;
			}
		}

		if (key == sk_Trace)
		{
			// todo
			currentSelection = &xsides[1];
			gfx_HighlightPoint(&xsides[1]);
		}

		if (key == sk_Graph)
		{
			gfx_Clear(&ui_Mode);

			sp_SetLabel(&ui_Mode, lbl_AngleMode);
			gfx_Print(&ui_Mode);
			gfx_ClearHighlight(currentSelection);
			gfx_Clear(&ui_Root);
			right_SelectAngle();
			return;
		}


		/* bbb -> ccc */
		if (key == sk_Right && PointEq(*currentSelection, xsides[0]))
		{

			gfx_ClearHighlight(&xsides[0]);
			gfx_HighlightPoint(&xsides[2]);
			currentSelection = &xsides[2];
			if (trigstatus.c)
			{
				disp_Simplified(&triangle.c);
			}
		}

		/* bbb -> aaa */
		if (key == sk_Down && PointEq(*currentSelection, xsides[0]))
		{
			gfx_ClearHighlight(&xsides[0]);
			gfx_HighlightPoint(&xsides[1]);
			currentSelection = &xsides[1];
			if (trigstatus.a)
			{
				disp_Simplified(&triangle.a);
			}
		}

		/* ccc -> aaa */
		if (key == sk_Down && PointEq(*currentSelection, xsides[2]))
		{
			gfx_ClearHighlight(&xsides[2]);
			gfx_HighlightPoint(&xsides[1]);
			currentSelection = &xsides[1];
			if (trigstatus.a)
			{
				disp_Simplified(&triangle.a);
			}
		}

		// [0] bbb
		// [1] aaa
		// [2] ccc

		/* ccc -> bbb */
		if (key == sk_Left && PointEq(*currentSelection, xsides[2]))
		{
			gfx_ClearHighlight(&xsides[2]);
			gfx_HighlightPoint(&xsides[0]);
			currentSelection = &xsides[0];
			if (trigstatus.b)
			{
				disp_Simplified(&triangle.b);
			}
		}

		/* aaa -> ccc */
		if (key == sk_Up || key == sk_Right && PointEq(*currentSelection, xsides[1]))
		{
			gfx_ClearHighlight(&xsides[1]);
			gfx_HighlightPoint(&xsides[2]);
			currentSelection = &xsides[2];
			if (trigstatus.c)
			{
				disp_Simplified(&triangle.c);
			}
		}

		/* aaa -> bbb */
		if (key == sk_Left && PointEq(*currentSelection, xsides[1]))
		{
			gfx_ClearHighlight(&xsides[1]);
			gfx_HighlightPoint(&xsides[0]);
			currentSelection = &xsides[0];
			if (trigstatus.b)
			{
				disp_Simplified(&triangle.b);
			}
		}
	}

	// [0] bbb
	// [1] aaa
	// [2] ccc

	if (PointEq(*currentSelection, xsides[0]))
	{
		dbg_sprintf(dbgout, "[DECIMATH] [Trig] User selected side %s\n", xsides[0].label);

		triangle.b   = io_gfx_ReadReal(&xsides[0]);
		trigstatus.b = true;
	}

	if (PointEq(*currentSelection, xsides[1]))
	{
		dbg_sprintf(dbgout, "[DECIMATH] [Trig] User selected side %s\n", xsides[1].label);
		triangle.a   = io_gfx_ReadReal(&xsides[1]);
		trigstatus.a = true;
	}

	if (PointEq(*currentSelection, xsides[2]))
	{
		dbg_sprintf(dbgout, "[DECIMATH] [Trig] User selected side %s\n", xsides[2].label);
		triangle.c   = io_gfx_ReadReal(&xsides[2]);
		trigstatus.c = true;
	}

	pythag_CheckSolvability();
	right_Sync();
	gfx_HighlightPoint(currentSelection);

	goto RECURSE;
}

void right_SelectAngle()
{
	uint8_t key;
	superpoint_t* currentSelection;
	const real_t real90 = os_Int24ToReal(90);
	currentSelection = &xangles[0];
	gfx_HighlightPoint(&xangles[0]);
	sohcahtoa_DrawNull();
	RECURSE:
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

		if (key == sk_Clear)
		{
			return;
		}

		if (key == sk_Zoom)
		{
			if (ui_dispSimpRoot)
			{
				gfx_Clear(&ui_Root);
				ui_dispSimpRoot = false;
			}
			else if (!ui_dispSimpRoot)
			{
				gfx_Print(&ui_Root);
				ui_dispSimpRoot = true;
			}
		}

		if (key == sk_Trace)
		{
			// todo
			currentSelection = &xsides[1];
			gfx_HighlightPoint(&xsides[1]);
		}

		if (key == sk_Graph)
		{
			gfx_Clear(&ui_Mode);
			//mode.label = "ANGLE MODE";
			sp_SetLabel(&ui_Mode, lbl_SideMode);
			gfx_Print(&ui_Mode);
			gfx_ClearHighlight(currentSelection);
			right_SelectSide();
			return;
		}

		/* 90 -> BBB */
		if (key == sk_Right && PointEq(*currentSelection, xangles[0]))
		{
			gfx_ClearHighlight(&xangles[0]);
			gfx_HighlightPoint(&xangles[1]);
			currentSelection = &xangles[1];

			sohcahtoa_DrawBBB();
		}

		/* 90 -> AAA */
		if (key == sk_Up && PointEq(*currentSelection, xangles[0]))
		{
			gfx_ClearHighlight(&xangles[0]);
			gfx_HighlightPoint(&xangles[2]);
			currentSelection = &xangles[2];

			sohcahtoa_DrawAAA();
		}

		/* AAA -> 90 */
		if (key == sk_Down && PointEq(*currentSelection, xangles[2]))
		{
			gfx_ClearHighlight(&xangles[2]);
			gfx_HighlightPoint(&xangles[0]);
			currentSelection = &xangles[0];

			sohcahtoa_DrawNull();
		}

		/* AAA -> BBB */
		if (key == sk_Right && PointEq(*currentSelection, xangles[2]))
		{
			gfx_ClearHighlight(&xangles[2]);
			gfx_HighlightPoint(&xangles[1]);
			currentSelection = &xangles[1];

			sohcahtoa_DrawBBB();
		}

		/* BBB -> 90 */
		if (key == sk_Left && PointEq(*currentSelection, xangles[1]))
		{
			gfx_ClearHighlight(&xangles[1]);
			gfx_HighlightPoint(&xangles[0]);
			currentSelection = &xangles[0];

			sohcahtoa_DrawNull();
		}

		/* BBB -> AAA */
		if (key == sk_Up && PointEq(*currentSelection, xangles[1]))
		{
			gfx_ClearHighlight(&xangles[1]);
			gfx_HighlightPoint(&xangles[2]);
			currentSelection = &xangles[2];

			sohcahtoa_DrawAAA();
		}
	}

	if (PointEq(*currentSelection, xangles[0]))
	{
		dbg_sprintf(dbgout, "[DECIMATH] [Trig] User selected angle 90, returning to angle selection\n");
		goto RECURSE;
	}

	if (PointEq(*currentSelection, xangles[1]))
	{
		dbg_sprintf(dbgout, "[DECIMATH] [Trig] User selected angle %s\n", xangles[1].label);

		// 90
		// BBB
		// AAA

		triangle.B   = io_gfx_ReadReal(&xangles[1]);
		trigstatus.B = true;
	}

	if (PointEq(*currentSelection, xangles[2]))
	{
		dbg_sprintf(dbgout, "[DECIMATH] [Trig] User selected angle %s\n", xangles[2].label);

		triangle.A   = io_gfx_ReadReal(&xangles[2]);
		trigstatus.A = true;
	}

	if (trigstatus.A)
	{
		triangle.B   = os_RealSub(&real90, &triangle.A);
		trigstatus.B = true;
		gfx_Clear(&angle_B);
	}
	else if (trigstatus.B)
	{
		triangle.A   = os_RealSub(&real90, &triangle.B);
		trigstatus.A = true;
		gfx_Clear(&angle_A);
	}

	right_Sync();
	gfx_HighlightPoint(currentSelection);
	goto RECURSE;
}

void trig_SolveRightTriangle()
{
	int index;

	/* Triangle coordinates */
	const int verts[6] = {
			30, 10,   /* (x0, y0) */
			30, 129,  /* (x1, y1) */
			189, 129, /* (x2, y2) */
	};

	triangle.C   = os_Int24ToReal(90);
	trigstatus.C = true;
	ui_dispSimpRoot = true;

	gfx_Begin();
	gfx_SetColor(gfx_blue);
	gfx_SetTextFGColor(gfx_black);

	/* Leg a */
	gfx_Line(verts[0], verts[1], verts[2], verts[3]);

	/* Leg b */
	gfx_Line(verts[2], verts[3], verts[4], verts[5]);

	/* Hypotenuse */
	gfx_Line(verts[4], verts[5], verts[0], verts[1]);

	// Leg b, a, c
	for (index = 0; index < 3; index++)
	{
		gfx_Print(&xangles[index]);
		gfx_Print(&xsides[index]);
	}

	gfx_Print(&ui_btn_Clear);
	gfx_Print(&ui_btn_Mode);
	gfx_Print(&ui_btn_EnableSimpRoot);
	gfx_Print(&ui_Mode);

	right_SelectAngle();

	gfx_ZeroScreen();
	gfx_End();

}