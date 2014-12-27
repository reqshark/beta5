/*
    Copyright (c) 2012-2013 Martin Sustrik  All rights reserved.

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom
    the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/


//the poller_kqueue.h header file & poller_kqueue.inc for iOS/Mac OSX/BSD platforms
//have been refactored and combined into poller.h & poller.c nanomsg aio sources
//probably the very trick achieved by good iOS SDK cross-compilation techniques

#include <sys/event.h>

//iOS & OSX macros
#define NN_POLLER_INCLUDED
#define NN_POLLER_IN 1
#define NN_POLLER_OUT 2
#define NN_POLLER_ERR 3
#define NN_POLLER_EVENT_IN 1
#define NN_POLLER_EVENT_OUT 2
#define NN_POLLER_MAX_EVENTS 32

struct nn_poller_hndl {
  int fd;
  int events;
};

struct nn_poller {

  /*  Current pollset. */
  int kq;

  /*  Number of events being processed at the moment. */
  int nevents;

  /*  Index of the event being processed at the moment. */
  int index;

  /*  Cached events. */
  struct kevent events [NN_POLLER_MAX_EVENTS];
};

int nn_poller_init (struct nn_poller *self);
void nn_poller_term (struct nn_poller *self);
void nn_poller_add (struct nn_poller *self, int fd,
                    struct nn_poller_hndl *hndl);
void nn_poller_rm (struct nn_poller *self, struct nn_poller_hndl *hndl);
void nn_poller_set_in (struct nn_poller *self, struct nn_poller_hndl *hndl);
void nn_poller_reset_in (struct nn_poller *self, struct nn_poller_hndl *hndl);
void nn_poller_set_out (struct nn_poller *self, struct nn_poller_hndl *hndl);
void nn_poller_reset_out (struct nn_poller *self, struct nn_poller_hndl *hndl);
int nn_poller_wait (struct nn_poller *self, int timeout);
int nn_poller_event (struct nn_poller *self, int *event,
                     struct nn_poller_hndl **hndl);