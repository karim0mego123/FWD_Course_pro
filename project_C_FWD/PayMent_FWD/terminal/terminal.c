#include "terminal.h"
string TransactionData[MaxTransactionDate]  ;
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{

	time_t date = time(NULL);
	struct tm tm = *localtime(&date);
	string year = (string)malloc(4);
	string mon = (string)malloc(2);
	string day = (string)malloc(2);
	sprintf(year, "%d", tm.tm_year + 1900);
	sprintf(mon, "%d", tm.tm_mon + 1);
	sprintf(day, "%d", tm.tm_mday);
	strcat((string)termData->transactionDate, day);
	strcat((string)termData->transactionDate, "/");
	strcat((string)termData->transactionDate, mon);
	strcat((string)termData->transactionDate, "/");
	strcat((string)termData->transactionDate, year);
	strcpy ((string)TransactionData,(string)termData->transactionDate) ;
	return CARD_OK ;
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	EN_terminalError_t Return_Status = TERMINAL_OK ;
	int card_expiry_day, card_expiry_month, term_transation_Day, term_transation_month, term_transation_year;
	/* sscanf devide string into intgers  */
	sscanf((string)cardData.cardExpirationDate, "%d/%d" ,&card_expiry_day,&card_expiry_month);
	sscanf((string)termData.transactionDate, "%d/%d/%d", &term_transation_Day,&term_transation_month ,&term_transation_year);

	if ( card_expiry_month > term_transation_month )
	{
		;
	}
	else if ( card_expiry_month == term_transation_month )
	{
		if ( card_expiry_day > term_transation_Day )
		{
			return Return_Status ;
		}
	}
	else
	{
		Return_Status = EXPIRED_CARD ;
	}

	return Return_Status ;
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
	EN_terminalError_t Return_Status = TERMINAL_OK ;
	uint32_t Loc_NumOFTry = 5 ; /* this variable hold the max numbers of tries */
	float Loc_Transaction_Amount  ;
	while (--Loc_NumOFTry)
	{
		printf("enter transaction amount = " ) ;
		CLEAR_BUFFER();
		scanf("%f",&Loc_Transaction_Amount) ;
		if ( Loc_Transaction_Amount <= 0 )
		{
			printf("you entered wrong money \n") ;
			Return_Status = INVALID_AMOUNT ;
		}
		else
		{
			termData->transAmount = Loc_Transaction_Amount ;
			break ;
		}
	}
	return Return_Status ;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
	EN_terminalError_t Return_Status = TERMINAL_OK ;
	if ( Max_amount <= 0 )
	{
		Return_Status =  INVALID_MAX_AMOUNT  ;
		printf("max_amount less or equal than zero\n") ;
	}
	else
	{
		termData->maxTransAmount = Max_amount   ;
	}
	return Return_Status  ;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
	EN_terminalError_t Return_Status = TERMINAL_OK ;
	if ( termData->transAmount > termData->maxTransAmount )
	{
		Return_Status =	EXCEED_MAX_AMOUNT ;
	}
	return Return_Status ;
}

void getTransactionDateTest(void)		/*	Test transation data	*/
{
	uint8_t Loc_Count = 0u ;
	string Loc_strDataTest [3] =  { "12/01/2020" , "A0/12/2020" , "12\02\2020" } ;
	for ( Loc_Count = 0 ; Loc_Count < 3 ; Loc_Count++ )
	{
		printf("%s	>>>   ",Loc_strDataTest[Loc_Count]) ;
		if (strlen((string)Loc_strDataTest) != 10)
		{
			printf("test case %d false\n",Loc_Count) ;
			continue ;
		}
		else if ( format_true ( (string)Loc_strDataTest[Loc_Count] ) == false )
		{
			printf("test case %d false\n",Loc_Count) ;
			continue ;
		}
		else
		{
			printf("test case %d true\n",Loc_Count) ;
		}
	}
}

bool format_true( string TestData )
{
	uint8_t Loc_count = 0 ;
	EN_terminalError_t Return_Status = true ;
	for ( Loc_count = 0 ; Loc_count<10 ; Loc_count++)
	{
		if (!isalnum(TestData[Loc_count]))
		{
			Return_Status = false ;
			break ;
		}
	}
	return Return_Status;
}

void isCardExpriedTest(void)
{
	uint8_t Loc_Count = 0 ;
	ST_terminalData_t Loc_testTerminal ;
	ST_cardData_t  Loc_TestCard;
	strcpy((string)Loc_testTerminal.transactionDate , (string)TransactionData ) ;
	string Loc_TestExpiredData[2] = { "01/12" , "15/09" } ;
	if ( TransactionData == NULL )
	{
		printf("NULL transactionData\n") ;
	}
	else
	{
		for ( Loc_Count = 0 ; Loc_Count < 2 ; Loc_Count++ )
		{
			strcpy((string)Loc_TestCard.cardExpirationDate, Loc_TestExpiredData[Loc_Count] ) ;
			if ( isCardExpired (Loc_TestCard,Loc_testTerminal) == EXPIRED_CARD )
			{
				printf("Test case 0 : %s is Expred\n",Loc_TestExpiredData[Loc_Count]) ;
			}
			else
			{
				printf("Test case 1 : %s is valid\n",Loc_TestExpiredData[Loc_Count]) ;
			}
		}
	}
}
void getTransactionAmountTest(void)
{
	uint8_t Loc_count = 0u ;
	float Test_amount[3] = { -100.12 , 0 , 1000 } ;
	ST_terminalData_t test ;
	for ( Loc_count = 0 ; Loc_count < 3 ; Loc_count++ )
	{
		test.transAmount = Test_amount[Loc_count] ;
		if ( getTransactionAmount (&test) == TERMINAL_OK )
		{
			printf("Test case %d : %.2fis valid",Loc_count,test.transAmount) ;
		}
		else
		{
			printf("Test case %d : %.2fis not valid",Loc_count,test.transAmount) ;
		}
	}
}
void setMaxAmountTest(void)
{
	uint8_t Loc_count = 0u ;
	float Test_amount[3] = { -100.12 , 0 , 1000 } ;
	ST_terminalData_t test ;
	for ( Loc_count = 0 ; Loc_count < 3 ; Loc_count++ )
	{
		test.maxTransAmount = Test_amount[Loc_count] ;
		if ( setMaxAmount (&test) == TERMINAL_OK )
		{
			printf("Test case %d : %.2fis valid",Loc_count,test.maxTransAmount) ;
		}
		else
		{
			printf("Test case %d : %.2fis not valid",Loc_count,test.maxTransAmount) ;
		}
	}
}

void isBelowMaxAmountTest(void)
{
	uint8_t Loc_count = 0u ;
	ST_terminalData_t Test[2] ;
	Test[0].maxTransAmount = 4000 ; Test[0].transAmount =5000 ;
	Test[1].maxTransAmount = 4000 , Test[1].transAmount =1000 ;
	for ( Loc_count = 0 ; Loc_count<2 ; Loc_count++ )
	{
		if (isBelowMaxAmount(Test)==EXCEED_MAX_AMOUNT)
		{
			printf("Test case 0 : false\n%f is greater than %f\n",Test[Loc_count].transAmount,Test[Loc_count].maxTransAmount) ;
		}
		else
		{
			printf("Test case 0 : true\n%f is less than %f\n",Test[Loc_count].transAmount,Test[Loc_count].maxTransAmount) ;
		}
	}
}
