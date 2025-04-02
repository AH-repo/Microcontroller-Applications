/* Includes ------------------------------------------------------------------*/
#include <assert.h>
#include "ring_buffer.h"


bool RingBuffer_Init(RingBuffer *ringBuffer, char *dataBuffer, size_t dataBufferSize) 
{
	assert(ringBuffer);
	assert(dataBuffer);
	assert(dataBufferSize > 0);
	
	if ((ringBuffer) && (dataBuffer) && (dataBufferSize > 0)) {
	    ringBuffer -> size = dataBufferSize;
	    ringBuffer -> data = dataBuffer;
	    ringBuffer -> head = 0;
	    ringBuffer -> tail = 0;
	    ringBuffer -> len = 0;
	  return true;
	}
	
	return false;
}

bool RingBuffer_Clear(RingBuffer *ringBuffer)
{
	assert(ringBuffer);

	if (ringBuffer) {
		ringBuffer -> head = 0;
	    ringBuffer -> tail = 0;
	    ringBuffer -> len = 0;
		return true;
	}
	return false;
}

bool RingBuffer_IsEmpty(const RingBuffer *ringBuffer)
{
  assert(ringBuffer);	
	if (ringBuffer->len == 0){
	return true;
	}
	return false;
}

size_t RingBuffer_GetLen(const RingBuffer *ringBuffer)
{
	assert(ringBuffer);
	
	if (ringBuffer) {
    return ringBuffer->len;
	}
	return 0;
	
}

size_t RingBuffer_GetCapacity(const RingBuffer *ringBuffer)
{
	assert(ringBuffer);
	
	if (ringBuffer) {
		return ringBuffer->size;
	}
	return 0;	
}


bool RingBuffer_PutChar(RingBuffer *ringBuffer, char c)
{
	assert(ringBuffer);
    
	if (ringBuffer) {
	    
	    if(ringBuffer->len != ringBuffer->size){
		    ringBuffer->data[ringBuffer->head] = c;
		    ringBuffer->len++;
		    
		    if(ringBuffer->head < ringBuffer->size - 1){
		        ringBuffer->head++;
		    }
		    
		    else{
		        ringBuffer->head = 0;
		    }
		    
		return true;
	    }
	    return false;  
	}
	return false;
}

bool RingBuffer_GetChar(RingBuffer *ringBuffer, char *c)
{
	assert(ringBuffer);
	assert(c);
	
  if ((ringBuffer) && (c)) {
		    if(ringBuffer->len == 0){
		        return false;
		    }
		    else{
                *c = ringBuffer->data[ringBuffer->tail];

                if (ringBuffer->tail < ringBuffer->size-1){
                    ringBuffer->tail++;
                    ringBuffer->len--;
                }
                else{
                    ringBuffer->tail = 0;
                    ringBuffer->len--;
                }
		    }
		    return true;
		    
		
	}
	return false;
}
