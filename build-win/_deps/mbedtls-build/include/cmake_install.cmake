# Install script for directory: /home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/x86_64-w64-mingw32-objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mbedtls" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/aes.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/aria.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/asn1.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/asn1write.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/base64.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/bignum.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/block_cipher.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/build_info.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/camellia.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/ccm.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/chacha20.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/chachapoly.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/check_config.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/cipher.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/cmac.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/compat-2.x.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/config_adjust_legacy_crypto.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/config_adjust_legacy_from_psa.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/config_adjust_psa_from_legacy.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/config_adjust_psa_superset_legacy.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/config_adjust_ssl.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/config_adjust_x509.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/config_psa.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/constant_time.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/ctr_drbg.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/debug.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/des.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/dhm.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/ecdh.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/ecdsa.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/ecjpake.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/ecp.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/entropy.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/error.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/gcm.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/hkdf.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/hmac_drbg.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/lms.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/mbedtls_config.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/md.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/md5.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/memory_buffer_alloc.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/net_sockets.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/nist_kw.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/oid.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/pem.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/pk.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/pkcs12.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/pkcs5.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/pkcs7.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/platform.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/platform_time.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/platform_util.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/poly1305.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/private_access.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/psa_util.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/ripemd160.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/rsa.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/sha1.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/sha256.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/sha3.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/sha512.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/ssl.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/ssl_cache.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/ssl_ciphersuites.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/ssl_cookie.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/ssl_ticket.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/threading.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/threading_alt.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/timing.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/version.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/x509.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/x509_crl.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/x509_crt.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/mbedtls/x509_csr.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/psa" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/psa/build_info.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/psa/crypto.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/psa/crypto_adjust_auto_enabled.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/psa/crypto_adjust_config_dependencies.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/psa/crypto_adjust_config_key_pair_types.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/psa/crypto_adjust_config_synonyms.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/psa/crypto_builtin_composites.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/psa/crypto_builtin_key_derivation.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/psa/crypto_builtin_primitives.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/psa/crypto_compat.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/psa/crypto_config.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/psa/crypto_driver_common.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/psa/crypto_driver_contexts_composites.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/psa/crypto_driver_contexts_key_derivation.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/psa/crypto_driver_contexts_primitives.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/psa/crypto_extra.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/psa/crypto_legacy.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/psa/crypto_platform.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/psa/crypto_se_driver.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/psa/crypto_sizes.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/psa/crypto_struct.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/psa/crypto_types.h"
    "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src/include/psa/crypto_values.h"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-build/include/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
