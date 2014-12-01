#ifndef __PIN_HPP__
#define __PIN_HPP__

// C
//#include <cstddef>

// STL
#include <string>
#include <vector>

// INTERNAL
#include "link.hpp"
#include "thread.hpp"
#include "objectblob.hpp"

namespace monadic
{
    class Pin
    {

        friend class Link;

    public:
        // Typedefs
        typedef enum
        {
            NODE_INPUT_PIN=0,
            NODE_OUTPUT_PIN
        } PinMode;

        Pin( monadic::Node* parentNode, const std::string& name, monadic::Pin::PinMode mode);
        virtual ~Pin();

        bool write( monadic::ObjectBlob* blob );
        std::vector< monadic::ObjectBlob* > read();
        std::string getLabel(){ return _name; }
        monadic::Node* getParent();

    private:
        std::string                     _name;
        PinMode                         _mode;
        monadic::Node*                  _parent;
        std::vector< monadic::Link* >   _links;

        void addLink( Link* l );

    protected:

    };
}
#endif // PIN_HPP
