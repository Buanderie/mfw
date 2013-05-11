#ifndef __NODEMANAGER_HPP__
#define __NODEMANAGER_HPP__

// INTERNAL
#include "singleton.hpp"

namespace monadic
{
    class NodeManager : public Singleton<NodeManager>
    {
        friend class Singleton<NodeManager>;

        private:
            NodeManager(){}
            ~NodeManager(){}

        public:

        private:
    };
}

#endif
