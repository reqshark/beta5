#import "chan.h"
#include "chan.h"

#import "nn.h"
#include "nn.h"
#import "pubsub.h"
#include "pubsub.h"
#import "tcp.h"
#include "tcp.h"
#import "sleep.h"
#include "sleep.h"

#include "poller.h"
#include <sys/select.h>

#define ADDR "tcp://206.221.182.202:51255"
#define NN_IN 1
#define NN_OUT 2

int getevents (int s, int events, int timeout);


chan_t* messages;
chan_t* done;
chan_t* jobs;

void* worker();
void* worker2();

//pthread_t th;
//pthread_create(&th, NULL, worker, NULL);

//pthread_t poll_rc;
//pthread_create(&poll_rc, NULL, worker2, NULL);


void init_channels(void);
