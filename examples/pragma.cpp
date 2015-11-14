#include <cstdlib>
#include <set>
#include <string>
#include <vector>


#include "../preprocessor.h"

// #pragma dummy "some text"
class DummyPragma
{
public:
    void Call( const std::string& text )
    {
        fprintf( stdout, "DummyPragma: text<%s>\n", text.c_str() );
    }
};

class MyPragmaCallback : public Preprocessor::PragmaCallback
{
private:
    std::set<std::string> alreadyProcessed;
    DummyPragma* dummy;

public:
    MyPragmaCallback()
    {
        dummy = new DummyPragma();
    }

    void CallPragma( const std::string& name, const Preprocessor::PragmaInstance& instance )
    {
        if( alreadyProcessed.count( name + instance.Text ))
            return;

        alreadyProcessed.insert( name + instance.Text );

        if( name == "dummy" )
            dummy->Call( instance.Text );
        else
            fprintf( stderr, "Warning: Unknown pragma name <%s> text <%s>\n", name.c_str(), instance.Text.c_str() );
    }
};

int main( int argc, char** argv )
{
    if( argc != 2 )
    {
        fprintf( stderr, "Usage: pragma [script_file]\n\n" );
        exit( EXIT_FAILURE );
    }

    Preprocessor::StringOutStream result, errors;
    Preprocessor::SetPragmaCallback( new MyPragmaCallback() );
    int errors_count = Preprocessor::Preprocess( argv[1], result, &errors );

    if( errors.String != "" )
    {
        while( errors.String[errors.String.length()-1] == '\n' )
            errors.String.pop_back();

        fprintf( stderr, "Preprocessor message <%s>\n", errors.String.c_str() );
    }

    if( errors_count )
    {
        fprintf( stderr, "Unable to preprocess file <%s>\n",  argv[1] );

        return( EXIT_FAILURE );
    }

    return( EXIT_SUCCESS );
}
