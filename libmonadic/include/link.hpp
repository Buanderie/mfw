#ifndef __LINK_HPP__
#define __LINK_HPP__

// INTERNAL
#include "node.hpp"

namespace monadic
{
    class Link
    {
    public:
        Link( monadic::Node* n1, monadic::Node* n2 );
        virtual ~Link();

    private:
        monadic::Node* _n1;
        monadic::Node* _n2;

    protected:

    };
}

#endif // LINK_HPP
