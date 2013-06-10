
// C
#include <dlfcn.h>

// INTERNAL
#include "node.hpp"
#include "nodeentry.hpp"

monadic::NodeEntry::NodeEntry( const std::string& dlPath )
{
    
}

monadic::NodeEntry::~NodeEntry()
{
    // Close DL and clean shit
}

void monadic::NodeEntry::open( const std::string& dlPath )
{
    // Open Dynamic Library
    _dlref = dlopen( dlPath.c_str(), RTLD_LAZY );
    //if( !_dlref )
    //polbak
    
    _createFuncPtr = (monadic::createNode_t*) dlsym( _dlref, "createNode" );
    _destroyFuncPtr = (monadic::destroyNode_t*) dlsym( _dlref, "destroyNode" );
    //if (!_createFuncPtr || !_destroyFuncPtr )    
}

monadic::createNode_t* monadic::NodeEntry::getConstructorPtr()
{
    return _createFuncPtr;
}

monadic::destroyNode_t* monadic::NodeEntry::getDestructorPtr()
{
    return _destroyFuncPtr;
}

std::string monadic::NodeEntry::getNodeName()
{
    return _nodeName;
}

