#include "../preprocessor.h"

#define UTILS_FORMATPATH
#include "utils.h"

int main( int argc, char** argv )
{
    const char* file = "script/dir2/file2.as";

    Preprocessor::StringOutStream result, errors;

    int errors_count = Preprocessor::Preprocess( file, result, &errors );
    if( errors.String != "" )
    {
        while( errors.String[errors.String.length()-1] == '\n' )
            errors.String.pop_back();

        fprintf( stderr, "Preprocessor message <%s>\n", errors.String.c_str() );
    }

    if( errors_count )
    {
        fprintf( stderr, "Unable to preprocess file <%s>\n",  file );

        return( EXIT_FAILURE );
    }

    std::vector<std::string> file_dependencies  = Preprocessor::GetFileDependencies();
    std::vector<std::string> files_preprocessed = Preprocessor::GetFilesPreprocessed();

    fprintf( stdout, "GetFileDependencies()\n" );
    for( int d = 0, dLen = file_dependencies.size(); d<dLen; d++ )
    {
        fprintf( stdout, "\t%s\n", file_dependencies[d].c_str() );
    }

    fprintf( stdout, "GetFilesPreprocessed()\n" );
    for( int d = 0, dLen = files_preprocessed.size(); d<dLen; d++ )
    {
        char* dep = new char[files_preprocessed[d].length()+1];
        std::strcpy( dep, files_preprocessed[d].c_str() );

        fprintf( stdout, "\t%s => ", dep );
        FormatPath( dep );
        fprintf( stdout, "%s\n", dep );

        delete[] dep;
    }

    return( EXIT_SUCCESS );
}
