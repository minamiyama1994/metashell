// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "string_set.hpp"
#include "test_shell.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_simple_completion)
{
  test_shell sh;

  BOOST_CHECK_EQUAL(string_set(), string_set(sh, "no_completion_for_this"));
  BOOST_CHECK_EQUAL(string_set("e"), string_set(sh, "doubl"));
  BOOST_CHECK_EQUAL(string_set("line", "t"), string_set(sh, "in"));
  BOOST_CHECK_EQUAL(string_set(), string_set(sh, "decltype(\"in"));
  BOOST_CHECK_EQUAL(string_set(), string_set(sh, "int"));
}

BOOST_AUTO_TEST_CASE(test_member_completion)
{
  test_shell sh;
  sh.store_in_buffer(
    "struct foo"
    "{"
      "typedef foo type;"
      "typedef int bar;"

      "double mem1;"
      "char mem2;"
    "};"
  );

  const string_set members_of_foo("~foo", "mem2", "mem1", "foo", "operator=");

  BOOST_CHECK_EQUAL(members_of_foo, string_set(sh, "decltype(foo()."));
  BOOST_CHECK_EQUAL(members_of_foo, string_set(sh, "decltype(((foo*)0)->"));

  BOOST_CHECK_EQUAL(
    members_of_foo + string_set("type", "bar"),
    string_set(sh, "foo::")
  );

  BOOST_CHECK_EQUAL(
    string_set("em1", "em2"),
    string_set(sh, "decltype(foo().m")
  );
  BOOST_CHECK_EQUAL(
    string_set("em1", "em2"),
    string_set(sh, "decltype(((foo*)0)->m")
  );
}

BOOST_AUTO_TEST_CASE(test_template_member_completion)
{
  test_shell sh;
  sh.store_in_buffer(
    "template <class T>"
    "struct foo"
    "{"
      "typedef T type;"
      "typedef int bar;"

      "double mem1;"
      "char mem2;"
    "};"
  );

  const string_set members_of_foo("~foo", "mem2", "mem1", "foo", "operator=");

  BOOST_CHECK_EQUAL(members_of_foo, string_set(sh, "decltype(foo<int>()."));
  BOOST_CHECK_EQUAL(
    members_of_foo,
    string_set(sh, "decltype(((foo<int>*)0)->")
  );

  BOOST_CHECK_EQUAL(
    members_of_foo + string_set("type", "bar"),
    string_set(sh, "foo<int>::")
  );

  BOOST_CHECK_EQUAL(
    string_set("em1", "em2"),
    string_set(sh, "decltype(foo<int>().m")
  );
  BOOST_CHECK_EQUAL(
    string_set("em1", "em2"),
    string_set(sh, "decltype(((foo<int>*)0)->m")
  );
}

BOOST_AUTO_TEST_CASE(test_included_completion)
{
  test_shell sh;
  sh.store_in_buffer("#include <vector>");

  BOOST_CHECK_EQUAL(string_set("r"), string_set(sh, "std::vecto"));
}

