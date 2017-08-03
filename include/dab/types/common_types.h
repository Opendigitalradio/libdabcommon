#ifndef DABCOMMON__TYPES__COMMON_TYPES
#define DABCOMMON__TYPES__COMMON_TYPES

#include "dab/types/parse_status.h"
#include "dab/types/queue.h"

#include <complex>
#include <cstdint>
#include <utility>
#include <vector>

/**
 * @author Felix Morgner
 *
 * @brief This namespace captures anything DAB related
 */
namespace dab
  {

  /**
   * @author Felix Morgner
   *
   * @brief A convenience alias that represents a complex sample.
   *
   * It might be worth noting that std::complex was designed to be bit compatible
   * with the C99 complex type and can thus be used in conjunction with fftw.
   */
  using sample_t = std::complex<float>;

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
  using sample_queue_t = internal::queue<sample_t>;

  /**
   * @author Felix Morgner
   *
   * @brief The type of a queue for transporting symbols
   */
  using symbol_queue_t = internal::queue<std::vector<float>>;

  namespace internal
    {

    /**
     * @author Felix Morgner
     *
     * @brief A convenience alias that represents a complex sample
     *
     * @deprecated @see dab::sample_t
     */
    using sample_t = dab::sample_t;

    }

  }

#endif

