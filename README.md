# 🏢 Meeting Room Booking System

ระบบจัดการการจองห้องประชุม (Meeting Room Booking System) พัฒนาโดยใช้ภาษา **C**  
รองรับฟังก์ชันเพิ่ม แก้ไข ค้นหา และลบข้อมูลการจอง  
รวมถึงมีระบบ **Unit Test** และ **End-to-End Test** เพื่อทดสอบความถูกต้องของโปรแกรม

---

## 📂 โครงสร้างโปรเจกต์

📦 meeting-room-booking/

├── main.c # โปรแกรมหลัก (Main program)

├── meet.c # ฟังก์ชันหลักของระบบจัดการการจอง

├── meet.h # ส่วนหัวของ meet.c

├── unittests.c # การทดสอบหน่วย (Unit Tests)

├── unittests.h # ส่วนหัวของ Unit Tests

├── e2etest.c # การทดสอบระบบแบบ End-to-End

├── e2etest.h # ส่วนหัวของ E2E Tests

├── meetings.csv # ไฟล์เก็บข้อมูลการจอง

└── meetings_backup.csv # สำเนาข้อมูล (สร้างอัตโนมัติระหว่างการทดสอบ)


---

## ⚙️ ฟังก์ชันหลักของระบบ

| ฟังก์ชัน | คำอธิบาย |
|----------:|-----------|
| `load_bookings()` | โหลดข้อมูลจากไฟล์ `meetings.csv` |
| `save_bookings()` | บันทึกข้อมูลกลับลงไฟล์ |
| `add_booking()` | เพิ่มข้อมูลการจองใหม่ |
| `search_booking()` | ค้นหาการจองจาก BookingID หรือชื่อผู้จอง |
| `update_booking()` | แก้ไขข้อมูลการจอง |
| `delete_booking()` | ลบข้อมูลการจอง |
| `display_menu()` | แสดงรายการการจองทั้งหมด |
| `displayMenu()` | แสดงเมนูหลักของระบบ |

---

## 🧩 ฟังก์ชันตรวจสอบความถูกต้อง

```c
is_valid_booking_id();     // ตรวจสอบรหัสจอง เช่น M001
is_valid_booker_name();    // ตรวจสอบชื่อผู้จอง
is_valid_room();           // ตรวจสอบห้องประชุม (A, B, C, D, F)
is_valid_date();           // ตรวจสอบวันที่ (YYYY-MM-DD)
is_valid_time();           // ตรวจสอบเวลา (HH:MM AM/PM)
is_duplicate_booking();    // ตรวจสอบการจองซ้ำในห้องเดียวกัน วันเดียวกัน เวลาเดียวกัน


```

## 🧠 วิธีคอมไพล์และรันโปรแกรม

🔹 คอมไพล์โปรแกรมหลัก

```c
gcc main.c meet.c -o meeting.exe


```

🔹 รันโปรแกรม

```c
meeting หรือ .\meeting.exe

```

## 🧪 การทดสอบ (Testing)

ทดสอบฟังก์ชันตรวจสอบความถูกต้องของข้อมูล

```c
gcc unittests.c meet.c -o unittests

```

🔹 รันโปรแกรม

```c

./unittests.exe

```
ผลลัพธ์ที่ได้ :

```c
All unit tests passed!

```
## 🔹 End-to-End Tests

ทดสอบการทำงานจริงของระบบ เช่น แก้ไข ค้นหา และลบการจอง

```c
gcc e2etest.c meet.c -o e2etest.exe

```

🔹 รันโปรแกรม

```c

.\e2etest.exe

```

ผลลัพธ์ที่ได้ :

```c
[PASS] test_search_booking
[PASS] test_update_booking
[PASS] test_delete_booking
All E2E tests passed!

```

## 💾 รูปแบบข้อมูล (meetings.csv)

```c
BookingID,BookerName,MeetingRoom,Date,Time
M001,John Doe,Conference Room A,2025-10-01,10:00 AM
M002,Jane Smith,Conference Room B,2025-10-01,02:00 PM

```
## 🧹 หมายเหตุ

-ไฟล์ meetings_backup.csv จะถูกสร้างและคืนค่าข้อมูลโดยอัตโนมัติระหว่างการทดสอบ E2E

-ระบบรองรับได้สูงสุด 100 การจอง (MAX_BOOKINGS)

# 👨‍💻 ผู้พัฒนา

Punnawit Khamthorn 68010713 (projec ครั้งเเรกครับ)
