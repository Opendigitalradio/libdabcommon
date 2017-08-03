#ifndef DABCOMMON_CONSTANTS_TRANSMISSION_MODES
#define DABCOMMON_CONSTANTS_TRANSMISSION_MODES

#include "dab/types/transmission_mode.h"

namespace dab
  {

  /**
   * @brief DAB transport mode 1 descriptor
   *
   * @author Felix Morgner
   * @since  1.0.0
   */
  internal::types::transmission_mode constexpr kTransmissionMode1{1, 1536,  76, 3, 12, 4, 196608, 504, 2048, 2656};

  /**
   * @brief DAB transport mode 2 descriptor
   *
   * @author Felix Morgner
   * @since  1.0.0
   */
  internal::types::transmission_mode constexpr kTransmissionMode2{2, 384,  76, 3,  3, 1, 49152,  126,  512, 664};

  /**
   * @brief DAB transport mode 3 descriptor
   *
   * @author Felix Morgner
   * @since  1.0.0
   */
  internal::types::transmission_mode constexpr kTransmissionMode3{3, 192, 153, 8,  4, 1, 49152, 63,  256, 345};

  /**
   * @brief DAB transport mode 4 descriptor
   *
   * @author Felix Morgner
   * @since  1.0.0
   */
  internal::types::transmission_mode constexpr kTransmissionMode4{4, 768,  76, 3,  6, 2, 98304, 252, 1024, 1328};

  }

#endif
