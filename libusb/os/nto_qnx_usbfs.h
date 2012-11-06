/*
 * QNX Neutrino backend for libusb
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef __LIBUSB_USBFS_H__
#define __LIBUSB_USBFS_H__

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/usbdi.h>
#include <fcntl.h>
#include <sys/queue.h>
#include <time.h>

/* message passing */
#include <sys/iofunc.h>
#include <sys/neutrino.h>
#include <sys/dispatch.h>

#include "libusb.h"
#include "libusbi.h"

/* The TIMEVAL_TO_TIMESPEC and TIMESPEC_TO_TIMEVAL macros should be in
   sys/time.h ideally, they are here in the meantime */

/* Macros for converting between `struct timeval' and `struct timespec'.  */
# define TIMEVAL_TO_TIMESPEC(tv, ts) {                                   \
        (ts)->tv_sec = (tv)->tv_sec;                                    \
        (ts)->tv_nsec = (tv)->tv_usec * 1000;                           \
}
# define TIMESPEC_TO_TIMEVAL(tv, ts) {                                   \
        (tv)->tv_sec = (ts)->tv_sec;                                    \
        (tv)->tv_usec = (ts)->tv_nsec / 1000;                           \
}

struct claimed_interfaces_list {
    TAILQ_ENTRY(claimed_interfaces_list) chain;
    int claimed_interface;
};

struct nto_qnx_device_priv
{
    unsigned char * dev_descriptor;
    unsigned char * config_descriptor;
    struct usbd_device * usbd_device; /**< pointer to QNX USB device structure */
    struct usbd_connection * connection; /**< pointer to QNX USB device structure */
    int selected_configuration;
    TAILQ_HEAD(, claimed_interfaces_list) claimed_interfaces;
};

struct nto_qnx_device_handle_priv
{
    /* Don't need this here anymore: */
    /* struct nu_dev * nu_dev; */

    /* TODO: Potential idea for this memory may be the control pipe
       that's currently opened as part of the, insertion callback */
    struct usbd_pipe * control_pipe; /**< device control pipe */
    int fds[2];                  /* file descriptors returned from pipe() */
    int interface_number;
    int alt;
};

struct nto_qnx_transfer_priv
{
    unsigned char * internal_buffer;
    struct usbd_urb * urb;
    struct usbd_pipe * transfer_pipe;
};

enum {
    MESSAGE_DEVICE_GONE,
    MESSAGE_ASYNC_IO_COMPLETE
};

enum nto_qnx_urb_type {
	NTO_QNX_URB_TYPE_ISO = 0,
	NTO_QNX_URB_TYPE_INTERRUPT = 1,
	NTO_QNX_URB_TYPE_CONTROL = 2,
	NTO_QNX_URB_TYPE_BULK = 3,
};

/* Function declarations */


#endif


