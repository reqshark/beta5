//
//  bridger.h
//  nn
//
//  created by Bent Cardan
//  reqshark software. lifestyles of the rich and/or resourceful. authored 12/23/2014
//

//#import "chan.h"
//#include "chan.h"

#import "nn.h"
#include "nn.h"
#import "pubsub.h"
#include "pubsub.h"
#import "tcp.h"
#include "tcp.h"
#import "sleep.h"
#include "sleep.h"
#import "inproc.h"
#include "inproc.h"

#include <pthread.h>



#include "poller.h"
#include <sys/select.h>

#define ADDR "tcp://206.221.182.202:51255"
#define NN_IN 1
#define NN_OUT 2

int getevents (int s, int events, int timeout);

//chan_t* messages;
//chan_t* done;
//chan_t* jobs;

//int sz = sizeof TCP_NO_DELAY;
int optval = 1;
size_t optlen = sizeof optval;

void* worker();
void* worker2();
void init_channels(void);
