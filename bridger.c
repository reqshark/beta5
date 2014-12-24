//
//  bridger.c
//  nn
//
//  Created by Bent Cardan on 12/23/14.
//  Copyright (c) 2014 Bent Cardan. All rights reserved.
//

#include "bridger.h"

int s, r, eid;

int getevents (int s, int events, int timeout){
  fd_set pollset;
  int rcvfd;
  int sndfd;
  int maxfd;
  int grc;
  
  
  size_t fdsz;
  struct timeval tv;
  int revents;
  
  maxfd = 0;
  FD_ZERO (&pollset);
  
  if (events & NN_IN) {
    fdsz = sizeof (rcvfd);
    grc = nn_getsockopt (s, NN_SOL_SOCKET, NN_RCVFD, (char*) &rcvfd, &fdsz);
    FD_SET (rcvfd, &pollset);
    if (rcvfd + 1 > maxfd)
      maxfd = rcvfd + 1;
  }
  
  //strictly for sending the next
  if (events & NN_OUT) {
    fdsz = sizeof (sndfd);
    grc = nn_getsockopt (s, NN_SOL_SOCKET, NN_SNDFD, (char*) &sndfd, &fdsz);
    FD_SET (sndfd, &pollset);
    if (sndfd + 1 > maxfd)
      maxfd = sndfd + 1;
  }
  
  if (timeout >= 0) {
    tv.tv_sec = timeout / 1000;
    tv.tv_usec = (timeout % 1000) * 1000;
  }
  
  select (maxfd, &pollset, NULL, NULL, timeout < 0 ? NULL : &tv);
  revents = 0;
  if ((events & NN_IN) && FD_ISSET (rcvfd, &pollset))
    revents |= NN_IN;
  if ((events & NN_OUT) && FD_ISSET (sndfd, &pollset))
    revents |= NN_OUT;
  return revents;
}

void* worker(){
  void* message;
  while (chan_recv(messages, &message) == 0)
  {
    printf("received message: %s\n", message);
  }
  
  // Notify that all jobs were received.
  printf("received all jobs\n");
  chan_send(done, "1");
  return NULL;
}

void* worker2() {
  while (1) {
    r = getevents (s, NN_IN, 10);
    if(r == 1){
      char *b = NULL;
      nn_recv (s, &b, NN_MSG, 0);
      chan_send(messages, b);
      nn_freemsg (b);
    }
  }
}


void init_channels(void){
  jobs = chan_init(0);
  done = chan_init(0);
  messages = chan_init(0);
  
  pthread_t th;
  pthread_create(&th, NULL, worker, NULL);
  
  pthread_t poll_rc;
  pthread_create(&poll_rc, NULL, worker2, NULL);
}