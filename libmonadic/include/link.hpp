#ifndef __LINK_HPP__
#define __LINK_HPP__

// C
#include <cstddef>

// INTERNAL
#include "thread.hpp"
#include "objectblob.hpp"
#include "bipbuffer.hpp"
#include "identifiable.hpp"
#include "jsonable.hpp"

namespace monadic
{
    class Pin;
    class Node;
    class Link : public monadic::Identifiable, monadic::JSONable
    {
    public:
        // Typedefs
        typedef enum
        {
            NODE_LINK_BLOCKING=0,
            NODE_LINK_NONBLOCKING
        } LinkMode;

        Link( monadic::Pin* pin1, monadic::Pin* pin2, std::size_t bandwidth, monadic::Link::LinkMode mode );
        virtual ~Link();

        void write( monadic::ObjectBlob* blob );
        monadic::ObjectBlob* read();
        std::size_t occupation();

        virtual picojson::object toJSON();

    private:
        monadic::Pin*       _p1;
        monadic::Pin*       _p2;
        std::size_t         _bandwidth;
        LinkMode            _mode;
        monadic::Mutex      _linkMtx;
        monadic::CondVar    _linkReadCnd;
        monadic::CondVar    _linkWriteCnd;

        // Internal Buffer
        monadic::BipBuffer* _buffer;

    protected:

    };
}

#endif // LINK_HPP
