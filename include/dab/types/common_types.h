#ifndef DABCOMMON_TYPES_COMMON_TYPES
#define DABCOMMON_TYPES_COMMON_TYPES

#include "dab/types/parse_status.h"
#include "dab/types/queue.h"

#include <complex>
#include <cstdint>
#include <utility>
#include <vector>

namespace dab
  {

  /**
   * @brief A convenience alias that represents a complex sample.
   *
   * It might be worth noting that std::complex was designed to be bit compatible
   * with the C99 complex type and can thus be used in conjunction with fftw.
   *
   * @author Felix Morgner
   * @since  1.0.1
   */
  using sample_t = std::complex<float>;

  /**
   * @brief A convenience alias that represents a vector of bytes
   *
   * @author Tobias Stauber
   * @since  1.0.0
   **/
  using byte_vector_t = std::vector<std::uint8_t>;

  /**
   * @brief A type used as return value by parsers.
   *
   * The first argument contains the return status of the parser.
   * The second argument contains the returned byte_vector_t.
   *
   * @author Tobias Stauber
   * @since  1.0.0
   **/
  using pair_status_vector_t = std::pair<dab::parse_status, byte_vector_t>;

  /**
   * @brief The type of a queue for transporting samples
   *
   * @author Felix Morgner
   * @since  1.0.0
   */
  using sample_queue_t = internal::queue<sample_t>;

  /**
   * @brief The type of a queue for transporting symbols
   *
   * @author Felix Morgner
   * @since  1.0.0
   */
  using symbol_queue_t = internal::queue<std::vector<float>>;

  namespace internal
    {

    /**
     * @brief A convenience alias that represents a complex sample
     *
     * @author Felix Morgner
     * @since  1.0.0
     *
     * @deprecated Deprecated since 1.0.1, see dab::sample_t
     */
    using sample_t = dab::sample_t;

    }

  }

#endif
