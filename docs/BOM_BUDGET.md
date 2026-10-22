# BOM sơ bộ tiết kiệm chi phí

Đây là danh mục theo **nhóm chức năng**, không phải danh sách mua hàng đã phê duyệt. Chưa có giá, số lượng chốt hay linh kiện được kiểm thử.

| Nhóm | Mục đích | Cách tiết kiệm an toàn | Trạng thái |
|---|---|---|---|
| Bộ điều khiển | Chạy state machine và giao tiếp | Dùng một bo phổ biến có tài liệu tốt; tránh thêm bo phụ nếu không cần | Chưa chọn |
| Điều khiển actuator | Điều khiển khớp/cơ cấu gắp | Chọn sau khi tính tải và kiểm tra tương thích tín hiệu/nguồn | Chưa chọn |
| Actuator chân | Tạo chuyển động | Không chọn chỉ theo mô-men quảng cáo; cần xét tải động, hình học, nhiệt và độ rơ | Chưa chọn |
| Cơ cấu gắp/khay | Giữ vật có hình dạng chưa biết | Mẫu thử khay/đệm thay thế trước khi làm kẹp tùy chỉnh | Chưa chọn |
| Cảm biến tư thế | Ước lượng góc thân | Chọn theo giao tiếp và tài liệu; hiệu chuẩn sau khi lắp | Chưa chọn |
| Cảm biến vật/khóa | Xác minh vật và trạng thái giữ | Ưu tiên tín hiệu độc lập, dễ kiểm tra | Chưa chọn |
| Nguồn và bảo vệ | Cấp nguồn phù hợp | Tính dòng đỉnh, thời gian chạy, bảo vệ quá dòng và ngắt nguồn | Chưa chọn |
| Khung và dây | Lắp ráp, sửa chữa | Mô-đun, ít chi tiết riêng, dây có nhãn, đầu nối có khóa | Chưa chọn |
| Dụng cụ/phụ tùng | Bảo trì | Dự phòng ốc vít, dây và chi tiết cơ khí nhỏ | Chưa chọn |

## Nguyên tắc tối ưu chi phí
1. Chốt luật thi, kích thước vật và mặt sàn trước.
2. Tạo mock-up cơ khí nhẹ để xác minh không gian và vị trí đặt vật.
3. Chỉ mua sau khi kiểm tra thông số kỹ thuật chính thức, dòng/điện áp tương thích và khả năng thay thế.
4. Tránh mua actuator rẻ nhưng thiếu tài liệu hoặc không đáp ứng tải thực; tổng chi phí sửa chữa có thể cao hơn.
5. Chia ngân sách thành: điều khiển/truyền động, cơ khí, nguồn/bảo vệ, cảm biến, phụ tùng. Để một khoản dự phòng cho thay thế.
6. Ghi giá và đường dẫn của từng linh kiện sau khi có lựa chọn cụ thể; giá thị trường thay đổi.

## Dữ liệu còn thiếu để chốt số lượng/giá
- Bo điều khiển hiện có hay phải mua mới.
- Số khớp/actuator theo cơ cấu chân được chọn.
- Kích thước và trọng tâm vật mục tiêu.
- Thời gian chạy liên tục cần đạt.
- Trần ngân sách bằng VND và phần trường hỗ trợ (nếu có).
