/*
 * Project         SSE debug interface demonstration
 * (c) copyright   2013
 * Company         Nuance
 *                 All rights reserved
 *
 * @file           ringbuffer.c
 * @author         martin.roessler@nuance.com
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef RINGBUFFER_C_
#define RINGBUFFER_C_

#include <stdlib.h>
#include "ringbuffer.h"

struct _sRingBuffer
{
	int iLength;
	int iReadIndex;
	int iWriteIndex;
	char * pcHead;
};


int createRingbuffer( tsRingbuffer ** ppsRingbuffer, unsigned int uiSize )
{
		if ( ( NULL == ppsRingbuffer) ||
		( NULL != *ppsRingbuffer ) ||
		( 0 == uiSize ) )
		{
		return iRINGBUFFER_ERROR;
		}
		else
		{
			tsRingbuffer * psRingbuffer = (tsRingbuffer*)calloc( 1, sizeof(tsRingbuffer) );

			if ( NULL == psRingbuffer )
			{
			return iRINGBUFFER_ERROR;
			}
			else
			{
			psRingbuffer->pcHead = (char*)calloc( uiSize +1, sizeof(char) );

			if ( NULL == psRingbuffer->pcHead )
			{
			free( psRingbuffer );
			return iRINGBUFFER_ERROR;
		}
		else
		{
			psRingbuffer->iLength = uiSize + 1; /* one byte more to detect a full ringbuffer */
			psRingbuffer->iReadIndex = 0;
			psRingbuffer->iWriteIndex = 0;

			*ppsRingbuffer = psRingbuffer;
		return iRINGBUFFER_OK;
		}
		}
	}
}

int destroyRingbuffer( tsRingbuffer ** ppsRingbuffer )
{
	if ( ( NULL == ppsRingbuffer) ||
	    ( NULL == *ppsRingbuffer ) )
	{
		return iRINGBUFFER_ERROR;
	}
	else
	{
		tsRingbuffer * psRingbuffer = *ppsRingbuffer;

		free( psRingbuffer->pcHead );
		free( psRingbuffer );

		*ppsRingbuffer = NULL;

		return iRINGBUFFER_OK;
	}
	}

int getFreeBytesRingbuffer( tsRingbuffer * psRingbuffer )
{
	if ( ( NULL == psRingbuffer) )
	{
	return iRINGBUFFER_ERROR;
	}
	else
	{
	int iFreeBytes = 0;

	if ( psRingbuffer->iWriteIndex == psRingbuffer->iReadIndex )
	{
	 iFreeBytes = psRingbuffer->iLength - 1;
	}
	else if ( psRingbuffer->iWriteIndex > psRingbuffer->iReadIndex )
	{
	 iFreeBytes = ( psRingbuffer->iLength - 1 ) + ( psRingbuffer->iReadIndex - psRingbuffer->iWriteIndex );
	}
	else
	{
	 iFreeBytes = (psRingbuffer->iReadIndex - psRingbuffer->iWriteIndex) - 1;
	}

	return iFreeBytes;
	}
}

int insertIntoRingbuffer( tsRingbuffer * psRingbuffer, const char * pcData, int iSize )
{
	if ( ( NULL == psRingbuffer) ||
	    ( NULL == pcData ) ||
	    ( 0 > iSize ) )
	{
	  return iRINGBUFFER_ERROR;
	}
	else
	{
		int iFreeBytes = 0;
		int iWrittenBytes = 0;
		int i;

		iFreeBytes = getFreeBytesRingbuffer( psRingbuffer );

		if ( iFreeBytes < iSize )
		{
		 iWrittenBytes = iFreeBytes;
		}
		else
		{
		 iWrittenBytes = iSize;
		}

		for ( i=0; i<iWrittenBytes; i++ )
		{
		 psRingbuffer->pcHead[ psRingbuffer->iWriteIndex ] = pcData[i];

		 /* mind the ringbuffer wrap */
		 psRingbuffer->iWriteIndex++;
		 if ( psRingbuffer->iWriteIndex == psRingbuffer->iLength )
		{
			psRingbuffer->iWriteIndex = 0;
		}
	}

		return iWrittenBytes;
		}
}

int extractFromRingbuffer( tsRingbuffer * psRingbuffer, char * pcData, int iSize )
{
	if ( ( NULL == psRingbuffer) ||
		( NULL == pcData ) ||
				( 0 > iSize ) )
	{
		return iRINGBUFFER_ERROR;
	}
	else
	{
		int iAvailableBytes = 0;
		int iExtractedBytes = 0;
		int i;

		iAvailableBytes = (psRingbuffer->iLength - 1) - getFreeBytesRingbuffer( psRingbuffer );

	if ( iAvailableBytes < iSize )
	{
	 iExtractedBytes = iAvailableBytes;
	}
	else
	{
	 iExtractedBytes = iSize;
	}

	for ( i=0; i<iExtractedBytes; i++ )
	{
	 pcData[i] = psRingbuffer->pcHead[ psRingbuffer->iReadIndex ];

	 /* mind the ringbuffer wrap */
	 psRingbuffer->iReadIndex++;
	 if ( psRingbuffer->iReadIndex == psRingbuffer->iLength )
	 {
	    psRingbuffer->iReadIndex = 0;
	 }
	}

	return iExtractedBytes;
	}
}


#endif /* RINGBUFFER_C_ */
