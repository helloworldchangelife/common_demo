# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <netinet/in.h>

int main()
{
    //创建套接字
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //将套接字和ip,port绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0 , sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(8230);

    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    //监听
    listen(serv_sock, 20);

    struct sockaddr_in cli_addr;
    socklen_t cli_addr_size = sizeof(cli_addr);
    int cli_sock = accept(serv_sock, (struct sockaddr*)&cli_addr, &cli_addr_size);

    //向cli发送数据
    char str[] = "change world !";
    write(cli_sock, str, sizeof(str));

    //关闭套接字
    close(cli_sock);
    close(serv_sock);

    return 0;
}
