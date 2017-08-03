#ifndef DABCOMMON_PARSE_STATUS
#define DABCOMMON_PARSE_STATUS

#include <cstdint>

namespace dab
  {

  /**
   * @author Tobias Stauber
   *
   * @brief Status values returned by parsers.
   *
   **/
  enum struct parse_status : std::uint8_t
    {
    invalid_crc, ///< The CRC16 checksum was invalid
    invalid_address, ///< The address did not match the expected one
    incomplete, ///< There is still data missing
    segment_lost, ///< At least one segment was missing
    ok ///< Everything went well
    };

  }

#endif
