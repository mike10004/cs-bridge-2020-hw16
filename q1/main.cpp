// mchaberski@novetta.com
// hw16 question 1

#include <string>
#include <iostream>
#include <fstream>
#include "stack.h"

using string = std::string;

const int BEGIN = -1;
const int END = -2;

const int OPENERS[] = {
    BEGIN,
    '{',
    '(',
    '[',
};

const int CLOSERS[] = {
    END,
    '}',
    ')',
    ']',
};

const size_t NUM_PAIRS = 4;

bool IsOpener(int ch) {
    for (int opener : OPENERS) {
        if (ch == opener) {
            return true;
        }
    }
    return false;
}

bool IsCloser(int ch) {
    for (int closer : CLOSERS) {
        if (ch == closer) {
            return true;
        }
    }
    return false;
}

bool IsPair(int opener, int closer) {
    for (size_t i = 0; i < NUM_PAIRS; i++) {
        if (OPENERS[i] == opener && CLOSERS[i] == closer) {
            return true;
        }
    }
    return false;
}

bool CheckCloser(int closer, Stack<int>& openers) {
    if (openers.IsEmpty()) {
        return false;
    }
    char opener = openers.Pop();
    return IsPair(opener, closer);
}

bool CheckProgram(std::istream& input_stream) {
    Stack<int> openers;
    while (input_stream) {
        string line;
        getline(input_stream, line);
        if (line == "begin") {
            openers.Push(BEGIN);
        }
        if (line == "end") {
            bool ok = CheckCloser(END, openers);
            if (!ok) {
                return false;
            }
        }
        for (char ch : line) {
            if (IsOpener(ch)) {
                openers.Push(ch);
            }
            if (IsCloser(ch)) {
                bool ok = CheckCloser(ch, openers);
                if (!ok) {
                    return false;
                }
            }
        }
    }
    return openers.IsEmpty();
}

#ifndef UNIT_TESTS     // stage: cut

int main(int argc, char* argv[]) {
    std::string pathname;
    if (argc == 2) {
        pathname.assign(argv[1]);
    } else {
        std::cout << "enter pathname of PASCAL program file: ";
        std::cin >> pathname;
    }
    std::ifstream input_stream(pathname);
    if (!input_stream) {
        std::cerr << "input file error: " << pathname << std::endl;
        return 1;
    }
    bool program_correct = CheckProgram(input_stream);
    std::cout << "program is " << (program_correct ? "OK" : "INCORRECT") << std::endl;
    return 0;
}

#endif    // stage: cut
