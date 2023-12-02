
// Lần lượt cộng số cuối cùng của số hiện tại vào kết quả (n%10)
// Trước khi cộng phải *10 cho hàng đơn vị => 10*res
// Xử lý xong số cuối hiện tại thì n/10 để chuyển đến số đơn vị tiếp theo
int reverseInteger(int n) {
    int res = 0;
    while (n) {
        res = 10*res + n%10; // Trước khi cộng số đơn vị thì *10 để thêm 1 số 0 cho hàng đơn vị
        n /= 10;
    }
    return res;
}