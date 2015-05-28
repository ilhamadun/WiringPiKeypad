/**
 * WiringPi Keypad Matrix Library
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
Keypad::Keypad(int _rowSize, int _columnSize)
: rowSize(_rowSize), columnSize(_columnSize), debounceDelay(200), pollingDelay(20)
{
	rowPin = (int *) malloc(sizeof(int) * rowSize);
	columnPin = (int *) malloc(sizeof(int) * columnSize);
}

/**
 * Class constructor
 */
Keypad::Keypad(int _rowSize, int _columnSize, int _debounce, int _polling)
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
void Keypad::setRowPin(int *row)
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
void Keypad::setColumnPin(int *column)
{
	for (int i = 0; i < columnSize; i++)
	{
		columnPin[i] = column[i];
	}
}

/**
 * Set debounce delay
 * 
 * @param delay 	delay in miliseconds
 */
void Keypad::setDebounceDelay(int delay)
{
	debounceDelay = delay;
}

/**
 * Set polling delay
 * 
 * @param delay 	delay in miliseconds
 */
void Keypad::setPollingDelay(int delay)
{
	pollingDelay = delay;
}

/**
 * Get debounce delay
 * 
 * @return  delay in miliseconds
 */
int Keypad::getDebounceDelay(void)
{
	return debounceDelay;
}

/**
 * Get polling delay
 * 
 * @return  delay in miliseconds
 */
int Keypad::getPollingDelay(void)
{
	return pollingDelay;
}

/**
 * Listen to keypress
 * 
 * @return  key structure
 */
struct key Keypad::getKey(void)
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
 * Print setup details
 */
void Keypad::printDetails(void)
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