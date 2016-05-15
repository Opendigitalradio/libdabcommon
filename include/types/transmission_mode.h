#ifndef __DAB__TRANSMISSION_MODE
#define __DAB__TRANSMISSION_MODE

#include <cstdint>

namespace dab
  {

  /**
   * @brief DAB transmission mode enumeration
   *
   * This enum declares the currently standardized transmission modes.
   * The dabdecode::ensemble class uses these modes to determine how to decode
   * the received frames. You can speficy the mode of a ensemble in
   * its constructor. You will need to know what transmission mode is used in
   * the DAB ensemble you are trying to receive.
   *
   * @internal
   * The modes that are declared here are specified in ETSI EN 300 401
   * @endinternal
   *
   * @see dabdecode::ensemble
   */
  enum struct transmission_mode : std::uint8_t
    {
    mode_1,
    mode_2,
    mode_3,
    mode_4
    };

  namespace __internal_common
    {

    namespace types
      {
      std::size_t frame_size(transmission_mode const mode) noexcept;

      std::size_t fic_size(transmission_mode const mode) noexcept;

      std::size_t punctured_codeword_size(transmission_mode const mode) noexcept;

      std::size_t fic_codeword_size(transmission_mode const mode) noexcept;

      std::size_t fibs_in_codeword(transmission_mode const mode) noexcept;

      std::size_t frame_symbols(transmission_mode const mode) noexcept;

      std::size_t symbol_size(transmission_mode const mode) noexcept;

      std::size_t msc_cifs(transmission_mode const mode) noexcept;

      std::size_t carriers(transmission_mode const mode) noexcept;

      std::size_t fft_length(transmission_mode const mode) noexcept;
      }
    }


  }

#endif

