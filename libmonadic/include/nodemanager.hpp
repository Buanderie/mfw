#ifndef __NODEMANAGER_HPP__
#define __NODEMANAGER_HPP__

// STL
#include <string>
#include <map>

// INTERNAL
#include "singleton.hpp"
#include "nodeentry.hpp"
#include "node.hpp"

namespace monadic
{
    class NodeManager : public Singleton<NodeManager>
    {
        friend class Singleton<NodeManager>;

        private:
            NodeManager(){}
            ~NodeManager(){}

        public:
            monadic::Node* create( std::string nodeName );

        private:
            std::map< std::string, NodeEntry > _entries;
    };
}

#endif
