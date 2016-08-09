#include "catch.hpp"

#include "Renamer/Renamer.hpp"
#include "Common/Common.hpp"

#include <list>
#include <string>

std::list<std::string> createExtFiles();
std::list<std::string> createNoExtFiles();

TEST_CASE("Testing Renamer Class", "[Renamer]") {
    SECTION("Testing rename") {
        SECTION("Must throw an exception if file list sizes do not match") {
            const std::list<std::string> fileList1 { "file1", "file2", "file3" };
            const std::list<std::string> fileList2 { "file1", "file2" };
            REQUIRE_THROWS(Renamer::rename(fileList1, fileList2));
        }

        SECTION("Must not throw an exception if file list sizes do match") {
            const std::list<std::string> fileList1 { "file1", "file2", "file3" };
            const std::list<std::string> fileList2 { "file1", "file2", "file3" };
            REQUIRE_NOTHROW(Renamer::rename(fileList1, fileList2));
        }
    }

    SECTION("Testing replace") {
        const std::list<std::string> extFiles = createExtFiles();
        const std::list<std::string> renamedFiles = Renamer::replace("test", "break", extFiles);
        REQUIRE(extFiles.size() == renamedFiles.size());
        std::list<std::string>::const_iterator file = renamedFiles.begin();
        REQUIRE(*file == "breakfile1.txt");
        file++;
        REQUIRE(*file == "breakfile2.txt");
        file++;
        REQUIRE(*file == "breakfile3.txt");
        file++;
        REQUIRE(*file == "breakfile4.txt");
        file++;
        REQUIRE(*file == "breakfile5.txt");
        REQUIRE(++file == renamedFiles.end());
    }

    SECTION("Test wipe rename and number") {
        SECTION("Utilize files with an extension") {
            const std::list<std::string> extFiles = createExtFiles();
            const std::list<std::string> renamedFiles = Renamer::wipeNameAndNumberFile(
                "vacation-",
                extFiles
            );
            REQUIRE(extFiles.size() == renamedFiles.size());
            std::list<std::string>::const_iterator file = renamedFiles.begin();
            REQUIRE(*file == "vacation-1.txt");
            file++;
            REQUIRE(*file == "vacation-2.txt");
            file++;
            REQUIRE(*file == "vacation-3.txt");
            file++;
            REQUIRE(*file == "vacation-4.txt");
            file++;
            REQUIRE(*file == "vacation-5.txt");
            REQUIRE(++file == renamedFiles.end());
        }

        SECTION("Utilize files without an extension") {
            const std::list<std::string> noExtFiles = createNoExtFiles();
            const std::list<std::string> renamedFiles = Renamer::wipeNameAndNumberFile(
                "vacation-",
                noExtFiles
            );
            REQUIRE(noExtFiles.size() == renamedFiles.size());
            std::list<std::string>::const_iterator file = renamedFiles.begin();
            REQUIRE(*file == "vacation-1");
            file++;
            REQUIRE(*file == "vacation-2");
            file++;
            REQUIRE(*file == "vacation-3");
            file++;
            REQUIRE(*file == "vacation-4");
            file++;
            REQUIRE(*file == "vacation-5");
            REQUIRE(++file == renamedFiles.end());
        }
    }

    SECTION("Testing number prepend") {
        const std::list<std::string> extFiles = createExtFiles();
        const std::list<std::string> renamedFiles = Renamer::numberPrepend("-", 5, extFiles);
        REQUIRE(extFiles.size() == renamedFiles.size());
        std::list<std::string>::const_iterator file = renamedFiles.begin();
        REQUIRE(*file == "5-testfile1.txt");
        file++;
        REQUIRE(*file == "6-testfile2.txt");
        file++;
        REQUIRE(*file == "7-testfile3.txt");
        file++;
        REQUIRE(*file == "8-testfile4.txt");
        file++;
        REQUIRE(*file == "9-testfile5.txt");
        REQUIRE(++file == renamedFiles.end());
    }

    SECTION("Testing number append") {
        const std::list<std::string> extFiles = createExtFiles();
        const std::list<std::string> renamedFiles = Renamer::numberAppend("__", 10, extFiles);
        REQUIRE(extFiles.size() == renamedFiles.size());
        std::list<std::string>::const_iterator file = renamedFiles.begin();
        REQUIRE(*file == "testfile1__10.txt");
        file++;
        REQUIRE(*file == "testfile2__11.txt");
        file++;
        REQUIRE(*file == "testfile3__12.txt");
        file++;
        REQUIRE(*file == "testfile4__13.txt");
        file++;
        REQUIRE(*file == "testfile5__14.txt");
        REQUIRE(++file == renamedFiles.end());
    }

    SECTION("Testing number append no extension") {
        const std::list<std::string> noExtFiles = createNoExtFiles();
        const std::list<std::string> renamedFiles = Renamer::numberAppend("__", 10, noExtFiles);
        REQUIRE(noExtFiles.size() == renamedFiles.size());
        std::list<std::string>::const_iterator file = renamedFiles.begin();
        REQUIRE(*file == "testfile1__10");
        file++;
        REQUIRE(*file == "testfile2__11");
        file++;
        REQUIRE(*file == "testfile3__12");
        file++;
        REQUIRE(*file == "testfile4__13");
        file++;
        REQUIRE(*file == "testfile5__14");
        REQUIRE(++file == renamedFiles.end());
    }

    SECTION("Testing delete preceding number and prepend number") {
        const std::list<std::string> extFiles = createExtFiles();
        const std::list<std::string> renamedFiles = Renamer::deletePrecedingAndNumberPrepend(
            "~",
            50,
            extFiles
        );
        REQUIRE(extFiles.size() == renamedFiles.size());
        std::list<std::string>::const_iterator file = renamedFiles.begin();
        REQUIRE(*file == "50~testfile1.txt");
        file++;
        REQUIRE(*file == "51~testfile2.txt");
        file++;
        REQUIRE(*file == "52~testfile3.txt");
        file++;
        REQUIRE(*file == "53~testfile4.txt");
        file++;
        REQUIRE(*file == "54~testfile5.txt");
        REQUIRE(++file == renamedFiles.end());
    }

    SECTION("Testing delete ending number and append number") {
        SECTION("Utilizing files with extensions") {
            const std::list<std::string> extFiles = createExtFiles();
            const std::list<std::string> renamedFiles = Renamer::deleteEndingAndNumberAppend(
                ",",
                100,
                extFiles
            );
            REQUIRE(extFiles.size() == renamedFiles.size());
            std::list<std::string>::const_iterator file = renamedFiles.begin();
            REQUIRE(*file == "testfile,100.txt");
            file++;
            REQUIRE(*file == "testfile,101.txt");
            file++;
            REQUIRE(*file == "testfile,102.txt");
            file++;
            REQUIRE(*file == "testfile,103.txt");
            file++;
            REQUIRE(*file == "testfile,104.txt");
            REQUIRE(++file == renamedFiles.end());
        }

        SECTION("Utilizing files without extensions") {
            const std::list<std::string> noExtFiles = createNoExtFiles();
            const std::list<std::string> renamedFiles = Renamer::deleteEndingAndNumberAppend(
                ",",
                100,
                noExtFiles
            );
            REQUIRE(noExtFiles.size() == renamedFiles.size());
            std::list<std::string>::const_iterator file = renamedFiles.begin();
            REQUIRE(*file == "testfile,100");
            file++;
            REQUIRE(*file == "testfile,101");
            file++;
            REQUIRE(*file == "testfile,102");
            file++;
            REQUIRE(*file == "testfile,103");
            file++;
            REQUIRE(*file == "testfile,104");
            REQUIRE(++file == renamedFiles.end());
        }
    }

    SECTION("Test prepend string") {
        const std::list<std::string> extFiles = createExtFiles();
        const std::list<std::string> renamedFiles = Renamer::prependString("hi-", extFiles);
        REQUIRE(extFiles.size() == renamedFiles.size());
        std::list<std::string>::const_iterator file = renamedFiles.begin();
        REQUIRE(*file == "hi-testfile1.txt");
        file++;
        REQUIRE(*file == "hi-testfile2.txt");
        file++;
        REQUIRE(*file == "hi-testfile3.txt");
        file++;
        REQUIRE(*file == "hi-testfile4.txt");
        file++;
        REQUIRE(*file == "hi-testfile5.txt");
        REQUIRE(++file == renamedFiles.end());
    }

    SECTION("Test append string") {
        SECTION("Utilizing file names with extensions") {
            const std::list<std::string> extFiles = createExtFiles();
            const std::list<std::string> renamedFiles = Renamer::appendString(".bye", extFiles);
            REQUIRE(extFiles.size() == renamedFiles.size());
            std::list<std::string>::const_iterator file = renamedFiles.begin();
            REQUIRE(*file == "testfile1.bye.txt");
            file++;
            REQUIRE(*file == "testfile2.bye.txt");
            file++;
            REQUIRE(*file == "testfile3.bye.txt");
            file++;
            REQUIRE(*file == "testfile4.bye.txt");
            file++;
            REQUIRE(*file == "testfile5.bye.txt");
            REQUIRE(++file == renamedFiles.end());
        }

        SECTION("Utilizing file names without an extension") {
            const std::list<std::string> noExtFiles = createNoExtFiles();
            const std::list<std::string> renamedFiles = Renamer::appendString(".bye", noExtFiles);
            REQUIRE(noExtFiles.size() == renamedFiles.size());
            std::list<std::string>::const_iterator file = renamedFiles.begin();
            REQUIRE(*file == "testfile1.bye");
            file++;
            REQUIRE(*file == "testfile2.bye");
            file++;
            REQUIRE(*file == "testfile3.bye");
            file++;
            REQUIRE(*file == "testfile4.bye");
            file++;
            REQUIRE(*file == "testfile5.bye");
            REQUIRE(++file == renamedFiles.end());
        }
    }
}

std::list<std::string> createExtFiles() {
    return std::list<std::string> {
        "testfile1.txt",
        "testfile2.txt",
        "testfile3.txt",
        "testfile4.txt",
        "testfile5.txt"
    };
}

std::list<std::string> createNoExtFiles() {
    return std::list<std::string> {
        "testfile1",
        "testfile2",
        "testfile3",
        "testfile4",
        "testfile5"
    };
}
