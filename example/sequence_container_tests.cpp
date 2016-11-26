#include "tests.h"
using namespace snowhouse;

template <typename T>
void SequenceContainerActual()
{
  const char* ExpectedActual = "\nActual: [ 1, 2, 3, 5, 8 ]";

  T container;
  container.clear();
  container.push_back(1);
  container.push_back(2);
  container.push_back(3);
  container.push_back(5);
  container.push_back(8);

  it("handles All()");
  {
    Assert::That(container, Has().All().GreaterThan(1).Or().LessThan(4));
  }

  it("handles failing All()");
  {
    AssertTestFails(Assert::That(container, Has().All().GreaterThan(4)), std::string("Expected: all greater than 4") + ExpectedActual);
  }

  it("handles invalid expression after All()");
  {
    AssertTestFails(Assert::That(container, Has().All().Not()), "The expression contains a not operator without any operand");
  }

  it("handles no expression after All()");
  {
    AssertTestFails(Assert::That(container, Has().All()), "The expression after \"all\" operator does not yield any result");
  }

  it("handles AtLeast()");
  {
    Assert::That(container, Has().AtLeast(1).LessThan(5));
  }

  it("handles failing AtLeast()");
  {
    AssertTestFails(Assert::That(container, Has().AtLeast(2).LessThan(2)), std::string("Expected: at least 2 less than 2") + ExpectedActual);
  }

  it("handles Exactly()");
  {
    Assert::That(container, Has().Exactly(1).EqualTo(3));
  }

  it("handles failing Exactly()");
  {
    AssertTestFails(Assert::That(container, Has().Exactly(2).EqualTo(3)), std::string("Expected: exactly 2 equal to 3") + ExpectedActual);
  }

  it("handles AtMost()");
  {
    Assert::That(container, Has().AtMost(1).EqualTo(5));
  }

  it("handles failing AtMost()");
  {
    AssertTestFails(Assert::That(container, Has().AtMost(1).EqualTo(3).Or().EqualTo(5)), std::string("Expected: at most 1 equal to 3 or equal to 5") + ExpectedActual);
  }

  it("handles None()");
  {
    Assert::That(container, Has().None().EqualTo(666));
  }

  it("handles failing None()");
  {
    AssertTestFails(Assert::That(container, Has().None().EqualTo(5)), std::string("Expected: none equal to 5") + ExpectedActual);
  }

  it("handles Contains()");
  {
    Assert::That(container, Contains(3));
  }

  it("detects failing Contains()");
  {
    AssertTestFails(Assert::That(container, Contains(99)), std::string("contains 99") + ExpectedActual);
  }

  it("handles HasLength()");
  {
    Assert::That(container, HasLength(5));
  }

  it("handles failing HasLength()");
  {
    AssertTestFails(Assert::That(container, HasLength(7)), std::string("of length 7") + ExpectedActual);
  }

  it("handles Contains() expression templates");
  {
    Assert::That(container, Contains(3));
  }

  it("detects failing Contains() expression templates");
  {
    AssertTestFails(Assert::That(container, Contains(99)), std::string("contains 99") + ExpectedActual);
  }

  it("handles HasLength()");
  {
    Assert::That(container, HasLength(5));
  }

  it("handles failing HasLength() for vectors");
  {
    AssertTestFails(Assert::That(container, HasLength(7)), std::string("of length 7") + ExpectedActual);
  }

  it("handles IsEmpty()");
  {
    T is_empty;

    Assert::That(is_empty, IsEmpty());
  }

  it("handles failing IsEmpty()");
  {
    AssertTestFails(Assert::That(container, IsEmpty()), "of length 0");
  }

  it("handles Is().Empty()");
  {
    T is_empty;

    Assert::That(is_empty, Is().Empty());
  }

  it("handles failing Is().Empty()");
  {
    AssertTestFails(Assert::That(container, Is().Empty()), "of length 0");
  }

  it("handles EqualsContainer()");
  {
    std::list<int> expected;
    expected.assign(container.begin(), container.end());

    AssertThat(container, EqualsContainer(expected));
  }

  it("handles EqualsContainer()");
  {
    std::list<int> expected;
    expected.assign(container.begin(), container.end());

    AssertThat(container, Is().EqualToContainer(expected));
  }

  it("handles failing EqualsContainer()");
  {
    const int e[] = {4, 2, 4};
    std::list<int> expected(e, e + sizeof(e) / sizeof(e[0]));

    AssertTestFails(Assert::That(container, EqualsContainer(expected)), "Expected: [ 4, 2, 4 ]");
  }

  it("handles failing EqualsContainer()");
  {
    const int e[] = {4, 2, 4};
    std::list<int> expected(e, e + sizeof(e) / sizeof(e[0]));

    AssertTestFails(Assert::That(container, Is().EqualToContainer(expected)), "Expected: [ 4, 2, 4 ]");
  }
}

void SequenceContainerTests()
{
  describe("Sequence containers (std::vector)");
  SequenceContainerActual<std::vector<int> >();

  describe("Sequence containers (std::list)");
  SequenceContainerActual<std::list<int> >();

  describe("Sequence containers (std::deque)");
  SequenceContainerActual<std::deque<int> >();
}
