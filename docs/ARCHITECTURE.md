# Kiến trúc đề xuất — robot tải 500 g

## Quyết định thiết kế hiện tại
- Robot bốn chân đã được người dùng xác nhận.
- Kích thước giới hạn được cung cấp: 28 × 28 × 28 cm cho toàn bộ robot; cần xác minh quy chế đo ở tư thế hoạt động hay tư thế gấp.
- Vật chưa biết hình dạng nên không khóa vào một kẹp chuyên dụng. Bản đầu tiên nên hướng đến **khay đỡ có gờ thấp + cơ cấu giữ có thể thay đổi**, với các miếng đệm thay thế. Chỉ chốt cơ khí sau khi biết kích thước vật và luật thi.
- Thiết kế cần xem xét cả sàn phẳng và bề mặt gồ ghề nhỏ; bề mặt thi chính xác vẫn cần xác nhận. Không tuyên bố vượt địa hình cho tới khi thử.
- Ưu tiên các mô-đun dễ thay, vít/giá đỡ tiêu chuẩn và linh kiện phổ biến; tránh đặt PCB tùy chỉnh ở giai đoạn đầu.

## Các lớp phần mềm
1. **App / serial diagnostics** — nhận lệnh, báo trạng thái, log lỗi.
2. **TaskController** — quản lý chuỗi tiếp cận → gắp → nâng → khóa → xác minh → mang → đặt.
3. **SafetySupervisor** — dừng yêu cầu chuyển động khi lỗi, timeout, cảm biến mất hoặc nghiêng quá giới hạn đã hiệu chuẩn.
4. **Perception** — dữ liệu khoảng cách/vật thể; giao diện chưa gắn với loại cảm biến cụ thể.
5. **MotionController** — giao diện mục tiêu chuyển động, không chứa pin mapping hoặc lệnh servo trực tiếp.
6. **Hardware drivers** — từng driver độc lập theo bo mạch/servo/cảm biến được mua. Chưa triển khai trong scaffold.
7. **Power/diagnostics** — đo trạng thái nguồn nếu phần cứng hỗ trợ; không giả định có telemetry khi chưa lắp.

## Quy tắc an toàn phần mềm
- Mặc định không cho phép đầu ra động cơ.
- Không chuyển sang CARRY nếu chưa có tín hiệu hợp lệ xác nhận vật được giữ và cơ cấu khóa đã đóng.
- Giá trị cảm biến thiếu, lỗi hoặc quá hạn được xem là UNKNOWN/FAIL, không được xem là thành công.
- Lệnh abort phải ưu tiên hơn lệnh nhiệm vụ.
- Mất liên lạc hoặc timeout dừng yêu cầu nhiệm vụ; phần cứng thật cần có biện pháp dừng độc lập thích hợp, không chỉ dựa vào phần mềm.
- Không coi state mô phỏng là số đo thực tế.

## Cân nhắc cơ khí
- Vật 500 g đặt cao làm tăng mô-men lật; giữ vật gần tâm thân và càng thấp càng tốt.
- Cơ cấu gắp không nên cần giữ bằng lực ma sát đơn thuần; ưu tiên bề mặt đỡ và giữ hình học.
- Thiết kế phải tránh điểm kẹp ở khớp chân/cơ cấu gắp và có thể tiếp cận công tắc/ngắt nguồn.
- Khối lượng 500 g là **tải hữu ích**, không phải tổng khối lượng robot. Phải lập ngân sách khối lượng riêng cho thân, truyền động, nguồn, cảm biến và cơ cấu gắp.

## Chưa chốt
Bo điều khiển, loại servo/actuator, cảm biến, hình học chân, cơ cấu gắp, nguồn, thời gian hoạt động và kích thước vật. Mọi phương án cơ khí phải nằm trong giới hạn tổng thể 28 × 28 × 28 cm. Không mua linh kiện dựa trên tên dự án hoặc mục tiêu tải đơn lẻ; cần tính toán và rà soát trước.
