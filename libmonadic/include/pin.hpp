#ifndef __PIN_HPP__
#define __PIN_HPP__

// C
//#include <cstddef>

// STL
#include <string>
#include <vector>

// INTERNAL
#include "identifiable.hpp"
#include "link.hpp"
#include "thread.hpp"
#include "objectblob.hpp"

namespace monadic
{
    class Pin : public Identifiable
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

        bool write( monadic::ObjectBlob* blob );
        std::vector< monadic::ObjectBlob* > read();

    private:
        std::string                     _name;
        PinMode                         _mode;
        std::vector< monadic::Link* >   _links;

    protected:

    };
}
#endif // PIN_HPP
