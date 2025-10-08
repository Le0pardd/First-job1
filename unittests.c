#include <stdio.h>
#include <assert.h>
#include "meet.h"
#include "unittests.h"

void test_is_valid_booking_id() {
    assert(is_valid_booking_id("M001") == 1);
    assert(is_valid_booking_id("M01") == 0);
    assert(is_valid_booking_id("A001") == 0);
    assert(is_valid_booking_id("M1234") == 0);
}

void test_is_valid_booker_name() {
    assert(is_valid_booker_name("John Doe") == 1);
    assert(is_valid_booker_name("John123") == 0);
    assert(is_valid_booker_name("") == 0);
}

void test_is_valid_room() {
    assert(is_valid_room("A") == 1);
    assert(is_valid_room("F") == 1);
    assert(is_valid_room("Z") == 0);
}

void test_is_valid_date() {
    assert(is_valid_date("2025-12-31") == 1);
    assert(is_valid_date("2025-02-30") == 0);
    assert(is_valid_date("2025/12/31") == 0);
    assert(is_valid_date("2025-13-01") == 0);
}

void test_is_valid_time() {
    assert(is_valid_time("10:00 AM") == 1);
    assert(is_valid_time("00:00 AM") == 0);
    assert(is_valid_time("13:00 PM") == 0);
    assert(is_valid_time("9:60 AM") == 0);
}

int main() {
    test_is_valid_booking_id();
    test_is_valid_booker_name();
    test_is_valid_room();
    test_is_valid_date();
    test_is_valid_time();
    printf("All unit tests passed!\n");
    return 0;
}
