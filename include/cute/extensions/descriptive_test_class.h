#ifndef DABCOMMON_CUTE_EXTENSIONS__DESCRIPTIVE_TEST_CLASS
#define DABCOMMON_CUTE_EXTENSIONS__DESCRIPTIVE_TEST_CLASS

#include <cute/cute_suite.h>

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <cxxabi.h>
#include <memory>
#include <string>
#include <typeinfo>

namespace cute
  {

  namespace extensions
    {

    namespace impl
      {

      bool demangle(std::type_info const & type, std::string & name)
        {
        int status{};
        auto demangled = std::unique_ptr<char, void (*)(void *)>{
          abi::__cxa_demangle(type.name(), nullptr, nullptr, &status),
          std::free};

        if(status)
          {
          return false;
          }

        name = demangled.get();
        return true;
        }

      }

    /**
     * @brief A self-descriptive suite class for CUTE
     *
     * This class is designed to be the base class for 'self-descriptive' CUTE suite classes. A 'self-descriptive' suite class
     * provides the following two functions:
     *
     * - static cute::suite suite()
     * - static std::string description()
     *
     * #cute::extensions::self_descriptive_suite provides as default implementation of #description that will generate a
     * description based on the derived class' name. An implementation of #suite must be provided by the user. Failing to do
     * so will result in a compilation error when used via the #CUTE_DESCRIPTIVE_RUN macro or a similar technique.
     *
     * @since 1.0.1
     * @author Felix Morgner
     */
    template<typename TestClass>
    struct self_descriptive_suite
      {
      static std::string description()
        {
        auto name = std::string{};
        if(!impl::demangle(typeid(TestClass), name))
          {
          return typeid(TestClass).name();
          }

        auto lastColon = name.find_last_of(':') + 1;
        if(lastColon != name.npos)
          {
          name = name.substr(lastColon, name.npos);
          }

        if(!name.size())
          {
          return "#UNKNOWN_TEST_CLASS#";
          }

        replace(name.begin(), name.end(), '_', ' ');
        name.erase(name.begin(), find_if_not(name.begin(), name.end(), [](char const c){ return std::isspace(c); }));

        std::size_t pos{};
        while(pos != name.npos)
          {
          name[pos] = std::toupper(name[pos]);
          pos = name.find_first_of(' ', pos);
          pos = name.find_first_not_of(' ', pos);
          }

        return name;
        }

      static cute::suite suite()
        {
        static_assert(sizeof(TestClass) < 0, "Missing implementation of 'suite()' for your test class!");
        return {};
        }
      };

    }

  }

/**
 * @brief Run the given #cute::extensions::self_descriptive_suite using the provided runner
 *
 * @since 1.0.1
 * @author Felix Morgner
 */
#define CUTE_DESCRIPTIVE_RUN(DescriptiveSuite,Runner) Runner(DescriptiveSuite::suite(), DescriptiveSuite::description().c_str())

/**
 * @brief Create a new 'self-descriptive' suite as a C++ @p struct
 *
 * @since 1.0.1
 * @author Felix Morgner
 */
#define CUTE_DESCRIPTIVE_STRUCT(ClassName) struct ClassName : cute::extensions::self_descriptive_suite<ClassName>

/**
 * @brief Create a new 'self-descriptive' suite as a C++ @p class
 *
 * @since 1.0.1
 * @author Felix Morgner
 */
#define CUTE_DESCRIPTIVE_CLASS(ClassName) class ClassName : public cute::extensions::self_descriptive_suite<ClassName>

#endif
