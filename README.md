# First-job1
ระบบจัดการข้อมูลการใช้บริการห้องประชุม


📘 รายละเอียดโปรแกรม

โปรแกรมนี้ช่วยให้ผู้ใช้สามารถ

-แสดงรายการการจองทั้งหมด

-เพิ่มข้อมูลการจองใหม่

-ค้นหาการจองจากรหัสหรือชื่อผู้จอง

-แก้ไขข้อมูลการจอง

-ลบข้อมูลการจอง

-บันทึกข้อมูลทั้งหมดไว้ในไฟล์ CSV



⚙️ วิธีคอมไพล์และรันโปรแกรม

gcc main.c meet.c -o meeting.exe

รันโปรแกรมใหม่

meet หรือ .\meeting.exe



🧭 เมนูการใช้งาน

เมื่อเปิดโปรแกรม จะปรากฏเมนูดังนี้:

===== Meeting Room Booking System =====

1. Display all bookings

2. Add booking

3. Search booking

4. Update booking

5. Delete booking

6. Exit

Choose an option:



💾 รูปแบบข้อมูลในไฟล์ meetings.csv

ข้อมูลจะถูกเก็บในรูปแบบ CSV เช่น

BookingID,BookerName,MeetingRoom,Date,Time

M001,John Smith,Conference Room A,2025-10-05,10:00 AM

M002,Alice Brown,Conference Room B,2025-10-06,01:30 PM

M003,Michael Lee,Conference Room C,2025-10-07,09:00 AM



🧩 การตรวจสอบความถูกต้องของข้อมูล (Validation)

โปรแกรมมีการตรวจสอบข้อมูลก่อนบันทึก เช่น:

ประเภท	เงื่อนไขที่ถูกต้อง

BookingID	รูปแบบต้องเป็น M001, M002, …

BookerName	ต้องไม่มีตัวเลข และไม่ว่างเปล่า

MeetingRoom	ต้องเป็น A, B, C, D หรือ F

Date	รูปแบบ YYYY-MM-DD

Time	รูปแบบ HH:MM AM/PM



👨‍💻 ผู้พัฒนา

ชื่อ: ปุณณวิช กำธร

วิชา: prog fund

ภาษาโปรแกรม: C

Compiler: GCC
