#include <stdio.h>
#include <string.h>

#define FILENAME "meetings.csv"
#define MAX_BOOKINGS 100

char bookingIDs[MAX_BOOKINGS][20];     // เก็บรหัสการจอง
char bookerNames[MAX_BOOKINGS][50];    // เก็บชื่อผู้จอง
char meetingRooms[MAX_BOOKINGS][50];  // เก็บห้องประชุม
char dates[MAX_BOOKINGS][20];     // เก็บวันที่
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


// ฟังก์ชันตรวจสอบ BookingID รูปแบบ M001, M002, ...
int is_valid_booking_id(const char *id) {
    return id[0] == 'M' &&
           id[1] >= '0' && id[1] <= '9' &&
           id[2] >= '0' && id[2] <= '9' &&
           id[3] >= '0' && id[3] <= '9' &&
           id[4] == '\0';
}

// ตรวจสอบ BookerName ต้องไม่ว่างและไม่มีตัวเลข
int is_valid_booker_name(const char *name) {
    if (name[0] == '\0') return 0;
    for (int i = 0; name[i] != '\0'; i++) {
        if (name[i] >= '0' && name[i] <= '9') return 0;
    }
    return 1;
}

// ตรวจสอบชื่อห้องประชุม ต้องเป็น A, B, C, D, F เท่านั้น
int is_valid_room(const char *room) {
    return (strcmp(room, "A") == 0 ||
            strcmp(room, "B") == 0 ||
            strcmp(room, "C") == 0 ||
            strcmp(room, "D") == 0 ||
            strcmp(room, "F") == 0);
}

// ตรวจสอบว่ามีการจองห้องเดียวกัน วันเดียวกัน เวลาเดียวกันหรือไม่
int is_duplicate_booking(const char *room, const char *date, const char *time) {
    char fullRoom[50];
    sprintf(fullRoom, "Conference Room %s", room);
    for (int i = 0; i < count; i++) {
        if (strcmp(meetingRooms[i], fullRoom) == 0 &&
            strcmp(dates[i], date) == 0 &&
            strcmp(times[i], time) == 0) {
            return 1;
        }
    }
    return 0;
}

// ตรวจสอบ BookingID ซ้ำ
int is_duplicate_booking_id(const char *id) {
    for (int i = 0; i < count; i++) {
        if (strcmp(bookingIDs[i], id) == 0) {
            return 1;
        }
    }
    return 0;
}

// ตรวจสอบรูปแบบวันที่ YYYY-MM-DD
int is_valid_date(const char *date) {
    if (strlen(date) != 10) return 0;
    if (date[4] != '-' || date[7] != '-') return 0;
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (date[i] < '0' || date[i] > '9') return 0;
    }
    int year = (date[0]-'0')*1000 + (date[1]-'0')*100 + (date[2]-'0')*10 + (date[3]-'0');
    int month = (date[5]-'0')*10 + (date[6]-'0');
    int day = (date[8]-'0')*10 + (date[9]-'0');
    if (month < 1 || month > 12) return 0;
    if (day < 1) return 0;
    int days_in_month[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    // leap year
    if (month == 2 && ((year%4==0 && year%100!=0) || (year%400==0))) {
        if (day > 29) return 0;
    } else {
        if (day > days_in_month[month]) return 0;
    }
    return 1;
}

// ตรวจสอบรูปแบบเวลา HH:MM AM/PM
int is_valid_time(const char *time) {
    int h, m;
    char period[3];
    // ตรวจสอบรูปแบบและอ่านค่า
    if (sscanf(time, "%d:%d %2s", &h, &m, period) != 3) return 0;
    // ตรวจสอบชั่วโมงและนาที
    if (h < 1 || h > 12) return 0;
    if (m < 0 || m > 59) return 0;
    // ตรวจสอบ AM หรือ PM (case-insensitive)
    if (!((period[0] == 'A' || period[0] == 'a' || period[0] == 'P' || period[0] == 'p') &&
          (period[1] == 'M' || period[1] == 'm') && period[2] == '\0')) return 0;
    return 1;
}

// เพิ่มข้อมูลการใช้บริการห้องประชุม
void add_booking() {
    if (count >= MAX_BOOKINGS) {
        printf("Booking full.\n");
        return;
    }
    char tempID[20];
    do {
        printf("Enter BookingID : ");
        scanf("%s", tempID);
        if (!is_valid_booking_id(tempID)) {
            printf("Invalid BookingID format. Try again.\n");
        } else if (is_duplicate_booking_id(tempID)) {
            printf("BookingID already exists. Try again.\n");
        }
    } while (!is_valid_booking_id(tempID) || is_duplicate_booking_id(tempID));
    strcpy(bookingIDs[count], tempID);

    char tempName[50];
    do {
        printf("Enter BookerName : ");
        scanf(" %[^\n]", tempName);
        if (!is_valid_booker_name(tempName)) {
            printf("Invalid name. Try again.\n");
        }
    } while (!is_valid_booker_name(tempName));
    strcpy(bookerNames[count], tempName);

    char tempRoom[10];
    do {
        printf("Enter MeetingRoom (A, B, C, D, F): ");
        scanf("%s", tempRoom);
        if (!is_valid_room(tempRoom)) {
            printf("Invalid room. Please enter A, B, C, D, or F only.\n");
        }
    } while (!is_valid_room(tempRoom));

    char tempDate[20], tempTime[15];
    do {
        printf("Enter Date (YYYY-MM-DD): ");
        scanf(" %[^\n]", tempDate);
        if (!is_valid_date(tempDate)) {
            printf("Invalid date format. Try again.\n");
        }
    } while (!is_valid_date(tempDate));

    do {
        printf("Enter Time : ");
        scanf(" %[^\n]", tempTime);
        if (!is_valid_time(tempTime)) {
            printf("Invalid time format. Try again.\n");
        }
    } while (!is_valid_time(tempTime));

    if (is_duplicate_booking(tempRoom, tempDate, tempTime)) {
        printf("This room is already booked for the same date and time. Please try again.\n");
        return;
    }

    sprintf(meetingRooms[count], "Conference Room %s", tempRoom);
    strcpy(dates[count], tempDate);
    strcpy(times[count], tempTime);

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
    char id[20];
    printf("Enter BookingID to update: ");
    scanf("%s", id);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(bookingIDs[i], id) == 0) {
            printf("Current info: %s | %s | %s | %s | %s\n", bookingIDs[i], bookerNames[i], meetingRooms[i], dates[i], times[i]);
            printf("Enter new Date (YYYY-MM-DD): ");
            scanf(" %[^\n]", dates[i]);
            printf("Enter new Time (e.g. 10:00 AM): ");
            scanf(" %[^\n]", times[i]);
            save_bookings();
            printf("Booking updated.\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("BookingID not found.\n");
    }
}


// ลบข้อมูลการใช้บริการตาม BookingID
void delete_booking() {
    char id[20];
    printf("Enter BookingID to delete: ");
    scanf("%s", id);
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(bookingIDs[i], id) == 0) {
            // เลื่อนข้อมูลตัวถัดไปขึ้นมาทับ
            for (int j = i; j < count - 1; j++) {
                strcpy(bookingIDs[j], bookingIDs[j+1]);
                strcpy(bookerNames[j], bookerNames[j+1]);
                strcpy(meetingRooms[j], meetingRooms[j+1]);
                strcpy(dates[j], dates[j+1]);
                strcpy(times[j], times[j+1]);
            }
            count--;
            save_bookings();
            printf("Booking deleted.\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("BookingID not found.\n");
    }
}

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