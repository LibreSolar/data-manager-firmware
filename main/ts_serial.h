/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Copyright (c) 2020 Martin Jäger / Libre Solar
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include <stdbool.h>

/**
 * Initiate the UART interface, event groups and semaphores.
 *
 * Must be called before starting the task.
 */
void ts_serial_setup(void);

/**
 * Thread listening to UART interface, needs to be spawned from main.
 */
void ts_serial_rx_task(void *arg);

/**
 * Returns latest pub message received on the interface and waits until timeout if receiving is
 * currently in progress
 *
 * \param timeout_ms Timeout in milliseconds
 *
 * \returns Pointer to received message (terminated string) or NULL if timed out
 */
char *ts_serial_pubmsg(int timeout_ms);

/**
 * Release buffer after processing to receive new messages
 *
 * This must be called after processing of a successfully received pubmsg is finished.
 */
void ts_serial_pubmsg_clear(void);

/**
 * Send request and lock response buffer
 *
 * \param req Request buffer (null-terminated)
 * \param timeout_ms Maximum timeout for getting buffer mutex
 *
 * \returns ESP_OK if request was sent, ESP_FAIL otherwise
 */
int ts_serial_request(char *req, int timeout_ms);

/**
 * Receive response from buffer
 *
 * This function should be called after ts_serial_request
 *
 * \param timeout_ms Timeout in milliseconds
 *
 * \returns Pointer to received message (terminated string) or NULL if timed out
 */
char *ts_serial_response(int timeout_ms);

/**
 * Release response buffer for new requests
 *
 * This must be called after processing of a successfully received response is finished.
 */
void ts_serial_response_clear(void);

#endif /* SERIAL_H_ */