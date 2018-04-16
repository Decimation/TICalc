//
// Created by Decimation on 4/7/2018.
//

#include "Trigonometry.h"
#include "MathLib.h"

/**
 * For non-right triangles
 *
 * todo: Right triangles to come soon
 */

static superpoint_t xangles[3] = {
		{{30,       119 - 10}, "AAA"},   // AAA
		{{10 + 155, 119 - 10}, "BBB"},   // BBB
		{{140 - 14, 32},       "CCC"}   // CCC
};

static superpoint_t xsides[3] = {
		{{10 + 180, 60},  "aaa"},  // aaa
		{{20,       60},  "bbb"},  // bbb
		{{140 - 45, 130}, "ccc"}   // ccc
};

static triangle_t   triangle;
static trigstatus_t trigstatus;
static superpoint_t mode      = {{230, 10}, "ANGLE MODE"};
static superpoint_t type      = {{230, 20}, "..."};

real_t io_gfx_ReadReal(superpoint_t* vBuffer)
{
	bool        isNeg    = false;
	uint8_t     key, i   = 0;
	real_t      rbuffer;
	static char lchars[] = "\0\0\0\0\0\0\0\0\0\0\"-RMH\0\0?[69LG\0\0.258KFC\0 147JEB\0\0XSNIDA\0\0\0\0\0\0\0\0";
	Clear(*vBuffer);
	Zero(vBuffer->label, strlen(vBuffer->label));
	lchars[33] = '0';
	lchars[18] = '3';


	while ((key = os_GetCSC()) != sk_Enter)
	{

		if (key == sk_Del)
		{
			vBuffer->label[--i] = '\0';
			//io_ClearFirstLine();
			Clear(*vBuffer);
			gfx_Print(*vBuffer);
		}

		if (key == 0x11)
		{
			dbg_sprintf(dbgout, "[DECIMATH] Negative sign keypress detected\n");
			rbuffer = os_StrToReal(vBuffer->label, NULL);
			rbuffer = os_RealNeg(&rbuffer);
			os_RealToStr(vBuffer->label, &rbuffer, 0, 0, -1);
			//io_ClearFirstLine();
			Clear(*vBuffer);
			gfx_Print(*vBuffer);
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
			vBuffer->label[i++] = lchars[key];
			dbg_sprintf(dbgout, "[DECIMATH] [RAW_INPUT] [KEYCODE] 0x%X (%d) \n", key, key);
		}


		gfx_Print(*vBuffer);

	}
	if (isNeg)
	{
		return rbuffer;
	}
	else
	{
		return os_StrToReal(vBuffer->label, NULL);
	}
}

void gfx_PrintColor(superpoint_t p, uint8_t color)
{
	gfx_SetTextFGColor(color);
	gfx_PrintStringXY(p.label, p.point.x, p.point.y);
	gfx_SetTextFGColor(gfx_black);
}

void gfx_Print(superpoint_t p)
{
	gfx_PrintStringXY(p.label, p.point.x, p.point.y);
}

void gfx_ClearHighlight(superpoint_t p)
{
	//gfx_SetTextFGColor(gfx_black);
	gfx_PrintColor(p, gfx_black);
}

void Clear(superpoint_t p)
{
	int w = gfx_GetStringWidth(p.label);
	gfx_SetColor(gfx_white);

	//dbg_sprintf(dbgout, "[DECIMATH] String width of [%s]: %d\n", p.label, w);
	gfx_FillRectangle(p.point.x, p.point.y, w, 9);
	gfx_SetColor(gfx_blue);
}

void gfx_HighlightPoint(superpoint_t p)
{
	//gfx_SetTextFGColor(gfx_red);
	gfx_PrintColor(p, gfx_red);
}

bool PointEq(superpoint_t a, superpoint_t b)
{
	return a.point.x == b.point.x && a.point.y == b.point.y;
}

void ClearTrianglePoints() {
	int index = 0;
	for (; index < 3; index++)
	{
		Clear(xangles[index]);
		Clear(xsides[index]);
	}
}
void RedrawTriangle()
{
	int index = 0;
	ClearTrianglePoints();
	for (index = 0; index < 3; index++)
	{
		gfx_Print(xangles[index]);
		gfx_Print(xsides[index]);
	}
}

real_t loc_AngleAf(real_t b, real_t c, real_t a) {
	float bf,cf,af, fbuf;
	real_t buf;
	char cbuf[10];
	bf = os_RealToFloat(&b);
	cf = os_RealToFloat(&c);
	af = os_RealToFloat(&a);
	fbuf = (pow(bf, 2) + pow(cf, 2) - pow(af, 2)) / (2 * bf * cf);
	buf = os_FloatToReal((float) acos(fbuf  * PI / 180));
	os_RealToStr(cbuf, &buf, 0,0,-1);
	dbg_sprintf(dbgout, "loc_AngleAf = %s\n", cbuf);
	return os_RealRound(&buf, 1);
}

real_t loc_AngleBf(real_t c, real_t a, real_t b) {
	float cf, af, bf, fbuf;
	real_t buf;
	char cbuf[10];
	cf = os_RealToFloat(&c);
	af = os_RealToFloat(&a);
	bf = os_RealToFloat(&b);
	fbuf = (pow(cf, 2) + pow(af, 2) - pow(bf, 2)) / (2 * cf * af);
	buf = os_FloatToReal((float) acos(fbuf * PI / 180));
	os_RealToStr(cbuf, &buf, 0,0,-1);
	dbg_sprintf(dbgout, "loc_AngleBf = %s\n", cbuf);
	return os_RealRound(&buf, 1);
}

// todo: fix
real_t loc_AngleA(real_t b, real_t c, real_t a)
{
	char buf[10];
	//cos A = (b2 + c2 − a2) / 2bc
	real_t real2 = os_Int24ToReal(2);
	real_t bplusc, numer, bc, denom, preres, final;
	real_t b2,c2,a2;
	b2 = os_RealPow(&b, &real2);
	c2 = os_RealPow(&c, &real2);
	a2 = os_RealPow(&a, &real2);

	bplusc = os_RealAdd(&b2, &c2);
	numer  = os_RealSub(&bplusc, &a2);

	bc    = os_RealMul(&b, &c);
	denom = os_RealMul(&bc, &real2);

	preres = os_RealDiv(&numer, &denom);
	os_RealToStr(buf, &preres, 0,0,-1);
	dbg_sprintf(dbgout, "preres = %s\n", buf);
	final = os_RealRound(&final, 1);
	os_RealToStr(buf, &final, 0,0,-1);
	dbg_sprintf(dbgout, "loc_AngleA = %s\n", buf);
	return os_RealRadToDeg(&final);
}

// todo: fix
real_t loc_AngleB(real_t c, real_t a, real_t b)
{
	char buf[10];
	//cos B = (c2 + a2 − b2) / 2ca
	real_t real2 = os_Int24ToReal(2);
	real_t cplusa, numer, ca, denom, preres, final;
	real_t c2,a2,b2;
	b2 = os_RealPow(&c, &real2);
	c2 = os_RealPow(&a, &real2);
	a2 = os_RealPow(&b, &real2);

	cplusa = os_RealAdd(&c2, &a2);
	numer  = os_RealSub(&cplusa, &b2);

	ca    = os_RealMul(&c, &a);
	denom = os_RealMul(&ca, &real2);

	preres = os_RealDiv(&numer, &denom);
	os_RealToStr(buf, &preres, 0,0,-1);
	dbg_sprintf(dbgout, "preres = %s\n", buf);
	final  = os_RealAcosRad(&preres);
	final = os_RealRound(&final, 1);
	os_RealToStr(buf, &final, 0,0,-1);
	dbg_sprintf(dbgout, "loc_AngleB = %s\n", buf);
	return os_RealRadToDeg(&final);
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

void Synchronize()
{

	if (trigstatus.A) {
		os_RealToStr(xangles[0].label, &triangle.A,0,0,-1);
	}
	if (trigstatus.B) {
		os_RealToStr(xangles[1].label, &triangle.B,0,0,-1);
	}
	if (trigstatus.C) {
		os_RealToStr(xangles[2].label, &triangle.C,0,0,-1);
	}
	if (trigstatus.a) {
		os_RealToStr(xsides[0].label, &triangle.a,0,0,-1);
	}
	if (trigstatus.b) {
		os_RealToStr(xsides[1].label, &triangle.b,0,0,-1);
	}
	if (trigstatus.c) {
		os_RealToStr(xsides[2].label, &triangle.c,0,0,-1);
	}
	RedrawTriangle();
}

void trig_SolveSSS()
{
	real_t buf;
	real_t real180 = os_Int24ToReal(180);
	triangle.A   = loc_AngleAf(triangle.b, triangle.b, triangle.c);
	trigstatus.A = true;

	triangle.B   = loc_AngleBf(triangle.c, triangle.a, triangle.b);
	trigstatus.B = true;

	buf = os_RealAdd(&triangle.A, &triangle.B);
	triangle.C   = os_RealSub(&real180, &buf);
	trigstatus.C = true;
	Synchronize();
}

void trig_CheckSolvability()
{
	real_t buf;
	dbg_sprintf(dbgout, "[DECIMATH] [Trig] Checking solvability...\n");
	dbg_printTriangle();

	// SSS
	if (trigstatus.a && trigstatus.b && trigstatus.c)
	{
		dbg_sprintf(dbgout, "SSS detected [%s, %s, %s]\n", xsides[0].label, xsides[1].label, xsides[2].label);
		Clear(type);
		type.label = "SSS";
		gfx_PrintColor(type, gfx_green);
		trig_SolveSSS();
	}

	// AAS
	// "AAS" is when we know two angles and one side (which is not between the angles).
	if (trigstatus.A && trigstatus.C && trigstatus.c)
	{

	}
	else if (trigstatus.B && trigstatus.C && trigstatus.b)
	{

	}
	else if (trigstatus.A && trigstatus.B && trigstatus.b)
	{

	}

	// ASA
	// "ASA" is when we know two angles and a side between the angles.
	if (trigstatus.A && trigstatus.c && trigstatus.B)
	{

	}
	else if (trigstatus.A && trigstatus.b && trigstatus.C)
	{

	}
	else if (trigstatus.B && trigstatus.a && trigstatus.C)
	{

	}

	// SAS
	// "SAS" is when we know two sides and the angle between them.
	if (trigstatus.b && trigstatus.A && trigstatus.c)
	{

	}
	else if (trigstatus.c && trigstatus.B && trigstatus.a)
	{

	}
	else if (trigstatus.b && trigstatus.C && trigstatus.a)
	{

	}

	// SSA
	// "SSA" is when we know two sides and an angle that is not the angle between the sides.
	// todo: check if it has multiple answers
	if (trigstatus.b && trigstatus.c && trigstatus.B)
	{

	}
	else if (trigstatus.b && trigstatus.a && trigstatus.B)
	{

	}
	else if (trigstatus.a && trigstatus.c && trigstatus.C)
	{

	}


}

void SelectSide()
{
	uint8_t      key;
	superpoint_t currentSelection = xsides[1]; // start at b
	gfx_HighlightPoint(xsides[1]);
	RECURSE:
	while ((key = os_GetCSC()) != sk_Enter)
	{
		if (key == sk_Clear)
		{
			return;
		}

		if (key == sk_Graph)
		{
			Clear(mode);
			mode.label = "ANGLE MODE";
			gfx_Print(mode);
			gfx_ClearHighlight(currentSelection);
			SelectAngle();
			return;
		}

		/* bbb -> aaa */
		if (key == sk_Right && PointEq(currentSelection, xsides[1]))
		{
			gfx_ClearHighlight(xsides[1]);
			gfx_HighlightPoint(xsides[0]);
			currentSelection = xsides[0];
		}

		/* bbb -> ccc */
		if (key == sk_Down && PointEq(currentSelection, xsides[1]))
		{
			gfx_ClearHighlight(xsides[1]);
			gfx_HighlightPoint(xsides[2]);
			currentSelection = xsides[2];
		}

		/* ccc -> bbb */
		if ((key == sk_Up || key == sk_Left) && PointEq(currentSelection, xsides[2]))
		{
			gfx_ClearHighlight(xsides[2]);
			gfx_HighlightPoint(xsides[1]);
			currentSelection = xsides[1];
		}

		/* ccc -> aaa */
		if (key == sk_Right && PointEq(currentSelection, xsides[2]))
		{
			gfx_ClearHighlight(xsides[2]);
			gfx_HighlightPoint(xsides[0]);
			currentSelection = xsides[0];
		}

		/* aaa -> bbb */
		if (key == sk_Left && PointEq(currentSelection, xsides[0]))
		{
			gfx_ClearHighlight(xsides[0]);
			gfx_HighlightPoint(xsides[1]);
			currentSelection = xsides[1];
		}

		/* aaa -> ccc */
		if (key == sk_Down && PointEq(currentSelection, xsides[0]))
		{
			gfx_ClearHighlight(xsides[0]);
			gfx_HighlightPoint(xsides[2]);
			currentSelection = xsides[2];
		}
	}

	if (PointEq(currentSelection, xsides[0]))
	{
		dbg_sprintf(dbgout, "[DECIMATH] [Trig] User selected side %s\n", xsides[0].label);
		triangle.a = io_gfx_ReadReal(&xsides[0]);
		trigstatus.a = true;
	}

	if (PointEq(currentSelection, xsides[1]))
	{
		dbg_sprintf(dbgout, "[DECIMATH] [Trig] User selected side %s\n", xsides[1].label);
		triangle.b = io_gfx_ReadReal(&xsides[1]);
		trigstatus.b = true;
	}

	if (PointEq(currentSelection, xsides[2]))
	{
		dbg_sprintf(dbgout, "[DECIMATH] [Trig] User selected side %s\n", xsides[2].label);
		triangle.c = io_gfx_ReadReal(&xsides[2]);
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

void SelectAngle()
{
	uint8_t      key;
	superpoint_t currentSelection = xangles[0];
	gfx_HighlightPoint(xangles[0]);
	RECURSE:
	while ((key = os_GetCSC()) != sk_Enter)
	{
		if (key == sk_Clear)
		{
			return;
		}

		if (key == sk_Graph)
		{
			Clear(mode);
			mode.label = "SIDE MODE";
			gfx_Print(mode);
			gfx_ClearHighlight(currentSelection);
			SelectSide();
			return;
		}

		/* AAA -> BBB */
		if (key == sk_Right && PointEq(currentSelection, xangles[0]))
		{
			gfx_ClearHighlight(xangles[0]);
			gfx_HighlightPoint(xangles[1]);
			currentSelection = xangles[1];
		}

		/* AAA -> CCC */
		if (key == sk_Up && PointEq(currentSelection, xangles[0]))
		{
			gfx_ClearHighlight(xangles[0]);
			gfx_HighlightPoint(xangles[2]);
			currentSelection = xangles[2];
		}

		/* BBB -> AAA */
		if (key == sk_Left && PointEq(currentSelection, xangles[1]))
		{
			gfx_ClearHighlight(xangles[1]);
			gfx_HighlightPoint(xangles[0]);
			currentSelection = xangles[0];
		}

		/* BBB -> CCC */
		if (key == sk_Up && PointEq(currentSelection, xangles[1]))
		{
			gfx_ClearHighlight(xangles[1]);
			gfx_HighlightPoint(xangles[2]);
			currentSelection = xangles[2];
		}

		/* CCC -> AAA */
		if (key == sk_Left && PointEq(currentSelection, xangles[2]))
		{
			gfx_ClearHighlight(xangles[2]);
			gfx_HighlightPoint(xangles[0]);
			currentSelection = xangles[0];
		}

		/* CCC -> BBB */
		if (key == sk_Down && PointEq(currentSelection, xangles[2]))
		{
			gfx_ClearHighlight(xangles[2]);
			gfx_HighlightPoint(xangles[1]);
			currentSelection = xangles[1];
		}
	}

	if (PointEq(currentSelection, xangles[0]))
	{
		dbg_sprintf(dbgout, "[DECIMATH] [Trig] User selected angle %s\n", xangles[0].label);
		triangle.A = io_gfx_ReadReal(&xangles[0]);
		trigstatus.A = true;
	}

	if (PointEq(currentSelection, xangles[1]))
	{
		dbg_sprintf(dbgout, "[DECIMATH] [Trig] User selected angle %s\n", xangles[1].label);
		triangle.B = io_gfx_ReadReal(&xangles[1]);
		trigstatus.B = true;
	}

	if (PointEq(currentSelection, xangles[2]))
	{
		dbg_sprintf(dbgout, "[DECIMATH] [Trig] User selected angle %s\n", xangles[2].label);
		triangle.C = io_gfx_ReadReal(&xangles[2]);
		trigstatus.C = true;
	}

	trig_CheckSolvability();
	gfx_HighlightPoint(currentSelection);
	goto RECURSE;
}

/**
 * todo: - add support for angle C ("90")
 *       - implement side mode
 */
void trig_SolveTriangle()
{
	int index = 0;


	/* Triangle coordinates */
	const int verts[6] = {
			140, 10,   /* (x0, y0) */
			10, 119,  /* (x1, y1) */
			209, 119, /* (x2, y2) */
	};

	os_ClrHome();

	gfx_Begin();

	gfx_SetColor(gfx_blue);
	gfx_SetTextFGColor(gfx_black);

	gfx_Print(mode);

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
		gfx_Print(xsides[index]);
	}

	SelectAngle();


	trig_Quit();
}