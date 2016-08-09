#include "Renamer.hpp"

#include "../Common/Common.hpp"

/**
 * Gets the files in the command line.
 *
 * @param start
 *     The start of the command lines to start accumulating file names.
 * @param argc
 *     The number of arguments in argv.
 * @param argv
 *     The arguments in the command line.
 * @return A list with all of the files extracted from the command line.
 */
static std::list<std::string> getFiles(
    const std::int32_t start,
    const std::int32_t argc,
    const char** argv
);

static const std::int32_t SUCCESS = 0;
static const std::int32_t ERROR = 1;

std::int32_t main(const std::int32_t argc, const char** argv) {
    if (argc < 2) {
        std::cout << "--help for information" << std::endl;
        return ERROR;
    }

    const std::string command = argv[1];
    if (command == "--help") {
        // Print help.
        std::cout << "usage: renamer command <args> <files>" << std:: endl;
        std::cout << "Commands are:" << std::endl;

        // Print rename command documentation.
        std::cout << "Basic renamer program" << std::endl;
        std::cout << '\t' << Renamer::RENAME_COMMAND << std::endl;
        std::cout << '\t' << Renamer::WIPE_RENAME_NUMBER_COMMAND;
        std::cout << "\tWipes the file's name and uses the input name and numbers the files";
        std::cout << " starting at 1" << std::endl << std::endl;

        // Add a name and a file.
        std::cout << "Adding a name and numbering the files" << std::endl;
        std::cout << '\t' << Renamer::NUMBER_PREPEND_COMMAND;
        std::cout << "\tPrepends a string and a number to the file name\t" << std::endl;
        std::cout << '\t' << Renamer::NUMBER_APPEND_COMMAND;
        std::cout << "\tAppends a string and a number to the file" << std::endl << std::endl;

        // Delete a number, add a name, and number the files.
        std::cout << "Delete a number, add a name, and number the files" << std::endl;
        std::cout << '\t' << Renamer::DELETE_PRECEDING_NUM_PREPEND_COMMAND;
        std::cout << "\tDeletes a preceding number and prepends a number to the file" << std::endl;
        std::cout << '\t' << Renamer::DELETE_ENDING_NUM_APPEND_COMMAND;
        std::cout << "\tDeletes an ending number and appends a number to the file" << std::endl;
        std::cout << std::endl;

        // Add a string to a file name.
        std::cout << "Add a name to the file name." << std::endl;
        std::cout << '\t' << Renamer::PREPEND_STRING_COMMAND;
        std::cout << "\tPrepends a string to the file(s)" << std::endl;
        std::cout << '\t' << Renamer::APPEND_STRING_COMMAND;
        std::cout << "\tAppends a string to the file(s)" << std::endl;
        return 0;
    }

    if (command == Renamer::RENAME_COMMAND) {
        // Rename command.
        if (argc <= 4) {
            std::cout << Renamer::RENAME_COMMAND << " requires arguments: <find name> ";
            std::cout << "<replace name> <files>" << std::endl;
            return ERROR;
        }

        const std::string findName = argv[2];
        const std::string replaceName = argv[3];
        const std::list<std::string> files = getFiles(4, argc, argv);
        const std::list<std::string> renamedFiles = Renamer::replace(findName, replaceName, files);
        Renamer::rename(files, renamedFiles);
        return SUCCESS;
    } else if (command == Renamer::NUMBER_PREPEND_COMMAND && argc > 4) {
        // Number prepend command.
        if (argc <= 4) {
            std::cout << Renamer::NUMBER_PREPEND_COMMAND << " requires arguments: <input string> ";
            std::cout << "<starting number> <files>" << std::endl;
            return ERROR;
        }

        const std::string inputString = argv[2];
        const std::int32_t startNum = Common::parseInt(argv[3]);
        const std::list<std::string> files = getFiles(4, argc, argv);
        const std::list<std::string> renamedFiles = Renamer::numberPrepend(
            inputString,
            startNum,
            files
        );
        Renamer::rename(files, renamedFiles);
        return SUCCESS;
    } else if (command == Renamer::NUMBER_APPEND_COMMAND) {
        // Number append command.
        if (argc <= 4) {
            std::cout << Renamer::NUMBER_APPEND_COMMAND << " requires arguments: <input string> ";
            std::cout << "<starting number> <files>" << std::endl;
            return ERROR;
        }

        const std::string inputString = argv[2];
        const std::int32_t startNum = Common::parseInt(argv[3]);
        const std::list<std::string> files = getFiles(4, argc, argv);
        const std::list<std::string> renamedFiles = Renamer::numberAppend(
            inputString,
            startNum,
            files
        );
        Renamer::rename(files, renamedFiles);
        return SUCCESS;
    } else if (command == Renamer::DELETE_PRECEDING_NUM_PREPEND_COMMAND) {
        // Delete and prepend number command.
        if (argc <= 4) {
            std::cout << Renamer::DELETE_PRECEDING_NUM_PREPEND_COMMAND << " requires arguments: ";
            std::cout << "<input string> <starting number> <files>" << std::endl;
            return ERROR;
        }

        const std::string inputString = argv[2];
        const std::int32_t startNum = Common::parseInt(argv[3]);
        const std::list<std::string> files = getFiles(4, argc, argv);
        const std::list<std::string> renamedFiles = Renamer::deletePrecedingAndNumberPrepend(
            inputString,
            startNum,
            files
        );
        Renamer::rename(files, renamedFiles);
        return SUCCESS;
    } else if (command == Renamer::DELETE_ENDING_NUM_APPEND_COMMAND) {
        // Delete and append number command.
        if (argc <= 4) {
            std::cout << Renamer::DELETE_ENDING_NUM_APPEND_COMMAND << " requires arguments: ";
            std::cout << "<input string> <starting number> <files>" << std::endl;
            return ERROR;
        }

        const std::string inputString = argv[2];
        const std::int32_t startNum = Common::parseInt(argv[3]);
        const std::list<std::string> files = getFiles(4, argc, argv);
        const std::list<std::string> renamedFiles = Renamer::deleteEndingAndNumberAppend(
            inputString,
            startNum,
            files
        );
        Renamer::rename(files, renamedFiles);
        return SUCCESS;
    } else if (command == Renamer::PREPEND_STRING_COMMAND) {
        // Prepends a given string.
        if (argc <= 3) {
            std::cout << Renamer::PREPEND_STRING_COMMAND << " requires arguments: <input string> ";
            std::cout << "<files>" << std::endl;
            return ERROR;
        }

        const std::string inputString = argv[2];
        const std::list<std::string> files = getFiles(3, argc, argv);
        const std::list<std::string> renamedFiles = Renamer::prependString(inputString, files);
        Renamer::rename(files, renamedFiles);
        return SUCCESS;
    } else if (command == Renamer::APPEND_STRING_COMMAND) {
        // Appends a given string
        if (argc <= 3) {
            std::cout << Renamer::APPEND_STRING_COMMAND << " requires arguments: <input string> ";
            std::cout << "<files>" << std::endl;
            return ERROR;
        }

        const std::string inputString = argv[2];
        const std::list<std::string> files = getFiles(3, argc, argv);
        const std::list<std::string> renamedFiles = Renamer::appendString(inputString, files);
        Renamer::rename(files, renamedFiles);
        return SUCCESS;
    } else if (command == Renamer::WIPE_RENAME_NUMBER_COMMAND) {
        if (argc <= 3) {
            std::cout << Renamer::WIPE_RENAME_NUMBER_COMMAND << " requires arguments: ";
            std::cout << "<input string> <files>" << std::endl;
            return ERROR;
        }

        const std::string inputString = argv[2];
        const std::list<std::string> files = getFiles(3, argc, argv);
        const std::list<std::string> renamedFiles = Renamer::wipeNameAndNumberFile(
            inputString,
            files
        );
        Renamer::rename(files, renamedFiles);
        return SUCCESS;
    } else {
        return ERROR;
    }
}

std::list<std::string> getFiles(
    const std::int32_t start,
    const std::int32_t argc,
    const char** argv
) {
    std::list<std::string> files;
    for (std::int32_t i = start; i < argc; i++)
        files.push_back(argv[i]);

    return files;
}
