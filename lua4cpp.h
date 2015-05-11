
extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
    #include "tolua++.h"
};

class CLuaFn
{
public:
    CLuaFn( void )
        : m_pState(NULL)
    {}
    ~CLuaFn( void ){}

public:
    void Init();        // 初始lua对象指针
    void Close();       // 关闭lua对象指针

    bool LoadLuaFile( const char * filename_ );
    int CallLuaFn( const char * funname_, int param1_, int param2_ );

public:
    lua_State * m_pState;

};
