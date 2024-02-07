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

idf_component_register(
    SRCS "${srcs}"
    INCLUDE_DIRS "${includes}"
    REQUIRES audio_pipeline audio_sal driver esp-adf-libs esp_http_client esp_lcd
)
