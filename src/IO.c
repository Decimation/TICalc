//
// Created by Decimation on 4/3/2018.
//

#include "IO.h"
#include "MathLib.h"


void io_print(const char* text, uint8_t xpos, uint8_t ypos)
{
	os_SetCursorPos(ypos, xpos);
	os_PutStrFull(text);
}

void io_println(const char* text, uint8_t xpos, uint8_t ypos)
{
	os_SetCursorPos(ypos, xpos);
	os_PutStrLine(text);
}

void io_ClearFirstLine()
{
	io_ClearLine(0, 0);
}

static const char* NullLine = "                         ";
real_t           * g_X;

void io_ClearLine(uint8_t x, uint8_t y)
{
	io_print(NullLine, x, y);
}

real_t io_RclX()
{
	ti_var_t v;
	real_t   r;
	g_X = ti_MallocReal();
	v   = ti_OpenVar(ti_X, "r+", TI_REAL_TYPE);
	ti_RclVar(v, ti_X, &g_X);
	r = os_RealCopy(g_X);
	//free(var_X);
	//ti_Close(v);
	return r;
}

void io_ReadLineDigit(char* buffer)
{
	// todo: remove remaining alpha chars in chars*
	uint8_t key, i      = 0;

	real_t       res;
	real_t       x_val_r;
	real_t       coeff_r;
	real_t       pi_real;
	const real_t null_r = os_Int24ToReal(0);
	char         coeffBuf[10];
	char         xBuf[20];

	static char chars[] = "\0\0\0\0\0\0\0\0\0\0\"-RMH\0\0?[69LG\0\0.258KFC\0 147JEB\0\0XSNIDA\0\0\0\0\0\0\0\0";
	mem_Zero(buffer, (int) strlen(buffer));
	// We don't want the compiler evaluating the literal as an escape sequence
	//chars[IndexOf(chars,'1')-1] = '0';

	// 0
	chars[33] = '0';

	// Theta
	chars[18] = '3';

	BREAK:
	while ((key = os_GetCSC()) != sk_Enter)
	{

		if (key == sk_Del)
		{
			buffer[--i] = '\0';
			io_ClearFirstLine();
			io_print(buffer, 0, 0);
		}

		/**
		 * If pi is input, inline the value of pi
		 * Supports coefficients and the literal pi
		 */
		if (key == sk_Power)
		{
			mem_Zero(coeffBuf, sizeof(coeffBuf));
			mem_Zero(xBuf, sizeof(xBuf));
			Substring(buffer, 0, i, coeffBuf);
			coeff_r = os_StrToReal(coeffBuf, NULL);
			dbg_sprintf(dbgout, "[DECIMATH] [i] Coefficient = %s\n", coeffBuf);
			pi_real = os_FloatToReal(PI);
			if (os_RealCompare(&coeff_r, &null_r) == 0)
			{
				res = pi_real;
			}
			else res = os_RealMul(&coeff_r, &pi_real);

			os_RealToStr(buffer, &res, 0, 0, -1);
			dbg_sprintf(dbgout, "[DECIMATH] [s] Result = %s\n", buffer);
			//buffer[IndexOf(buffer, 'H')] = '.';
			io_ClearFirstLine();
			io_print(buffer, 0, 0);
			goto BREAK;
		}

		if (key == 0x11)
		{
			dbg_sprintf(dbgout, "[DECIMATH] Negative sign keypress detected\n");

			//buffer[--key] = '-';
			//io_ClearFirstLine();
			//io_print(buffer, 0, 0);
			//goto BREAK;
		}

		/**
		 * If X is input, read from the variable X
		 * Supports coefficients and literal 'X'
		 * The value of X will be inlined
		 */
		if (chars[key] == 'X')
		{
			dbg_sprintf(dbgout, "[DECIMATH] X keypress detected\n");
			//Zero(coeffBuf, sizeof(coeffBuf));
			//Zero(xBuf, sizeof(xBuf));

			x_val_r = io_RclX();
			//x_val_r = os_Int24ToReal(5);
			os_RealToStr(xBuf, &x_val_r, 0, 0, -1);
			dbg_sprintf(dbgout, "[DECIMATH] [i] X = %s\n", xBuf);

			/**
			 * Put coefficient in coeffBuf
			 */
			Substring(buffer, 0, i, coeffBuf);
			coeff_r = os_StrToReal(coeffBuf, NULL);

			dbg_sprintf(dbgout, "[DECIMATH] [i] Coefficient = %s\n", coeffBuf);


			if (os_RealCompare(&coeff_r, &null_r) == 0)
			{
				res = x_val_r;
			}
			else res = os_RealMul(&coeff_r, &x_val_r);

			os_RealToStr(buffer, &res, 0, 0, -1);
			dbg_sprintf(dbgout, "[DECIMATH] [s] Result = %s\n", buffer);
			goto BREAK;
		}
		else if (chars[key])
		{
			/*for (; x < sizeof(chars) -1; x++) {
				if (chars[key] == chars[x]) {
					sprintf(buffer, "%c | %d", chars[key], x);
					io_print(buffer,0,1);
				}
			}*/
			buffer[i++] = chars[key];
			dbg_sprintf(dbgout, "[DECIMATH] [RAW_INPUT] [KEYCODE] 0x%X (%d) \n", key, key);
		}

		io_print(buffer, 0, 0);

	}
	dbg_sprintf(dbgout, "[DECIMATH] [RAW_INPUT] %s\n", buffer);

}


void io_ReadArray(real_t* out, int len)
{
	int  index = 0;
	char buf[10];
	while (index < len)
	{
		sprintf(buf, "%d of %d", index + 1, len);
		io_print(buf, 0, 1);
		io_ClearFirstLine();
		out[index++] = io_ReadReal();
	}

	os_ClrHome();
}

void io_ReadLineAlpha(char* buffer)
{
	const char chars[] = "\0\0\0\0\0\0\0\0\0\0\"WRMH\0\0?[VQLG\0\0:ZUPKFC\0 YTOJEB\0\0XSNIDA\0\0\0\0\0\0\0\0";
	uint8_t    key, i  = 0;
	mem_Zero(buffer, (int) strlen(buffer));
	while ((key = os_GetCSC()) != sk_Enter)
	{
		if (chars[key])
		{
			buffer[i++] = chars[key];
		}
		io_print(buffer, 0, 0);
	}
}


// todo: add X and pi functionality from io_ReadLineDigit
real_t io_ReadReal()
{
	bool        isNeg    = false;
	uint8_t     key, i   = 0;
	real_t      rbuffer;
	static char lchars[] = "\0\0\0\0\0\0\0\0\0\0\"-RMH\0\0?[69LG\0\0.258KFC\0 147JEB\0\0XSNIDA\0\0\0\0\0\0\0\0";
	char* buffer = g_inputBuffer;
	mem_Zero(buffer, INPUT_SIZE);
	lchars[33] = '0';
	lchars[18] = '3';

	while ((key = os_GetCSC()) != sk_Enter)
	{

		if (key == sk_Del)
		{
			buffer[--i] = '\0';
			io_ClearFirstLine();
			io_print(buffer, 0, 0);
		}

		if (key == 0x11)
		{
			dbg_sprintf(dbgout, "[DECIMATH] Negative sign keypress detected\n");
			rbuffer = os_StrToReal(buffer, NULL);
			rbuffer = os_RealNeg(&rbuffer);
			os_RealToStr(buffer, &rbuffer, 0, 0, -1);
			io_ClearFirstLine();
			io_print(buffer, 0, 0);
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
			buffer[i++] = lchars[key];
			dbg_sprintf(dbgout, "[DECIMATH] [RAW_INPUT] [KEYCODE] 0x%X (%d) \n", key, key);
		}

		io_print(buffer, 0, 0);

	}
	if (isNeg)
	{
		return rbuffer;
	}
	else
	{
		return os_StrToReal(buffer, NULL);
	}
}

float io_ReadFloat()
{
	real_t r;
	io_ReadLineDigit(g_inputBuffer);
	r = os_StrToReal(g_inputBuffer, NULL);
	return os_RealToFloat(&r);
}

int io_ReadInt()
{
	real_t r = io_ReadReal();
	return os_RealToInt24(&r);
}