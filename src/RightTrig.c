//
// Created by Decimation on 4/14/2018.
//

#include "RightTrig.h"
#include "GraphicsExt.h"
#include "Library.h"

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

static const superpoint_t ui_btn_Mode  = {280, 230, "Mode"};
static const superpoint_t ui_btn_Clear = {215, 230, "Clear"};

static superpoint_t       ui_Mode      = {{230, 10}, "ANGLE MODE"};
static const char lbl_AngleMode[] = "ANGLE MODE";
static const char lbl_SideMode[]  = "SIDE MODE";

static const char lbl_ADJ[] = "ADJ";
static const char lbl_HYP[] = "HYP";
static const char lbl_OPP[] = "OPP";

static triangle_t triangle;

static superpoint_t funcData[3] = {
		{10, 185, "sin = "},
		{10, 205, "cos = "},
		{10, 225, "tan = "}
};

static superpoint_t funcData2[3] = {
		{130, 185, "cot = "},
		{130, 205, "sec = "},
		{130, 225, "csc = "}
};

void sohcahtoa_DrawAAA()
{
	char x[10];
	char y[10];
	char buf[20];
	int index = 0;
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

	// SOH
	os_RealToStr(x, &triangle.a, 0,0,6);
	os_RealToStr(y, &triangle.c, 0,0,6);
	sprintf(buf, "%s / %s", x, y);
	strcat(funcData[0].label, buf);
	//sp_SetLabel(&funcData[0], buf);

	// CAH
	os_RealToStr(x, &triangle.b, 0,0,6);
	os_RealToStr(y, &triangle.c, 0,0,6);
	sprintf(buf, "%s / %s", x, y);
	strcat(funcData[1].label, buf);
	//sp_SetLabel(&funcData[1], buf);

	// TOA
	os_RealToStr(x, &triangle.a, 0,0,6);
	os_RealToStr(y, &triangle.b, 0,0,6);
	sprintf(buf, "%s / %s", x, y);
	strcat(funcData[2].label, buf);
	//sp_SetLabel(&funcData[2], buf);

	// cot = adj/opp
	os_RealToStr(x, &triangle.b, 0,0,6);
	os_RealToStr(y, &triangle.a, 0,0,6);
	sprintf(buf, "%s / %s", x, y);
	strcat(funcData2[0].label, buf);

	// sec = hyp/adj
	os_RealToStr(x, &triangle.c, 0,0,6);
	os_RealToStr(y, &triangle.b, 0,0,6);
	sprintf(buf, "%s / %s", x, y);
	strcat(funcData2[1].label, buf);

	// csc = hyp/opp
	os_RealToStr(x, &triangle.c, 0,0,6);
	os_RealToStr(y, &triangle.a, 0,0,6);
	sprintf(buf, "%s / %s", x, y);
	strcat(funcData2[2].label, buf);

	for (index = 0; index < 3; index++)
	{
		gfx_PrintColor(&xsides_oah[index], gfx_green);
		gfx_PrintColor(&funcData[index], gfx_black);
		gfx_PrintColor(&funcData2[index], gfx_black);
	}


}

void sohcahtoa_DrawBBB()
{
	char x[10];
	char y[10];
	char buf[20];
	int index = 0;
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

	// SOH
	os_RealToStr(x, &triangle.b, 0,0,6);
	os_RealToStr(y, &triangle.c, 0,0,6);
	sprintf(buf, "%s / %s", x, y);
	strcat(funcData[0].label, buf);
	//sp_SetLabel(&funcData[0], buf);

	// CAH
	os_RealToStr(x, &triangle.a, 0,0,6);
	os_RealToStr(y, &triangle.c, 0,0,6);
	sprintf(buf, "%s / %s", x, y);
	strcat(funcData[1].label, buf);
	//sp_SetLabel(&funcData[1], buf);

	// TOA
	os_RealToStr(x, &triangle.b, 0,0,6);
	os_RealToStr(y, &triangle.a, 0,0,6);
	sprintf(buf, "%s / %s", x, y);
	strcat(funcData[2].label, buf);
	//sp_SetLabel(&funcData[2], buf);

	// cot = adj/opp
	os_RealToStr(x, &triangle.a, 0,0,6);
	os_RealToStr(y, &triangle.b, 0,0,6);
	sprintf(buf, "%s / %s", x, y);
	strcat(funcData2[0].label, buf);

	// sec = hyp/adj
	os_RealToStr(x, &triangle.c, 0,0,6);
	os_RealToStr(y, &triangle.a, 0,0,6);
	sprintf(buf, "%s / %s", x, y);
	strcat(funcData2[1].label, buf);

	// csc = hyp/opp
	os_RealToStr(x, &triangle.c, 0,0,6);
	os_RealToStr(y, &triangle.b, 0,0,6);
	sprintf(buf, "%s / %s", x, y);
	strcat(funcData2[2].label, buf);

	for (index = 0; index < 3; index++)
	{
		gfx_PrintColor(&xsides_oah[index], gfx_green);
		gfx_PrintColor(&funcData[index], gfx_black);
		gfx_PrintColor(&funcData2[index], gfx_black);
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

void right_SelectSide() {
	uint8_t      key;
	real_t       buffer, buffer2;
	const real_t real90 = os_Int24ToReal(90);
	superpoint_t* currentSelection;


	currentSelection = &xsides[0];
	gfx_HighlightPoint(&xsides[0]);
	sohcahtoa_DrawNull();
	RECURSE:
	while ((key = os_GetCSC()) != sk_Enter)
	{
		// [0] bbb
		// [1] aaa
		// [2] ccc

		if (key == sk_Clear)
		{
			return;
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
			sp_SetLabel(&ui_Mode, lbl_AngleMode);
			gfx_Print(&ui_Mode);
			gfx_ClearHighlight(currentSelection);
			right_SelectAngle();
			return;
		}

		// [0] bbb
		// [1] aaa
		// [2] ccc

		/* bbb -> ccc */
		if (key == sk_Right && PointEq(*currentSelection, xsides[0]))
		{
			gfx_ClearHighlight(&xsides[0]);
			gfx_HighlightPoint(&xsides[2]);
			currentSelection = &xsides[2];
		}

		/* bbb -> aaa */
		if (key == sk_Down && PointEq(*currentSelection, xsides[0]))
		{
			gfx_ClearHighlight(&xsides[0]);
			gfx_HighlightPoint(&xsides[1]);
			currentSelection = &xsides[1];
		}

		/* ccc -> aaa */
		if (key == sk_Down && PointEq(*currentSelection, xsides[2]))
		{
			gfx_ClearHighlight(&xsides[2]);
			gfx_HighlightPoint(&xsides[1]);
			currentSelection = &xsides[1];
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
		}

		/* aaa -> ccc */
		if (key == sk_Up || key == sk_Right && PointEq(*currentSelection, xsides[1]))
		{
			gfx_ClearHighlight(&xsides[1]);
			gfx_HighlightPoint(&xsides[2]);
			currentSelection = &xsides[2];
		}

		/* aaa -> bbb */
		if (key == sk_Left && PointEq(*currentSelection, xsides[1]))
		{
			gfx_ClearHighlight(&xsides[1]);
			gfx_HighlightPoint(&xsides[0]);
			currentSelection = &xsides[0];
		}
	}

	// [0] bbb
	// [1] aaa
	// [2] ccc

	if (PointEq(*currentSelection, xsides[0]))
	{
		dbg_sprintf(dbgout, "[DECIMATH] [Trig] User selected side %s\n", xsides[0].label);

		triangle.b = io_gfx_ReadReal(&xsides[0]);
	}

	if (PointEq(*currentSelection, xsides[1]))
	{
		dbg_sprintf(dbgout, "[DECIMATH] [Trig] User selected side %s\n", xsides[1].label);
		triangle.a = io_gfx_ReadReal(&xsides[1]);
	}

	if (PointEq(*currentSelection, xsides[2]))
	{
		dbg_sprintf(dbgout, "[DECIMATH] [Trig] User selected side %s\n", xsides[2].label);
		triangle.c = io_gfx_ReadReal(&xsides[2]);
	}

	Redraw();
	gfx_HighlightPoint(currentSelection);
	goto RECURSE;
}

void right_SelectAngle()
{
	uint8_t      key;
	real_t       buffer, buffer2;
	const real_t real90 = os_Int24ToReal(90);
	superpoint_t* currentSelection;

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

		triangle.B = io_gfx_ReadReal(&xangles[1]);
	}

	if (PointEq(*currentSelection, xangles[2]))
	{
		dbg_sprintf(dbgout, "[DECIMATH] [Trig] User selected angle %s\n", xangles[2].label);

		triangle.A = io_gfx_ReadReal(&xangles[2]);
	}

	Redraw();
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

	triangle.C = os_Int24ToReal(90);

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

	right_SelectAngle();

	gfx_ZeroScreen();
	gfx_End();

}