# Bastard
<a name="ve-dau-trang"/>

##  Mục lục
* [1. Hướng dẫn cài đặt và chạy game](#cai-dat)
* [2. Mô tả chung về trò chơi](#mo-ta)
* [3. Các chức năng của trò chơi](#chuc-nang)
* [4. Các kĩ thuật lập trình được sử dụng](#ki-thuat)
* [5. Hỗ trợ](#ho-tro)
* [6. Kết luận](#ket-luan)
* [7. Tham Khảo](#tham-khao)

<a name="cai-dat"/>

## I, Hướng dẫn cài đặt và chạy game
  ### B1: Tải project về
  Cách 1: Trên Github, chọn Code => Download ZIP  
  Cách 2: Mở terminal tại thư mục muốn lưu project, sử dụng lệnh `git init` để khởi tạo Git, sau đó dùng lệnh `git clone https://github.com/duon9/ProjectSDL.git` để clone project về máy  
  ### B2: Chạy game
  Tìm file main.exe và chạy file.

<a name="mo-ta"/>

## II, Mô tả chung về trò chơi
  **Thể loại:** `Sinh tồn`, `phiêu lưu`
  
  [Video minh hoạ](https://youtu.be/tB6vfdWeKW8)
  Game sinh tồn, phiêu lưu trong thế giới 2D có thể di chuyển đánh quái.

  Người chơi hoá thân vào nhân vật trong game, di chuyển quanh bản đồ và tấn công quái vật để kiếm số điểm cao nhất

  Người chơi có thể nhận nhiệm vụ tại GuideHouse

  Người chơi có lượng máu tối đa là 300 và sẽ chết khi lượng máu trở về 0. Tốc độ di chuyển và sát thương của người chơi cao hơn quái vật

  Tiêu diệt một con quái vật sẽ được thêm 1 điểm

<a name = "chuc-nang"/>

### III, Các chức năng của trò chơi
  - Điều khiển nhân vật di chuyển bằng các phím mũi tên và tấn công bằng`chuột trái`, `chuột phải để dùng skill`
  - F1 để pause, F2 để save game
  - Z để đổi skill(có 7 skill: lửa, nước, băng, ánh sáng, magma, lôi, hoán đổi)
  - Hệ thống HP, đánh quái và quái tự tấn công người chơi
  - Quái vật tự đuổi theo người chơi khi vào phạm vi và tấn công, quái vật có thể hồi sinh theo một thời gian nhất định
  - Menu đơn giản, người chơi có thể chơi lại khi nhân vật chết

<a name = "ki-thuat"/>

### IV, Các kỹ thuật lập trình được sử dụng
  - Sử dụng thư viện đồ họa SDL
  - Lập trình hướng đối tượng(OOP)
  - Lập trình đa luồng(Multithread)
  - Design Pattern: Singleton, Multiton
  - Con trỏ, cấp phát động
  - Chuẩn hóa vector
  - Sử dụng các thuật toán cơ bản như thuật toán xử lý va chạm, animation,....
  - Hệ thống tile-map nhiều lớp xếp chồng lên nhau và có những chức năng riêng (collision, monster, map)

<a name = "ho-tro"/>

### V, Hỗ trợ
- Sử dụng Photoshop để edit ảnh
- Sử dụng Tiled để làm map

### VI, Kết luận
  Do là game đầu tay nên còn nhiều thiếu sót, game cần được cải tiến và fix vài lỗi nhỏ
  

