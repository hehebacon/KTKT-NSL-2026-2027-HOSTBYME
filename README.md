# Robot tải vật 500 g — KTKT NSL 2026–2027

> **Trạng thái: khung phần mềm ban đầu, chưa phải robot sẵn sàng vận hành.** Chưa có xác nhận phần cứng, chưa nạp lên bo mạch và chưa thử tải thực tế.

## Mục tiêu đã xác định
- Robot bốn chân, kích thước mục tiêu khoảng 28 cm; giới hạn dự án: 30 × 30 × 30 cm.
- Mục tiêu tải hữu ích: 500 g.
- Tự tiếp cận vật, nhặt vật từ mặt đất, đưa lên lưng và khóa tải.
- Có kiểm tra trạng thái và dừng an toàn khi cảm biến không hợp lệ.

## Kiến trúc phát triển
1. **Giai đoạn A — mô phỏng/serial:** kiểm tra state machine, lệnh và điều kiện chuyển trạng thái; chưa điều khiển servo thật.
2. **Giai đoạn B — tích hợp phần cứng:** chỉ sau khi chốt bo điều khiển, servo, cảm biến và nguồn; thêm driver riêng cho đúng phần cứng.
3. **Giai đoạn C — thử nghiệm có giám sát:** kiểm tra từng chức năng khi robot được đỡ/cố định, sau đó mới thử di chuyển không tải và tăng tải theo từng bước. Người lớn/giáo viên phụ trách phải duyệt an toàn.

## Hiện có
- State machine và giao diện serial chẩn đoán.
- Cấu hình kích thước/tải ở mức mục tiêu.
- Tài liệu yêu cầu và trình tự nhặt–khóa tải.

## Chưa có / chưa kiểm chứng
- Chưa chọn bo mạch, servo, cảm biến, bộ truyền động và pin.
- Chưa có inverse kinematics hoặc bộ cân bằng đã xác nhận cho hình học thực.
- Chưa có driver servo thật; chương trình hiện không phát lệnh điều khiển động cơ.
- Chưa biên dịch/nạp trên phần cứng thực; chưa kiểm chứng khả năng mang 500 g hay tự cân bằng.

## Serial commands
- `help` — liệt kê lệnh
- `status` — trạng thái hiện tại
- `selftest` — kiểm tra logic nội bộ không điều khiển phần cứng
- `arm` / `disarm` — chỉ đổi cờ logic mô phỏng; không kích hoạt motor
- `abort` — yêu cầu về trạng thái dừng

## Build
Khung dùng PlatformIO/Arduino framework. Board trong `platformio.ini` chỉ là cấu hình tạm; phải thay bằng đúng board đã chọn trước khi coi kết quả build là có ý nghĩa.
