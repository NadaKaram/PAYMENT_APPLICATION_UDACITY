/*
 ============================================================================
 Name        : Application.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Application.h"
ST_cardData_t card6;
extern ST_terminalData_t card4;
extern ST_accountsDB_t accountsDB[255];
extern ST_transaction_t array[255];
int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	printf("enter the holder name\n");
	if (getCardHolderName(gets(array[0].cardHolderData.cardHolderName))==WRONG_NAME)
	{
		printf("wrong name");

	}
	else
	{
		printf("enter the expiration date");
		gets(array[0].cardHolderData.cardExpirationDate);
		strcpy(card6.cardExpirationDate,array[0].cardHolderData.cardExpirationDate);
		if(getCardExpiryDate(&array[0])==WRONG_EXP_DATE)
		{
			printf("WRONG_EXP_DATE");
		}
		else
		{
			printf("Enter card PAN");
			gets(array[0].cardHolderData.primaryAccountNumber);
			strcpy(card6.primaryAccountNumber,array[0].cardHolderData.primaryAccountNumber);
			if(getCardPAN(&card6)==WRONG_PAN)
			{
				printf("WRONG_PAN");
			}
			else
			{
				printf("enter the transaction date");
				gets(array[0].terminalData.transactionDate);
                 strcpy(card4.transactionDate,array[0].terminalData.transactionDate);
				if(isCardExpired(&card6,&card4)==EXPIRED_CARD )
				{
					printf("Declined expired card");

				}
				else
				{
					printf("enter the transaction amount");
					scanf("%f",&array[0].terminalData.transAmount);
					card4.transAmount=array[0].terminalData.transAmount;
					array[0].terminalData.maxTransAmount=5000;
					card4.maxTransAmount=array[0].terminalData.maxTransAmount;
					if( (isBelowMaxAmount(&card4))==EXCEED_MAX_AMOUNT)
					{
                           printf("Declind Amount Exceeding limit");
					}
					else
					{


						if(isValidAccount(&card6,accountsDB)==ACCOUNT_NOT_FOUND)
						{
							printf("Declind valid account");
						}
						else
						{
							printf("valid account");
                              if(recieveTransactionData(&array[0])==DECLINED_STOLEN_CARD)
                              {
                            	  printf("DECLINED_STOLEN_CARD");
                              }
                              else
                              {
							if(isAmountAvailable(&card4,&accountsDB[0])==LOW_BALANCE)
							{
								printf("Declined insufficient fund");
							}
							else
							{
								array[0].terminalData.maxTransAmount -=array[0].terminalData.transAmount;
								accountsDB[0].balance=array[0].terminalData.maxTransAmount;
								printf("the new balance is : %f\n",accountsDB[0].balance);
								 saveTransaction(array);
								 listSavedTransactions();
							}
                              }
						}
					}

				}
			}
			{

			}
		}
	}





	/*
	getCardHolderNameTest();
	getCardExpiryDateTest();
	getCardPANTest();
	 */
	/*
	getTransactionDateTest();
	printf("\n");
	isCardExpriedTest();
	printf("\n");
	getTransactionAmountTest();
	printf("\n");
	isBelowMaxAmountTest();
	printf("\n");
	setMaxAmountTest();
	 */
	/*
	isValidAccountTest();
	printf("\n");
	isBlockedAccountTest();
	printf("\n");
	isAmountAvailableTest();
	printf("\n");
	 */
	/*
	recieveTransactionDataTest();
	saveTransactionTest();
	listSavedTransactionsTest();
	 */

}
