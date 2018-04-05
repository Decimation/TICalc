//
// Created by Decimation on 4/3/2018.
//

#include "IO.h"

/**
 * NOTE NOTE NOTE
 *
 * The prompt for any of the os_Get* functions cannot be too long.
 * If the user inputs more than the length of the screen, it will cause a RAM reset.
 */

void PutFloat(float f, uint8_t xpos, uint8_t ypos) {
	char buf[20];
	FloatToString(f, buf, 9);
	print(buf, xpos,ypos);
}

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

void ReadLineDigit(char* buffer)
{
	// todo: remove remaining alpha chars in chars*
	int x = 0;
	uint8_t key, i = 0;
	static char chars[] = "\0\0\0\0\0\0\0\0\0\0\"WRMH\0\0?[69LG\0\0.258KFC\0 147JEB\0\0XSNIDA\0\0\0\0\0\0\0\0";
	Zero(buffer, (int) strlen(buffer));
	// We don't want the compiler evaluating the literal as an escape sequence
	//chars[IndexOf(chars,'1')-1] = '0';

	// 0
	chars[33] = '0';

	// Theta
	chars[18] = '3';


	while ((key = os_GetCSC()) != sk_Enter)
	{

		if (chars[key])
		{
			/*for (; x < sizeof(chars) -1; x++) {
				if (chars[key] == chars[x]) {
					sprintf(buffer, "%c | %d", chars[key], x);
					print(buffer,0,1);
				}
			}*/
			buffer[i++] = chars[key];
		}
		print(buffer,0,0);
	}
}

void Hex(char c, char* out) {
	sprintf(out, "%02x", c);
}

void ReadLineAlpha(char* buffer)
{
	const char chars[] = "\0\0\0\0\0\0\0\0\0\0\"WRMH\0\0?[VQLG\0\0:ZUPKFC\0 YTOJEB\0\0XSNIDA\0\0\0\0\0\0\0\0";
	uint8_t   key, i  = 0;
	Zero(buffer, (int) strlen(buffer));
	while ((key = os_GetCSC()) != sk_Enter)
	{
		if (chars[key])
		{
			buffer[i++] = chars[key];
		}
		print(buffer,0,0);
	}
}

float ReadFloat() {
	ReadLineDigit(g_inputBuffer);
	return StringToFloat(g_inputBuffer);
}

int ReadInt() {
	ReadLineDigit(g_inputBuffer);
	return atoi(g_inputBuffer);
}

int24_t os_GetNumberInput(const char* prompt)
{
	/* Ask the user to type a string, which gets stored in inputBuf */
	os_GetStringInput(prompt, g_inputBuffer, INPUT_SIZE);
	return atoi(g_inputBuffer);
}

float os_GetFloatInput(const char* prompt)
{
	/* Ask the user to type a string, which gets stored in inputBuf */
	os_GetStringInput(prompt, g_inputBuffer, INPUT_SIZE);

	return StringToFloat(g_inputBuffer);
}