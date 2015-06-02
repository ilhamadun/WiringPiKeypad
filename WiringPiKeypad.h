/**
 * WiringPi Matrix Keypad Library
 *
 * Copyright (c) 2015 Ilham Imaduddin <ilham.imaduddin@mail.ugm.ac.id>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 */

#ifndef _KEYPAD_H_
#define _KEYPAD_H_

#include <iostream>
#include <vector>
#include <wiringPi.h>

struct key
{
	int row;
	int column;
};

class WiringPiKeypad
{
protected:
	int rowSize;
	int columnSize;
	int *rowPin;
	int *columnPin;
	std::vector<std::vector<char>> matrix;
	int debounceDelay;
	int pollingDelay;

public:
	WiringPiKeypad(int _rowSize, int _columnSize);
	WiringPiKeypad(int _rowSize, int _columnSize, int debounceDelay, int pollingDelay);
	void setRowPin(int *row);
	void setColumnPin(int *column);
	void setMatrix(std::vector<std::vector<char>> m);
	void setDebounceDelay(int delay);
	void setPollingDelay(int delay);
	int getDebounceDelay(void);
	int getPollingDelay(void);
	struct key getRawKey(void);
	char getKey(void);
	bool inputIs(int row, int column);
	bool inputIs(struct key keypress, int row, int column);
	void printDetails(void);
};

#endif