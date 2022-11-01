#include "server.h"

ST_accountsDB_t DB_arr[MaxAcountsDateBase] = {
		{3000.241f,RUNNING,"456351985072075340"},
		{2000.12f,RUNNING,"321654987456132798"},
		{9000.213f,RUNNING,"089732057830583898"},
		{7000.214f,BLOCKED,"078329857983750289"},
		{6000.1212f,RUNNING,"097349057880925794"},
		{1000.09f,RUNNING,"073480583748092789"},
		{4000.89f,BLOCKED,"136871323216548751"},
		{213214.09f,RUNNING,"0734812318092789"},
		{41230.89f,BLOCKED,"13687132321621351"},
		{8000.789f,RUNNING,"348976523896529753"}};

ST_accountsDB_t DB_Stolen[MaxAcountsDateBase] = {
		{1000.12f,RUNNING,"312421312421323133"},
		{5001.124f,BLOCKED,"413214123141412343"}} ;

uint8_t Actual_numAccounts_DataBase = 10u ;
uint8_t NumCurrentAccount = 0 ;
uint8_t NUM_Transactions  = 2 ;
uint32_t transactionSequenceNumber = 0 ;

ST_transaction_t TrsnsactionsDataBase[MaxAcountsDateBase] = {{{"karim ayman abdel latef", "8921739471289491", "09/23"}, {3423.0f, 234234.0f, "30/10/2022"},TERMINAL_OK,1},
		{{"ahmed ayman abdel latef" , "9018420830803280", "10/24"}, {2323.0f, 23522.0f, "28/10/2022"} ,TERMINAL_OK,0} };

EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
	EN_transState_t Return_Status = APPROVED ;

	getCardHolderName(&(transData->cardHolderData)) ;
	getCardExpiryDate(&(transData->cardHolderData)) ;
	getTransactionDate(&(transData->terminalData)) ;
	getCardPAN		 (&(transData->cardHolderData)) ;
	setMaxAmount(&(transData->terminalData)) ;
	getTransactionAmount(&(transData->terminalData)) ;

	if ( isCardExpired(transData->cardHolderData,transData->terminalData)  == EXPIRED_CARD )
	{
		Return_Status = EXPIRED_CARD ;
		return  Return_Status ;
	}

	if ( isValidAccount(&(transData->cardHolderData)) == ACCOUNT_NOT_FOUND )
	{
		Return_Status = ACCOUNT_NOT_FOUND ;
		return Return_Status ;
	}

	if ( isBlockedAccount() == BLOCKED )
	{
		Return_Status = BLOCKED_ACCOUNT ;
		return BLOCKED_ACCOUNT ;
	}

	if (isBelowMaxAmount(&(transData->terminalData)) == EXCEED_MAX_AMOUNT )
	{
		Return_Status = EXCEED_MAX_AMOUNT ;
		return Return_Status ;
	}

	if ( isAmountAvailable(&(transData->terminalData)) == LOW_BALANCE )
	{
		Return_Status = LOW_BALANCE ;
		return Return_Status ;
	}


	if ( saveTransaction(transData) == SERVER_OK )
	{
		Return_Status = SERVER_OK ;
		return Return_Status ;
	}
	return APPROVED  ;
}
EN_serverError_t isValidAccount(ST_cardData_t *cardData)
{
	uint8_t Loc_Count = 0u ;
	EN_serverError_t Return_Status = ACCOUNT_NOT_FOUND ;

	for ( Loc_Count = 0 ; Loc_Count < Actual_numAccounts_DataBase ; Loc_Count++ )
	{
		if ( stricmp( (string)cardData->primaryAccountNumber , (string)DB_arr[Loc_Count].primaryAccountNumber  ) == 0 )
		{
			Return_Status =  SERVER_OK ;
			NumCurrentAccount = Loc_Count ;
			return Return_Status ;
		}
	}

	for ( Loc_Count = 0 ; Loc_Count < NumStolenCard ; Loc_Count++ )
	{
		if ( stricmp( (string)cardData->primaryAccountNumber , (string)DB_Stolen[Loc_Count].primaryAccountNumber  ) == 0 )
		{
			Return_Status = stolen ;
			printf("stolen card\n") ;
			exit(true) ;
		}
	}
	return ACCOUNT_NOT_FOUND ;
}
EN_accountState_t isBlockedAccount(void)
{
	EN_accountState_t Return_Status = RUNNING ;
	if ( DB_arr[NumCurrentAccount].state == BLOCKED )
	{
		Return_Status = BLOCKED ;
		return BLOCKED ;
	}
	return Return_Status ;
}
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
	EN_serverError_t Return_Status = SERVER_OK ;
	if ( termData->transAmount > DB_arr[NumCurrentAccount].balance )
	{
		Return_Status = LOW_BALANCE ;
	}
	return Return_Status ;
}
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
	EN_serverError_t Return_Status = SERVER_OK ;
	uint32_t Loc_Test , Loc_count = 0 ;
	if (NUM_Transactions > MaxNumTransaction)
	{
		Return_Status = SAVING_FAILED ;
		printf("saving failed\n") ;
		return Return_Status ;
	}
	/* save card informations
	 *     DB_arr[NumCurrentAccount].balance -= transData->terminalData.transAmount ;
	 *			*/

	DB_arr[NumCurrentAccount].balance -= transData->terminalData.transAmount;

	strcpy((string)TrsnsactionsDataBase[NUM_Transactions].cardHolderData.cardHolderName, (string)transData->cardHolderData.cardHolderName);
	strcpy((string)TrsnsactionsDataBase[NUM_Transactions].cardHolderData.primaryAccountNumber, (string)transData->cardHolderData.primaryAccountNumber);
	strcpy((string)TrsnsactionsDataBase[NUM_Transactions].cardHolderData.cardExpirationDate, (string)transData->cardHolderData.cardExpirationDate);

	/* save terminal informations			*/
	strcpy((string)TrsnsactionsDataBase[NUM_Transactions].terminalData.transactionDate, (string)transData->terminalData.transactionDate);
	TrsnsactionsDataBase[NUM_Transactions].terminalData.transAmount = transData->terminalData.transAmount;
	TrsnsactionsDataBase[NUM_Transactions].terminalData.maxTransAmount = transData->terminalData.maxTransAmount;

	/* save transaction's informations		*/
	TrsnsactionsDataBase[NUM_Transactions].transactionSequenceNumber = NUM_Transactions;
	TrsnsactionsDataBase[NUM_Transactions].transState = transData->transState;
	printf("enter 1 to git all transactions\n") ;
	CLEAR_BUFFER() ;
	scanf("%d",&Loc_Test) ;
	NUM_Transactions++;
	if ( Loc_Test == 1)
	{
		for (Loc_count = 0 ; Loc_count< NUM_Transactions ; Loc_count++ )
		{
			display(TrsnsactionsDataBase[Loc_count]) ;
		}
	}

	/* increament for the next transaction	*/
	return Return_Status ;

}
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData)
{
	/*so this sequnce number is not been used*/
	EN_serverError_t Return_Status = SERVER_OK ;
	if (transactionSequenceNumber >= NUM_Transactions)
	{
		Return_Status = TRANSACTION_NOT_FOUND ;
	}

	/* get card informations
	 */
	strcpy((string)transData->cardHolderData.cardHolderName, (string)TrsnsactionsDataBase[transactionSequenceNumber].cardHolderData.cardHolderName);
	strcpy((string)transData->cardHolderData.primaryAccountNumber, (string)TrsnsactionsDataBase[transactionSequenceNumber].cardHolderData.primaryAccountNumber);
	strcpy((string)transData->cardHolderData.cardExpirationDate, (string)TrsnsactionsDataBase[transactionSequenceNumber].cardHolderData.cardExpirationDate);

	/* get terminal informations			*/
	strcpy((string)transData->terminalData.transactionDate, (string)TrsnsactionsDataBase[transactionSequenceNumber].terminalData.transactionDate);
	transData->terminalData.maxTransAmount  = TrsnsactionsDataBase[transactionSequenceNumber].terminalData.maxTransAmount;
	transData->terminalData.transAmount = TrsnsactionsDataBase[transactionSequenceNumber].terminalData.transAmount;

	/* get transaction informations		*/
	transData->transactionSequenceNumber = transactionSequenceNumber;
	transData->transState = TrsnsactionsDataBase[transactionSequenceNumber].transState;


	return Return_Status ;
}
