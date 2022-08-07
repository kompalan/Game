/**
 * @file Utils.h
 * @author Anurag Kompalli
 *
 *
 */

#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include <string>

namespace Engine {
    class Utils
    {
    public:
        static std::string ReadFile(const char* path)
        {
            FILE* file = fopen(path, "rt");
            fseek(file, 0, SEEK_END);
            unsigned long length = ftell(file);

            char* data = new char[length + 1];
            memset(data, 0, length+1);

            fseek(file, 0, SEEK_SET);
            fread(data, 1, length, file);
            fclose(file);

            std::string result(data);

            delete[] data;

            return result;
        }
    };
}

#endif //GAME_UTILS_H
