#ifndef __DAB__TYPES__COMMON_TYPES
#define __DAB__TYPES__COMMON_TYPES

#include <cstdint>
#include <vector>
#include <utility>

#include "types/parse_status.h"

namespace dab
  {
  namespace types
    {
    /**
     * @author Tobias Stauber
     *
     * @brief A type that resembles a vector of bytes.
     *
     **/
    using byte_vector_t = std::vector<std::uint8_t>;

    /**
     * @author Tobias Stauber
     *
     * @brief A type used as return value by parsers.
     *
     * The first argument resembles the return status of the parser.
     * The second argument resembles the returned byte_vector_t.
     **/
    using pair_status_vector_t = std::pair<dab::parse_status, byte_vector_t>;
    }

  }
#endif //__DAB__TYPES__COMMON_TYPES
