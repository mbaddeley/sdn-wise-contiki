/*
 * Copyright (c) 2019, Toshiba Research Europe Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */
/**
 * \file
 *         uSDN Core: SDN statistics.
 * \author
 *         Michael Baddeley <m.baddeley@bristol.ac.uk>
 */
#include "contiki.h"
#include "contiki-lib.h"
#include "node-id.h"

#include <stdio.h>
#include <string.h>

/* Log configuration */
#include "log-ng.h"
#include "log-ng-conf.h"
#define LOG_MODULE "SDN-PWR"
#define LOG_LEVEL LOG_LEVEL_INFO

PROCESS(sdn_pwr_process, "Periodic SDN statistics output");
/*---------------------------------------------------------------------------*/
static inline unsigned long
to_milliseconds(uint64_t time)
{
  return (unsigned long)(time / (RTIMER_SECOND / 1000));
}

/*---------------------------------------------------------------------------*/
static inline void
print_division(unsigned long x, unsigned long y)
{
  unsigned int a = (unsigned int)((100L * x) / y);
  unsigned int b = (unsigned int)((10000L * x / y) - (100L * x / y) * 100);
  if(b < 0) {
    b = (~b + 1);
  }
  printf("%02u.%02u", a, b % 100);
}


/*---------------------------------------------------------------------------*/
void
sdn_pwr_start(clock_time_t period)
{
  LOG_INFO("Starting sdn_pwr_process\n");
  process_start(&sdn_pwr_process, (void *)&period);
}
/*---------------------------------------------------------------------------*/
void
sdn_pwr_stop(void)
{
  LOG_INFO("Ending sdn_pwr_process\n");
  process_exit(&sdn_pwr_process);
}

/*---------------------------------------------------------------------------*/
void
sdn_energy_print()
{
  static unsigned long last_cpu, last_lpm, last_transmit, last_listen;

  unsigned long cpu, lpm, transmit, listen;
  unsigned long all_cpu, all_lpm, all_transmit, all_listen;
  unsigned long time_on, radio_on; //radio_off;
  unsigned long all_time_on, all_radio_on; //all_radio_off;

  /*
   * Update all energest times. Should always be called before energest
   * times are read.
   */
  energest_flush();

  /* Get current energest times (to date) */
  all_cpu = energest_type_time(ENERGEST_TYPE_CPU) / (RTIMER_SECOND / 1000);
  all_lpm = energest_type_time(ENERGEST_TYPE_LPM) / (RTIMER_SECOND / 1000);
  all_transmit = energest_type_time(ENERGEST_TYPE_TRANSMIT) / (RTIMER_SECOND / 1000);
  all_listen = energest_type_time(ENERGEST_TYPE_LISTEN) / (RTIMER_SECOND / 1000);

  /* Work out time since last called */
  cpu = all_cpu - last_cpu;
  lpm = all_lpm - last_lpm;
  transmit = all_transmit - last_transmit;
  listen = all_listen - last_listen;

  /* Save current times for next call */
  last_cpu = all_cpu;
  last_lpm = all_lpm;
  last_transmit = all_transmit;
  last_listen = all_listen;

  /* This round's radio + time */
  time_on = cpu + lpm;
  radio_on = transmit + listen;
  // radio_off = time_on - radio_on;

  /* Total radio + time */
  all_time_on = all_cpu + all_lpm;
  all_radio_on = all_transmit + all_listen;
  // all_radio_off = all_time_on - all_radio_on;

  /* Print information about average radio-on time per second */
  LOG_STAT("PW ");
  LOG_STAT_(" (r "); print_division(all_radio_on, all_time_on);
  LOG_STAT_(" / "); print_division(radio_on, time_on);
  LOG_STAT_(" tx "); print_division(all_transmit, all_time_on);
  LOG_STAT_(" / "); print_division(transmit, time_on);
  LOG_STAT_(" rx "); print_division(all_listen, all_time_on);
  LOG_STAT_(" / "); print_division(listen, time_on);
  LOG_STAT_(")\n");
}

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(sdn_pwr_process, ev, data)
{
  static struct etimer periodic;
  clock_time_t *period;
  PROCESS_BEGIN();

  period = data;

  if(period == NULL) {
    LOG_ERR("Exiting SDN power process!\n");
    PROCESS_EXIT();
  }
  etimer_set(&periodic, *period);

  while(1) {
    PROCESS_WAIT_UNTIL(etimer_expired(&periodic));
    etimer_reset(&periodic);
    sdn_energy_print();
  }

  PROCESS_END();
}
