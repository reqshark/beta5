//
//  bridger.c
//  nn
//
//  created by Bent Cardan
//  reqshark software. lifestyles of the rich and/or resourceful. authored 12/23/2014
//

#include <stdio.h>
#include "bridger.h"
#include "string.h"


int s, r, eid;

int getevents (int s, int events, int timeout){
  int rcvfd, maxfd, grc, revents;
  size_t fdsz;
  struct timeval tv;
  
  fd_set pollset;
  maxfd = 0;
  FD_ZERO (&pollset);
  
  if (events & NN_IN) {
    fdsz = sizeof (rcvfd);
    grc = nn_getsockopt (s, NN_SOL_SOCKET, NN_RCVFD, (char*) &rcvfd, &fdsz);
    FD_SET (rcvfd, &pollset);
    if (rcvfd + 1 > maxfd)
      maxfd = rcvfd + 1;
  }
  
  if (timeout >= 0) {
    tv.tv_sec = timeout / 1000;
    tv.tv_usec = (timeout % 1000) * 1000;
  }
  
  select (maxfd, &pollset, NULL, NULL, timeout < 0 ? NULL : &tv);
  revents = 0;
  if ((events & NN_IN) && FD_ISSET (rcvfd, &pollset))
    revents |= NN_IN;
  return revents;
}

void* worker() {
  void* message;
  int x=0;
  double l = 0;
  
  while (chan_recv(messages, &message) == 0) {
    ++x;
    if(x % 10000 == 0){
      char *msg = (char *)message;
      const char* fourteen = "14";
      const char *ptr = strstr(msg, fourteen);
      double d;
      sscanf(ptr, "%lf", &d);
      if(l){
        float f = (d-l)/1000;
        printf("10K msgs in %g secs. %d msgs recvd\n", f, x);
      }
      l = d;
    }
  }
  return NULL;
}

void* worker2() {
  while (1) {
    r = getevents (s, NN_IN, 10);
    if(r == 1){
      char *b = NULL;
      nn_recv (s, &b, NN_MSG, 0);
      chan_send (messages, b);
      nn_freemsg (b);
    }
  }
}


void init_channels(void) {
  jobs = chan_init(0);
  done = chan_init(0);
  messages = chan_init(0);
  
  pthread_t th;
  pthread_create(&th, NULL, worker, NULL);
  
  pthread_t poll_rc;
  pthread_create(&poll_rc, NULL, worker2, NULL);
}