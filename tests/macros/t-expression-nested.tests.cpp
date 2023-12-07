#include "dummy.hpp"
#include "lifecycle-tracker.hpp"
#include "test-stream.hpp"
#include "trace-out/trace-out.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("$t(...) nested in some expression", "[t]")
{
	SECTION("with rvalue")
	{
		int subject {$t(456)};

		REQUIRE(subject == 456);
	}

	SECTION("with lvalue")
	{
		int subject1 {456};
		int &subject2 {$t(subject1)};

		REQUIRE(&subject2 == &subject1);
	}
}

TEST_CASE("$tbin(...) nested in some expression", "[tbin]")
{
	SECTION("with rvalue")
	{
		int subject {$tbin(456)};

		REQUIRE(subject == 456);
	}

	SECTION("with lvalue")
	{
		int subject1 {456};
		int &subject2 {$tbin(subject1)};

		REQUIRE(&subject2 == &subject1);
	}
}

TEST_CASE("$toct(...) nested in some expression", "[toct]")
{
	SECTION("with rvalue")
	{
		int subject {$toct(456)};

		REQUIRE(subject == 456);
	}

	SECTION("with lvalue")
	{
		int subject1 {456};
		int &subject2 {$toct(subject1)};

		REQUIRE(&subject2 == &subject1);
	}
}

TEST_CASE("$thex(...) nested in some expression", "[thex]")
{
	SECTION("with rvalue")
	{
		int subject {$thex(456)};

		REQUIRE(subject == 456);
	}

	SECTION("with lvalue")
	{
		int subject1 {456};
		int &subject2 {$thex(subject1)};

		REQUIRE(&subject2 == &subject1);
	}
}

TEST_CASE("$t(<value>) keeps lifecycle", "[t]")
{
	SECTION("while assigning a reference")
	{
		lifecycle_tracker *subject_ptr;
		{
			lifecycle_tracker subject;
			subject_ptr = &subject;

			lifecycle_tracker &reference {$t(subject)};
			REQUIRE(&reference == &subject);
		}

		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).default_constructed == 1);
		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).copy_constructed == 0);
		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).move_constructed == 0);
		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).destructed == 1);
		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).copy_assigned == 0);
		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).move_assigned == 0);
	}

	SECTION("while copy-constructing")
	{
		lifecycle_tracker *subject_ptr;
		lifecycle_tracker *another_ptr;
		{
			lifecycle_tracker subject;
			subject_ptr = &subject;

			lifecycle_tracker another {$t(subject)};
			another_ptr = &another;
		}

		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).default_constructed == 1);
		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).copy_constructed == 0);
		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).move_constructed == 0);
		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).destructed == 1);
		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).copy_assigned == 0);
		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).move_assigned == 0);

		REQUIRE(lifecycle_tracker::statistics_for(another_ptr).default_constructed == 0);
		REQUIRE(lifecycle_tracker::statistics_for(another_ptr).copy_constructed == 1);
		REQUIRE(lifecycle_tracker::statistics_for(another_ptr).move_constructed == 0);
		REQUIRE(lifecycle_tracker::statistics_for(another_ptr).destructed == 1);
		REQUIRE(lifecycle_tracker::statistics_for(another_ptr).copy_assigned == 0);
		REQUIRE(lifecycle_tracker::statistics_for(another_ptr).move_assigned == 0);
	}

	SECTION("while move-constructing")
	{
		lifecycle_tracker *subject_ptr;
		lifecycle_tracker *another_ptr;
		{
			lifecycle_tracker subject;
			subject_ptr = &subject;

			lifecycle_tracker another {std::move($t(subject))};
			another_ptr = &another;
		}

		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).default_constructed == 1);
		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).copy_constructed == 0);
		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).move_constructed == 0);
		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).destructed == 1);
		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).copy_assigned == 0);
		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).move_assigned == 0);

		REQUIRE(lifecycle_tracker::statistics_for(another_ptr).default_constructed == 0);
		REQUIRE(lifecycle_tracker::statistics_for(another_ptr).copy_constructed == 0);
		REQUIRE(lifecycle_tracker::statistics_for(another_ptr).move_constructed == 1);
		REQUIRE(lifecycle_tracker::statistics_for(another_ptr).destructed == 1);
		REQUIRE(lifecycle_tracker::statistics_for(another_ptr).copy_assigned == 0);
		REQUIRE(lifecycle_tracker::statistics_for(another_ptr).move_assigned == 0);
	}

	SECTION("while copy-assigning")
	{
		lifecycle_tracker *subject_ptr;
		lifecycle_tracker *another_ptr;
		{
			lifecycle_tracker subject;
			subject_ptr = &subject;

			lifecycle_tracker another;
			another_ptr = &another;

			another = $t(subject);
		}

		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).default_constructed == 1);
		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).copy_constructed == 0);
		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).move_constructed == 0);
		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).destructed == 1);
		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).copy_assigned == 0);
		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).move_assigned == 0);

		REQUIRE(lifecycle_tracker::statistics_for(another_ptr).default_constructed == 1);
		REQUIRE(lifecycle_tracker::statistics_for(another_ptr).copy_constructed == 0);
		REQUIRE(lifecycle_tracker::statistics_for(another_ptr).move_constructed == 0);
		REQUIRE(lifecycle_tracker::statistics_for(another_ptr).destructed == 1);
		REQUIRE(lifecycle_tracker::statistics_for(another_ptr).copy_assigned == 1);
		REQUIRE(lifecycle_tracker::statistics_for(another_ptr).move_assigned == 0);
	}

	SECTION("while move-assigning")
	{
		lifecycle_tracker *subject_ptr;
		lifecycle_tracker *another_ptr;
		{
			lifecycle_tracker subject;
			subject_ptr = &subject;

			lifecycle_tracker another;
			another_ptr = &another;

			another = std::move($t(subject));
		}

		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).default_constructed == 1);
		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).copy_constructed == 0);
		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).move_constructed == 0);
		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).destructed == 1);
		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).copy_assigned == 0);
		REQUIRE(lifecycle_tracker::statistics_for(subject_ptr).move_assigned == 0);

		REQUIRE(lifecycle_tracker::statistics_for(another_ptr).default_constructed == 1);
		REQUIRE(lifecycle_tracker::statistics_for(another_ptr).copy_constructed == 0);
		REQUIRE(lifecycle_tracker::statistics_for(another_ptr).move_constructed == 0);
		REQUIRE(lifecycle_tracker::statistics_for(another_ptr).destructed == 1);
		REQUIRE(lifecycle_tracker::statistics_for(another_ptr).copy_assigned == 0);
		REQUIRE(lifecycle_tracker::statistics_for(another_ptr).move_assigned == 1);
	}
}

