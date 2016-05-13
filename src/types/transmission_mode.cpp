#include "types/transmission_mode.h"
#include "types/mode_descriptor.h"

#include <stdexcept>

namespace dab
  {

  namespace __internal_common
    {

    namespace types
      {

      std::size_t frame_size(transmission_mode const mode) noexcept
        {
        switch(mode)
          {
          case transmission_mode::mode_1:
            return mode_1::symbol_bits::value * mode_1::frame_symbols::value;
            break;
          case transmission_mode::mode_2:
            return mode_2::symbol_bits::value * mode_2::frame_symbols::value;
            break;
          case transmission_mode::mode_3:
            return mode_3::symbol_bits::value * mode_3::frame_symbols::value;
            break;
          case transmission_mode::mode_4:
            return mode_4::symbol_bits::value * mode_4::frame_symbols::value;
            break;
          }
        }

      std::size_t fic_size(transmission_mode const mode) noexcept
        {
        switch(mode)
          {
          case transmission_mode::mode_1:
            return mode_1::symbol_bits::value * mode_1::fic_symbols::value;
            break;
          case transmission_mode::mode_2:
            return mode_2::symbol_bits::value * mode_2::fic_symbols::value;
            break;
          case transmission_mode::mode_3:
            return mode_3::symbol_bits::value * mode_3::fic_symbols::value;
            break;
          case transmission_mode::mode_4:
            return mode_4::symbol_bits::value * mode_4::fic_symbols::value;
            break;
          }
        }

      std::size_t punctured_codeword_size(transmission_mode const mode) noexcept
        {
        switch(mode)
          {
          case transmission_mode::mode_1:
            return mode_1::fib_codeword_bits::value * 3;
            break;
          case transmission_mode::mode_2:
            return mode_2::fib_codeword_bits::value * 3;
            break;
          case transmission_mode::mode_3:
            return mode_3::fib_codeword_bits::value * 3;
            break;
          case transmission_mode::mode_4:
            return mode_4::fib_codeword_bits::value * 3;
            break;
          }
        }

      std::size_t fic_codeword_size(transmission_mode const mode) noexcept
        {
        switch(mode)
          {
          case transmission_mode::mode_1:
            return mode_1::fib_codeword_bits::value;
            break;
          case transmission_mode::mode_2:
            return mode_2::fib_codeword_bits::value;
            break;
          case transmission_mode::mode_3:
            return mode_3::fib_codeword_bits::value;
            break;
          case transmission_mode::mode_4:
            return mode_4::fib_codeword_bits::value;
            break;
          }
        }

      std::size_t fibs_in_codeword(transmission_mode const mode) noexcept
        {
        switch(mode)
          {
          case transmission_mode::mode_1:
            return mode_1::fib_codeword_bits::value / 256;
            break;
          case transmission_mode::mode_2:
            return mode_2::fib_codeword_bits::value / 256;
            break;
          case transmission_mode::mode_3:
            return mode_3::fib_codeword_bits::value / 256;
            break;
          case transmission_mode::mode_4:
            return mode_4::fib_codeword_bits::value / 256;
            break;
          }
        }

      std::size_t frame_symbols(transmission_mode const mode) noexcept
        {
        switch(mode)
          {
          case transmission_mode::mode_1:
            return mode_1::frame_symbols::value;
            break;
          case transmission_mode::mode_2:
            return mode_2::frame_symbols::value;
            break;
          case transmission_mode::mode_3:
            return mode_3::frame_symbols::value;
            break;
          case transmission_mode::mode_4:
            return mode_4::frame_symbols::value;
            break;
          }
        }

      std::size_t symbol_size(transmission_mode const mode) noexcept
        {
        switch(mode)
          {
          case transmission_mode::mode_1:
            return mode_1::carriers::value * 2;
            break;
          case transmission_mode::mode_2:
            return mode_2::carriers::value * 2;
            break;
          case transmission_mode::mode_3:
            return mode_3::carriers::value * 2;
            break;
          case transmission_mode::mode_4:
            return mode_4::carriers::value * 2;
            break;
          }
        }

      std::size_t msc_cifs(transmission_mode const mode) noexcept
        {
        switch(mode)
          {
          case transmission_mode::mode_1:
            return mode_1::frame_cifs::value;
            break;
          case transmission_mode::mode_2:
            return mode_2::frame_cifs::value;
            break;
          case transmission_mode::mode_3:
            return mode_3::frame_cifs::value;
            break;
          case transmission_mode::mode_4:
            return mode_4::frame_cifs::value;
            break;
          }
        }

      }

    }

  }

