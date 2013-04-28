#ifndef __NODEFACTORY_HPP__
#define __NODEFACTORY_HPP__

#include "singleton.hpp"

namespace monadic
{
    class NodeFactory : public Singleton<NodeFactory>
    {
        friend class Singleton<NodeFactory>;

        public:

        protected:

        private:
            NodeFactory(){}
            ~NodeFactory(){}
    };
}

#endif
