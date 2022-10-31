
#include "app.h"

int main()
{
	uint8_t ch ;
	while (true)
	{
		appStart();
		printf("enter (y) to do another operation\n") ;
		CLEAR_BUFFER() ;
		scanf("%c",&ch) ;
		if ( ch != 'y' )
		{
			break ;
		}
	}
	return CARD_OK ;
}
