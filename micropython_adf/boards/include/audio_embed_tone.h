
/*
 * ESPRESSIF MIT License
 *
 * Copyright (c) 2022 <ESPRESSIF SYSTEMS (SHANGHAI) CO., LTD>
 *
 * Permission is hereby granted for use on all ESPRESSIF SYSTEMS products, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef AUDIO_EMBED_TONE_URI_H
#define AUDIO_EMBED_TONE_URI_H

typedef struct {
    const uint8_t * address;
    int size;
} embed_tone_t;

extern const uint8_t mp3_boot_start[]                                   asm("_binary_boot_mp3_start"         );
extern const uint8_t mp3_boot_end[]                                     asm("_binary_boot_mp3_end"           );
extern const uint8_t mp3_bound_failed_start[]                           asm("_binary_bound_failed_mp3_start" );
extern const uint8_t mp3_bound_failed_end[]                             asm("_binary_bound_failed_mp3_end"   );
extern const uint8_t mp3_bound_success_start[]                          asm("_binary_bound_success_mp3_start");
extern const uint8_t mp3_bound_success_end[]                            asm("_binary_bound_success_mp3_end"  );
extern const uint8_t mp3_busy_start[]                                   asm("_binary_busy_mp3_start"         );
extern const uint8_t mp3_busy_end[]                                     asm("_binary_busy_mp3_end"           );
extern const uint8_t mp3_closed_start[]                                 asm("_binary_closed_mp3_start"       );
extern const uint8_t mp3_closed_end[]                                   asm("_binary_closed_mp3_end"         );
extern const uint8_t mp3_full_start[]                                   asm("_binary_full_mp3_start"         );
extern const uint8_t mp3_full_end[]                                     asm("_binary_full_mp3_end"             );
extern const uint8_t mp3_invalid_operation_start[]                      asm("_binary_invalid_operation_mp3_start");
extern const uint8_t mp3_invalid_operation_end[]                        asm("_binary_invalid_operation_mp3_end"    );
extern const uint8_t mp3_low_power_start[]                              asm("_binary_low_power_mp3_start"          );
extern const uint8_t mp3_low_power_end[]                                asm("_binary_low_power_mp3_end"            );
extern const uint8_t mp3_network_unavailable_start[]                    asm("_binary_network_unavailable_mp3_start");
extern const uint8_t mp3_network_unavailable_end[]                      asm("_binary_network_unavailable_mp3_end"  );
extern const uint8_t mp3_not_bound_start[]                              asm("_binary_not_bound_mp3_start"          );
extern const uint8_t mp3_not_bound_end[]                                asm("_binary_not_bound_mp3_end"            );
extern const uint8_t mp3_no_your_pkg_start[]                            asm("_binary_no_your_pkg_mp3_start"        );
extern const uint8_t mp3_no_your_pkg_end[]                              asm("_binary_no_your_pkg_mp3_end"          );
extern const uint8_t mp3_timeout_start[]                                asm("_binary_timeout_mp3_start"            );
extern const uint8_t mp3_timeout_end[]                                  asm("_binary_timeout_mp3_end"              );
extern const uint8_t mp3_unlock_failed_start[]                          asm("_binary_unlock_failed_mp3_start"          );
extern const uint8_t mp3_unlock_failed_end[]                            asm("_binary_unlock_failed_mp3_end"            );
extern const uint8_t mp3_unlock_not_allow_failed_start[]                asm("_binary_unlock_not_allow_failed_mp3_start");
extern const uint8_t mp3_unlock_not_allow_failed_end[]                  asm("_binary_unlock_not_allow_failed_mp3_end"   );
extern const uint8_t mp3_unlock_success_start[]                         asm("_binary_unlock_success_mp3_start"          );
extern const uint8_t mp3_unlock_success_end[]                           asm("_binary_unlock_success_mp3_end"            );
extern const uint8_t mp3_wifi_config_success_start[]                    asm("_binary_wifi_config_success_mp3_start"     );
extern const uint8_t mp3_wifi_config_success_end[]                      asm("_binary_wifi_config_success_mp3_end"       );
extern const uint8_t mp3_wifi_conn_failed_start[]                       asm("_binary_wifi_conn_failed_mp3_start"        );
extern const uint8_t mp3_wifi_conn_failed_end[]                         asm("_binary_wifi_conn_failed_mp3_end"          );
extern const uint8_t mp3_wifi_network_unavailable_start[]               asm("_binary_wifi_network_unavailable_mp3_start");
extern const uint8_t mp3_wifi_network_unavailable_end[]                 asm("_binary_wifi_network_unavailable_mp3_end"  );
extern const uint8_t mp3_remind_to_close_start[]                        asm("_binary_remind_to_close_mp3_start"         );
extern const uint8_t mp3_remind_to_close_end[]                          asm("_binary_remind_to_close_mp3_end"           );
extern const uint8_t mp3_wifi_config_start_start[]                      asm("_binary_wifi_config_start_mp3_start"       );
extern const uint8_t mp3_wifi_config_start_end[]                        asm("_binary_wifi_config_start_mp3_end"         );
extern const uint8_t mp3_complete_binding_guide_start[]                 asm("_binary_complete_binding_guide_mp3_start"  );
extern const uint8_t mp3_complete_binding_guide_end[]                   asm("_binary_complete_binding_guide_mp3_end"    );
extern const uint8_t mp3_operation_not_allowed_start[]                  asm("_binary_operation_not_allowed_mp3_start"   );
extern const uint8_t mp3_operation_not_allowed_end[]                    asm("_binary_operation_not_allowed_mp3_end"     );
extern const uint8_t mp3_not_completely_closed_start[]                  asm("_binary_not_completely_closed_mp3_start"   );
extern const uint8_t mp3_not_completely_closed_end[]                    asm("_binary_not_completely_closed_mp3_end"     );

extern const uint8_t mp3_input_cancel_start[]                           asm("_binary_cancel_mp3_start"   );
extern const uint8_t mp3_input_cancel_end[]                             asm("_binary_cancel_mp3_end"     );
extern const uint8_t mp3_enter_phone_num_start[]                        asm("_binary_enter_phone_number_mp3_start"   );
extern const uint8_t mp3_enter_phone_num_end[]                          asm("_binary_enter_phone_number_mp3_end"     );
extern const uint8_t mp3_enter_room_num_start[]                         asm("_binary_enter_room_number_mp3_start"   );
extern const uint8_t mp3_enter_room_num_end[]                           asm("_binary_enter_room_number_mp3_end"     );


extern const uint8_t mp3_enter_company_id_start[]            			asm("_binary_enter_company_id_mp3_start"   );
extern const uint8_t mp3_enter_company_id_end[]              			asm("_binary_enter_company_id_mp3_end"     );

extern const uint8_t mp3_enter_company_id_or_phone_num_start[]          asm("_binary_enter_company_id_or_phone_num_mp3_start"   );
extern const uint8_t mp3_enter_company_id_or_phone_num_end[]            asm("_binary_enter_company_id_or_phone_num_mp3_end"     );

extern const uint8_t mp3_enter_room_num_or_phone_num_start[]            asm("_binary_enter_room_num_or_phone_num_mp3_start"   );
extern const uint8_t mp3_enter_room_num_or_phone_num_end[]              asm("_binary_enter_room_num_or_phone_num_mp3_end"     );

extern const uint8_t mp3_user_input_tips_start[]           				asm("_binary_user_input_tips_mp3_start"   );
extern const uint8_t mp3_user_input_tips_end[]             				asm("_binary_user_input_tips_mp3_end"     );

extern const uint8_t mp3_room_not_deliverable_start[]           		asm("_binary_room_not_deliverable_mp3_start"   );
extern const uint8_t mp3_room_not_deliverable_end[]             		asm("_binary_room_not_deliverable_mp3_end"     );

extern const uint8_t mp3_no_deliverable_box_start[]           		asm("_binary_no_deliverable_box_mp3_start"   );
extern const uint8_t mp3_no_deliverable_box_end[]             		asm("_binary_no_deliverable_box_mp3_end"     );

/**
 * @brief embed tone corresponding resource information, as a variable of the `embed_flash_stream_set_context` function
 */
embed_tone_t g_embed_tone[] = {
    [0] = { .address = mp3_boot_start, .size  = 9762, },
    [1] = { .address = mp3_bound_failed_start,.size = 22301,},
    [2] = { .address = mp3_bound_success_start, .size  = 10546, },
    [3] = { .address = mp3_busy_start,.size = 22458,},
    [4] = { .address = mp3_closed_start, .size  = 9762, },
    [5] = { .address = mp3_full_start,.size = 22458,},
    [6] = { .address = mp3_invalid_operation_start, .size  = 8352, },
    [7] = { .address = mp3_low_power_start,.size = 20107,},
    [8] = { .address = mp3_network_unavailable_start, .size  = 11643, },
    [9] = { .address = mp3_not_bound_start,.size = 14778,},
    [10] = { .address = mp3_no_your_pkg_start, .size  = 12270, },
    [11] = { .address = mp3_timeout_start,.size = 27473,},
    [12] = { .address = mp3_unlock_failed_start, .size  = 11173, },
    [13] = { .address = mp3_unlock_not_allow_failed_start,.size = 10703,},
    [14] = { .address = mp3_unlock_success_start, .size  = 27160, },
    [15] = { .address = mp3_wifi_config_success_start,.size = 16188,},
    [16] = { .address = mp3_wifi_conn_failed_start, .size  = 29668, },
    [17] = { .address = mp3_wifi_network_unavailable_start,.size = 32332,},
    [18] = { .address = mp3_remind_to_close_start,.size = 9762,},
    [19] = { .address = mp3_wifi_config_start_start, .size  = 12897, },
    [20] = { .address = mp3_complete_binding_guide_start,.size = 28727,},
    [21] = { .address = mp3_operation_not_allowed_start, .size  = 13837, },
    [22] = { .address = mp3_not_completely_closed_start,.size = 16815,},
    [23] = { .address = mp3_input_cancel_start, .size  = 22615, },
    [24] = { .address = mp3_enter_phone_num_start,.size = 42206,},
    [25] = { .address = mp3_enter_room_num_start, .size  = 41423, },
};

/**
 * @brief embed tone url index for `embed_tone_url` array
 */
enum tone_url_e {
    ALARM_MP3 = 0,
    NEW_MESSAGE_MP3 = 1,
    EMBED_TONE_URL_MAX = 26,
};


/**
 * @brief embed tone url
 */
const char * embed_tone_url[] = {
    "embed://tone/0_boot.mp3",
    "embed://tone/1_bound_failed.mp3",
    "embed://tone/2_bound_success.mp3",
    "embed://tone/3_busy.mp3",
    "embed://tone/4_closed.mp3",
    "embed://tone/5_full.mp3",
    "embed://tone/6_invalid_operation.mp3",
    "embed://tone/7_low_power.mp3",
    "embed://tone/8_network_unavailable.mp3",
    "embed://tone/9_not_bound.mp3",
    "embed://tone/10_no_your_pkg.mp3",
    "embed://tone/11_timeout.mp3",
    "embed://tone/12_unlock_failed.mp3",
    "embed://tone/13_unlock_not_allow_failed.mp3",
    "embed://tone/14_unlock_success.mp3",
    "embed://tone/15_wifi_config_success.mp3",
    "embed://tone/16_wifi_conn_failed.mp3",
    "embed://tone/17_wifi_network_unavailable.mp3",
    "embed://tone/18_remind_to_close.mp3",
    "embed://tone/19_wifi_config_start.mp3",
    "embed://tone/20_complete_binding_guide.mp3",
    "embed://tone/21_operation_not_allowed.mp3",
    "embed://tone/22_not_completely_closed.mp3",
    "embed://tone/23_cancel.mp3",
    "embed://tone/24_enter_phone_number.mp3",   
    "embed://tone/25_enter_room_number.mp3", 
};



#endif // AUDIO_EMBED_TONE_URI_H