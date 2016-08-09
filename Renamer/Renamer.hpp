#ifndef RENAMER_HPP
#define RENAMER_HPP

#include <cstdio>
#include <iostream>
#include <list>
#include <string>

class Renamer {
public:
    /**
     * The console command to trigger the rename function.
     */
    static const std::string RENAME_COMMAND;

    /**
     * The console command to trigger the number prepend function.
     */
    static const std::string NUMBER_PREPEND_COMMAND;

    /**
     * The console command to trigger the number append function.
     */
    static const std::string NUMBER_APPEND_COMMAND;

    /**
     * The console command to trigger the delete preceding and number prepend function.
     */
    static const std::string DELETE_PRECEDING_NUM_PREPEND_COMMAND;

    /**
     * The console command to trigger the delete ending and number append function.
     */
    static const std::string DELETE_ENDING_NUM_APPEND_COMMAND;

    /**
     * The console command to trigger the prepend string function.
     */
    static const std::string PREPEND_STRING_COMMAND;

    /**
     * The console command to trigger the append string function.
     */
    static const std::string APPEND_STRING_COMMAND;

    /**
     * The console command to trigger the wipe rename and number function.
     */
    static const std::string WIPE_RENAME_NUMBER_COMMAND;

    static void rename(
        const std::list<std::string> &currentFiles,
        const std::list<std::string> &renamedFiles
    );

    /**
     * Renames a file. Uses a find name, and replacement name to give the file a new name.
     *
     * @param findName
     *      The name to find and replace.
     * @param replaceName
     *      Replaces the findName with this name.
     * @param files
     *      The file paths to rename.
     */
    static std::list<std::string> replace(
        const std::string &findName,
        const std::string &replaceName,
        const std::list<std::string> &files
    );

    /**
     * Wipes the input name and then replaces it and numbers.
     *
     * @param inputString
     *      The input string to replace the file name.
     * @param files
     *      The files to rename.
     */
    static std::list<std::string> wipeNameAndNumberFile(
        const std::string &inputString,
        const std::list<std::string> &files
    );

    /**
     * Numbers a batch of files. Prepends the numbers. Numbers are positively consecutive.
     *
     * @param inputString
     *      The input string to prepend to file names.
     * @param startNum
     *      The starting number.
     * @param files
     *      The file paths to rename.
     */
    static std::list<std::string> numberPrepend(
        const std::string &inputString,
        const int32_t startNum,
        const std::list<std::string> &files
    );

    /**
     * Numbers a batch of files. Numbers are positively consecutive.
     *
     * @param inputString
     *      The input string to append to the files.
     * @param startNum
     *      The starting number.
     * @param files
     *      The file paths to rename.
     */
    static std::list<std::string> numberAppend(
        const std::string &inputString,
        const int32_t startNum,
        const std::list<std::string> &files
    );

    /**
     * Conduct a number prepending while also deleting a preceding number.
     *
     * @param inputString
     *      The input string to prepend to the files.
     * @param startNum
     *      The starting number.
     * @param files
     *      The file paths to rename.
     */
    static std::list<std::string> deletePrecedingAndNumberPrepend(
        const std::string &inputString,
        const int32_t startNum,
        const std::list<std::string> &files
    );

    /**
     * Conduct a number appending, but remove the number before it.
     *
     * @param inputString
     *      The input string to append to the files.
     * @param startNum
     *      The starting number.
     * @param files
     *      The file paths to rename.
     */
    static std::list<std::string> deleteEndingAndNumberAppend(
        const std::string &inputString,
        const int32_t startNum,
        const std::list<std::string> &files
    );

    /**
     * Prepends the input onto the file name.
     *
     * @param inputString
     *      The input string to prepend to the files.
     * @param files
     *      The file paths to rename.
     */
    static std::list<std::string> prependString(
        const std::string &inputString,
        const std::list<std::string> &files
    );

    /**
     * Appends the input onto the file name.
     *
     * @param inputString
     *      The input string to append to the file names.
     * @param files
     *      The file paths to rename.
     */
    static std::list<std::string> appendString(
        const std::string &inputString,
        const std::list<std::string> &files
    );

private:
    /**
     * A const with all of the ASCII digits.
     */
    static const std::string DIGITS;
};

#endif // RENAMER_HPP
