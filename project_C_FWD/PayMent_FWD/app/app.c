#include "app.h"
void appStart(void)
{
	ST_transaction_t transaction = {{"", "", ""}, {0.0f, 0.0f, ""}, 0, 0};
	EN_transState_t flag = recieveTransactionData(&transaction);
	switch (flag)
	{
	case EXPIRED_CARD:
		printf("EXPIRED_CARD\n");
		break;

	case EXCEED_MAX_AMOUNT:
		printf("EXCEEDING THE LIMIT\n");
		break;
	case LOW_BALANCE:
		printf("LOW_BALANCE\n");
		break;
	case ACCOUNT_NOT_FOUND :
		printf("ACCOUNT NOT found\n") ;
		break ;
	case APPROVED :
		printf("APPROVED\n");
		display(&transaction);
		break ;
	case BLOCKED_ACCOUNT :
		printf("blocked account\n") ;
		break;
	}

}
void display(ST_transaction_t *transData)
{
	printf("Card's Holder Name: %s", transData->cardHolderData.cardHolderName);
	printf("Card PAN: %s\n", transData->cardHolderData.primaryAccountNumber);
	printf("Card Expiry Date: %s\n", transData->cardHolderData.cardExpirationDate);
	printf("Transaction Date: %s\n", transData->terminalData.transactionDate);
	printf("Transaction Maximum Amount: %.2f\n", transData->terminalData.maxTransAmount);
	printf("Transaction Amount: %.2f\n", transData->terminalData.transAmount);
	printf("current money in card = %.2f\n",DB_arr[NumCurrentAccount].balance);
}
