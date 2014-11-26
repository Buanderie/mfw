#ifndef __FILESYSTEM_HPP__
#define __FILESYSTEM_HPP__

// STL
#include <string>
#include <iterator>
#include <vector>

#if defined(__LINUX__)
// LINUX
#include <dirent.h>
#include <sys/stat.h>
#elif defined(__WINDOWS__)
#include <windows.h>
#endif

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
				#if defined(__LINUX__)
                struct stat st;
                if (stat(_pathStr.c_str(), &st) == -1)
                    return false;
                return !((st.st_mode & S_IFDIR) == 0);
				#elif defined(__WINDOWS__)
				HANDLE dir;
				WIN32_FIND_DATA file_data;
				dir = FindFirstFile((_pathStr + "/*").c_str(), &file_data);
				return (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
				#endif
            }

            bool    exists()
            {
#if defined(__LINUX__)
                struct stat buffer;
                return (stat (_pathStr.c_str(), &buffer) == 0);
#elif defined(__WINDOWS__)
				return true;
#endif
            }

            size_t  size()
            {
                if( exists() && isRegularFile() )
                {
					#if defined(__LINUX__)
                    struct stat st;
                    stat(_pathStr.c_str(), &st);
                    return st.st_size;
					#elif defined(__WINDOWS__)
					return 0;
					#endif
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

                #if defined(__WINDOWS__)
                HANDLE dir;
                WIN32_FIND_DATA file_data;

                if ((dir = FindFirstFile((_pathStr + "/*").c_str(), &file_data)) == INVALID_HANDLE_VALUE)
                    return res; // No files found

                do {
                    const std::string file_name = file_data.cFileName;
                    const std::string full_file_name = _pathStr + "/" + file_name;
                    const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

                    if (file_name[0] == '.')
                        continue;

					Path p(full_file_name);
					res.push_back(p);
					if (recursiveSearch)
					{
						if (p.isDirectory())
						{
							// Append to res, children of p
							std::vector< monadic::filesystem::Path > subres = p.getChildren(recursiveSearch);
							res.insert(res.end(), subres.begin(), subres.end());
						}
					}
                    
                } while (FindNextFile(dir, &file_data));

                FindClose(dir);
                #elif defined(__LINUX__)
                DIR *dir;
                struct dirent *ent;
                struct stat st;
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
                #endif
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
