#include <stdio.h>
#include <assert.h>
#include "meet.h"
#include "e2etest.h"

#define MAX_BOOKINGS 100
extern int count;
extern char bookingIDs[MAX_BOOKINGS][20];
extern char bookerNames[MAX_BOOKINGS][50];
extern char meetingRooms[MAX_BOOKINGS][50];
extern char dates[MAX_BOOKINGS][20];
extern char times[MAX_BOOKINGS][15];

void backup_csv() {
    FILE *src = fopen("meetings.csv", "r");
    FILE *dst = fopen("meetings_backup.csv", "w");
    if (src && dst) {
        char buf[256];
        while (fgets(buf, sizeof(buf), src)) {
            fputs(buf, dst);
        }
    }
    if (src) fclose(src);
    if (dst) fclose(dst);
}

void restore_csv() {
    FILE *src = fopen("meetings_backup.csv", "r");
    FILE *dst = fopen("meetings.csv", "w");
    if (src && dst) {
        char buf[256];
        while (fgets(buf, sizeof(buf), src)) {
            fputs(buf, dst);
        }
    }
    if (src) fclose(src);
    if (dst) fclose(dst);
}

void setup_mock_data() {
    FILE *fp = fopen("meetings.csv", "w");
    assert(fp != NULL);
    fprintf(fp, "M100,Test User,Conference Room A,2025-12-31,10:00 AM\n");
    fclose(fp);
}

void test_search_booking() {
    load_bookings();
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(bookingIDs[i], "M100") == 0 && strcmp(bookerNames[i], "Test User") == 0) {
            found = 1;
        }
    }
    assert(found == 1);
    printf("[PASS] test_search_booking\n");
}

void test_update_booking() {
    load_bookings();
    for (int i = 0; i < count; i++) {
        if (strcmp(bookingIDs[i], "M100") == 0) {
            strcpy(dates[i], "2026-01-01");
            strcpy(times[i], "11:00 AM");
        }
    }
    save_bookings();
    load_bookings();
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(bookingIDs[i], "M100") == 0 && strcmp(dates[i], "2026-01-01") == 0 && strcmp(times[i], "11:00 AM") == 0) {
            found = 1;
        }
    }
    assert(found == 1);
    printf("[PASS] test_update_booking\n");
}

void test_delete_booking() {
    load_bookings();
    int idx = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(bookingIDs[i], "M100") == 0) {
            idx = i;
            break;
        }
    }
    if (idx != -1) {
        for (int j = idx; j < count - 1; j++) {
            strcpy(bookingIDs[j], bookingIDs[j+1]);
            strcpy(bookerNames[j], bookerNames[j+1]);
            strcpy(meetingRooms[j], meetingRooms[j+1]);
            strcpy(dates[j], dates[j+1]);
            strcpy(times[j], times[j+1]);
        }
        count--;
        save_bookings();
    }
    load_bookings();
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(bookingIDs[i], "M100") == 0) {
            found = 1;
        }
    }
    assert(found == 0);
    printf("[PASS] test_delete_booking\n");
}

int main() {
    backup_csv();
    setup_mock_data();
    test_search_booking();
    test_update_booking();
    test_delete_booking();
    restore_csv();
    printf("All E2E tests passed!\n");
    return 0;
}
