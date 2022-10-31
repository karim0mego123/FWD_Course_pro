#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_

#include  "terminal.h"

#define MaxAcountsDateBase	255
#define MaxNumTransaction	255
#define NumStolenCard	2
typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t  terminalData;
	EN_terminalError_t transState;
	uint32_t transactionSequenceNumber;
}ST_transaction_t;

typedef enum EN_transState_t
{
     APPROVED,
	 DECLINED_INSUFFECIENT_FUND,
	 DECLINED_STOLEN_CARD,
	 FRAUD_CARD,
	 INTERNAL_SERVER_ERROR,
	 stolen
}EN_transState_t;

typedef enum EN_serverError_t
{
     SERVER_OK,
	 SAVING_FAILED,
	 TRANSACTION_NOT_FOUND,
	 ACCOUNT_NOT_FOUND,
	 LOW_BALANCE,
	 BLOCKED_ACCOUNT=6,

}EN_serverError_t ;

typedef enum EN_accountState_t
{
     RUNNING,
     BLOCKED
}EN_accountState_t;

typedef struct ST_accountsDB_t
{
     float balance;
     EN_accountState_t state;
     uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;


EN_transState_t recieveTransactionData(ST_transaction_t *transData);
/************************************************************
 * Name : getCardHolderName(API)							*
 * Param(in) : NA											*
 * Param(out) : CardData									*
 * Param(in/out) : NA										*
 * return : EN_cardError_t 									*
 * Author : Kareim Elmligy                                  *
 * Last Modification : 28/10                                *
 ***********************************************************/

EN_serverError_t isValidAccount(ST_cardData_t *cardData);
/************************************************************
 * Name : getCardHolderName(API)							*
 * Param(in) : NA											*
 * Param(out) : CardData									*
 * Param(in/out) : NA										*
 * return : EN_cardError_t 									*
 * Author : Kareim Elmligy                                  *
 * Last Modification : 28/10                                *
 ***********************************************************/

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData);
/************************************************************
 * Name : getCardHolderName(API)							*
 * Param(in) : NA											*
 * Param(out) : CardData									*
 * Param(in/out) : NA										*
 * return : EN_cardError_t 									*
 * Author : Kareim Elmligy                                  *
 * Last Modification : 28/10                                *
 ***********************************************************/

EN_serverError_t saveTransaction(ST_transaction_t *transData);
/************************************************************
 * Name : getCardHolderName(API)							*
 * Param(in) : NA											*
 * Param(out) : CardData									*
 * Param(in/out) : NA										*
 * return : EN_cardError_t 									*
 * Author : Kareim Elmligy                                  *
 * Last Modification : 28/10                                *
 ***********************************************************/

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData);
/************************************************************
 * Name : getCardHolderName(API)							*
 * Param(in) : NA											*
 * Param(out) : CardData									*
 * Param(in/out) : NA										*
 * return : EN_cardError_t 									*
 * Author : Kareim Elmligy                                  *
 * Last Modification : 28/10                                *
 ***********************************************************/

EN_accountState_t isBlockedAccount(void);
/************************************************************
 * Name : getCardHolderName(API)							*
 * Param(in) : NA											*
 * Param(out) : CardData									*
 * Param(in/out) : NA										*
 * return : EN_cardError_t 									*
 * Author : Kareim Elmligy                                  *
 * Last Modification : 28/10                                *
 ***********************************************************/

#endif /* SERVER_SERVER_H_ */
