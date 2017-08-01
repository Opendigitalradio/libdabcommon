#ifndef DABCOMMON__LITERALS__BINARY_LITERAL
#define DABCOMMON__LITERALS__BINARY_LITERAL

#include <utility>

namespace dab
  {
  namespace literals
    {
    namespace impl
      {

      constexpr unsigned long long two_to(std::size_t power) {
        return power ? 2ull * two_to(power - 1) : 1ull;
      }

      template<char ...>
        struct parse_binary;

      template<char ...Digits> //Case for ‘0’
        struct parse_binary<'0', Digits...> {
          static unsigned long long const value { parse_binary<Digits...>::value };
        };

      template<char ...Digits> //Case for ‘1’
        struct parse_binary<'1', Digits...> {
          static unsigned long long const value {
            two_to(sizeof ...(Digits)) + parse_binary<Digits...>::value };
        };

      template<> //Base case
        struct parse_binary<> {
          static unsigned long long const value { 0 };
        };
      }

    /**
     * @author Tobias Stauber
     *
     * @brief An user defined literal for binary numbers
     *
     **/
    template<char ...Digits>
      constexpr unsigned long long operator"" _b() {
        return impl::parse_binary<Digits...>::value;
      }
    }
  }

#endif
