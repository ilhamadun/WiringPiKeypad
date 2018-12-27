WiringPi Matrix Keypad Library
==============================

WiringPiKeypad is a library to interface a matrix keypad. Raspberry Pi, Odroid C1, and other board with WiringPi is supported.

---
//a simple demo 

int row[4] = {21, 22, 23, 24};
int column[4] = {1, 2, 3, 4};
std::vector<std::vector<char>> matrix {
    {'D', 'C', 'B', 'A'},
    {'#', '9', '6', '3'},
    {'0', '8', '5', '2'},
    {'*', '7', '4', '1'}
};

WiringPiKeypad *keypad = new WiringPiKeypad(4, 4);

keypad->setRowPin(row);
keypad->setColumnPin(column);
keypad->setMatrix(matrix);

char key = keypad->getKey();

---
### License
This software is licensed under the [MIT License](http://opensource.org/licenses/MIT).
