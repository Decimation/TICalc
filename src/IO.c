//
// Created by Decimation on 4/3/2018.
//

#include "IO.h"
#include "C:\CEdev\include\debug.h"
#include "MathLib.h"


void print(const char* text, uint8_t xpos, uint8_t ypos)
{
	os_SetCursorPos(ypos, xpos);
	os_PutStrFull(text);
}

void println(const char* text, uint8_t xpos, uint8_t ypos)
{
	os_SetCursorPos(ypos, xpos);
	os_PutStrLine(text);
}

void ClearFirstLine()
{
	ClearLine(0, 0);
}

static const char* NullLine = "                         ";
real_t* g_X;

void ClearLine(uint8_t x, uint8_t y)
{
	print(NullLine, x, y);
}

real_t RclX()
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

void ReadLineDigit(char* buffer)
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

	static char chars[] = "\0\0\0\0\0\0\0\0\0\0\"WRMH\0\0?[69LG\0\0.258KFC\0 147JEB\0\0XSNIDA\0\0\0\0\0\0\0\0";
	Zero(buffer, (int) strlen(buffer));
	// We don't want the compiler evaluating the literal as an escape sequence
	//chars[IndexOf(chars,'1')-1] = '0';

	// 0
	chars[33] = '0';

	// Theta
	chars[18] = '3';

	//chars[IndexOf(chars, 'H')] = '\u03C0';

	BREAK:
	while ((key = os_GetCSC()) != sk_Enter)
	{

		if (key == sk_Del)
		{
			buffer[--i] = '\0';
			ClearFirstLine();
			print(buffer, 0, 0);
		}

		/**
		 * If pi is input, inline the value of pi
		 * Supports coefficients and the literal pi
		 */
		if (key == sk_Power)
		{
			Zero(coeffBuf, sizeof(coeffBuf));
			Zero(xBuf, sizeof(xBuf));
			Substring(buffer, 0, i, coeffBuf);
			coeff_r = os_StrToReal(coeffBuf, NULL);
			dbg_sprintf(dbgout, "[DECIMATH] [i] Coefficient = %s\n", coeffBuf);
			pi_real = os_FloatToReal(PI);
			if (os_RealCompare(&coeff_r, &null_r) == 0)
			{
				res = pi_real;
			}
			else res     = os_RealMul(&coeff_r, &pi_real);

			os_RealToStr(buffer, &res, 0, 0, -1);
			dbg_sprintf(dbgout, "[DECIMATH] [s] Result = %s\n", buffer);
			//buffer[IndexOf(buffer, 'H')] = '.';
			ClearFirstLine();
			print(buffer, 0, 0);
			goto BREAK;
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

			x_val_r = RclX();
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
					print(buffer,0,1);
				}
			}*/
			buffer[i++] = chars[key];
		}

		print(buffer, 0, 0);

	}
	dbg_sprintf(dbgout, "[DECIMATH] [RAW_INPUT] %s\n", buffer);
}


void ReadLineAlpha(char* buffer)
{
	const char chars[] = "\0\0\0\0\0\0\0\0\0\0\"WRMH\0\0?[VQLG\0\0:ZUPKFC\0 YTOJEB\0\0XSNIDA\0\0\0\0\0\0\0\0";
	uint8_t    key, i  = 0;
	Zero(buffer, (int) strlen(buffer));
	while ((key = os_GetCSC()) != sk_Enter)
	{
		if (chars[key])
		{
			buffer[i++] = chars[key];
		}
		print(buffer, 0, 0);
	}
}

real_t ReadReal() {
	ReadLineDigit(g_inputBuffer);
	return os_StrToReal(g_inputBuffer, NULL);
}

float ReadFloat()
{
	real_t r;
	ReadLineDigit(g_inputBuffer);
	r = os_StrToReal(g_inputBuffer, NULL);
	return os_RealToFloat(&r);
	//return StringToFloat(g_inputBuffer);
}

int ReadInt()
{
	real_t r;
	ReadLineDigit(g_inputBuffer);
	//return atoi(g_inputBuffer);
	r = os_StrToReal(g_inputBuffer, NULL);
	return os_RealToInt24(&r);
}

/*int24_t os_GetNumberInput(const char* prompt)
{
	os_GetStringInput(prompt, g_inputBuffer, INPUT_SIZE);
	return atoi(g_inputBuffer);
}

float os_GetFloatInput(const char* prompt)
{
	os_GetStringInput(prompt, g_inputBuffer, INPUT_SIZE);

	return StringToFloat(g_inputBuffer);
}*/