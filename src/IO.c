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

void ReadLine(char* buffer)
{
	const char* chars = "\0\0\0\0\0\0\0\0\0\0\"WRMH\0\0?[VQLG\0\0:ZUPKFC\0 YTOJEB\0\0XSNIDA\0\0\0\0\0\0\0\0";
	uint8_t   key, i  = 0;
	//char      buffer[50];

	while ((key = os_GetCSC()) != sk_Enter)
	{
		if (chars[key])
		{
			buffer[i++] = chars[key];
		}
	}
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