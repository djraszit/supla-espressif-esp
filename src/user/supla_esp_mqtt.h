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

#ifndef SUPLA_MQTT_H_
#define SUPLA_MQTT_H_

#include "supla_esp.h"

#ifdef MQTT_SUPPORT_ENABLED

void ICACHE_FLASH_ATTR supla_esp_mqtt_init(void);
void ICACHE_FLASH_ATTR supla_esp_mqtt_before_system_restart(void);
void ICACHE_FLASH_ATTR supla_esp_mqtt_client_start(void);
void ICACHE_FLASH_ATTR supla_esp_mqtt_client_stop(void);
const char ICACHE_FLASH_ATTR *supla_esp_mqtt_topic_prefix(void);
uint8 ICACHE_FLASH_ATTR supla_esp_mqtt_prepare_message(char **topic_name_out,
                                                       void **message_out,
                                                       size_t *message_size_out,
                                                       const char *topic,
                                                       const char *message);
uint8 ICACHE_FLASH_ATTR supla_esp_mqtt_ha_prepare_message(
    char **topic_name_out, void **message_out, size_t *message_size_out,
    uint8 num, const char *json_config);

void ICACHE_FLASH_ATTR supla_esp_mqtt_wants_publish(uint8 idx_from,
                                                    uint8 idx_to);
void ICACHE_FLASH_ATTR supla_esp_mqtt_wants_subscribe(void);

uint8 ICACHE_FLASH_ATTR
supla_esp_board_mqtt_get_subscription_topic(char **topic_name, uint8 index);
uint8 ICACHE_FLASH_ATTR supla_esp_board_mqtt_get_message_for_publication(
    char **topic_name, void **message, size_t *message_size, uint8 index);

#endif /*MQTT_SUPPORT_ENABLED*/

#endif
