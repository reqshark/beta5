//
//  bridger.c
//  nn
//
//  created by Bent Cardan
//  reqshark software. lifestyles of the rich and/or resourceful. authored 12/23/2014
//

#include <stdio.h>
#include <stdlib.h>
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

char* msgGet(int s){
  char *b = NULL;
  nn_recv (s, &b, NN_MSG, 1);
  return b;
}

int msgFree(char* m){
  nn_freemsg(m);
  return 0;
}