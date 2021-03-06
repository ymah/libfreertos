#ifndef _QUEUE_H
#define _QUEUE_H


#include <stdint.h>
/*
 * each service is associated to a unique identifier
 *
 *
 */


#define returnServiceAddress 0x801000
struct xQueueCreateParameters_s {
  uint32_t lenght;
  uint32_t size_type;
  uint32_t returnCall;
};
typedef struct xQueueCreateParameters_s xQueueCreateParameters;



struct xQueueSendParameters_s {
 uint32_t queue;
 uint32_t * itemToQueue;
 uint32_t tickToWait;
};
typedef struct xQueueSendParameters_s xQueueSendParameters;



struct xQueueReceiveParameters_s {
 uint32_t queue;
 uint32_t * bufferReceive;
 uint32_t tickToWait;
};
typedef struct xQueueReceiveParameters_s xQueueReceiveParameters;


#define queueCreate     0x15
#define queueSend       0x16
#define queueReceive    0x17
#define sbrk            0x18
#define channelCom      0x19

void initQueueService();
uint32_t xProtectedQueueCreate( uint32_t uxQueueLength, uint32_t uxItemSize );
uint32_t xProtectedQueueSend(uint32_t xQueue,uint32_t pvItemToQueue,uint32_t xTicksToWait);
uint32_t xProtectedQueueReceive(uint32_t xQueue,uint32_t pvBuffer,uint32_t xTicksToWait);


#endif
