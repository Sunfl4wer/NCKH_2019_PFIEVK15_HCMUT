# Phần mềm của hệ thống bật tắt đèn bằng tín hiệu não.
## Chương trình C++ dùng đê lấy tín hiệu từ Emotiv Engine và gửi tín hiệu ra Arduino qua cổng usb.<br/>
- Nếu nháy mắt trái: gửi "1" đến Arduino<br/>
- Nếu nháy mắt phải: gửi "2" đến Arduino<br/>
## Chương trình Arduino nhận tín hiệu từ cổng usb và điều khiển bật tắt led.<br/>
- Nếu nhận "1": bật led<br/>
- Nếu nhận "2": tắt led<br/>