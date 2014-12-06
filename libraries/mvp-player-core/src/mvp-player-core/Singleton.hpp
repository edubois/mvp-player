#ifndef _CORE_SINGLETON_HPP_
#define	_CORE_SINGLETON_HPP_

namespace mvpplayer
{

template<class T>
class Singleton
{
protected:
    Singleton() {}
    virtual ~Singleton() {}

public:
    inline static T & getInstance()
    {
        static T instance; // static should be threadsafe in C++11
        return instance;
    }
private:

};

}

#endif
