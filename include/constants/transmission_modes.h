#ifndef __DAB_CONSTANTS__TRANSMISSION_MODES
#define __DAB_CONSTANTS__TRANSMISSION_MODES

#include "types/transmission_mode.h"

namespace dab
  {

  /**
   * @brief This namespace contains the constants for the four standardized transmission modes
   */
  namespace transmission_modes
    {

    /**
     * @ingroup dab_modes
     * @brief DAB transport mode 1 descriptor
     *
     * This type alias generates the descriptor for DAB transport mode 1.
     */
    __internal_common::types::transmission_mode constexpr kTransmissionMode1{1, 1536,  76, 3, 12, 4, 96000, 246, 1000, 1297};

    /**
     * @ingroup dab_modes
     * @brief DAB transport mode 2 descriptor
     *
     * This type alias generates the descriptor for DAB transport mode 2.
     */
    __internal_common::types::transmission_mode constexpr kTransmissionMode2{2, 384,  76, 3,  3, 1, 24000,  62,  250, 324};

    /**
     * @ingroup dab_modes
     * @brief DAB transport mode 3 descriptor
     *
     * This type alias generates the descriptor for DAB transport mode 3.
     */
    __internal_common::types::transmission_mode constexpr kTransmissionMode3{3, 192, 153, 8,  4, 1, 24000, 31,  125, 168};

    /**
     * @ingroup dab_modes
     * @brief DAB transport mode 4 descriptor
     *
     * This type alias generates the descriptor for DAB transport mode 4.
     */
    __internal_common::types::transmission_mode constexpr kTransmissionMode4{4, 768,  76, 3,  6, 2, 48000, 123, 500, 648};

    }

  }

#endif

