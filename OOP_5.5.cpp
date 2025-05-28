#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

const set<string> cpp_keywords = {"alignas",       "alignof",     "and",
                                  "and_eq",        "asm",         "auto",
                                  "bitand",        "bitor",       "bool",
                                  "break",         "case",        "catch",
                                  "char",          "char8_t",     "char16_t",
                                  "char32_t",      "class",       "compl",
                                  "concept",       "const",       "consteval",
                                  "constexpr",     "constinit",   "const_cast",
                                  "continue",      "co_await",    "co_return",
                                  "co_yield",      "decltype",    "default",
                                  "delete",        "do",          "double",
                                  "dynamic_cast",  "else",        "enum",
                                  "explicit",      "export",      "extern",
                                  "false",         "float",       "for",
                                  "friend",        "goto",        "if",
                                  "inline",        "int",         "long",
                                  "mutable",       "namespace",   "new",
                                  "noexcept",      "not",         "not_eq",
                                  "nullptr",       "operator",    "or",
                                  "or_eq",         "private",     "protected",
                                  "public",        "register",    "reinterpret_cast",
                                  "requires",      "return",      "short",
                                  "signed",        "sizeof",      "static",
                                  "static_assert", "static_cast", "struct",
                                  "switch",        "template",    "this",
                                  "thread_local",  "throw",       "true",
                                  "try",           "typedef",     "typeid",
                                  "typename",      "union",       "unsigned",
                                  "using",         "virtual",     "void",
                                  "volatile",      "wchar_t",     "while",
                                  "xor",           "xor_eq"};

struct KeywordInfo {
    int count = 0;
    set<int> lines;
};

int main() {
    ifstream input("OOP_5.5_input.cpp");
    ofstream output("OOP_5.5_output.txt");

    if (!input.is_open()) {
        cerr << "Не удалось открыть файл input.cpp" << endl;
        return 1;
    }

    map<string, KeywordInfo> keyword_map;
    string line;
    int line_number = 0;

    while (getline(input, line)) {
        ++line_number;
        stringstream ss(line);
        string token;
        while (ss >> token) {
            // Удалим лишние символы с начала и конца (например, ; , ( ) и т.п.)
            token = regex_replace(token, regex(R"(^\W+|\W+$)"), "");
            if (cpp_keywords.count(token)) {
                keyword_map[token].count++;
                keyword_map[token].lines.insert(line_number);
            }
        }
    }

    for (const auto& [keyword, info] : keyword_map) {
        output << keyword << ": " << info.count << " раз(а), строки: ";
        bool first = true;
        for (int line : info.lines) {
            if (!first) output << ", ";
            output << line;
            first = false;
        }
        output << '\n';
    }

    input.close();
    output.close();
    cout << "Анализ завершён. Результат записан в OOP_5.5_output.txt" << endl;
    return 0;
}
