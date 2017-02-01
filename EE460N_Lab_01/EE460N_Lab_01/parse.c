//
//  parse.c
//  EE460N_Lab_01
//
//  Created by Alex Lostak on 1/29/17.
//  Copyright © 2017 Alex Lostak. All rights reserved.
//

#include "parse.h"
#define MAX_LINE_LENGTH 255
enum
{
	   DONE, OK, EMPTY_LINE
};

int isOpcode (char* op) {
    if (!strcmp(op, "add")) {
        return 1;
    } else if (!strcmp(op, "and")) {
        return 1;
    } else if (!strcmp(op, "brn")) {
        return 1;
    } else if (!strcmp(op, "brp")) {
        return 1;
    } else if (!strcmp(op, "brnp")) {
        return 1;
    } else if (!strcmp(op, "br")) {
        return 1;
    } else if (!strcmp(op, "brz")) {
        return 1;
    } else if (!strcmp(op, "brnz")) {
        return 1;
    } else if (!strcmp(op, "brzp")) {
        return 1;
    } else if (!strcmp(op, "brnzp")) {
        return 1;
    } else if (!strcmp(op, "jmp")) {
        return 1;
    } else if (!strcmp(op, "jsr")) {
        return 1;
    } else if (!strcmp(op, "jsrr")) {
        return 1;
    } else if (!strcmp(op, "ldb")) {
        return 1;
    } else if (!strcmp(op, "ldw")) {
        return 1;
    } else if (!strcmp(op, "lea")) {
        return 1;
    } else if (!strcmp(op, "not")) {
        return 1;
    } else if (!strcmp(op, "ret")) {
        return 1;
    } else if (!strcmp(op, "rti")) {
        return 1;
    } else if (!strcmp(op, "shf")) {
        return 1;
    } else if (!strcmp(op, "stb")) {
        return 1;
    } else if (!strcmp(op, "stw")) {
        return 1;
    } else if (!strcmp(op, "trap")) {
        return 1;
    } else if (!strcmp(op, "xor")) {
        return 1;
    }
    return -1;
}

int toNum( char * pStr ) {
    char * t_ptr;
    char * orig_pStr;
    int t_length,k;
    int lNum, lNeg = 0;
    long int lNumLong;
    
    orig_pStr = pStr;
    if( *pStr == '#' )				/* decimal */
    {
        pStr++;
        if( *pStr == '-' )				/* dec is negative */
        {
            lNeg = 1;
            pStr++;
        }
        t_ptr = pStr;
        t_length = strlen(t_ptr);
        for(k=0;k < t_length;k++)
        {
            if (!isdigit(*t_ptr))
            {
                printf("Error: invalid decimal operand, %s\n",orig_pStr);
                exit(4);
            }
            t_ptr++;
        }
        lNum = atoi(pStr);
        if (lNeg)
            lNum = -lNum;
        
        return lNum;
    }
    else if( *pStr == 'x' )	/* hex     */
    {
        pStr++;
        if( *pStr == '-' )				/* hex is negative */
        {
            lNeg = 1;
            pStr++;
        }
        t_ptr = pStr;
        t_length = strlen(t_ptr);
        for(k=0;k < t_length;k++)
        {
            if (!isxdigit(*t_ptr))
            {
                printf("Error: invalid hex operand, %s\n",orig_pStr);
                exit(4);
            }
            t_ptr++;
        }
        lNumLong = strtol(pStr, NULL, 16);    /* convert hex string into integer */
        lNum = (lNumLong > INT_MAX)? INT_MAX : lNumLong;
        if( lNeg )
            lNum = -lNum;
        return lNum;
    }
    else
    {
        printf( "Error: invalid operand, %s\n", orig_pStr);
        exit(4);  /* This has been changed from error code 3 to error code 4, see clarification 12 */
    }
}

int readAndParse (FILE * pInfile, char * pLine, char ** pLabel, char ** pOpcode, char ** pArg1, char ** pArg2, char ** pArg3, char ** pArg4) {
    char * lRet, * lPtr;
	   int i;
	   if( !fgets( pLine, MAX_LINE_LENGTH, pInfile ) )
           return( DONE );
	   for( i = 0; i < strlen( pLine ); i++ )
           pLine[i] = tolower( pLine[i] );
	   
    /* convert entire line to lowercase */
	   *pLabel = *pOpcode = *pArg1 = *pArg2 = *pArg3 = *pArg4 = pLine + strlen(pLine);
    
	   /* ignore the comments */
	   lPtr = pLine;
    
	   while( *lPtr != ';' && *lPtr != '\0' &&
             *lPtr != '\n' )
           lPtr++;
    
	   *lPtr = '\0';
	   if( !(lPtr = strtok( pLine, "\t\n ," ) ) )
           return( EMPTY_LINE );
    
	   if( isOpcode( lPtr ) == -1 && lPtr[0] != '.' ) /* found a label */
       {
           *pLabel = lPtr;
           if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );
       }
	   
    *pOpcode = lPtr;
    
	   if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );
	   
    *pArg1 = lPtr;
	   
    if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );
    
	   *pArg2 = lPtr;
	   if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );
    
	   *pArg3 = lPtr;
    
	   if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );
    
	   *pArg4 = lPtr;
    
	   return( OK );
}
