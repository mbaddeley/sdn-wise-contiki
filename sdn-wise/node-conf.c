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
 *         SDN-WISE Node Configurations.
 * \author
 *         Sebastiano Milardo <s.milardo@hotmail.it>
 */

/**
 * \addtogroup sdn-wise
 * @{
 */

#include <string.h>
#include <stdio.h>

#include "contiki.h"
#include "node-id.h"
#include "address.h"
#include "node-conf.h"
#include "net/rime/rime.h"

#ifndef SDN_WISE_DEBUG
#define SDN_WISE_DEBUG 0
#endif
#if SDN_WISE_DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

#define MAX_TX_NODES 5
#define TX_NODES 10,11,17,16,15
static int data_tx_nodes[MAX_TX_NODES] = {TX_NODES};

static uint8_t
is_a_tx_node() {
  int i;
  for (i = 0; i < MAX_TX_NODES; i++) {
    if (data_tx_nodes[i] == node_id) {
      return 1;
    }
  }
  return 0;
}

/*----------------------------------------------------------------------------*/
  node_conf_t conf;
/*----------------------------------------------------------------------------*/
  void
  node_conf_init(void)
  {

#if COOJA
    conf.my_address.u8[1] = linkaddr_node_addr.u8[0];
    conf.my_address.u8[0] = linkaddr_node_addr.u8[1];
#else
    conf.my_address = get_address_from_int(_MY_ADDRESS);
    linkaddr_node_addr.u8[1] = conf.my_address.u8[0];
    linkaddr_node_addr.u8[0] = conf.my_address.u8[1];
#endif
    conf.requests_count = 0;
    conf.my_net = _NET;
    conf.beacon_period = _BEACON_PERIOD;
    conf.report_period = _REPORT_PERIOD;
    conf.rule_ttl = _RULE_TTL;
    conf.rssi_min = _RSSI_MIN;
    conf.packet_ttl = _PACKET_TTL;
#if SINK
    conf.is_active = 1;
    conf.nxh_vs_sink = conf.my_address;
    conf.sink_address = conf.my_address;
    conf.distance_from_sink = _MIN_DISTANCE;
    conf.hops_from_sink = 0;
#else
    conf.is_active = 0;
    set_broadcast_address(&(conf.nxh_vs_sink));
    set_broadcast_address(&(conf.sink_address));
    conf.distance_from_sink = _MAX_DISTANCE;
    conf.hops_from_sink = _PACKET_TTL;
    conf.reset_period = _RESET_PERIOD;
#endif
    // HACK: This allows us to pick and choose which nodes send data REMOVEME
    conf.send_data = is_a_tx_node();
  }
/*----------------------------------------------------------------------------*/
  void
  print_node_conf(void){
    printf("[CFG]: NODE: ");
    print_address(&(conf.my_address));
    printf("\n");
    printf("[CFG]: - Network ID: %d\n[CFG]: - Beacon Period: %d\n[CFG]: - "
      "Report Period: %d\n[CFG]: - Rules TTL: %d\n[CFG]: - Min RSSI: "
      "%d\n[CFG]: - Packet TTL: %d\n[CFG]: - Next Hop -> Sink: ",
      conf.my_net, conf.beacon_period, conf.report_period,
      conf.rule_ttl, conf.rssi_min, conf.packet_ttl);
    print_address(&(conf.nxh_vs_sink));
    printf(" (hops: %d, distance: %d)\n", conf.hops_from_sink, conf.distance_from_sink);
    printf("[CFG]: - Sink: ");
    print_address(&(conf.sink_address));
    printf("[CFG]: - TX_NODE: %u", conf.send_data);
    printf("\n");
  }
/*----------------------------------------------------------------------------*/
/** @} */
