/*
 * Copyright (C) 2015 SDN-WISE
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * \file
 *         Header file for the SDN-WISE Contiki porting.
 * \author
 *         Sebastiano Milardo <s.milardo@hotmail.it>
 */

/**
 * \defgroup sdn-wise SDN-WISE porting
 * @{
 *
 * The SDN-WISE module implements SDN-WISE in Contiki.
 */

#ifndef SDN_WISE_H_
#define SDN_WISE_H_

#include "lib/list.h"
#include "lib/memb.h"
#include "packet-buffer.h"

#define SDN_CODE_STRING(code) \
  ((code == DATA) ? ("DATA") : \
  (code == BEACON) ? ("BEACON") : \
  (code == REPORT) ? ("REPORT") : \
  (code == REQUEST) ? ("REQUEST") : \
  (code == RESPONSE) ? ("RESPONSE") : \
  (code == OPEN_PATH) ? ("OPEN_PATH") : \
  (code == CONFIG) ? ("CONFIG") : \
  (code == REG_PROXY) ? ("REG_PROXY") : "UNKNOWN")

// // So we can keep track of the last REQUEST pid from each node

#define MAX_NODES 32
extern uint16_t pid_request[MAX_NODES];
extern uint8_t have_received_open_path[MAX_NODES];

void rf_unicast_send(packet_t*);
void rf_broadcast_send(packet_t*);

#endif /* SDN_WISE_H_ */
/** @} */
