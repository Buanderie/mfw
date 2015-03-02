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
#include "identifiable.hpp"

namespace monadic
{
    class Pin : public monadic::Identifiable
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
        virtual void OnLinkConnected( monadic::Link* link );
        virtual void OnLinkDisconnected( monadic::Link* link );

        bool write( monadic::ObjectBlob* blob );
        std::vector< monadic::ObjectBlob* > read();
        std::string getLabel(){ return _name; }
        monadic::Node* getParent();
        monadic::Pin::PinMode getMode();
        bool isConnected();
        void waitForConnection();

    private:
        std::string                     _name;
        PinMode                         _mode;
        monadic::Node*                  _parent;
        std::vector< monadic::Link* >   _links;
        monadic::Mutex                  _mtx;

        monadic::Mutex                  _linkMtx;
        monadic::CondVar                _linkCnd;

        void addLink( Link* l );
        void removeLink( monadic::Link* link );

    protected:

    };
}
#endif // PIN_HPP
