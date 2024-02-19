#
# Main component makefile.
#
# This Makefile can be left empty. By default, it will take the sources in the 
# src/ directory, compile them and link them into lib(subdirectory_name).a 
# in the build directory. This behaviour is entirely configurable,
# please read the ESP-IDF documents if you need to do this.
#

COMPONENT_EMBED_TXTFILES := audio/boot.mp3   \
audio/bound_failed.mp3                  \
audio/bound_success.mp3                 \
audio/busy.mp3                          \
audio/closed.mp3                        \
audio/full.mp3                          \
audio/invalid_operation.mp3             \
audio/low_power.mp3                     \
audio/network_unavailable.mp3           \
audio/not_bound.mp3                     \
audio/no_your_pkg.mp3                   \
audio/timeout.mp3                       \
audio/unlock_failed.mp3                 \
audio/unlock_not_allow_failed.mp3       \
audio/unlock_success.mp3                \
audio/wifi_config_success.mp3           \
audio/wifi_conn_failed.mp3              \
audio/wifi_network_unavailable.mp3      \
audio/remind_to_close.mp3               \
audio/wifi_config_start.mp3             \
audio/complete_binding_guide.mp3        \
audio/operation_not_allowed.mp3         \
audio/not_completely_closed.mp3         \
audio/cancel.mp3                        \
audio/enter_phone_number.mp3            \
audio/enter_room_number.mp3             \
audio/user_input_tips.mp3          		\
audio/enter_company_id.mp3       		\
audio/enter_company_id_or_phone_num.mp3	\
audio/enter_room_num_or_phone_num.mp3

