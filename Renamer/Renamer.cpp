#include "Renamer.hpp"

#include "../Common/Common.hpp"
#include "../Common/Exception.hpp"

// Constants.
const std::string Renamer::RENAME_COMMAND = "--rename";
const std::string Renamer::NUMBER_PREPEND_COMMAND = "--num-prepend";
const std::string Renamer::NUMBER_APPEND_COMMAND = "--num-append";
const std::string Renamer::DELETE_PRECEDING_NUM_PREPEND_COMMAND = "--del-prec-num-prep";
const std::string Renamer::DELETE_ENDING_NUM_APPEND_COMMAND = "--del-end-num-app";
const std::string Renamer::PREPEND_STRING_COMMAND = "--pre-str";
const std::string Renamer::APPEND_STRING_COMMAND = "--app-str";
const std::string Renamer::WIPE_RENAME_NUMBER_COMMAND = "--wipe-rename-number";

const std::string Renamer::DIGITS = "1234567890";

void Renamer::rename(
    const std::list<std::string> &currentFiles,
    const std::list<std::string> &renamedFiles
) {
    const std::list<std::string>::size_type currentFilesSize = currentFiles.size();
    const std::list<std::string>::size_type renamedFilesSize = renamedFiles.size();
    if (currentFilesSize != renamedFilesSize)
        throw Exception("Rename failed due to mismatched file sizes");

    std::list<std::string>::const_iterator renamedFile = renamedFiles.begin();
    for (const auto &file : currentFiles) {
        std::rename(file.c_str(), renamedFile->c_str());
        renamedFile++;
    }
}

std::list<std::string> Renamer::replace(
    const std::string &findName,
    const std::string &replaceName,
    const std::list<std::string> &files
) {
    std::list<std::string> renamedFiles;
    for (const auto &file : files) {
        const std::size_t pos = file.find(findName);    // Find the find string.
        if (pos != std::string::npos) {
            // New file is everything before the find string and the replacement
            // and everything after.
            // newFile = (before)(argv[REPLACE_NAME_POS] = replaceString)(after)
            const std::string newFile = file.substr(0, pos) + replaceName +
                file.substr(pos + findName.length());
            renamedFiles.push_back(newFile);
        }
    }
    return renamedFiles;
}

std::list<std::string> Renamer::wipeNameAndNumberFile(
    const std::string &inputString,
    const std::list<std::string> &files
) {
    std::list<std::string> renamedFiles;
    std::int32_t count = 1;
    for (const auto &file : files) {
        const std::size_t dotPos = file.find_last_of('.');
        std::string newFile;
        if (dotPos != std::string::npos)
            newFile = inputString + Common::toString(count) + file.substr(dotPos);
        else
            newFile = inputString + Common::toString(count);

        renamedFiles.push_back(newFile);
        count++;
    }
    return renamedFiles;
}

std::list<std::string> Renamer::numberPrepend(
    const std::string &inputString,
    const int32_t startNum,
    const std::list<std::string> &files
) {
    std::list<std::string> renamedFiles;
    std::int32_t count = startNum;
    // Prepend
    for (const auto &file : files) {
        std::string newFile = file;
        const std::string insertString = Common::toString(count) + inputString;
        newFile.insert(newFile.find_last_of('\\') + 1, insertString);
        count++;
        renamedFiles.push_back(newFile);
    }
    return renamedFiles;
}

std::list<std::string> Renamer::numberAppend(
    const std::string &inputString,
    const int32_t startNum,
    const std::list<std::string> &files
) {
    std::list<std::string> renamedFiles;
    std::int32_t count = startNum;
    // Append
    for (const auto &file : files) {
        // Result looks like (fileName)(inputName)(sum)(extension).
        // Converts the int count to a string sum.
        const std::size_t dotPos = file.find_last_of('.');
        std::string newFile;
        if (dotPos != std::string::npos) {
            // File has an extension.
            newFile = file.substr(0, dotPos) + inputString + Common::toString(count) +
                file.substr(dotPos);
        } else {
            // File has no extension.
            newFile = file + inputString + Common::toString(count);
        }

        renamedFiles.push_back(newFile);
        count++;
    }
    return renamedFiles;
}

std::list<std::string> Renamer::deletePrecedingAndNumberPrepend(
    const std::string &inputString,
    const int32_t startNum,
    const std::list<std::string> &files
) {
    std::list<std::string> renamedFiles;
    std::int32_t count = startNum;
    // Prepend.
    for (const auto &file : files) {
        // Result looks like (sum)(inputName)(currentFile)
        const std::string filePath = file.substr(0, file.find_last_of('\\') + 1);
        const std::string fileName = file.substr(file.find_last_of('\\') + 1);
        const std::string moddedName = Common::toString(count) + inputString +
            fileName.substr(fileName.find_first_not_of(DIGITS));
        const std::string newFile = filePath + moddedName;
        count++;
        renamedFiles.push_back(newFile);
    }
    return renamedFiles;
}

std::list<std::string> Renamer::deleteEndingAndNumberAppend(
    const std::string &inputString,
    const int32_t startNum,
    const std::list<std::string> &files
) {
    std::list<std::string> renamedFiles;
    std::int32_t count = startNum;
    // Append
    for (const auto &file : files) {
        // Result looks like (fileName)(inputName)(sum)(extension).
        const std::size_t dotPos = file.find_last_of('.');         // The pos of dot
        std::string fileName;
        std::string extension;
        if (dotPos != std::string::npos) {
            fileName = file.substr(0, dotPos);       // The file's name
            extension = file.substr(dotPos);
        } else {
            fileName = file;
        }

        // Pos of non-num
        const std::size_t numPos = fileName.find_last_not_of(DIGITS);
        const std::string newFile = fileName.substr(0, numPos + 1) + inputString +
            Common::toString(count) + extension;
        renamedFiles.push_back(newFile);
        // Inc count.
        count++;
    }
    return renamedFiles;
}

std::list<std::string> Renamer::prependString(
    const std::string &inputString,
    const std::list<std::string> &files
) {
    std::list<std::string> renamedFiles;
    for (const auto &file : files) {
        std::string newFile = file;
        newFile.insert(newFile.find_last_of('\\') + 1, inputString);
        renamedFiles.push_back(newFile);
    }
    return renamedFiles;
}

std::list<std::string> Renamer::appendString(
    const std::string &inputString,
    const std::list<std::string> &files
) {
    std::list<std::string> renamedFiles;
    for (const auto &file : files) {
        const std::size_t dotPos = file.find_last_of('.');
        std::string newFile;
        if (dotPos != std::string::npos)
            newFile = file.substr(0, dotPos) + inputString + file.substr(dotPos);
        else
            newFile = file + inputString;

        renamedFiles.push_back(newFile);
    }
    return renamedFiles;
}
