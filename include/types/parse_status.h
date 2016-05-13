#ifndef __DAB__PARSE_STATUS
#define __DAB__PARSE_STATUS

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
    invalid_crc,
    invalid_address,
    incomplete,
    segment_lost,
    ok
    };
  }
#endif //__DAB__PARSE_STATUS
