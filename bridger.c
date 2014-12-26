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

char* data;

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

/* 
 void* worker1() {
  while (ready == 1) {
    printf("%s" , data);
  }
  return NULL;
}
*/

void ready(char* data){

  printf("%s", data);
  
  free(data);
  
}

int receivedMessageHandler( char* b ) {

  u_long x;
  x = strlen(b);
  data= calloc (x+1, sizeof(x));
  strncpy(data,b,x);
  ready(data);
  return x;
}


void* worker2() {
    
  int xxx;
  int progress = 0 ;
  
  while (1) {
    r = getevents (s, NN_IN, 10);
  
    
    if(r == 1){
      char *b = NULL;
      printf ("%d\n", r);
      xxx = nn_recv (s, &b, NN_MSG, 1);
      progress++;
      printf ("%d %d %d \n", r, xxx, progress );

      
      receivedMessageHandler( b );
      
      nn_freemsg (b);
      
        
    }
  }
}



void init_channels(void) {
  
//  jobs = chan_init(0);
//  done = chan_init(0);
//  messages = chan_init(0);
  
  pthread_t poll_rc;
  pthread_create(&poll_rc, NULL, worker2, NULL);

//  pthread_t poll_rc2;
//  pthread_create(&poll_rc2, NULL, worker1, NULL);

  
}