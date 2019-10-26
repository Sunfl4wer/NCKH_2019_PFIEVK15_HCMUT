# Phần mềm của hệ thống bật tắt đèn bằng tín hiệu não.
Chương trình C++ dùng đê lấy tín hiệu từ Emotiv Engine và gửi tín hiệu ra Arduino qua cổng usb.\n
  \tNếu nháy mắt trái: gửi "1" đến Arduino\n
  \tNếu nháy mắt phải: gửi "2" đến Arduino\n
Chương trình Arduino nhận tín hiệu từ cổng usb và điều khiển bật tắt led.\n
  \tNếu nhận "1": bật led\n
  \tNếu nhận "2": tắt led\n
