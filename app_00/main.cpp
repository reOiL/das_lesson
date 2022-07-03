#include "daScript/daScript.h"

using namespace das;

int main()
{
    NEED_MODULE(Module_BuiltIn)
    Module::Initialize();
    TextPrinter tout;
    ModuleGroup dummyLibGroup;
    auto fAccess = make_smart<FsFileAccess>();
    auto program = compileDaScript("script/main.das", fAccess, tout, dummyLibGroup);
    if ( program->failed() )
    {
        tout << "failed to compile\n";
        for ( auto & err : program->errors )
            tout << reportError(err.at, err.what, err.extra, err.fixme, err.cerr );
        return -1;
    }
    Context ctx(program->getContextStackSize());
    if ( !program->simulate(ctx, tout) ) {
        tout << "failed to simulate\n";
        for ( auto & err : program->errors )
            tout << reportError(err.at, err.what, err.extra, err.fixme, err.cerr );
        return -1;
    }
    Module::Shutdown();
    return 0;
}
