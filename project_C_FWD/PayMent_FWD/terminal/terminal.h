/*
  * terminal.h
 *
 *  Created on: Oct 8, 2022
 *      Author: karim
 */

#ifndef TERMINAL_TERMINAL_H_
#define TERMINAL_TERMINAL_H_

#include "card.h"
#define MaxTransactionDate	10
#define Max_amount			6000
typedef struct ST_terminalData_t
{
	float transAmount;
	float maxTransAmount;
	uint8_t transactionDate[MaxTransactionDate];
} ST_terminalData_t;

typedef enum EN_terminalError_t
{
     TERMINAL_OK,
	 WRONG_DATE,
	 EXPIRED_CARD,
	 INVALID_CARD,
	 INVALID_AMOUNT,
	 EXCEED_MAX_AMOUNT,
	 INVALID_MAX_AMOUNT
}EN_terminalError_t ;

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
/************************************************************
 * Name : not a getTransactionDate (API)					*
 * Param(in) : NA											*
 * Param(out) : CardData									*
 * Param(in/out) : NA										*
 * return : EN_cardError_t 									*
 * Author : Kareim Elmligy                                  *
 * Last Modification : 28/10                                *
 ***********************************************************/
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);
/************************************************************
 * Name : not a primitive datatype(API)						*
 * Param(in) : NA											*
 * Param(out) : CardData									*
 * Param(in/out) : NA										*
 * return : EN_cardError_t 									*
 * Author : Kareim Elmligy                                  *
 * Last Modification : 28/10                                *
 ***********************************************************/

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
/************************************************************
 * Name : getTransactionAmount(API)							*
 * Param(in) : NA											*
 * Param(out) : CardData									*
 * Param(in/out) : NA										*
 * return : EN_cardError_t 									*
 * Author : Kareim Elmligy                                  *
 * Last Modification : 28/10                                *
 ***********************************************************/

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
/************************************************************
 * Name : isBelowMaxAmount(API)								*
 * Param(in) : NA											*
 * Param(out) : CardData									*
 * Param(in/out) : NA										*
 * return : EN_cardError_t 									*
 * Author : Kareim Elmligy                                  *
 * Last Modification : 28/10                                *
 ***********************************************************/

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData);
/************************************************************
 * Name : setMaxAmount(API)									*
 * Param(in) : NA											*
 * Param(out) : CardData									*
 * Param(in/out) : NA										*
 * return : EN_cardError_t 									*
 * Author : Kareim Elmligy                                  *
 * Last Modification : 28/10                                *
 ***********************************************************/

void getTransactionDateTest(void);
/************************************************************
 * Name : getTransactionDateTest(API)						*
 * Param(in) : NA											*
 * Param(out) : CardData									*
 * Param(in/out) : NA										*
 * return : EN_cardError_t 									*
 * Author : Kareim Elmligy                                  *
 * Last Modification : 28/10                                *
 ***********************************************************/

bool format_true( string TestData );
/************************************************************
 * Name : format_true(API)									*
 * Param(in) : NA											*
 * Param(out) : CardData									*
 * Param(in/out) : NA										*
 * return : EN_cardError_t 									*
 * Author : Kareim Elmligy                                  *
 * Last Modification : 28/10                                *
 ***********************************************************/
void isCardExpriedTest(void);
/************************************************************
 * Name : isCardExpriedTest(API)							*
 * Param(in) : NA											*
 * Param(out) : CardData									*
 * Param(in/out) : NA										*
 * return : EN_cardError_t 									*
 * Author : Kareim Elmligy                                  *
 * Last Modification : 28/10                                *
 ***********************************************************/
void getTransactionAmountTest(void);
/************************************************************
 * Name : getTransactionAmountTest(API)						*
 * Param(in) : NA											*
 * Param(out) : CardData									*
 * Param(in/out) : NA										*
 * return : EN_cardError_t 									*
 * Author : Kareim Elmligy                                  *
 * Last Modification : 28/10                                *
 ***********************************************************/
void setMaxAmountTest(void);
/************************************************************
 * Name : setMaxAmountTest(API)								*
 * Param(in) : NA											*
 * Param(out) : CardData									*
 * Param(in/out) : NA										*
 * return : EN_cardError_t 									*
 * Author : Kareim Elmligy                                  *
 * Last Modification : 28/10                                *
 ***********************************************************/
void isBelowMaxAmountTest(void);
/************************************************************
 * Name : isBelowMaxAmountTest(API)							*
 * Param(in) : NA											*
 * Param(out) : CardData									*
 * Param(in/out) : NA										*
 * return : EN_cardError_t 									*
 * Author : Kareim Elmligy                                  *
 * Last Modification : 28/10                                *
 ***********************************************************/
#endif /* TERMINAL_TERMINAL_H_ */
