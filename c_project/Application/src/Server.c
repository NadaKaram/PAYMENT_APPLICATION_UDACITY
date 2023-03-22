/*
 ============================================================================
 Name        : Server.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
//initialize the array with structures to test the list function then do videos to test every function and do the app
#include <stdio.h>
#include <stdlib.h>
#include "Server.h"
ST_accountsDB_t accountsDB[255] ={{20000,RUNNING,"1234567891012345"},
		{40000,BLOCKED,"1234567890567808"},{(float)50000,BLOCKED,"1234567890567700"},{(float)40000,RUNNING,"1234567890565608"},
		{50000,RUNNING,"1234567890567878"},{70000,RUNNING,"1234567890567898"},{90000,RUNNING,"1234567890567808"},{40000,BLOCKED,"1234567890567809"}};
ST_transaction_t array[255]={0};
ST_cardData_t card2;
ST_terminalData_t card4;
ST_transaction_t transData;
static int k=0;

void isValidAccountTest(void)
{
	printf("the function name :  isValidAccountTest \n");
	printf("test case 1: \n");
	printf("input data :1234567891012345 \n");
	scanf("%s",card2.primaryAccountNumber);
	printf("Expected result is :SERVER_OK \n");
	if( isValidAccount(&card2,accountsDB) == CARD_OK)
	{
		printf("Actual result : SERVER_OK\n");
	}
	else
	{
		printf("Actual result : ACCOUNT_NOT_FOUND\n");
	}
	printf("test case 2: \n");
	printf("input data :1234567890567898\n");
	scanf("%s",card2.primaryAccountNumber);
	printf("Expected result is :SERVER_OK \n");
	if( isValidAccount(&card2,accountsDB) == CARD_OK)
	{
		printf("Actual result : SERVER_OK\n");
	}
	else
	{
		printf("Actual result : ACCOUNT_NOT_FOUND\n");
	}
	printf("test case 3: \n");
	printf("input data :1234567899506432\n");
	scanf("%s",card2.primaryAccountNumber);
	printf("Expected result is :ACCOUNT_NOT_FOUND \n");
	if( isValidAccount(&card2,accountsDB) == CARD_OK)
	{
		printf("Actual result : SERVER_OK\n");
	}
	else
	{
		printf("Actual result : ACCOUNT_NOT_FOUND\n");
	}
}
void isBlockedAccountTest(void)
{
	printf("the function name :  isBlockedAccountTest \n");
	printf("test case 1: \n");
	printf("input data : account 1\n");

	if( isBlockedAccount(accountsDB)== CARD_OK)
	{
		printf("SERVER_OK \n");
	}
	else
	{
		printf("BLOCKED_ACCOUNT\n");
	}
	printf("test case 2: \n");
	printf("input data : account 2\n");

	if( isBlockedAccount(&accountsDB[1])== CARD_OK)
	{
		printf("SERVER_OK\n");
	}
	else
	{
		printf("BLOCKED_ACCOUNT\n");
	}
	printf("test case 3: \n");
	printf("input data : account 4\n");

	if( isBlockedAccount(&accountsDB[3])== CARD_OK)
	{
		printf("SERVER_OK\n");
	}
	else
	{
		printf("BLOCKED_ACCOUNT\n");
	}
}
void isAmountAvailableTest(void)
{
	printf("the function name : isAmountAvailableTest \n");
	printf("test case 1: for account 1 \n");
	printf("input data : 15000\n");
	scanf("%f",&card4.transAmount);
	printf("the expected result is : SERVER_OK\n");
	if(isAmountAvailable(&card4, accountsDB) == CARD_OK)
	{
		printf("Actual Result : SERVER_OK\n");
	}
	else
	{
		printf("Actual Result : LOW_BALANCE\n");
	}
	printf("test case 2: for account 1 \n");
	printf("input data : 25000\n");
	scanf("%f",&card4.transAmount);
	printf("the expected result is :  LOW_BALANCE\n");
	if(isAmountAvailable(&card4, accountsDB) == CARD_OK)
	{
		printf("Actual Result : SERVER_OK\n");
	}
	else
	{
		printf("Actual Result : LOW_BALANCE\n");
	}
	printf("test case 3 : for account 2 \n");
	printf("input data : 35000\n");
	scanf("%f",&card4.transAmount);
	printf("the expected result is : SERVER_OK\n");
	if(isAmountAvailable(&card4, &accountsDB[1]) == CARD_OK)
	{
		printf("Actual Result : SERVER_OK\n");
	}
	else
	{
		printf("Actual Result : LOW_BALANCE\n");
	}
	printf("test case 4 : for account 2 \n");
	printf("input data : 50000\n");
	scanf("%f",&card4.transAmount);
	printf("the expected result is :  LOW_BALANCE\n");
	if(isAmountAvailable(&card4, &accountsDB[1]) == CARD_OK)
	{
		printf("Actual Result : SERVER_OK\n");
	}
	else
	{
		printf("Actual Result : LOW_BALANCE\n");
	}
}
void recieveTransactionDataTest(void)
{


	for(int i=0;i<8;i++)
	{
		if(recieveTransactionData(&array[i])==APPROVED)
		{
			printf("the state of %s is :",array[i].cardHolderData.primaryAccountNumber);
			printf("APPROVED\n");
			array[i].transState=0;
		}
		else if(recieveTransactionData(&array[i])==FRAUD_CARD)
		{
			printf("the state of %s is :",array[i].cardHolderData.primaryAccountNumber);
			printf("FRAUD_CARD\n");
			array[i].transState=3;
		}
		else if(recieveTransactionData(&array[i])==DECLINED_STOLEN_CARD)
		{
			printf("the state of %s is :",array[i].cardHolderData.primaryAccountNumber);
			printf("DECLINED_STOLEN_CARD\n");
			array[i].transState=2;
		}
		else if(recieveTransactionData(&array[i])==DECLINED_INSUFFECIENT_FUND)
		{
			printf("the state of %s is :",array[i].cardHolderData.primaryAccountNumber);
			printf("DECLINED_INSUFFECIENT_FUND\n");
			array[i].transState=1;
		}
		else if(recieveTransactionData(&array[i])==INTERNAL_SERVER_ERROR)
		{
			printf("the state of %s is :",array[i].cardHolderData.primaryAccountNumber);
			printf("INTERNAL_SERVER_ERROR\n");
			array[i].transState=4;
		}
		printf("\n");
		k++;
	}
}

EN_transStat_t recieveTransactionData( ST_transaction_t *transData)
{


	if(isBlockedAccount(&accountsDB[k])==BLOCKED_ACCOUNT)
	{
		array[k].transState=DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;
	}

	else if(isAmountAvailable(&transData[52],&accountsDB[k])==LOW_BALANCE)
	{
		array[k].transState=DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}

	else if(saveTransaction(transData)==TRANSACTION_NOT_FOUND)
	{
		array[k].transState=INTERNAL_SERVER_ERROR;
		return INTERNAL_SERVER_ERROR;
	}
	else
	{
		array[k].transState=APPROVED;
		return APPROVED;
	}

}
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence)
{
	for(int i=0;i<10;i++)
	{
		if (strcmp(cardData ->primaryAccountNumber,accountRefrence[i].primaryAccountNumber)==0)
		{
			return SERVER_OK;
		}

	}

	return  ACCOUNT_NOT_FOUND;
}
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{

	if (accountRefrence->state == 0)
	{
		return SERVER_OK;
	}
	else if(accountRefrence->state == 1)
	{
		return BLOCKED_ACCOUNT;
	}

}
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence)
{
	if(termData ->transAmount <= accountRefrence->balance )
	{
		return  SERVER_OK;
	}
	else
	{
		return LOW_BALANCE;
	}

}
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
	for(int m=0;m<10;m++)
	{
		transData[m].transactionSequenceNumber=m+1;
	}
	for(int m=0;m<10;m++)
	{

		if(transData[m].transState == APPROVED)
		{
			return SERVER_OK;
		}
		else if (transData [m].transState == FRAUD_CARD)
		{
			return ACCOUNT_NOT_FOUND;
		}
		else if(transData[m].transState == DECLINED_STOLEN_CARD)
		{
			return  BLOCKED_ACCOUNT ;
		}
		else if(transData[m].transState ==  DECLINED_INSUFFECIENT_FUND)
		{
			return LOW_BALANCE;
		}
		else if(transData [m].transState==  INTERNAL_SERVER_ERROR)
		{
			return TRANSACTION_NOT_FOUND;
		}
	}
}

void listSavedTransactions(void)
{
	for(int i=0;i<8;i++)
	{
		printf("##########################\n");
		printf("Transaction Sequence Number: %d\n",array[i].transactionSequenceNumber);
		printf("Transaction Date: %s\n",array[i].terminalData.transactionDate);
		printf("Transaction Amount: %f\n",array[i].terminalData.transAmount);
		if(array[i].transState==0)
		{
			printf("Transaction State: APPROVED\n");
		}
		else if(array[i].transState==1)
		{
			printf("Transaction State: DECLINED_INSUFFECIENT_FUND\n");
		}
		else if(array[i].transState==2)
		{
			printf("Transaction State: DECLINED_STOLEN_CARD\n");
		}
		else if(array[i].transState==3)
		{
			printf("Transaction State: FRAUD_CARD\n");
		}
		else if(array[i].transState==4)
		{
			printf("Transaction State: INTERNAL_SERVER_ERROR\n");
		}

		printf("Terminal Max Amount: %f\n",array[i].terminalData.maxTransAmount);
		printf("Cardholder Name: %s",array[i].cardHolderData.cardHolderName);
		printf("\n");
		printf("PAN: %s\n",array[i].cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date:%s\n",array[i].cardHolderData.cardExpirationDate);
		printf("##########################\n");
		printf("\n");
	}
}
void saveTransactionTest(void)
{
	saveTransaction(array);
}
void listSavedTransactionsTest(void)
{
	printf("enter name 1 :\n");
	gets(array[0].cardHolderData.cardHolderName);
	printf("enter name 2 :\n");
	gets(array[1].cardHolderData.cardHolderName);
	printf("enter expiration date");
	gets(array[0].cardHolderData.cardExpirationDate);
	printf("enter expiration date");
	gets(array[1].cardHolderData.cardExpirationDate);
	printf("enter pan");
	gets(array[0].cardHolderData.primaryAccountNumber);
	printf("enter pan");
	gets(array[1].cardHolderData.primaryAccountNumber);
	array[0].terminalData.transAmount=1000;
	array[1].terminalData.transAmount=2000;
	array[0].terminalData.maxTransAmount=30000;
	array[1].terminalData.maxTransAmount=40000;
	listSavedTransactions();
}



	//printf("%x\n",&transData+51);
	//printf("%x\n",&(transData->cardHolderData));

	//printf("%d\n",*(transData+51));





	/* Testing isVald account
	ST_cardData_t card2;
		gets(card2.primaryAccountNumber);
		EN_serverError_t card= isValidAccount(&card2,accountsDB);
		if(card == CARD_OK)
		{
			printf("SERVER_OK");
		}
		else
		{
			printf(" ACCOUNT_NOT_FOUND");
		}
	 */
	/* Testing blocked account
	EN_serverError_t card= isBlockedAccount(accountsDB);
			if(card == CARD_OK)
			{
				printf("SERVER_OK");
			}
			else
			{
				printf("BLOCKED_ACCOUNT");
			}
	 */
	/* transAmount
	ST_terminalData_t card4;
	scanf("%f",&card4.transAmount);
	EN_serverError_t card= isAmountAvailable(&card4, accountsDB);
	if(card == CARD_OK)
	{
		printf("SERVER_OK");
	}
	else
	{
		printf("LOW_BALANCE");
	}
	 */

	/*
	for(int i=0;i<10;i++)
	{
		if(recieveTransactionData(&array[i])==APPROVED)
		{
			printf("the state of %s is :",accountsDB[i].primaryAccountNumber);
			printf("APPROVED");
			array[i].transState=0;
		}
		else if(recieveTransactionData(&array[i])==FRAUD_CARD)
		{
			printf("the state of %s is :",accountsDB[i].primaryAccountNumber);
			printf("FRAUD_CARD\n");
			array[i].transState=3;
		}
		else if(recieveTransactionData(&array[i])==DECLINED_STOLEN_CARD)
		{
			printf("the state of %s is :",accountsDB[i].primaryAccountNumber);
			printf("DECLINED_STOLEN_CARD\n");
			array[i].transState=2;
		}
		else if(recieveTransactionData(&array[i])==DECLINED_INSUFFECIENT_FUND)
		{
			printf("the state of %s is :",accountsDB[i].primaryAccountNumber);
			printf("DECLINED_INSUFFECIENT_FUND\n");
			array[i].transState=1;
		}
		else if(recieveTransactionData(&array[i])==INTERNAL_SERVER_ERROR)
		{
			printf("the state of %s is :",accountsDB[i].primaryAccountNumber);
			printf("INTERNAL_SERVER_ERROR\n");
			array[i].transState=4;
		}
		printf("\n");
		k++;
	}
	 */
	/*
	recieveTransactionData(array);

	/*
	for(int i=0;i<10;i++)
	{
		printf("the state of %s is %d",accountsDB[i].primaryAccountNumber,array[i].transactionSequenceNumber);
		printf("\n");
	}


	 */







