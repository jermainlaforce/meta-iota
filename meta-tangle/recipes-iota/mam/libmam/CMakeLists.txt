# Borrowed from iot2tangle' cmake-mam
# Find the original at https://github.com/iot2tangle/cmake-mam
# Written by Daniel Carpincho (github.com/demichele) and Alejandro Elustondo (github.com/aleelus).
# Adapted to the BitBake environment by Bernardo Rodrigues (github.com/bernardoaraujor).

set(ENTANGLED_DIR ${CMAKE_SOURCE_DIR})
set(MAM_DIR ${ENTANGLED_DIR}/mam)
set(COMMON_DIR ${ENTANGLED_DIR}/common)

add_definitions(-DMAM_MSS_TRAVERSAL)
add_definitions(-DMAM_POLY_MRED_BINARY)

# common-trinary
set(COMMON_TRINARY
#   ${COMMON_DIR}/trinary/add.c
#   ${COMMON_DIR}/trinary/flex_trit.c
#   ${COMMON_DIR}/trinary/ptrit_incr.c
#   ${COMMON_DIR}/trinary/trit_array.c
#   ${COMMON_DIR}/trinary/trit_byte.c
#   ${COMMON_DIR}/trinary/trit_long.c
#   ${COMMON_DIR}/trinary/trit_ptrit.c
    ${COMMON_DIR}/trinary/trit_tryte.c
    ${COMMON_DIR}/trinary/tryte_ascii.c
#   ${COMMON_DIR}/trinary/tryte_long.c
    ${COMMON_DIR}/trinary/tryte.h
    ${COMMON_DIR}/trinary/trits.h
    ${COMMON_DIR}/defs.h
    ${COMMON_DIR}/stdint.h
)
set(COMMON_CRYPTO
    ${COMMON_DIR}/crypto/ftroika/ftroika.c
    ${COMMON_DIR}/crypto/troika/troika.c
    ${COMMON_DIR}/crypto/ftroika/ftroika.h
    ${COMMON_DIR}/crypto/troika/troika.h
)

#==============mam source=====================
# mam-api
set(MAM_API_DIR ${MAM_DIR}/api)
set(MAM_API
    ${MAM_API_DIR}/api.c
    ${MAM_API_DIR}/trit_t_to_mam_msg_read_context_t_map.c
    ${MAM_API_DIR}/trit_t_to_mam_msg_write_context_t_map.c
)

# mam-examples
set(MAM_EXAMPLES_DIR ${MAM_DIR}/examples)
set(MAM_EXAMPLES
    ${MAM_EXAMPLES_DIR}/common.c
    ${MAM_EXAMPLES_DIR}/recv.c
    ${MAM_EXAMPLES_DIR}/send-common.c
    ${MAM_EXAMPLES_DIR}/send-header.c
    ${MAM_EXAMPLES_DIR}/send-msg.c
    ${MAM_EXAMPLES_DIR}/send-packet.c
)

# mam-mam
set(MAM_MAM_DIR ${MAM_DIR}/mam)
set(MAM_MAM
    ${MAM_MAM_DIR}/channel.c
    ${MAM_MAM_DIR}/endpoint.c
    ${MAM_MAM_DIR}/message.c
    ${MAM_MAM_DIR}/mam_channel_t_set.c
    ${MAM_MAM_DIR}/mam_endpoint_t_set.c
    ${MAM_MAM_DIR}/mam_pk_t_set.c
)

# mam-mss
set(MAM_MSS_DIR ${MAM_DIR}/mss)
set(MAM_MSS
#    ${MAM_MSS_DIR}/mss_classic.c
    ${MAM_MSS_DIR}/mss_common.c
    ${MAM_MSS_DIR}/mss_traversal.c
    ${MAM_MSS_DIR}/mss.h
)

# mam-ntru
set(MAM_NTRU_DIR ${MAM_DIR}/ntru)
set(MAM_NTRU
    ${MAM_NTRU_DIR}/ntru.c
    ${MAM_NTRU_DIR}/poly.c
    ${MAM_NTRU_DIR}/mam_ntru_pk_t_set.c
    ${MAM_NTRU_DIR}/mam_ntru_sk_t_set.c
)

# mam-pb3
set(MAM_PB3_DIR ${MAM_DIR}/pb3)
set(MAM_PB3
    ${MAM_PB3_DIR}/pb3.c
)

# mam-prng
set(MAM_PRNG_DIR ${MAM_DIR}/prng)
set(MAM_PRNG
    ${MAM_PRNG_DIR}/prng.c
)

# mam-prototype
set(MAM_PROTOTYPE_DIR ${MAM_DIR}/prototype)
set(MAM_PROTOTYPE
    ${MAM_PROTOTYPE_DIR}/mam.c
    ${MAM_PROTOTYPE_DIR}/mask.c
)

# mam-psk
set(MAM_PSK_DIR ${MAM_DIR}/psk)
set(MAM_PSK
    ${MAM_PSK_DIR}/psk.c
    ${MAM_PSK_DIR}/mam_psk_t_set.c
)

# mam-sponge
set(MAM_SPONGE_DIR ${MAM_DIR}/sponge)
set(MAM_SPONGE
    ${MAM_SPONGE_DIR}/sponge.c
    ${MAM_SPONGE_DIR}/spongos_types.c
    ${MAM_SPONGE_DIR}/spongos.c
)

# mam-trits
set(MAM_TRITS_DIR ${MAM_DIR}/trits)
set(MAM_TRITS
    ${MAM_TRITS_DIR}/buffers.c
    ${MAM_TRITS_DIR}/trits.c
)

# mam-troika
set(MAM_TROIKA_DIR ${MAM_DIR}/troika)
set(MAM_TROIKA
    ${MAM_TROIKA_DIR}/troika.c
    ${MAM_TROIKA_DIR}/troika.h
)

# mam-wots
set(MAM_WOTS_DIR ${MAM_DIR}/wots)
set(MAM_WOTS
    ${MAM_WOTS_DIR}/wots.c
)

# mam
set(MAM
    ${MAM_API}
    ${MAM_EXAMPLES}
    ${MAM_MAM}
    ${MAM_MSS}
    ${MAM_NTRU}
    ${MAM_PB3}
    ${MAM_PRNG}
    ${MAM_PROTOTYPE}
    ${MAM_PSK}
    ${MAM_SPONGE}
    ${MAM_TRITS}
    ${MAM_TROIKA}
    ${MAM_WOTS}
)

#==============end of mam source=====================

add_library(mam ${MAM})
add_library(mam-api ${MAM_API})
add_library(mam-examples ${MAM_EXAMPLES})
add_library(trinary ${COMMON_TRINARY})
add_library(common-crypto ${COMMON_CRYPTO})

add_dependencies(mam
      	entangled::common
	common-crypto
)

target_link_libraries(mam PUBLIC
  entangled::common
  common-crypto
)

target_link_libraries(mam-api PUBLIC
  mam
  entangled::common
)

target_link_libraries(mam-examples PUBLIC
  entangled::cclient
  entangled::common
  mam-api
)

install(DIRECTORY "${PROJECT_SOURCE_DIR}/mam/" DESTINATION "${CMAKE_INSTALL_PREFIX}/include/entangled/mam" FILES_MATCHING PATTERN "*.h")
install(TARGETS mam mam-api mam-examples common-crypto DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
