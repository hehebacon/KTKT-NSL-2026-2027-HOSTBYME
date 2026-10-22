# Kế hoạch kiểm thử và tiêu chí chấp nhận

## Tình trạng hiện tại
Chỉ xác nhận các tệp source/tài liệu tồn tại trên GitHub. Chưa có bằng chứng biên dịch thành công, chưa nạp lên bo, chưa kiểm tra điện, chưa chuyển động, chưa thử tải. Các bước bên dưới là kế hoạch tương lai.

## Giai đoạn 0 — xác nhận đề bài
- Lấy quy chế chính thức, kích thước giới hạn, bề mặt thi, vật mẫu và cách chấm.
- Xác nhận 500 g là tải hữu ích hay tổng tải; hiện đang hiểu là tải hữu ích.
- Chốt kích thước/khối lượng vật mẫu tối thiểu và tối đa nếu ban tổ chức có quy định.

## Giai đoạn 1 — kiểm tra logic không có actuator
- [ ] Build trên đúng môi trường và board mục tiêu.
- [ ] `help`, `status`, `selftest` trả về đúng.
- [ ] Lệnh không hợp lệ không thay đổi trạng thái nhiệm vụ.
- [ ] Lệnh quá dài được loại bỏ, không làm tràn bộ đệm.
- [ ] `arm` bị từ chối khi đầu ra phần cứng còn vô hiệu hóa.
- [ ] `abort` đưa state về FAULT và tắt cờ logic.
- [ ] `demo` kết thúc ở FAULT vì chưa có cảm biến thật; không được ghi nhận là đã gắp thành công.

## Giai đoạn 2 — rà soát cơ khí/điện (chưa cấp nguồn actuator)
- [ ] Kiểm tra kích thước tổng thể theo quy chế.
- [ ] Rà soát điểm kẹp, dây vướng, cố định nguồn và khả năng ngắt nguồn.
- [ ] Kiểm tra cực tính, đầu nối, định mức dòng/điện áp bằng tài liệu linh kiện.
- [ ] Giáo viên/người lớn có kinh nghiệm duyệt sơ đồ và cách thử trước khi cấp nguồn.

## Giai đoạn 3 — kiểm tra cảm biến và actuator riêng
- [ ] Mỗi cảm biến được kiểm tra riêng; lỗi/mất tín hiệu phải hiện rõ.
- [ ] Actuator được kiểm tra riêng trong gá cố định, không gắn tải chưa xác minh.
- [ ] Đo nhiệt độ, dòng và độ rơ theo tài liệu/giới hạn của linh kiện.
- [ ] Nút/ngắt khẩn cấp được kiểm tra độc lập với giao diện phần mềm.

## Giai đoạn 4 — chuyển động không tải
- [ ] Thử đứng yên và chuyển động chậm trên sàn phẳng, có người giám sát.
- [ ] Lặp lại trên bề mặt gồ ghề nhỏ chỉ khi thử phẳng đạt.
- [ ] Ghi video, cấu hình, lỗi và số lần thành công/thất bại.
- [ ] Nếu robot lật, giật bất thường, nóng, phát tiếng lạ hoặc mất tín hiệu: dừng và tìm nguyên nhân trước khi thử lại.

## Giai đoạn 5 — gắp và tăng tải từng bước
- [ ] Thử với vật nhẹ, dễ giữ và không có cạnh nguy hiểm.
- [ ] Xác minh độc lập trạng thái vật hiện diện và cơ cấu khóa.
- [ ] Tăng tải theo các bước đã được giáo viên/người phụ trách duyệt; không nhảy thẳng đến 500 g.
- [ ] Chỉ công bố “đạt 500 g” sau nhiều lần thử lặp lại theo đúng bài thi, có ghi nhận khối lượng và kết quả.
- [ ] Thử trên mặt phẳng trước; chỉ mở rộng sang bề mặt gồ ghề khi ổn định.

## Bảng log cho mỗi lần thử
Ngày/giờ | Firmware commit | Cấu hình | Bề mặt | Khối lượng vật | Kết quả | Lỗi/ghi chú

Không dùng mô phỏng, compile, hoặc ước lượng mô-men làm bằng chứng thay cho thử nghiệm vật lý.
