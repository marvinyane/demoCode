/*
 * Project         SSE debug interface demonstration
 * (c) copyright   2013
 * Company         Nuance
 *                 All rights reserved
 *
 * @file           ringbuffer.h
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

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
/* --------------------------------------------------------------- */

#define iRINGBUFFER_OK (0)
#define iRINGBUFFER_ERROR (-1)

typedef struct _sRingBuffer tsRingbuffer;

int createRingbuffer( tsRingbuffer ** ppsRingbuffer, unsigned int uiSize );

int destroyRingbuffer( tsRingbuffer ** ppsRingbuffer );

/* returns number of actually written bytes or iRINGBUFFER_ERROR for a failure */
int insertIntoRingbuffer( tsRingbuffer * psRingbuffer, const char * pcData, int uiSize );

/* returns number of actually extracted bytes or iRINGBUFFER_ERROR for a failure */
int extractFromRingbuffer( tsRingbuffer * psRingbuffer, char * pcData, int uiSize );

/* --------------------------------------------------------------- */
#ifdef __cplusplus
}
#endif /* C++ */


#endif /* RINGBUFFER_H_ */
