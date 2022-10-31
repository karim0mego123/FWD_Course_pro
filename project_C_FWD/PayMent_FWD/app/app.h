#ifndef APPLICATION_APP_H_
#define APPLICATION_APP_H_

#include "server.h"
extern ST_accountsDB_t DB_arr[MaxAcountsDateBase] ;
extern uint8_t NumCurrentAccount ;
void display(ST_transaction_t *transData);
void appStart(void);
#define 	getCardHolderName1		1
#define 	getCardExpiryDate1		2
#define 	getCardPAN1				3
#define 	getTransactionDate1		4
#define 	isCardExpriedTest1		5
#define 	getTransactionAmount1	6
#define 	setMaxAmount1			7
#define 	isBelowMaxAmount1		8


#endif  /* APPLICATION_APP_H_ */
