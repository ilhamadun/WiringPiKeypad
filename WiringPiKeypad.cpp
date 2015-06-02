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

#include "WiringPiKeypad.h"

/**
 * Class constructor
 */
WiringPiKeypad::WiringPiKeypad(int _rowSize, int _columnSize)
: rowSize(_rowSize), columnSize(_columnSize), debounceDelay(200), pollingDelay(20)
{
	rowPin = (int *) malloc(sizeof(int) * rowSize);
	columnPin = (int *) malloc(sizeof(int) * columnSize);
}

/**
 * Class constructor
 */
WiringPiKeypad::WiringPiKeypad(int _rowSize, int _columnSize, int _debounce, int _polling)
: rowSize(_rowSize), columnSize(_columnSize), debounceDelay(_debounce), pollingDelay(_polling)
{
	rowPin = (int *) malloc(sizeof(int) * rowSize);
	columnPin = (int *) malloc(sizeof(int) * columnSize);
}

/**
 * Set row pin
 * 
 * @param 	row 	array with rowSize elements
 */
void WiringPiKeypad::setRowPin(int *row)
{
	for (int i = 0; i < rowSize; i++)
	{
		rowPin[i] = row[i];
	}
}

/**
 * Set column pin
 * 
 * @param 	column 	array with columnSize elements
 */
void WiringPiKeypad::setColumnPin(int *column)
{
	for (int i = 0; i < columnSize; i++)
	{
		columnPin[i] = column[i];
	}
}

/**
 * Set keypad matrix
 * 
 * @param matrix 	keypad matrix
 */
void WiringPiKeypad::setMatrix(std::vector<std::vector<char>> m)
{
	matrix = m;
}

/**
 * Set debounce delay
 * 
 * @param delay 	delay in miliseconds
 */
void WiringPiKeypad::setDebounceDelay(int delay)
{
	debounceDelay = delay;
}

/**
 * Set polling delay
 * 
 * @param delay 	delay in miliseconds
 */
void WiringPiKeypad::setPollingDelay(int delay)
{
	pollingDelay = delay;
}

/**
 * Get debounce delay
 * 
 * @return  delay in miliseconds
 */
int WiringPiKeypad::getDebounceDelay(void)
{
	return debounceDelay;
}

/**
 * Get polling delay
 * 
 * @return  delay in miliseconds
 */
int WiringPiKeypad::getPollingDelay(void)
{
	return pollingDelay;
}

/**
 * Listen to keypress and return raw key data
 * 
 * @return  key structure
 */
struct key WiringPiKeypad::getRawKey(void)
{
	struct key k;

	for (int i = 0; i < columnSize; i++)
	{
		pinMode(columnPin[i], INPUT);
		pullUpDnControl(columnPin[i], PUD_UP);
	}

	for (int i = 0; i < rowSize; i++)
	{
		pinMode(rowPin[i], INPUT);
		pullUpDnControl(rowPin[i], PUD_OFF);
	}

	while (1)
	{
		for (int i = 0; i < rowSize; i++)
		{
			pinMode(rowPin[i], OUTPUT);
			digitalWrite(rowPin[i], LOW);

			for (int j = 0; j < columnSize; j++)
			{
				if (! digitalRead(columnPin[j]))
				{
					delay(debounceDelay);
					k.row = i;
					k.column = j;

					return k;
				}
			}

			pinMode(rowPin[i], INPUT);
			pullUpDnControl(rowPin[i], PUD_OFF);

			delay(pollingDelay);
		}
	}
}

/**
 * Get keypress and return key data from matrix
 * 
 * @return  pressed key
 */
char WiringPiKeypad::getKey(void)
{
	struct key k = getRawKey();

	return matrix[k.row][k.column];;
}

/**
 * Check input value
 * 
 * @param  row    	row value to check
 * @param  column 	column value to check
 */
bool WiringPiKeypad::inputIs(int row, int column)
{
	return inputIs(getRawKey(), row, column);
}

/**
 * Check input value
 *
 * @param  key 		keypress
 * @param  row    	row value to check
 * @param  column 	column value to check
 */
bool WiringPiKeypad::inputIs(struct key keypress, int row, int column)
{
	if (keypress.row == row && keypress.column == column)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * Print setup details
 */
void WiringPiKeypad::printDetails(void)
{
	std::cout << "Row size:\t" << rowSize << std::endl;
	std::cout << "Column size:\t" << rowSize << std::endl;

	std::cout << "Row pin:\t";
	for (int i = 0; i < rowSize; i++)
	{
		std::cout << rowPin[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "Column pin:\t";
	for (int i = 0; i < columnSize; i++)
	{
		std::cout << columnPin[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "Debounce delay:\t" << debounceDelay << std::endl;
	std::cout << "Polling delay:\t" << pollingDelay << std::endl;
}