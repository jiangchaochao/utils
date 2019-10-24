//
// Created by jiangc on 10/22/19.
//

#ifndef TOOLS_UART_H
#define TOOLS_UART_H
// 打开串口
int UartOpen(int fd, const char* pathname);
// 设置串口
int UartSet(int fd, int bitrate, int c_flow, int bits, char parity, int stop);
// 安全读串口
ssize_t SafeRead(int fd, void *vptr, size_t n);
// 安全写串口
ssize_t SafeWrite(int fd, const void* vptr, size_t n);
// 普通写串口
int UartWrite(int fd, const char* w_buf, size_t len);
// 普通读串口
int UartRead(int fd, char* r_buf, size_t len);
// 关闭串口
int UartClose(int fd);
// 测试接口
void UartHello();
#endif //TOOLS_UART_H
