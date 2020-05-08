// mchaberski@novetta.com
// hw16 question 1

#ifndef UNIT_TESTS     // stage: cut
#include <iostream>
#include <fstream>
#endif                  // stage: cut
#include <string>
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

void Trim(const std::string& s, size_t& start, size_t& len) {
    start = 0;
    size_t end_exclusive = s.length();
    while (start < s.length() && std::isspace(s[start])) {
        start++;
    }
    while (end_exclusive > 0 && std::isspace(s[end_exclusive - 1])) {
        end_exclusive--;
    }
    len = end_exclusive - start;
}

bool TrimmedEquals(const std::string& a, const std::string& b) {
    size_t a_start, a_len;
    Trim(a, a_start, a_len);
    size_t b_start, b_len;
    Trim(b, b_start, b_len);
    return a.compare(a_start, a_len, b, b_start, b_len) == 0;
}

bool CheckProgram(std::istream& input_stream) {
    Stack<int> openers;
    while (input_stream) {
        string line;
        getline(input_stream, line);
        if (TrimmedEquals(line, "begin")) {
            openers.Push(BEGIN);
        }
        if (TrimmedEquals(line, "end")) {
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
