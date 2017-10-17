#include <QString>

#include "Random.h"

namespace Util
{
    namespace Random
    {
        std::string GenerateRandomString(unsigned int randomStringLength)
        {
            const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");

            QString randomString;
            for (unsigned int i = 0; i < randomStringLength; i++)
            {
                int index = qrand() % possibleCharacters.length();
                QChar nextChar = possibleCharacters.at(index);
                randomString.append(nextChar);
            }

            return randomString.toStdString();
        }
    }
}
