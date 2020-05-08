#include <catch.hpp>
#include <iostream>
#include <sstream>

using istringstream = std::istringstream;

bool CheckProgram(std::istream& input_stream);

TEST_CASE("check_program_empty") {
    istringstream text("");
    REQUIRE(CheckProgram(text));
}

TEST_CASE("check_program_simple") {
    istringstream text("begin\nend\n");
    REQUIRE(CheckProgram(text));
}

TEST_CASE("check_program_ok") {
    istringstream text(R"(
begin
	Write('Input number 1:');
	Readln(Num1);
	Writeln('Input number 2:');
	Readln(Num2);
	Sum := Num1 + Num2; {addition}
    a := int[3];
    a[0] = 1;
    a[1] = 3 * (2 + 1);
	Writeln(Sum);
	Readln;
end
)");
    REQUIRE(CheckProgram(text));
}

TEST_CASE("NestedBeginEnd") {
    istringstream text(R"(begin
a := 1
b := 2
c := (a + b)
d := (a - b) {subtraction}
begin
  some loop
  e := arr[(a + 1)]
end
f := 1
end
)");
    REQUIRE(CheckProgram(text));
}

TEST_CASE("check_program_bad1") {
    istringstream text(R"(
begin
a := 1  { comment }
b := 2 * ((3 + 4)
c := x[9+a]
end
)");
    REQUIRE_FALSE(CheckProgram(text));
}

