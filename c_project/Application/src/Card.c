/*
 ============================================================================
 Name        : Card.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Card.h"
#include "string.h"
	ST_cardData_t card3;
void getCardHolderNameTest(void)
{
	EN_cardError_t s;
	printf("function name : getCardHolderName \n");
	printf("test case 1: \n");
	printf("input data : nadia karam abdelmonem  \n");
	s=getCardHolderName("nadia karam abdelmonem");
	printf("Expected result is : CARD_OK\n");
	if(s==0)
		printf("actual result is : CARD_OK\n");
	else
		printf("actual result : WRONG_NAME\n");


	printf("test case 2: \n");
	printf("input data : na/a karam abdelmonem \n");
	s=getCardHolderName("na/a karam abdelmonem");
	printf("Expected result : WRONG_NAME \n");
	if(s==0)
		printf("actual result is : CARD_OK\n");
	else
		printf("actual result : WRONG_NAME\n");

	printf("test case 3: \n");
	printf("input data : nada karam\n");
	s=getCardHolderName("nada karam");
	printf("Expected result : WRONG_NAME \n");
	if(s==0)
		printf("actual result is : CARD_OK\n");
	else
		printf("actual result : WRONG_NAME\n");


}
void getCardExpiryDateTest (void)
{
	//EN_cardError_t m;


	printf("function name :getCardExpiryDateTest \n");
	printf("test case 1: \n");
	scanf("%s",card3.cardExpirationDate);
	printf("input data : 08/22 \n");

	printf("Expected result is : CARD_OK\n");
	if(getCardExpiryDate(&card3)==0)
		printf("actual result is : CARD_OK\n");
	else
		printf("actual result : WRONG_EXP_DATE\n");


	printf("test case 2: \n");
	printf("input data : 5/23 \n");
	scanf("%s",card3.cardExpirationDate);
	printf("Expected result :  WRONG_EXP_DATE \n");

	if(getCardExpiryDate(&card3)==0)
		printf("actual result is : CARD_OK\n");
	else
		printf("actual result : WRONG_EXP_DATE\n");

	printf("test case 3: \n");
	printf("input data :12\22 \n");
	scanf("%s",card3.cardExpirationDate);
	printf("Expected result :WRONG_EXP_DATE \n");

	if(getCardExpiryDate(&card3)==0)
		printf("actual result is : WRONG_EXP_DATE\n");
	else
		printf("actual result :  WRONG_EXP_DATE\n");



}
void getCardPANTest(void)
{
	//EN_cardError_t s;

	printf("function name :getCardPANTest \n");
	printf("test case 1: \n");
	printf("input data : 12345678912345678 \n");
	scanf("%s",card3.primaryAccountNumber);
	printf("Expected result is : CARD_OK\n");
	if(getCardPAN(&card3)==0)
		printf("actual result is : CARD_OK\n");
	else
		printf("actual result : WRONG_PAN\n");


	printf("test case 2: \n");
	printf("input data : 123456789 \n");
	scanf("%s",card3.primaryAccountNumber);
	printf("Expected result : WRONG_PAN \n");
	if(getCardPAN(&card3)==0)
		printf("actual result is : CARD_OK\n");
	else
		printf("actual result : WRONG_PAN\n");
	printf("test case 3: \n");
	printf("input data : 1234567az89 \n");
	scanf("%s",card3.primaryAccountNumber);
	printf("Expected result : WRONG_PAN \n");
	if(	getCardPAN(&card3)==0)
		printf("actual result is : CARD_OK\n");
	else
		printf("actual result : WRONG_PAN\n");

}

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
	uint8_t length = strlen(cardData ->cardHolderName);


	for( int i=0;cardData ->cardHolderName[i] !='\0';i++)
	{
		if(cardData ->cardHolderName[i] < 'a' || cardData ->cardHolderName[i] >'z')
		{
			if(cardData ->cardHolderName[i] < 'A' || cardData ->cardHolderName[i] >'Z')
			{
				if(cardData ->cardHolderName[i]==' ')
					continue;
				return WRONG_NAME;
				break;
			}
		}
	}


	if(length >= 20 && length <=24)
	{
		return CARD_OK;

	}
	else
	{
		return WRONG_NAME;
	}




}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
	uint8_t length = strlen(cardData -> cardExpirationDate);
	if(length < 5 || length >5 ||cardData -> cardExpirationDate[2] != '/' || atoi(cardData -> cardExpirationDate )>12 || atoi(cardData -> cardExpirationDate+3 )<22 )
	{
		return  WRONG_EXP_DATE;
	}
	else
	{
		return CARD_OK;
	}
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{

	int length = strlen(cardData -> primaryAccountNumber);
	for(int i=0;cardData->primaryAccountNumber[i] !='\0';i++)
	{
		for(char j='a';j<='z';j++)
		{
			if(cardData->primaryAccountNumber[i] == j)
			{

				return WRONG_PAN;
				break;
			}
		}
	}
	if(length >= 16 && length <=19)
	{
		return CARD_OK;
	}

	else
	{
		return WRONG_PAN;
	}


}
/*
void main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	//getCardHolderNameTest();
	//getCardExpiryDateTest();
	getCardPANTest();

}
*/
	/*
	//Testing CardHolderName
	EN_cardError_t card2;
	 card2 = getCardHolderName("nadia karam abdelm");

	if(card2 == CARD_OK)
	{
		printf("CARD_OK");
	}
	else
	{
		printf("wrong name");
	}

	 */
	//Testing cardExpirationDate
	/*
	ST_cardData_t card3;
	gets(card3.cardExpirationDate);
	EN_cardError_t card = getCardExpiryDate(&card3);
	if(card == CARD_OK)
	{
		printf("CARD_OK");
	}
	else
	{
		printf("WRONG_EXP_DATE");
	}
	 */


//Testing CardPan
/*
	ST_cardData_t card2;
	gets(card2.primaryAccountNumber);
	EN_cardError_t card = getCardPAN(&card2);
	if(card == CARD_OK)
	{
		printf("CARD_OK");
	}
	else
	{
		printf("WRONG_PAN");
	}
 */


