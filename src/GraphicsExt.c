//
// Created by Decimation on 4/22/2018.
//

#include "GraphicsExt.h"

void gfx_Clear(superpoint_t* p)
{
	int w = gfx_GetStringWidth(p->label);
	gfx_SetColor(gfx_white);

	//dbg_sprintf(dbgout, "[DECIMATH] String width of [%s]: %d\n", p->label, w);
	gfx_FillRectangle(p->point.x, p->point.y, w, 9);
	gfx_SetColor(gfx_blue);
}

void gfx_Print(superpoint_t* p)
{
	//Clear(p);
	gfx_PrintStringXY(p->label, p->point.x, p->point.y);
}

void sp_SetLabel(superpoint_t* p, const char* s)
{
	gfx_Clear(p);
	mem_Zero(p->label, 20);
	strncpy(p->label, s, strlen(s));
}

real_t io_gfx_ReadReal(superpoint_t* vBuffer)
{
	//superpoint_t old      = *vBuffer;
	bool         isNeg    = false;
	uint8_t      key, i   = 0;
	real_t       rbuffer;
	static char  lchars[] = "\0\0\0\0\0\0\0\0\0\0\"-RMH\0\0?[69LG\0\0.258KFC\0 147JEB\0\0XSNIDA\0\0\0\0\0\0\0\0";
	gfx_Clear(vBuffer);
	mem_Zero(vBuffer->label, 20);
	lchars[33] = '0';
	lchars[18] = '3';


	while ((key = os_GetCSC()) != sk_Enter)
	{

		if (key == sk_Del)
		{
			gfx_Clear(vBuffer);
			vBuffer->label[--i] = '\0';
			//io_ClearFirstLine();
			gfx_Clear(vBuffer);
			gfx_Print(vBuffer);
		}

		if (key == 0x11)
		{
			dbg_sprintf(dbgout, "[DECIMATH] Negative sign keypress detected\n");
			rbuffer = os_StrToReal(vBuffer->label, NULL);
			rbuffer = os_RealNeg(&rbuffer);
			os_RealToStr(vBuffer->label, &rbuffer, 0, 0, 6);
			//io_ClearFirstLine();
			gfx_Clear(vBuffer);
			gfx_Print(vBuffer);
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
		gfx_Print(vBuffer);
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

bool PointEq(superpoint_t a, superpoint_t b)
{
	return a.point.x == b.point.x && a.point.y == b.point.y;
}

void gfx_ClearHighlight(superpoint_t* p)
{
	//gfx_SetTextFGColor(gfx_black);
	gfx_Clear(p);
	gfx_PrintColor(p, gfx_black);
}

void gfx_PrintColor(superpoint_t* p, uint8_t color)
{
	gfx_SetTextFGColor(color);
	gfx_PrintStringXY(p->label, p->point.x, p->point.y);
	gfx_SetTextFGColor(gfx_black);
}

void gfx_HighlightPoint(superpoint_t* p)
{
	//gfx_SetTextFGColor(gfx_red);
	gfx_PrintColor(p, gfx_red);
}