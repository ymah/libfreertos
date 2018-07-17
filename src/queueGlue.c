#include <stdint.h>
#include <pip/api.h>
#include <pip/paging.h>
#include <pip/pipcall.h>
#include <pip/compat.h>
#include <pip/debug.h>
#include "queueGlue.h"

#define NULL ((void*)0)
extern int printf(const char *c,...);

xQueueCreateParameters * createArgs = NULL;
xQueueSendParameters * sendArgs = NULL;
xQueueReceiveParameters * recArgs = NULL; // que receive

uint32_t * receiveBuffer;


void * locmemcpy (void *dest, const void *src, uint32_t len)
{
  char *d = dest;
  const char *s = src;
  while (len--)
    *d++ = *s++;
  return dest;
}

void initQueueService(){
  if(createArgs == NULL)
    createArgs = allocPage();

  if(sendArgs == NULL)
    sendArgs = allocPage();

  if(recArgs == NULL)
      recArgs = allocPage();
}
/**
 * [xProtectedQueueCreate create a queue in the father]
 * @param  uxQueueLength The maximum number of items the queue can hold at any one time.
 * @param  uxItemSize    The size, in bytes, required to hold each item in the queue.
 * @return               If the queue is created successfully then a handle to the created queue is returned. If the memory required to create the queue could not be allocated then NULL is returned.
 */
uint32_t xProtectedQueueCreate( uint32_t uxQueueLength, uint32_t uxItemSize ){



  createArgs->lenght = uxQueueLength;
  createArgs->size_type = (uint32_t)uxItemSize;
  createArgs->returnCall = (uint32_t)0xDEADBEEF;
  Pip_Notify(0,0x80,queueCreate,(uint32_t)createArgs);

  /* FreeRTOS gave us in createArgs->returnCall the address of the queue */
  return createArgs->returnCall;


}


/**
 * [xProtectedQueueSend send something in a queue created in the parent partition]
 * @param xQueue        	The handle to the queue on which the item is to be posted.
 * @param pvItemToQueue A pointer to the item that is to be placed on the queue. The size of the items the queue will hold was defined when the queue was created, so this many bytes will be copied from pvItemToQueue into the queue storage area.
 * @param xTicksToWait  The maximum amount of time the task should block waiting for space to become available on the queue, should it already be full. The call will return immediately if the queue is full and xTicksToWait is set to 0. The time is defined in tick periods so the constant portTICK_PERIOD_MS should be used to convert to real time if this is required.
 */
uint32_t xProtectedQueueSend(uint32_t xQueue,uint32_t pvItemToQueue,uint32_t xTicksToWait){




  sendArgs->queue = xQueue;
  sendArgs->itemToQueue = (uint32_t*)pvItemToQueue;
  sendArgs->tickToWait = xTicksToWait;

  Pip_Notify(0,0x80,queueSend,(uint32_t)sendArgs);

  return *(uint32_t*)0x600000;;

}

/**
 * [xProtectedQueueReceive receive something from a queue in the parent partition]
 * @param xQueue       The handle to the queue from which the item is to be received.
 * @param pvBuffer     Pointer to the buffer into which the received item will be copied.
 * @param xTicksToWait The maximum amount of time the task should block waiting for an item to receive should the queue be empty at the time of the call. Setting xTicksToWait to 0 will cause the function to return immediately if the queue is empty. The time is defined in tick periods so the constant portTICK_PERIOD_MS should be used to convert to real time if this is required.
 */
uint32_t xProtectedQueueReceive(uint32_t xQueue,uint32_t pvBuffer,uint32_t xTicksToWait){


  recArgs->queue = xQueue;
  recArgs->bufferReceive = (uint32_t*) pvBuffer;
  recArgs->tickToWait = xTicksToWait;

  Pip_Notify(0,0x80,queueReceive,(uint32_t)recArgs);


  return *(uint32_t*)0x600000;

}
