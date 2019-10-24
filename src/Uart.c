//
// Created by jiangc on 10/22/19.
//


#include <fcntl.h>
#include <termios.h>
#include <zconf.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include "../inc/Uart.h"
/**
 * 打开串口设备,返回文件描述符
 * O_NOCTTY:如果路径名指向终端设备，不要把这个设备用作控制终端
 * O_NONBLOCK:如果路径名指向 FIFO/块文件/字符文件，则把文件的打开和后继 I/O设置为非阻塞模式（nonblocking mode）
 * 对于串口的打开操作，必须使用O_NOCTTY参数，它表示打开的是一个终端设备，程序不会成为该端口的控制终端。如果不使用此标志，
 * 任务的一个输入都会影响进程。如键盘上过来的Ctrl+C中止信号等都将影响进程。
 * @param fd
 * @param pathname
 * @return 成功返回fd,失败返回-1
 */
int UartOpen(int fd, const char *pathname) {

    assert(pathname);
    fd = open(pathname, O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (-1 == fd) {
        perror("Open Uart failed!");
        return -1;
    }
    return fd;
}

/**
 * 设置串口参数, 比特率, 流控制, 数据位, 校验位, 停止位
 * @param fd
 * @param bitrate
 * @param c_flow
 * @param bits
 * @param parity
 * @param stop
 * @return
 */
int UartSet(int fd, int bitrate, int c_flow, int bits, char parity, int stop) {
    struct termios options;

    /*获取终端属性*/
    if (tcgetattr(fd, &options) < 0) {
        perror("tcgetattr error");
        return -1;
    }
    /*设置输入输出波特率，两者保持一致*/
    switch (bitrate) {
        case 4800:
            cfsetispeed(&options, B4800);
            cfsetospeed(&options, B4800);
            break;
        case 9600:
            cfsetispeed(&options, B9600);
            cfsetospeed(&options, B9600);
            break;
        case 19200:
            cfsetispeed(&options, B19200);
            cfsetospeed(&options, B19200);
            break;
        case 38400:
            cfsetispeed(&options, B38400);
            cfsetospeed(&options, B38400);
            break;
        case 57600:
            cfsetispeed(&options, B57600);
            cfsetospeed(&options, B57600);
            break;
        case 115200:
            cfsetispeed(&options, B115200);
            cfsetospeed(&options, B115200);
            break;
        default:
            fprintf(stderr, "Unknown bitrate!\n");
            return -1;
    }

    /*设置控制模式*/
    options.c_cflag |= CLOCAL;   // 保证程序不占用串口
    options.c_cflag |= CREAD;    // 保证程序可以从串口中读取数据

    /*设置数据流控制*/
    switch (c_flow) {
        case 0:                                //不进行流控制
            options.c_cflag &= ~CRTSCTS;
            break;
        case 1:                                // 进行硬件流控制
            options.c_cflag |= CRTSCTS;
            break;
        case 2:                                // 进行软件流控制
            options.c_cflag |= IXON | IXOFF | IXANY;
            break;
        default:
            fprintf(stderr, "Unknown c_flow!\n");
            return -1;
    }
    /*设置数据位*/
    switch (bits) {
        case 5:
            options.c_cflag &= ~CSIZE;   // 屏蔽其他标志位
            options.c_cflag |= CS5;
            break;
        case 6:
            options.c_cflag &= ~CSIZE;   // 屏蔽其他标志位
            options.c_cflag |= CS6;
            break;
        case 7:
            options.c_cflag &= ~CSIZE;   // 屏蔽其他标志位
            options.c_cflag |= CS7;
            break;
        case 8:
            options.c_cflag &= ~CSIZE;   // 屏蔽其他标志位
            options.c_cflag |= CS8;
            break;
        default:
            fprintf(stderr, "Unknown bits!\n");
            return -1;
    }

    /*设置校验位*/
    switch (parity) {
        case 'n':                         //无奇偶校验位
        case 'N':
            options.c_cflag &= ~PARENB;   // PARENB:产生奇偶位，执行奇偶校验
            options.c_cflag &= ~INPCK;    // 使奇偶校验起作用
            break;
        case 's':                         // 设为空格,即停止位为2位
        case 'S':
            options.c_cflag &= ~PARENB;   // PARENB:产生奇偶位，执行奇偶校验
            options.c_cflag &= ~CSTOPB;   // CSTOPB：使用两位停止位
            break;
        case 'o':                         // 设置奇校验
        case 'O':
            options.c_cflag |= PARENB;    // PARENB：产生奇偶位，执行奇偶校验
            options.c_cflag |= PARODD;    // PARODD：若设置则为奇校验,否则为偶校验
            options.c_cflag |= INPCK;     // INPCK：使奇偶校验起作用
            options.c_cflag |= ISTRIP;    // ISTRIP：若设置则有效输入数字被剥离7个字节，否则保留全部8位
            break;
        case 'e':                         // 设置偶校验
        case 'E':
            options.c_cflag |= PARENB;    // PARENB：产生奇偶位，执行奇偶校验
            options.c_cflag &= ~PARODD;   // PARODD：若设置则为奇校验,否则为偶校验
            options.c_cflag |= INPCK;     // INPCK：使奇偶校验起作用
            options.c_cflag |= ISTRIP;    // ISTRIP：若设置则有效输入数字被剥离7个字节，否则保留全部8位
            break;
        default:
            fprintf(stderr, "Unknown parity!\n");
            return -1;
    }

    /*设置停止位*/
    switch (stop) {
        case 1:
            options.c_cflag &= ~CSTOPB;   // CSTOPB：使用两位停止位
            break;
        case 2:
            options.c_cflag |= CSTOPB;    // CSTOPB：使用两位停止位
            break;
        default:
            fprintf(stderr, "Unknown stop!\n");
            return -1;
    }
    /*设置输出模式为原始输出*/
    options.c_oflag &= ~OPOST;            //OPOST：若设置则按定义的输出处理，否则所有c_oflag失效

    /*设置本地模式为原始模式
     *ICANON：允许规范模式进行输入处理
     *ECHO：允许输入字符的本地回显
     *ECHOE：在接收EPASE时执行Backspace,Space,Backspace组合
     *ISIG：允许信号
     */
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    /*设置等待时间和最小接受字符*/
    options.c_cc[VTIME] = 0;              //可以在select中设置
    options.c_cc[VMIN] = 1;               //最少读取一个字符

    /*如果发生数据溢出，只接受数据，但是不进行读操作*/
    tcflush(fd, TCIFLUSH);

    /*激活配置*/
    if (tcsetattr(fd, TCSANOW, &options) < 0) {
        perror("tcsetattr failed");
        return -1;
    }

    return 0;
}


/**
 * 写串口操作
 * @param fd
 * @param w_buf
 * @param len
 * @return
 */
int UartWrite(int fd, const char *w_buf, size_t len) {
    ssize_t cnt = 0;

    cnt = SafeWrite(fd, w_buf, len);
    if (cnt == -1) {
        fprintf(stderr, "write error!\n");
        return -1;
    }

    return cnt;
}

/**
 * 读串口操作
 * @param fd
 * @param r_buf
 * @param len
 * @return
 */
int UartRead(int fd, char *r_buf, size_t len) {
    ssize_t cnt = 0;
    fd_set rfds;
    struct timeval time;
    int ret;

    /*将文件描述符加入读描述符集合*/
    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);

    /*设置超时为15s*/
    time.tv_sec = 15;
    time.tv_usec = 0;

    /*实现串口的多路I/O*/
    ret = select(fd + 1, &rfds, NULL, NULL, &time);
    switch (ret) {
        case -1:
            fprintf(stderr, "select error!\n");
            return -1;
        case 0:
            fprintf(stderr, "time over!\n");
            return -1;
        default:
            cnt = SafeRead(fd, r_buf, len);
            if (cnt == -1) {
                fprintf(stderr, "read error!\n");
                return -1;
            }
            return cnt;
    }
}

int UartClose(int fd) {
    assert(fd);
    close(fd);

    /*可以在这里做些清理工作*/

    return 0;
}

ssize_t SafeRead(int fd, void *vptr, size_t n) {
    size_t nleft;
    ssize_t nread;
    char *ptr;

    ptr = vptr;
    nleft = n;

    while (nleft > 0) {
        if ((nread = read(fd, ptr, nleft)) < 0) {
            if (errno == EINTR)//被信号中断
                nread = 0;
            else
                return -1;
        } else if (nread == 0)
            break;
        nleft -= nread;
        ptr += nread;
    }
    return (n - nleft);
}

ssize_t SafeWrite(int fd, const void *vptr, size_t n) {
    size_t nleft;
    ssize_t nwritten;
    const char *ptr;

    ptr = vptr;
    nleft = n;

    while (nleft > 0) {
        if ((nwritten = write(fd, ptr, nleft)) <= 0) {
            if (nwritten < 0 && errno == EINTR)
                nwritten = 0;
            else
                return -1;
        }
        nleft -= nwritten;
        ptr += nwritten;
    }
    return (n);
}

void UartHello() {
    printf("uart test!\n");
}
