#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
 * Title: Lab 4
 * Semester: COP4338 - Spring 2021
 * Author Megan Jane Thompson
 * Panther ID: 3276301
 *
 * I affirm that the revisions of this program is entirely
 * my own work and none of it is the work of any other person.
 *
 * This program takes in a user's decimal value, converts it
 * to binary, alters a specified index of the binary string,
 * and returns the new decimal number.
 *
 */


/********CONVERT DECIMAL TO BINARY********/
long decimalToBinary(int userVal){
	int decNum = userVal;
    long biNum = 0;
    long base = 1;
	int remainder;

	while (decNum != 0){
        remainder = decNum % 2;                        	//captures 1 for binary number
        biNum = biNum + remainder * base;			   	//adds 1 to binary number
        decNum = decNum / 2;
        base = base * 10;
    }
    return biNum;
}


/********CHECK USER BIT********/
int checkUserBit(int bitVal){
	int validFlag;

	if((bitVal >= 0) && (bitVal <= 31)){				//bit index to be between 0 and 31 inclusive
		validFlag = 1;
	}
	else{
		validFlag = 0;
		printf("\nBit number %d is an invalid entry. Please try again.\n", bitVal);
	}
	return validFlag;
}


/********ALTER BINARY NUMBER********/
void alterBinaryStr(char *binaryStr, int bitIndex, char opt){
	int valIndex = 31 - bitIndex;						//flips index val for string structure
	if((opt == 'c') || (opt == 'C')){
		binaryStr[valIndex] = '0';						//clears index val to 0
	}
	else{
		binaryStr[valIndex] = '1';						//sets index val to 1
	}
}


/********BINARY STRING TO DECIMAL********/
int binaryStrToDecimal(char *binaryStr) {
    int decVal = 0;
    long base = 1;   									//initializes base value to 1, ex: 2^0
    int i;
    int strLen = strlen(binaryStr);

    for (i = strLen-1; i >= 0; --i) {
    	if (binaryStr[i] == '1'){						//converts binarys 1's to decimal value
    		decVal += base;
    	}
        base = base * 2;
    }
    return decVal;
}


/********MAIN********/
int main(){
	char repeatOperation;

	do{
		int userNum = -1;
		int userBitIndex = -1;
		int userBitFlag = -1;
		int newNum = 0;
		long biNum;
		char clear[100];
		char str[33];
		char *binaryStr;
		char option;

		do{													//loop to obtain value 1 to 1000, inclusive
			printf("\nEnter a number 1 to 1000, inclusive: ");
			scanf("%d", &userNum);
		}while(userNum < 1 || userNum > 1000);

		biNum = decimalToBinary(userNum);					//call to get binary number from decimal number
		sprintf(str, "%032ld", biNum);
		binaryStr = str;									//pointer to binary string

		SetOrClear:											//jump back if option is not 'c' or 's'
		fgets(clear, 100, stdin);							//flushes io
		printf("\nDo you want to clear or set a bit? (Type 'c' for clear and type 's' for set): ");
		scanf("%c", &option);
		if(option == 'c' || option == 'C'){					//checks for clear option
			do{
				printf("\nType the bit would you like to clear between 0 and 31, inclusive: ");
				scanf("%d", &userBitIndex);
				userBitFlag = checkUserBit(userBitIndex);	//call to check user bit index value
			}while(userBitFlag == 0);						//keeps looping until valid bit index is selected
		}
		else if(option == 's' || option == 'S'){			//checks for set option
			do{
				printf("\nType the bit would you like to set between 0 and 31, inclusive: ");
				scanf("%d", &userBitIndex);
				userBitFlag = checkUserBit(userBitIndex);	//call to check user bit index value
			}while(userBitFlag == 0);						//keeps looping until valid bit index is selected
		}
		else{
			goto SetOrClear;
		}

		alterBinaryStr(binaryStr, userBitIndex, option);	//call to adjust binary string
		newNum = binaryStrToDecimal(binaryStr);				//call to covert new binary to new decimal value
		printf("\nYou entered '%d' and selected '%c' option for bit index '%d'. The new number is: %d", userNum, option, userBitIndex, newNum);

		fgets(clear, 100, stdin);							//flushes io
		printf("\n\nDo you want to repeat the operation? (Type 'y' for yes): ");
		scanf("%c", &repeatOperation);
	}
	while(repeatOperation == 'Y' || repeatOperation == 'y');
	printf("\nGOODBYE\n");

	exit(0);
}
