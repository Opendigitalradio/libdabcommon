#ifndef __DAB__TYPES__COMMON_TYPES
#define __DAB__TYPES__COMMON_TYPES

#include "types/parse_status.h"

#include <readerwriterqueue.h>

#include <complex>
#include <cstdint>
#include <utility>
#include <vector>

namespace dab
  {

  namespace __internal_common
    {

      /**
       * @author Felix Morgner
       *
       * @internal
       *
       * @brief A convenience alias that represents a complex sample.
       *
       * It might be worth noting that std::complex was designed to be bit compatible
       * with the C99 complex type and can thus be used in conjunction with fftw.
       */
      using sample_t = std::complex<float>;

    }

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

  /**
   * @author Felix Morgner
   *
   * @brief The type of a queue for transporting samples
   */
  using sample_queue_t = moodycamel::ReaderWriterQueue<__internal_common::sample_t>;

  }

#endif

