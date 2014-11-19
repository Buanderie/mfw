#ifndef __PIN_HPP__
#define __PIN_HPP__

// C
//#include <cstddef>

// STL
#include <string>

namespace monadic
{
    class Pin
    {
    public:
        // Typedefs
        typedef enum
        {
            NODE_INPUT_PIN=0,
            NODE_OUTPUT_PIN
        } PinMode;

        Pin(const std::string& name, monadic::Pin::PinMode mode);
        virtual ~Pin();

    private:
        std::string _name;
        PinMode     _mode;

    protected:

    };
}
#endif // PIN_HPP
