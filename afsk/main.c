/*
 *  A sample application transmitting 1k2 AFSK in X.25 format
 *
 *  Portions Copyright (C) 2018 Jonathan Brandenburg
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "status.h"
#include "ax5043.h"
#include "ax25.h"
#include "spi/ax5043spi.h"

ax5043_conf_t hax5043;
ax25_conf_t hax25;

static void init_rf();
void config_x25();
void trans_x25();

int main(void) {
    setSpiChannel(SPI_CHANNEL);
    setSpiSpeed(SPI_SPEED);
    initializeSpi();

    int ret;
    uint8_t data[1024];
    // 0x03 is a UI frame
    // 0x0F is no Level 3 protocol
    // rest is dummy CubeSatSim telemetry in AO-7 format 	
    const char *str = "\x03\x0fhi hi 101 102 103 104 202 203 204 205 303 304 305 306 404 405 406 407 408 505 506 507 508 606 607 608 609\n";

    /* Infinite loop */
    for (;;) {
        sleep(2);
    	
	// send X.25 packet

    	init_rf();

    	ax25_init(&hax25, (uint8_t *) "CQ", '2', (uint8_t *) "DX", '2',
    		AX25_PREAMBLE_LEN,
   		 AX25_POSTAMBLE_LEN);

        
	printf("INFO: Transmitting X.25 packet\n");

        memcpy(data, str, strnlen(str, 256));
        ret = ax25_tx_frame(&hax25, &hax5043, data, strnlen(str, 256));
        if (ret) {
            fprintf(stderr,
                    "ERROR: Failed to transmit AX.25 frame with error code %d\n",
                    ret);
            exit(EXIT_FAILURE);
        }
        ax5043_wait_for_transmit();
        if (ret) {
            fprintf(stderr,
                    "ERROR: Failed to transmit entire AX.25 frame with error code %d\n",
                    ret);
            exit(EXIT_FAILURE);
        }

    }

    return 0;
}

static void init_rf() {
    int ret;
    ret = ax5043_init(&hax5043, XTAL_FREQ_HZ, VCO_INTERNAL);
    if (ret != PQWS_SUCCESS) {
        fprintf(stderr,
                "ERROR: Failed to initialize AX5043 with error code %d\n", ret);
        exit(EXIT_FAILURE);
    }
}
