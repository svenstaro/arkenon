#include "check.hpp"

#include <GL/glew.h>
#include <AL/alure.h>
#include <iostream>

bool _alCheck(const char* file, int line) {
    ALenum error = alGetError();
    if(error == AL_NO_ERROR) return true;

    std::cerr << "[[ " << file << ":" << line << " ]] " << std::endl;

    switch (error) {
        case AL_INVALID_ENUM:
            std::cerr << "AL_INVALID_ENUM: an unacceptable value has been specified for an enumerated argument" << std::endl;
            break;
        case AL_INVALID_VALUE:
            std::cerr << "AL_INVALID_VALUE: a numeric argument is out of range" << std::endl;
            break;
        case AL_INVALID_OPERATION:
            std::cerr << "AL_INVALID_OPERATION: the specified operation is not allowed in the current state" << std::endl;
            break;
        case AL_OUT_OF_MEMORY:
            std::cerr << "AL_OUT_OF_MEMORY: there is not enough memory left to execute the command" << std::endl;
            break;
        case AL_INVALID_NAME:
            std::cerr << "AL_INVALID_NAME: invalid name argument" << std::endl;
            break;
        default:
            std::cerr << "Error not listed. Value: " << error << std::endl;
            break;
    }

    int* a = nullptr;
    *a = 1;
    return false;
}

bool _glCheck(const char* file, int line) {
    int error = glGetError();
    if(error == GL_NO_ERROR) return true;

    std::cerr << "[[ " << file << ":" << line << " ]] " << std::endl;

    while(error != GL_NO_ERROR) {
        switch (error) {
            case GL_INVALID_ENUM:
                std::cerr << "GL_INVALID_ENUM: an unacceptable value has been specified for an enumerated argument" << std::endl;
                break;
            case GL_INVALID_VALUE:
                std::cerr << "GL_INVALID_VALUE: a numeric argument is out of range" << std::endl;
                break;
            case GL_INVALID_OPERATION:
                std::cerr << "GL_INVALID_OPERATION: the specified operation is not allowed in the current state" << std::endl;
                break;
            case GL_OUT_OF_MEMORY:
                std::cerr << "GL_OUT_OF_MEMORY: there is not enough memory left to execute the command" << std::endl;
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION_EXT: the object bound to FRAMEBUFFER_BINDING_EXT is not \"framebuffer complete\"" << std::endl;
                break;
            default:
                std::cerr << "Error not listed. Value: " << error << std::endl;
                break;
        }
        error = glGetError();
    }
    int* a = nullptr;
    *a = 1;
    return false;
}

bool _ftCheck(int error, const char* file, int line) {
    if(error) {
        std::string msg;

        if(error == FT_Err_Cannot_Open_Resource) msg = "Cannot Open Resource";
        else if(error == FT_Err_Unknown_File_Format) msg = "Unknown File Format";
        else if(error == FT_Err_Invalid_File_Format) msg = "Invalid File Format";
        else if(error == FT_Err_Invalid_Version) msg = "Invalid Version";
        else if(error == FT_Err_Lower_Module_Version) msg = "Lower Module Version";
        else if(error == FT_Err_Invalid_Argument) msg = "Invalid Argument";
        else if(error == FT_Err_Unimplemented_Feature) msg = "Unimplemented Feature";
        else if(error == FT_Err_Invalid_Table) msg = "Invalid Table";
        else if(error == FT_Err_Invalid_Offset) msg = "Invalid Offset";
        else if(error == FT_Err_Invalid_Glyph_Index) msg = "Invalid Glyph Index";
        else if(error == FT_Err_Invalid_Character_Code) msg = "Invalid Character Code";
        else if(error == FT_Err_Invalid_Glyph_Format) msg = "Invalid Glyph Format";
        else if(error == FT_Err_Cannot_Render_Glyph) msg = "Cannot Render Glyph";
        else if(error == FT_Err_Invalid_Outline) msg = "Invalid Outline";
        else if(error == FT_Err_Invalid_Composite) msg = "Invalid Composite";
        else if(error == FT_Err_Too_Many_Hints) msg = "Too Many Hints";
        else if(error == FT_Err_Invalid_Pixel_Size) msg = "Invalid Pixel Size";
        else if(error == FT_Err_Invalid_Handle) msg = "Invalid Handle";
        else if(error == FT_Err_Invalid_Library_Handle) msg = "Invalid Library Handle";
        else if(error == FT_Err_Invalid_Driver_Handle) msg = "Invalid Driver Handle";
        else if(error == FT_Err_Invalid_Face_Handle) msg = "Invalid Face Handle";
        else if(error == FT_Err_Invalid_Size_Handle) msg = "Invalid Size Handle";
        else if(error == FT_Err_Invalid_Slot_Handle) msg = "Invalid Slot Handle";
        else if(error == FT_Err_Invalid_CharMap_Handle) msg = "Invalid CharMap Handle";
        else if(error == FT_Err_Invalid_Cache_Handle) msg = "Invalid Cache Handle";
        else if(error == FT_Err_Invalid_Stream_Handle) msg = "Invalid Stream Handle";
        else if(error == FT_Err_Too_Many_Drivers) msg = "Too Many Drivers";
        else if(error == FT_Err_Too_Many_Extensions) msg = "Too Many Extensions";
        else if(error == FT_Err_Out_Of_Memory) msg = "Out of Memory";
        else if(error == FT_Err_Unlisted_Object) msg = "Unlisted Object";
        else if(error == FT_Err_Cannot_Open_Stream) msg = "Cannot Open Stream";
        else if(error == FT_Err_Invalid_Stream_Seek) msg = "Invalid Stream Seek";
        else if(error == FT_Err_Invalid_Stream_Skip) msg = "Invalid Stream Skip";
        else if(error == FT_Err_Invalid_Stream_Read) msg = "Invalid Stream Read";
        else if(error == FT_Err_Invalid_Stream_Operation) msg = "Invalid Stream Operation";
        else if(error == FT_Err_Invalid_Frame_Operation) msg = "Invalid Frame Operation";
        else if(error == FT_Err_Nested_Frame_Access) msg = "Nested Frame Access";
        else if(error == FT_Err_Invalid_Frame_Read) msg = "Invalid Frame Read";
        else if(error == FT_Err_Raster_Uninitialized) msg = "Raster Uninitialized";
        else if(error == FT_Err_Raster_Corrupted) msg = "Raster Corrupted";
        else if(error == FT_Err_Raster_Overflow) msg = "Raster Overflow";
        else if(error == FT_Err_Raster_Negative_Height) msg = "Raster Negative Height";
        else if(error == FT_Err_Too_Many_Caches) msg = "Too Many Caches";
        else if(error == FT_Err_Invalid_Opcode) msg = "Invalid Opcode";
        else if(error == FT_Err_Too_Few_Arguments) msg = "Too Few Arguments";
        else if(error == FT_Err_Stack_Overflow) msg = "Stack Overflow";
        else if(error == FT_Err_Code_Overflow) msg = "Code Overflow";
        else if(error == FT_Err_Bad_Argument) msg = "Bad Argument";
        else if(error == FT_Err_Divide_By_Zero) msg = "Divide By Zero";
        else if(error == FT_Err_Invalid_Reference) msg = "Invalid Reference";
        else if(error == FT_Err_Debug_OpCode) msg = "Debug OpCode";
        else if(error == FT_Err_ENDF_In_Exec_Stream) msg = "ENDF In Exec Stream";
        else if(error == FT_Err_Nested_DEFS) msg = "Nested DEFS";
        else if(error == FT_Err_Invalid_CodeRange) msg = "Invalid CodeRange";
        else if(error == FT_Err_Execution_Too_Long) msg = "Execution Too Long";
        else if(error == FT_Err_Too_Many_Function_Defs) msg = "Too Many Function Defs";
        else if(error == FT_Err_Too_Many_Instruction_Defs) msg = "Too Many Instruction Defs";
        else if(error == FT_Err_Table_Missing) msg = "Table Missing";
        else if(error == FT_Err_Horiz_Header_Missing) msg = "Horiz Header Missing";
        else if(error == FT_Err_Locations_Missing) msg = "Locations Missing";
        else if(error == FT_Err_Name_Table_Missing) msg = "Name Table Missing";
        else if(error == FT_Err_CMap_Table_Missing) msg = "CMap Table Missing";
        else if(error == FT_Err_Hmtx_Table_Missing) msg = "Hmtx Table Missing";
        else if(error == FT_Err_Post_Table_Missing) msg = "Post Table Missing";
        else if(error == FT_Err_Invalid_Horiz_Metrics) msg = "Invalid Horiz Metrics";
        else if(error == FT_Err_Invalid_CharMap_Format) msg = "Invalid CharMap Format";
        else if(error == FT_Err_Invalid_PPem) msg = "Invalid PPem";
        else if(error == FT_Err_Invalid_Vert_Metrics) msg = "Invalid Vert Metrics";
        else if(error == FT_Err_Could_Not_Find_Context) msg = "Could Not Find Context";
        else if(error == FT_Err_Invalid_Post_Table_Format) msg = "Invalid Post Table Format";
        else if(error == FT_Err_Invalid_Post_Table) msg = "Invalid Post Table";
        else if(error == FT_Err_Syntax_Error) msg = "Syntax Error";
        else if(error == FT_Err_Stack_Underflow) msg = "Stack Underflow";
        else if(error == FT_Err_Ignore) msg = "Ignore";
        else if(error == FT_Err_Missing_Startfont_Field) msg = "Missing Startfont Field";
        else if(error == FT_Err_Missing_Font_Field) msg = "Missing Font Field";
        else if(error == FT_Err_Missing_Size_Field) msg = "Missing Size Field";
        else if(error == FT_Err_Missing_Chars_Field) msg = "Missing Chars Field";
        else if(error == FT_Err_Missing_Startchar_Field) msg = "Missing Startchar Field";
        else if(error == FT_Err_Missing_Encoding_Field) msg = "Missing Encoding Field";
        else if(error == FT_Err_Missing_Bbx_Field) msg = "Missing Bbx Field";
        else msg = "Unknown Error";

        std::cerr << "[[ " << file << ":" << line << " ]] " << std::endl;
        std::cerr << "FreeType2 Error: " << msg << std::endl;
        return false;
    }
    return true;
}
