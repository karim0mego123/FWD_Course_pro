/*
 * card.c
 *
 *  Created on: Oct 8, 2022
 *      Author: karim
 */
#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
	string Loc_StrName = NULL ;	/* Holdtemp name entered by user throgh command window */
	uint8_t Loc_NameSize = 0  ; /* Hold Name Size entered by user */
	uint8_t Loc_NumOFTry = 5 ; /* this variable hold the max numbers of tries */
	EN_cardError_t Return_Status = CARD_OK ;
	Loc_StrName = (string)malloc(sizeof(char)*CARD_HALDER_NALMELEN_MAx + 10 ) ;
	if (Loc_StrName == NULL)
	{
		return CARD_NOK ;
	}
	else
	{
		while (--Loc_NumOFTry)
		{
			printf("enter card holder name[20:24] : \n" ) ;
			CLEAR_BUFFER();
			gets(Loc_StrName) ;

			Loc_NameSize = strlen(Loc_StrName) ;
			if(( Loc_NameSize < CARD_HALDER_NALMELEN_Min )||(Loc_NameSize > CARD_HALDER_NALMELEN_MAx))
			{
				Return_Status =  WRONG_NAME ;
				printf("name is wrong less or more than[20:24] !\n") ;
				continue ;
			}

			if ( isAlphanumeric( Loc_StrName , Loc_NameSize ) == true  )
			{
				strcpy( (string)cardData->cardHolderName , Loc_StrName ) ;
				Return_Status = CARD_OK ;
				break;
			}
			else
			{
				printf("name is wrong!\n") ;
				Return_Status = WRONG_NAME ;
			}
			if ( Loc_NumOFTry == 1 )
			{
				exit(true) ;
			}
		} /*End while */
	}

	return Return_Status ;
}
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
	uint8_t Loc_NumOFTry = 5 ; /* this variable hold the max numbers of tries */
	string Loc_StrDate = NULL ;
	uint8_t Loc_NameSize = 0 ;
	EN_cardError_t Return_Status = CARD_OK ;
	Loc_StrDate = (string) malloc ( sizeof(char)*CARD_EXPIRE_DATE+4) ;
	if (Loc_StrDate == NULL)
	{
		Return_Status = CARD_NOK ;
	}
	else
	{
		while (--Loc_NumOFTry)
		{
			printf("enter card expiry date DD/MM : " ) ;
			CLEAR_BUFFER() ;
			gets( (string) Loc_StrDate )  ;
			Loc_NameSize = strlen((string)Loc_StrDate);
			if ( format_is_true ((string)Loc_StrDate,Loc_NameSize) == true )
			{
				strcpy((string)cardData->cardExpirationDate,(string)Loc_StrDate) ;
				Return_Status = CARD_OK ;
				break ;
			}
			else
			{
				Return_Status = WRONG_NAME ;
				printf("wrong date!\n") ;
			}
			if ( Loc_NumOFTry == 1 )
			{
				exit(true) ;
			}
		}
	}
	return Return_Status ;
}
EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
	uint8_t Loc_NumOFTry = 5 ; /* this variable hold the max numbers of tries */
	uint32_t Loc_StrSize = 0 ;
	string cardpan = NULL ;
	EN_cardError_t Return_Status = CARD_OK ;
	cardpan = (string) malloc (sizeof(PRIM_ACCOUNTNUM_LEN+10)) ;
	while (--Loc_NumOFTry)
	{
		printf("enter card primary account number[16:19] = " ) ;
		CLEAR_BUFFER();
		gets((string)cardpan) ;
		Loc_StrSize = strlen((string)cardpan) ;
		if (Loc_StrSize >= 16 && Loc_StrSize <=19 && isAlphanumeric(cardpan,Loc_StrSize) )
		{
			strcpy((string)cardData->primaryAccountNumber, (string)cardpan ) ;
			Return_Status = CARD_OK ;
			break ;
		}
		else
		{
			Return_Status = WRONG_PAN ;
			printf("wrong pan card!\n") ;
		}
		if ( Loc_NumOFTry == 1 )
		{
			exit(true) ;
		}
	}
	return Return_Status ;
}
bool isAlphanumeric(uint8_t *arr , uint8_t Loc_NameSize )
{
	bool Return_Status = true ;
	uint8_t Loc_StrCount = 0 ;

	if (arr == NULL )
	{
		Return_Status = false ;
	}
	else
	{
		for ( Loc_StrCount = 0 ; Loc_StrCount < Loc_NameSize ; Loc_StrCount++ )
		{
			if ( arr[Loc_StrCount] == ' ' )
			{
				continue ;
			}
			if ( !isalnum(arr[Loc_StrCount]) )
			{
				Return_Status = false;
				break  ;
			}
			else
			{
				/* DO NOTHIG*/
			}
		}
	}
	return Return_Status ;
}
bool format_is_true(uint8_t *arr,uint8_t Loc_NameSize )
{
	// the right format is "number + number + '/' + number + number"

	bool Return_Status = true ;
	uint8_t Loc_StrCount = 0 ;
	if (arr == NULL )
	{
		Return_Status = false ;
	}
	else
	{
		if ( Loc_NameSize != 5 )
		{
			Return_Status = false ;
		}
		else
		{
			for ( Loc_StrCount = 0 ; Loc_StrCount < Loc_NameSize ; Loc_StrCount++ )
			{
				if (  arr[2] != '/' )
				{
					Return_Status = false ;
					break ;
				}
				else
				{
					continue ;
				}
				if ( arr[Loc_StrCount] < 48 || arr[Loc_StrCount] >57 )
				{
					Return_Status = false;
					break  ;
				}
				else
				{
					/* DO NOTHIG*/
				}
			}
		}
	}
	return Return_Status ;
}

void getCardHolderNameTest(void)
{
	ST_cardData_t* Loc_cardTest = NULL ;
	uint8_t Loc_NameSize = 0 ;
	if ( getCardHolderName(Loc_cardTest)== CARD_NOK  )
	{
		printf("test case 0 : \n");
		printf("NULL string name\n") ;
	}
	Loc_cardTest = (ST_cardData_t*) malloc(sizeof(Loc_cardTest->cardHolderName)*3+30) ;
	strcpy( (string)(Loc_cardTest->cardHolderName) ,(string)"karim ayman abdel latef" ) ;
	if ( getCardHolderName(Loc_cardTest)== CARD_OK )
	{
		printf("test case 1 : \n");
		printf("%s : \n",Loc_cardTest->cardHolderName);
		printf("name is ok less than 24 and more than 20\n");
	}

	strcpy( (string)(Loc_cardTest->cardHolderName) , (string)"karim ayman" ) ;
	if ( getCardHolderName(Loc_cardTest)== WRONG_NAME )
	{
		printf("test case 2 : \n");
		printf("%s : \n",Loc_cardTest->cardHolderName);
		printf("WRONG_NAME less than 20\n");
	}

	strcpy((string)Loc_cardTest->cardHolderName , (string)"karim&#*$ayman" ) ;
	Loc_NameSize = strlen((string)Loc_cardTest->cardHolderName);
	if ( ( isAlphanumeric( Loc_cardTest->cardHolderName,Loc_NameSize) != true ) )
	{
		printf("test case 3 :  \n");
		printf("%s : \n",Loc_cardTest->cardHolderName);
		printf("name contain especial char \n") ;
	}
}

void getCardExpiryDateTest (void)
{
	ST_cardData_t *Loc_cardTest = NULL  ;
	uint8_t Loc_NameSize = 0 ;
	if ( Loc_cardTest->cardExpirationDate == NULL )
	{
		printf("test case 0 : \n");
		printf("NULL String date \n") ;
	}
	Loc_cardTest = (ST_cardData_t*) malloc(sizeof (ST_cardData_t)) ;
	strcpy((string)Loc_cardTest->cardExpirationDate , "21/13" ) ;
	Loc_NameSize = strlen((string)Loc_cardTest->cardHolderName);
	if ( format_is_true(Loc_cardTest->cardExpirationDate,Loc_NameSize ) == true )
	{
		printf("test case 1 : \n");
		printf("%s : ",Loc_cardTest->cardExpirationDate) ;
		printf("format is true\n") ;
	}
	strcpy((string)Loc_cardTest->cardExpirationDate , "21L13") ;
	Loc_NameSize = strlen((string)Loc_cardTest->cardHolderName);
	if ( format_is_true( Loc_cardTest->cardExpirationDate,Loc_NameSize ) != true )
	{
		printf("test case 2 : \n");
		printf("%s : ",Loc_cardTest->cardExpirationDate) ;
		printf("format is not true\n") ;
	}
}
void getCardPANTest (void)
{
	ST_cardData_t *Loc_PanCardTest = NULL ;
	if ( Loc_PanCardTest->primaryAccountNumber == NULL )
	{
		printf("test case 0 : \n");
		printf("%s : ",Loc_PanCardTest->primaryAccountNumber) ;
		printf("wrong pan \n") ;
	}
	strcpy((string)Loc_PanCardTest->primaryAccountNumber , (string)"0123456789") ;
	if ( getCardPAN ( Loc_PanCardTest ) == WRONG_PAN )
	{
		printf("test case 1 : \n");
		printf("%s : ",Loc_PanCardTest->primaryAccountNumber) ;
		printf("wrong pan \n") ;
	}
	strcpy((string)Loc_PanCardTest->primaryAccountNumber ,(string) "0123456789012345678912" ) ;
	if ( getCardPAN ( Loc_PanCardTest ) == WRONG_PAN )
	{
		printf("test case 2 : \n");
		printf("%s : ",Loc_PanCardTest->primaryAccountNumber) ;
		printf("wrong pan \n") ;
	}
	strcpy((string)Loc_PanCardTest->primaryAccountNumber,(string) "012345678912345678" ) ;
	if ( getCardPAN ( Loc_PanCardTest ) == CARD_OK )
	{
		printf("test case 3 : \n");
		printf("%s : ",Loc_PanCardTest->primaryAccountNumber) ;
		printf("correct pan \n") ;
	}
}
