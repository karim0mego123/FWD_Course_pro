#ifndef CARD_CARD_H_
#define CARD_CARD_H_

#include "Common.h"
#include "ctype.h"

#define CLEAR_BUFFER()	fflush(stdin) ; \
						fflush(stdout);

#define CARD_HALDER_NALMELEN 	25u
#define PRIM_ACCOUNTNUM_LEN   	20u
#define CARD_EXPIRE_DATE 	6u

#define CARD_HALDER_NALMELEN_MAx   (CARD_HALDER_NALMELEN)
#define CARD_HALDER_NALMELEN_Min   (CARD_HALDER_NALMELEN-5)


typedef struct ST_cardData_t
{
	uint8_t cardHolderName[CARD_HALDER_NALMELEN];
	uint8_t primaryAccountNumber[PRIM_ACCOUNTNUM_LEN];
	uint8_t cardExpirationDate[CARD_EXPIRE_DATE];
}ST_cardData_t;

typedef enum EN_cardError_t
{
	CARD_OK=0,
	WRONG_NAME,
	WRONG_EXP_DATE,
	WRONG_PAN,
	CARD_NOK,
	ENUM_cardError_LEN
}EN_cardError_t;


EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
/************************************************************
 * Name : getCardHolderName(API)							*
 * Param(in) : NA											*
 * Param(out) : CardData									*
 * Param(in/out) : NA										*
 * return : EN_cardError_t 									*
 * Author : Kareim Elmligy                                  *
 * Last Modification : 28/10                                *
 ***********************************************************/

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
/************************************************************
- * Name : getCardExpiryDate(API)							*
 * Param(in) : NA											*
 * Param(out) : CardData									*
 * Param(in/out) : NA										*
 * return : EN_cardError_t 									*
 * Author : Kareim Elmligy                                  *
 * Last Modification : 28/10                                *
 ***********************************************************/

EN_cardError_t getCardPAN(ST_cardData_t *cardData);
/************************************************************
 * Name : getCardPAN(API)									*
 * Param(in) : NA											*
 * Param(out) : CardData									*
 * Param(in/out) : NA										*
 * return : EN_cardError_t 									*
 * Author : Kareim Elmligy                                  *
 * Last Modification : 28/10                                *
 ***********************************************************/

bool isAlphanumeric(uint8_t *arr , uint8_t Loc_NameSize );
/************************************************************
 * Name : isAlphanumeric(API)								*
 * Param(in) : NA											*
 * Param(out) : CardData									*
 * Param(in/out) : NA										*
 * return : EN_cardError_t 									*
 * Author : Kareim Elmligy                                  *
 * Last Modification : 28/10                                *
 ***********************************************************/

bool format_is_true(uint8_t *arr,uint8_t Loc_NameSize );
/************************************************************
 * Name : format_is_true(API)								*
 * Param(in) : NA											*
 * Param(out) : CardData									*
 * Param(in/out) : NA										*
 * return : EN_cardError_t 									*
 * Author : Kareim Elmligy                                  *
 * Last Modification : 28/10                                *
 ***********************************************************/

void getCardPANTest (void);
/************************************************************
 * Name : getCardPANTest(API)								*
 * Param(in) : NA											*
 * Param(out) : CardData									*
 * Param(in/out) : NA										*
 * return : EN_cardError_t 									*
 * Author : Kareim Elmligy                                  *
 * Last Modification : 28/10                                *
 ***********************************************************/

void getCardExpiryDateTest (void);
/************************************************************
 * Name : getCardHolderName(API)							*
 * Param(in) : NA											*
 * Param(out) : CardData									*
 * Param(in/out) : NA										*
 * return : EN_cardError_t 									*
 * Author : Kareim Elmligy                                  *
 * Last Modification : 28/10                                *
 ***********************************************************/

void getCardHolderNameTest(void);
/************************************************************
 * Name : getCardHolderNameTest(API)						*
 * Param(in) : NA											*
 * Param(out) : CardData									*
 * Param(in/out) : NA										*
 * return : EN_cardError_t 									*
 * Author : Kareim Elmligy                                  *
 * Last Modification : 28/10                                *
 ***********************************************************/


#endif /* CARD_CARD_H_ */
