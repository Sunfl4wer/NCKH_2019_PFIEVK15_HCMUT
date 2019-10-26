# Phần mềm của hệ thống bật tắt đèn bằng tín hiệu não.
## Chương trình C++ dùng đê lấy tín hiệu từ Emotiv Engine và gửi tín hiệu ra Arduino qua cổng usb.<br/>
- Nếu nháy mắt trái: gửi "1" đến Arduino.<br/>
- Nếu nháy mắt phải: gửi "2" đến Arduino.<br/>

## Chương trình Arduino nhận tín hiệu từ cổng usb và điều khiển bật tắt led.<br/>
- Nếu nhận "1": bật led.<br/>
- Nếu nhận "2": tắt led.<br/>

## Build chương trình C++.<br/>
- Để build chương trình C++ một cách dễ dàng ta nên dùng Visual Studio 2015.<br/>
- Tải [Emotiv Community SDK](https://github.com/Emotiv/community-sdk) vào một thư mục nào đó trên máy.<br/>
- Sau đó tạo một project trong VS2015, tạo các tệp header và source có nội dung và tên giống như các tệp trong [C++](https://github.com/Sunfl4wer/NCKH_2019_PFIEVK15_HCMUT/tree/master/EEG_signal_control/C%2B%2B).<br/>
- Sau đó bấm *alt+enter* để mở cửa sổ *properties*.<br/>
- Chọn Linker -> General -> Additional Library Directories thêm đường dẫn đến thư mục <emotiv Community SDK directory>\lib\win32 tron thư viện *Emotiv Community SDK* vừa tải ở trên.<br/>
- Chọn Linker -> Input -> Additional Dependencies thêm <emotiv Community SDK directory>\lib\win32\edk.lib.<br/>
- Chọn C/C++ -> Additional Include Directory thêm <emotiv Community SDK directory>\include.<br/>
- Tiến hành build với platform win32.
- Để chạy chương trình ta cần phải chép tệp edk.dll vào thư mục debug của project.<br/>
