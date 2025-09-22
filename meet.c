#include <stdio.h>
#include <string.h>

#define FILENAME "meetings.csv"
#define MAX_BOOKINGS 100

char bookingIDs[MAX_BOOKINGS][20];     // เก็บรหัสการจอง
char bookerNames[MAX_BOOKINGS][50];    // เก็บชื่อผู้จอง
char meetingRooms[MAX_BOOKINGS][30];   // เก็บห้องประชุม
char dates[MAX_BOOKINGS][15];          // เก็บวันที่
char times[MAX_BOOKINGS][15];          // เก็บเวลา

int count = 0; // นับจำนวนการจอง

// อ่านข้อมูลจากไฟล์ CSV
void load_bookings() {
    FILE *fp = fopen(FILENAME, "r");
    if (!fp) return;
    count = 0;
    while (fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
        bookingIDs[count], bookerNames[count], meetingRooms[count], dates[count], times[count]) == 5) {
        count++;
    }
    fclose(fp);
}


// บันทึกข้อมูลลงไฟล์ CSV
void save_bookings() {
    FILE *fp = fopen(FILENAME, "w");
    if (!fp) return;
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%s,%s,%s,%s\n", bookingIDs[i], bookerNames[i], meetingRooms[i], dates[i], times[i]);
    }
    fclose(fp);
}


// เพิ่มข้อมูลการใช้บริการห้องประชุม
void add_booking() {
    if (count >= MAX_BOOKINGS) {
        printf("Booking full.\n");
        return;
    }
    printf("Enter BookingID: "); scanf("%s", bookingIDs[count]);
    printf("Enter BookerName: "); scanf(" %[^\n]", bookerNames[count]);
    printf("Enter MeetingRoom: "); scanf("%s", meetingRooms[count]);
    printf("Enter Date (YYYY-MM-DD): "); scanf("%s", dates[count]);
    printf("Enter Time (HH:MM): "); scanf("%s", times[count]);
    count++;
    save_bookings();
    printf("Booking added.\n");
}

// ค้นหาข้อมูลการใช้บริการ (โดยค้นหาจาก bookingID หรือ bookerName)
void search_booking() {
    char key[50];
    printf("Search by BookingID or BookerName: "); scanf(" %[^\n]", key);
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(bookingIDs[i], key) == 0 || strstr(bookerNames[i], key)) {
            printf("%s | %s | %s | %s | %s\n", bookingIDs[i], bookerNames[i], meetingRooms[i], dates[i], times[i]);
            found = 1;
        }
    }
    if (!found) printf("No booking found.\n");
}


// อัพเดตข้อมูลการใช้บรการ #ยังเขียนไม่เสร็จ
void update_booking() {
    printf("Update booking function is not implemented yet.\n");
}


// ลบข้อมูลการใช้บริการ #ยังเขียนไม่เสร็จ
void delete_booking() {
    printf("Delete booking function is not implemented yet.\n");
}

// เเสดงเมนูให้ผู้ใช้เลือกดำเนินการต่างๆ #ยังไม่เสร็จ
void display_menu() {
    printf("BookingID | BookerName | MeetingRoom | Date | Time\n");
    for (int i = 0; i < count; i++) {
        printf("%s | %s | %s | %s | %s\n", bookingIDs[i], bookerNames[i], meetingRooms[i], dates[i], times[i]);
    }
}

// เเสดงเมนูหลัก
void displayMenu() {
    printf("===== Meeting Room Booking System =====\n");
    printf("1. Display all bookings\n");
    printf("2. Add booking\n");
    printf("3. Search booking\n");
    printf("4. Update booking\n");
    printf("5. Delete booking\n");
    printf("6. Exit\n");
    printf("Choose an option: ");
}