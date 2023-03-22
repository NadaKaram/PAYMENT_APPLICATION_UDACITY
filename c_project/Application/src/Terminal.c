/*
 ============================================================================
 Name        : Terminal.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "terminal.h"
#include "string.h"
extern ST_terminalData_t card3;
void getTransactionDateTest(void)
{

	printf("function name :getTransactionDateTest \n");
	printf("test case 1: \n");
	printf("input data : 25/12/2022 \n");
	scanf("%s",card3.transactionDate);

	printf("Expected result is :TERMINAL_OK\n");
	if( getTransactionDate(&card3)==0)
		printf("actual result is : TERMINAL_OK\n");
	else
		printf("actual result : WRONG_DATE\n");


	printf("test case 2: \n");
	printf("input data : 12/12/2021\n");
	scanf("%s",card3.transactionDate);

	printf("Expected result is :WRONG_DATE\n");
	if( getTransactionDate(&card3)==0)
		printf("actual result is : TERMINAL_OK\n");
	else
		printf("actual result : WRONG_DATE\n");


	printf("test case 3: \n");
	printf("input data :12\12\2022 \n");
	scanf("%s",card3.transactionDate);

	printf("Expected result is :WRONG_DATE\n");
	if( getTransactionDate(&card3)==0)
		printf("actual result is : TERMINAL_OK\n");
	else
		printf("actual result : WRONG_DATE\n");

}
void isCardExpriedTest(void){
	ST_terminalData_t card4;
	ST_cardData_t card3={"nada karam abdelmonen","123456789123456789","12/22"};
	printf("function name : isCardExpriedTest \n");
	printf("test case 1: \n");
	printf("input data : 12/12/2022 \n");
	scanf("%s",card4.transactionDate);

	printf("Expected result is :TERMINAL_OK\n");
	if(isCardExpired(&card3,&card4)==0)
		printf("actual result is : TERMINAL_OK\n");
	else
		printf("actual result : EXPIRED_CARD\n");


	printf("test case 2: \n");
	printf("input data :01/01/2023\n");
	scanf("%s",card3.cardExpirationDate);

	printf("Expected result is :EXPIRED_CARD\n");
	if(isCardExpired(&card3,&card4)==0)
		printf("actual result is : TERMINAL_OK\n");
	else
		printf("actual result : EXPIRED_CARD\n");
	printf("test case 3: \n");
		printf("input data : 08\\12\\2022 \n");
		scanf("%s",card3.cardExpirationDate);

		printf("Expected result is :EXPIRED_CARD\n");
		if(isCardExpired(&card3,&card4)==0)
			printf("actual result is : TERMINAL_OK\n");
		else
			printf("actual result : EXPIRED_CARD\n");

}
void getTransactionAmountTest(void)
{
	//ST_terminalData_t card3;
	//card3.maxTransAmount=5000;
	printf("function name :getTransactionAmountTest \n");
	printf("input data :2000 \n");
	printf("test case 1: \n");
	scanf("%f",&card3.transAmount);

	printf("Expected result is :TERMINAL_OK\n");
	if(  getTransactionAmount(&card3)==0)
		printf("actual result is : TERMINAL_OK\n");
	else
		printf("actual result : INVALID_AMOUNT\n");


	printf("test case 2: \n");
	printf("input data : -5\n");
	scanf("%f",&card3.transAmount);

	printf("Expected result is :INVALID_AMOUNT\n");
	if( getTransactionAmount(&card3)==0)
		printf("actual result is : TERMINAL_OK\n");
	else
		printf("actual result : INVALID_AMOUNT\n");


	printf("test case 3: \n");
	printf("input data : 0 \n");
	scanf("%f",&card3.transAmount);

	printf("Expected result is :INVALID_AMOUNT\n");
	if(getTransactionAmount(&card3)==0)
		printf("actual result is : TERMINAL_OK\n");
	else
		printf("actual result : INVALID_AMOUNT\n");

}
void isBelowMaxAmountTest(void)
{

	//ST_terminalData_t card3;
	card3.maxTransAmount=500;
	printf("function name :isBelowMaxAmountTest \n");
	printf("test case 1: \n");
	printf("input data : 500 \n");
	scanf("%f",&card3.transAmount);
	printf("the Expected result is :TERMINAL_OK \n");
	if( isBelowMaxAmount(&card3) == TERMINAL_OK)
	{
		printf("the actual result is : TERMINAL_OK\n");
	}
	else
	{
		printf("the actual result is : EXCEED_MAX_AMOUNT \n");
	}

	printf("test case 2: \n");
	printf("input data : 700 \n");
	scanf("%f",&card3.transAmount);

	printf("the Expected result is :EXCEED_MAX_AMOUNT \n");
	if( isBelowMaxAmount(&card3) == TERMINAL_OK)
	{
		printf("the actual result is : TERMINAL_OK\n");
	}
	else
	{
		printf("the actual result is : EXCEED_MAX_AMOUNT \n");
	}

}
void setMaxAmountTest(void)
{

	printf("test case 1: \n");
	printf("input data : 5700\n");
	printf("function name :setMaxAmountTest \n");
	printf("Expected result : 5700\n");
	if(setMaxAmount (&card3,5700) ==TERMINAL_OK )
	{
		printf("the actual result is : %0.1f \n",card3.transAmount);
	}
	else
	{
		printf("the actual result is : INVALID_MAX_AMOUNT \n");
	}

	printf("test case 2: \n");
	printf("input data : -500\n");

	printf("Expected result :INVALID_MAX_AMOUNT\n");
	if(setMaxAmount (&card3,-500) ==TERMINAL_OK )
	{
		printf("the actual result is : %0.1f \n",card3.transAmount);
	}
	else
	{
		printf("the actual result is : INVALID_MAX_AMOUNT \n");
	}
}
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
	uint8_t length = strlen(termData ->transactionDate);
	if(length < 10 || length >10 ||termData ->transactionDate[2] != '/' || atoi(termData ->transactionDate )>31 || atoi(termData ->transactionDate +3 )>12 || atoi(termData ->transactionDate + 6)<2022 || termData ->transactionDate[5] !='/')
	{
		return   WRONG_DATE;
	}
	else
	{
		return TERMINAL_OK;
	}

}
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
	if(atoi(termData ->transactionDate +8) ==   atoi(cardData -> cardExpirationDate+3))
	{
		if(atoi(termData ->transactionDate +3) <= atoi(cardData -> cardExpirationDate) )
		{
			return  TERMINAL_OK;
		}
		else
		{
			return EXPIRED_CARD;
		}
	}
	else if(atoi(termData ->transactionDate +8) < atoi(cardData -> cardExpirationDate+3))
	{
		return  TERMINAL_OK;
	}
	else
	{
		return EXPIRED_CARD;

	}
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
	if(termData ->transAmount <= 0)
	{
		return INVALID_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
	if( termData ->transAmount <= termData ->maxTransAmount)
	{
		return   TERMINAL_OK;
	}
	else
	{
		return EXCEED_MAX_AMOUNT;
	}
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount)
{
	if(maxAmount > 0)
	{
		termData ->transAmount = maxAmount;
		return  TERMINAL_OK;
	}
	else
	{
		return  INVALID_MAX_AMOUNT;
	}
}
/*
int main(void){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	getTransactionDateTest();
	printf("\n");
	isCardExpriedTest();
	printf("\n");
	getTransactionAmountTest();
	printf("\n");
	isBelowMaxAmountTest();
	printf("\n");
	setMaxAmountTest();

	ST_terminalData_t card3;
	gets(card3.transactionDate);
	EN_terminalError_t card = getTransactionDate(&card3);
	if(card == TERMINAL_OK)
	{
		printf("TERMINAL_OK");
	}
	else
	{
		printf("WRONG_DATE");
	}
	 */


	//Testing isCard Expired
	/*
	ST_terminalData_t card3 ={1,2,"22/12/2022"}; //transaction date
	ST_cardData_t card4;
	gets(card4.cardExpirationDate);
	EN_terminalError_t card = isCardExpired(&card4,&card3);
	if(card == TERMINAL_OK)
	{
		printf("TERMINAL_OK");
	}
	else
	{
		printf("EXPIRED_CARD");
	}


	 */
	/* Testing the amount
	ST_terminalData_t card4;

	scanf("%f",&card4.transAmount);

	EN_terminalError_t card = getTransactionAmount(&card4);
	if(card == TERMINAL_OK)
	{
		printf("TERMINAL_OK");
	}
	else
	{
		printf("INVALID_AMOUNT");
	}
	 */
	/*
	ST_terminalData_t card3;
	card3.maxTransAmount=500;
	scanf("%f",&card3.transAmount);
	EN_terminalError_t card = isBelowMaxAmount(&card3);
	if(card == TERMINAL_OK)
	{
		printf("TERMINAL_OK");
	}
	else
	{
		printf("EXCEED_MAX_AMOUNT");
	}
	 */

	/* Testing setMaxAmount
	ST_terminalData_t card4;
	EN_terminalError_t card5 = setMaxAmount (&card4,570);
	if(card5 ==TERMINAL_OK )
	{
		printf("%f",card4.transAmount);
	}
	else
	{
		printf("INVALID_MAX_AMOUNT");
	}
	 */

