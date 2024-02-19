set(srcs
    ${ADF_BOARD_INIT_SRC}
    ${ADF_BOARD_CODEC_SRC}
    ${ADF_BOARD_DIR}/board_pins_config.c
    ${ADF_COMPS}/audio_hal/audio_hal.c
    ${ADF_COMPS}/audio_hal/audio_volume.c
    ${ADF_COMPS}/audio_stream/http_stream.c
    ${ADF_COMPS}/audio_stream/i2s_stream.c
    ${ADF_COMPS}/audio_stream/raw_stream.c
    ${ADF_COMPS}/audio_stream/http_playlist.c
    ${ADF_COMPS}/audio_stream/lib/gzip/gzip_miniz.c
    ${ADF_COMPS}/audio_stream/lib/hls/hls_parse.c
    ${ADF_COMPS}/audio_stream/lib/hls/hls_playlist.c
    ${ADF_COMPS}/audio_stream/lib/hls/join_path.c
    ${ADF_COMPS}/audio_stream/lib/hls/line_reader.c
    ${ADF_COMPS}/esp_peripherals/driver/i2c_bus/i2c_bus.c


    ${ADF_COMPS}/audio_stream/tone_stream.c
    ${ADF_COMPS}/tone_partition/tone_partition.c
    ${ADF_COMPS}/esp_actions/partition_action.c
    ${ADF_COMPS}/esp_dispatcher/esp_dispatcher.c
    ${ADF_COMPS}/esp_dispatcher/esp_delegate.c
    ${ADF_COMPS}/audio_stream/embed_flash_stream.c
    

)

set(includes
    ${ADF_BOARD_DIR}/
    ${ADF_BOARD_CODEC_INC}
    $ENV{ADF_PATH}/micropython_adf/boards/include
    ${ADF_COMPS}/audio_board/include
    ${ADF_COMPS}/audio_hal/include
    ${ADF_COMPS}/audio_hal/driver/include
    ${ADF_COMPS}/audio_stream/include
    ${ADF_COMPS}/audio_stream/lib/gzip/include
    ${ADF_COMPS}/audio_stream/lib/hls/include
    ${ADF_COMPS}/esp_peripherals/include
    ${ADF_COMPS}/esp_peripherals/driver/i2c_bus
    ${ADF_COMPS}/display_service/include
    ${ADF_COMPS}/esp_dispatcher/include


    ${ADF_COMPS}/tone_partition/include
    ${IDF_PATH}/components/bootloader_support/include
    ${IDF_PATH}/components/esp_app_format/include
    ${ADF_COMPS}/esp_actions/include
)
set(COMPONENT_EMBED_TXTFILES					
audio/boot.mp3                          
audio/bound_failed.mp3                  
audio/bound_success.mp3                 
audio/busy.mp3                          
audio/closed.mp3                        
audio/full.mp3                          
audio/invalid_operation.mp3             
audio/low_power.mp3                     
audio/network_unavailable.mp3           
audio/not_bound.mp3                     
audio/no_your_pkg.mp3                   
audio/timeout.mp3                       
audio/unlock_failed.mp3                 
audio/unlock_not_allow_failed.mp3       
audio/unlock_success.mp3                
audio/wifi_config_success.mp3           
audio/wifi_conn_failed.mp3            
audio/wifi_network_unavailable.mp3     
audio/remind_to_close.mp3               
audio/wifi_config_start.mp3             
audio/complete_binding_guide.mp3        
audio/operation_not_allowed.mp3         
audio/not_completely_closed.mp3         
audio/cancel.mp3                        
audio/enter_phone_number.mp3            
audio/enter_room_number.mp3             
audio/user_input_tips.mp3          		
audio/enter_company_id.mp3       		
audio/enter_company_id_or_phone_num.mp3	
audio/enter_room_num_or_phone_num.mp3
audio/no_deliverable_box.mp3
audio/room_not_deliverable.mp3
)
idf_component_register(
    SRCS "${srcs}"
    INCLUDE_DIRS "${includes}"
    REQUIRES audio_pipeline audio_sal driver esp-adf-libs esp_http_client esp_lcd
    EMBED_TXTFILES "${COMPONENT_EMBED_TXTFILES}"
)
