#ifndef __FILESYSTEMLINUX_HPP__
#define __FILESYSTEMLINUX_HPP__

// STL
#include <string>
#include <iterator>
#include <vector>

// LINUX
#include <dirent.h>
#include <sys/stat.h>

namespace monadic
{
    namespace filesystem
    {
        class Path
        {
        public:
            Path( const std::string& pathStr = "" )
                :_pathStr(pathStr)
            {

            }

            Path( const monadic::filesystem::Path& other )
            {
                _pathStr = other._pathStr;
            }

            virtual ~Path()
            {

            }

            bool    isRegularFile(){ return !isDirectory(); }
            bool    isDirectory()
            {
                class stat st;
                if (stat(_pathStr.c_str(), &st) == -1)
                    return false;
                return !((st.st_mode & S_IFDIR) == 0);
            }

            bool    exists()
            {
                class stat buffer;
                return (stat (_pathStr.c_str(), &buffer) == 0);
            }

            size_t  size()
            {
                if( exists() && isRegularFile() )
                {
                    struct stat st;
                    stat(_pathStr.c_str(), &st);
                    return st.st_size;
                }
                else
                    return 0;
            }

            std::string str()
            {
                return _pathStr;
            }

            std::string extension()
            {
                std::string res;
                if( !isRegularFile() )
                    return std::string("");

                size_t pointPos = _pathStr.find_last_of( '.' );
                if( pointPos == std::string::npos )
                    return std::string("");

                size_t extSize = _pathStr.size() - pointPos;
                res = _pathStr.substr( pointPos, extSize );

                return res;
            }

            std::vector< monadic::filesystem::Path > getChildren(bool recursiveSearch=false )
            {
                std::vector< monadic::filesystem::Path > res;

                DIR *dir;
                class dirent *ent;
                class stat st;
                dir = opendir(_pathStr.c_str());
                while ((ent = readdir(dir)) != NULL)
                {
                    const std::string file_name = ent->d_name;
                    const std::string full_file_name = _pathStr + "/" + file_name;
                    if (file_name[0] == '.')
                        continue;
                    if (stat(full_file_name.c_str(), &st) == -1)
                        continue;

                    //res.push_back(Path(full_file_name));
                    Path p( full_file_name );
                    res.push_back(p);
                    if( recursiveSearch )
                    {
                        if( p.isDirectory() )
                        {
                            // Append to res, children of p
                            std::vector< monadic::filesystem::Path > subres = p.getChildren(recursiveSearch);
                            res.insert(res.end(), subres.begin(), subres.end());
                        }
                    }
                }
                return res;
            }

        private:
            std::string _pathStr;

        protected:

        };

        // TODO
        /*
        class PathIterator : public std::iterator< std::input_iterator_tag, monadic::filesystem::Path >
        {
        public:
            PathIterator(monadic::filesystem::Path* x) :p(x) {}
            PathIterator(const PathIterator& mit) : p(mit.p) {}
            PathIterator& operator++() {++p;return *this;}
            PathIterator operator++(int) {PathIterator tmp(*this); operator++(); return tmp;}
            bool operator==(const PathIterator& rhs) {return p==rhs.p;}
            bool operator!=(const PathIterator& rhs) {return p!=rhs.p;}
            int& operator*() {return *p;}

        private:
            monadic::filesystem::Path* _path;

        protected:

        };
        */
    }
}

#endif
