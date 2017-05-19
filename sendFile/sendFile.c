
#include     <stdio.h>
#include     <stdlib.h> 
#include     <unistd.h>  
#include     <sys/types.h>
#include     <sys/stat.h>
#include     <fcntl.h> 
#include     <termios.h>
#include     <errno.h>
#include     <pthread.h>

pthread_mutex_t work_mutex;
int flag = 0;

int openFile(char *arg)
{
	struct termios ti;
	int fd = open(arg, O_RDWR | O_NOCTTY);
	if (fd < 0) {
		fprintf(stderr, "Can't open serial port: %s (%d)\n",
						strerror(errno), errno);
		return -1;
	}

	tcflush(fd, TCIOFLUSH);

	if (tcgetattr(fd, &ti) < 0) {
		fprintf(stderr, "Can't get port settings: %s (%d)\n",
						strerror(errno), errno);
		close(fd);
		return -1;
	}

	cfmakeraw(&ti);

	ti.c_cflag |=  CLOCAL;
	ti.c_cflag &= ~CRTSCTS;
	ti.c_cflag |=  PARENB;
	ti.c_cflag &= ~PARODD;
	ti.c_cflag &= ~CSIZE;
	ti.c_cflag |=  CS8;
	ti.c_cflag &= ~CSTOPB;

	ti.c_cc[VMIN] = 1;
	ti.c_cc[VTIME] = 0;

	cfsetospeed(&ti, B115200);

	if (tcsetattr(fd, TCSANOW, &ti) < 0) {
		fprintf(stderr, "Can't change port settings: %s (%d)\n",
						strerror(errno), errno);
		close(fd);
		return -1;
	}

	tcflush(fd, TCIOFLUSH);

	if (fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK) < 0) {
		fprintf(stderr, "Can't set non blocking mode: %s (%d)\n",
						strerror(errno), errno);
		close(fd);
		return -1;
    }

    return fd;
}

void readThread(int fd)
{
    while(1){
        char buffer[256] = {0};
        int ret = 0;
        pthread_mutex_lock(&work_mutex);
        while((ret = read(fd, buffer, sizeof(buffer))) != 0){
            int i = 0;
            printf("\n");
            for(; i < ret; i++)
                putchar(buffer[i]);
        }
        printf("\n");
        pthread_mutex_unlock(&work_mutex);  
        sleep(1);
    }
}

int main(int argc, char** argv)
{
    int res ;
    int fd;
    pthread_t read_thread;

    if(argc < 2){
        printf("not enouth arguments\n");
        return 0;
    }

    fd = openFile(argv[1]);
    if(fd < 0){
        return 0;
    }

    res = pthread_mutex_init(&work_mutex, NULL); //init mutex
    if (res != 0)
    {
        perror("Mutex initialization failed");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&read_thread, NULL, readThread, fd);//create new thread
    if (res != 0)
    {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    while(1){
        char ch = 0;
        pthread_mutex_lock(&work_mutex); 
        printf("# ");
        while((ch = getchar()) && ch != '\n' && ch != EOF){
            write(fd, &ch, 1);
        }
        pthread_mutex_unlock(&work_mutex);
        sleep(1);
    }
    return 0;
}
