/*
 Copyright (C) AC SOFTWARE SP. Z O.O.

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include "dimmer.h"
#include "supla_esp_devconn.h"

uint8 dimmer_brightness[3] = { 0, 0, 0 };

#define B_CFG_PORT         0

void ICACHE_FLASH_ATTR supla_esp_board_set_device_name(char *buffer, uint8 buffer_size) {
	ets_snprintf(buffer, buffer_size, "Dimmer");
}


void ICACHE_FLASH_ATTR supla_esp_board_gpio_init(void) {
		
	supla_input_cfg[0].type = INPUT_TYPE_BTN_MONOSTABLE;
	supla_input_cfg[0].gpio_id = B_CFG_PORT;
	supla_input_cfg[0].flags = INPUT_FLAG_PULLUP | INPUT_FLAG_CFG_BTN;
}

void ICACHE_FLASH_ATTR supla_esp_board_pwm_init(void) {
	supla_esp_channel_set_rgbw_value(0, 0, 0, supla_esp_state.brightness[0], 0, 0);
	supla_esp_channel_set_rgbw_value(1, 0, 0, supla_esp_state.brightness[1], 0, 0);
	supla_esp_channel_set_rgbw_value(2, 0, 0, supla_esp_state.brightness[2], 0, 0);
	supla_log(LOG_DEBUG, "Channel:0, value:%d\n\r", supla_esp_state.brightness[0]);
	supla_log(LOG_DEBUG, "Channel:1, value:%d\n\r", supla_esp_state.brightness[1]);
	supla_log(LOG_DEBUG, "Channel:2, value:%d\n\r", supla_esp_state.brightness[2]);
}

void ICACHE_FLASH_ATTR supla_esp_board_set_channels(TDS_SuplaDeviceChannel_C *channels, unsigned char *channel_count) {

	*channel_count = 3;

	channels[0].Type = SUPLA_CHANNELTYPE_DIMMER;
	channels[0].Number = 0;
	supla_esp_channel_rgbw_to_value(channels[0].value, 0, 0, supla_esp_state.brightness[0]);
	
	channels[1].Type = SUPLA_CHANNELTYPE_DIMMER;
	channels[1].Number = 1;
	supla_esp_channel_rgbw_to_value(channels[1].value, 0, 0, supla_esp_state.brightness[1]);
	
	channels[2].Type = SUPLA_CHANNELTYPE_DIMMER;
	channels[2].Number = 2;
	supla_esp_channel_rgbw_to_value(channels[2].value, 0, 0, supla_esp_state.brightness[2]);

}

char ICACHE_FLASH_ATTR supla_esp_board_set_rgbw_value(int ChannelNumber, int *Color, float *ColorBrightness, float *Brightness) {
	
	supla_log(LOG_DEBUG, "Channel:%d\n\r", ChannelNumber);

	dimmer_brightness[ChannelNumber] = *Brightness;
	
	if ( dimmer_brightness[ChannelNumber] > 100 )
		dimmer_brightness[ChannelNumber] = 100;
	
	supla_esp_pwm_set_percent_duty(dimmer_brightness[ChannelNumber], 100, ChannelNumber);

	return 1;
}


void ICACHE_FLASH_ATTR supla_esp_board_get_rgbw_value(int ChannelNumber, int *Color, float *ColorBrightness, float *Brightness) {

	if ( Brightness != NULL ) {
			*Brightness = dimmer_brightness[ChannelNumber];
	}

}

void ICACHE_FLASH_ATTR supla_esp_board_send_channel_values_with_delay(void *srpc) {

}
