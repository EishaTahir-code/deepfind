#include <iostream>
#include "Set.h"

void check(bool ok, const char* name) {
    std::cout << (ok ? "PASS: " : "FAIL: ") << name << "\n";
}

int main() {
    CustomSet<std::string> s;
    s.insert("the");
    s.insert("the");
    check(s.size() == 1, "duplicate is ignored");
    check(s.contains("the"), "contains finds an inserted word");
    check(!s.contains("stack"), "contains says false for a missing word");

    s.insert("is");
    s.insert("of");
    check(s.size() == 3, "size is 3 after three different words");
    check(s.items().size() == 3, "items returns all 3 words");

    s.remove("is");
    check(!s.contains("is") && s.size() == 2, "remove takes the word out");
    s.remove("cat");
    check(s.size() == 2, "removing a missing word changes nothing");

    CustomSet<std::string> copy = s;
    copy.insert("new");
    check(s.size() == 2 && copy.size() == 3, "copy is independent of the original");

    CustomSet<std::string> stop = makeStopWords();
    check(stop.contains("the"), "the is a stop word");
    check(!stop.contains("for"), "for is NOT a stop word");
    check(!stop.contains("stack"), "stack is NOT a stop word");
}