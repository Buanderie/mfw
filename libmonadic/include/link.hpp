#ifndef __LINK_HPP__
#define __LINK_HPP__

// C
#include <cstddef>

// INTERNAL
#include "node.hpp"
#include "thread.hpp"
#include "objectblob.hpp"
#include "bipbuffer.hpp"

namespace monadic
{
    class Link
    {
    public:
        // Typedefs
        typedef enum
        {
            NODE_LINK_BLOCKING=0,
            NODE_LINK_NONBLOCKING
        } LinkMode;

        Link( monadic::Node* n1, monadic::Node* n2, std::size_t bandwidth, monadic::Link::LinkMode mode );
        virtual ~Link();

        void write( monadic::ObjectBlob* blob );
        monadic::ObjectBlob* read();
        std::size_t occupation();


    private:
        monadic::Node*      _n1;
        monadic::Node*      _n2;
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
