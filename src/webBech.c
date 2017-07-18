#include "socket.c"
#include <unistd.h>
#include <sys/param.h>
#include <rpc/types.h>
#include <getopt.h>
#include <strings.h>
#include <time.h>
#include <signal.h>

/* values */
volatile int timerexpired = 0;
int speed = 0;
int failed = 0;
int bytes = 0;

/* globals */
int http10 = 1; /* 0 - http/0.9, 1 - http/1.0, 2 - http/1.1 */
/* Allow: GET, HEAD, OPTIONS, TRACE */
#define METHOD_GET 0
#define METHOD_HEAD 1
#define METHOD_OPTIONS 2
#define METHOD_TRACE 3

#define PROGRAM_VERSION "1.5"

int method = METHOD_GET;
int clients = 1;
int force = 0;
int force_reload = 0;
int proxyport = 80;
char *proxyhost = NULL;
int benchtime = 30;

/* internal */
int mypipe[2];
char host[MAXHOSTNAMELEN];
#define REQUEST_SIZE 2048
char request[REQUEST_SIZE];
/**
 *
 * http://www.cnblogs.com/liwei0526vip/p/4873111.html
 *
 */
static const struct option long_options[] = {
		{ "force", no_argument, &force, 1 },
		{ "reload", no_argument, &force_reload, 1 },
		{ "time", required_argument, NULL, 't' },
		{ "help", no_argument, NULL, '?' },
		{ "http09", no_argument, NULL, '9' },
		{ "http10", no_argument, NULL, '1' },
		{ "http11", no_argument, NULL, '2' },
		{ "get", no_argument, &method, METHOD_GET },
		{ "head", no_argument, &method, METHOD_HEAD },
		{ "options", no_argument, &method, METHOD_OPTIONS },
		{ "trace", no_argument, &method, METHOD_TRACE },
		{ "version", no_argument, NULL, 'V' },
		{ "proxy", required_argument, NULL, 'p' },
		{ "clients", required_argument, NULL, 'c' },
		{ NULL, 0, NULL, 0 }
};

/* prototypes */
static void benchcore(const char* host, const int port, const char *request);
static int bench(void);
static void build_request(const char *url);

static void alarm_handler(int signal) {
	// 默認爲0,表示值未過期，1表示過期，在後邊程序收到該信號後，會跳出循環，結束程序運行
	timerexpired = 1;
}

static void usage(void) {
	fprintf(stderr,
			"webbench [option]... URL\n"
					"  -f|--force               Don't wait for reply from server.\n"
					"  -r|--reload              Send reload request - Pragma: no-cache.\n"
					"  -t|--time <sec>          Run benchmark for <sec> seconds. Default 30.\n"
					"  -p|--proxy <server:port> Use proxy server for request.\n"
					"  -c|--clients <n>         Run <n> HTTP clients at once. Default one.\n"
					"  -9|--http09              Use HTTP/0.9 style requests.\n"
					"  -1|--http10              Use HTTP/1.0 protocol.\n"
					"  -2|--http11              Use HTTP/1.1 protocol.\n"
					"  --get                    Use GET request method.\n"
					"  --head                   Use HEAD request method.\n"
					"  --options                Use OPTIONS request method.\n"
					"  --trace                  Use TRACE request method.\n"
					"  -?|-h|--help             This information.\n"
					"  -V|--version             Display program version.\n");
}

int main(int argc, char *argv[]) {
	int opt = 0;
	int options_index = 0;
	char *tmp = NULL;

	if (argc == 1) {
		usage();
		return 2;
	}
	while ((opt = getopt_long(argc, argv, "912Vfrt:p:c:?h", long_options,
			&options_index)) != EOF) {
		switch (opt) {
		case 0:
			break;
		case 'h':
			case '?':
			usage();
			break;
		case 'f':
			force = 1;
			break;
		case 'r':
			force_reload = 1;
			break;
		case '9':
			http10 = 0;
			break;
		case '1':
			http10 = 1;
			break;
		case '2':
			http10 = 2;
			break;
		case 't':

//  `getopt' finds an option that takes an argument,
//	the argument value is returned her
			benchtime = atoi(optarg);
			if (0 == benchtime) {
				benchtime = 30;
			}
			break;
		case 'p':
			/* proxy server parsing server:port */
			tmp = strrchr(optarg, ':');
			proxyhost = optarg;
			if (tmp == NULL) {
				break;
			}
			if (tmp == optarg) {
				fprintf(stderr, "Error in option --proxy %s: Missing hostName.\n"
						"Usage:  hostname:portNumber, www.baidu.com:80\n", optarg);
				return 2;
			}
			if (tmp == optarg + strlen(optarg) - 1) {
				fprintf(stderr, "Error in option --proxy %s Port number is missing.\n"
						"Usage:  hostname:portNumber, www.baidu.com:80\n", optarg);
				return 2;
			}
			// 將域名和端口號碼拆爲兩個字符串
			*tmp = '\0';
			proxyport = atoi(tmp + 1);
			break;
		case 'c':
			// todo set ammout of clients
			clients = atoi(optarg);
			if (clients == 0) {
				clients = 1;
			}
			break;
		default:
			printf("short option:%c\n", opt);
			break;
		}

	}
	/**
	 * URL 跟在所有参数的最后位置
	 */
	if (optind == argc) {
		fprintf(stderr, "webbech: Missing URL! \n");
		usage();
		return 2;
	}

	/* Copyright */
	fprintf(stderr, "Webbench - Simple Web Benchmark "PROGRAM_VERSION"\n"
	"Copyright (c) Radim Kolar 1997-2004, GPL Open Source Software.\n");
	// 最后一个参数是　URL
	build_request(argv[optind]);
	printf("Runing info: ");
	if (1 == clients)
		printf("1 client");
	else
		printf("%d clients", clients);

	printf(", running %d sec", benchtime);

	if (force)
		printf(", early socket close");
	if (NULL != proxyhost)
		printf(", via proxy server %s:%d", proxyhost, proxyport);
	if (force_reload)
		printf(", forcing reload");

	printf(".\n");

	return bench();
}

/**
 * 支持 GET, POST, HEAD, OPTIONS, TRACE　５ 种方法
 */
void build_request(const char *url) {
	char tmp[10];
	int i;
	memset(host, 0, MAXHOSTNAMELEN);
	memset(request, 0, REQUEST_SIZE);
// 各个 http 版本的差异
// https://itbilu.com/other/relate/EkwKysXIl.html
	if (force_reload && proxyhost != NULL && http10 < 1)
		http10 = 1;
	if (method == METHOD_HEAD && http10 < 1)
		// GET、POST、HEAD
		http10 = 1;
	if (method == METHOD_OPTIONS && http10 < 2)
		// HTTP/1.1新增了：OPTIONS、PUT、DELETE、TRACE、CONNECT五种HTTP请求方法。
		http10 = 2;
	if (method == METHOD_TRACE && http10 < 2)
		http10 = 2;

	switch (method) {
	default:
		case METHOD_GET:
		strcpy(request, "GET");
		break;
	case METHOD_HEAD:
		strcpy(request, "HEAD");
		break;
	case METHOD_OPTIONS:
		strcpy(request, "OPTIONS");
		break;
	case METHOD_TRACE:
		strcpy(request, "TRACE");
		break;
	}
	strcat(request, " ");
// URL

	if (NULL == strstr(url, "://")) {
		fprintf(stderr, "\n%s: must contain '://' is not a valid URL.\n", url);
		exit(2);
	}
	if (strlen(url) > 1500) {
		fprintf(stderr, "URL is too long.\n");
		exit(2);
	}
	if (0 != strncasecmp("http://", url, 7)) {
		fprintf(stderr, "\nOnly HTTP protocol is directly supported, set --proxy for others.\n");
		exit(2);
	}

	/* protocol/host delimiter */
	i = strstr(url, "://") - url + 3;

	//@TODO 这里 host 名称为什么要以 / 结尾？
	if (strchr(url + i, '/') == NULL) {
		fprintf(stderr, "\nInvalid URL syntax - hostname don't ends with '/'.\n");
		exit(2);
	}

	if (proxyhost == NULL) {
		/* get port from hostname */
		if (index(url + i, ':') != NULL
				&& index(url + i, ':') < index(url + i, '/')) {
			strncpy(host, url + i, strchr(url + i, ':') - url - i);
			memset(tmp, 0, 10);
			strncpy(tmp, index(url + i, ':') + 1,
					strchr(url + i, '/') - index(url + i, ':') - 1);
			proxyport = atoi(tmp);
			if (proxyport == 0)
				proxyport = 80;
		} else {
			strncpy(host, url + i, strcspn(url + i, "/"));
		}
		strcat(request + strlen(request), url + i + strcspn(url + i, "/"));
	} else {
		strcat(request, url);
	}

	if (http10 == 1)
		strcat(request, " HTTP/1.0");
	else if (http10 == 2)
		strcat(request, " HTTP/1.1");

	strcat(request, "\r\n");

	if (http10 > 0)
		strcat(request, "User-Agent: WebBench "PROGRAM_VERSION"\r\n");
	if (proxyhost == NULL && http10 > 0) {
		strcat(request, "Host: ");
		strcat(request, host);
		strcat(request, "\r\n");
	}

	if (force_reload && proxyhost != NULL) {
		strcat(request, "Pragma: no-cache\r\n");
	}

	if (http10 > 1)
		strcat(request, "Connection: close\r\n");

	/* add empty line at end */
	if (http10 > 0)
		strcat(request, "\r\n");

	printf("\nRequest:\n%s\n", request);
}


static int bench(void) {
	int i, j, k;
	pid_t pid = 0;
	FILE *f;

	/* check  availability s of target server */
	i = Socket(proxyhost == NULL ? host : proxyhost, proxyport);
	if (i < 0) {
		fprintf(stderr, "\nConnect to server failed. Aborting benchmark.\n");
		return 1;
	}
	close(i);

	/* create pipe */
	if (pipe(mypipe)) {
		perror("pipe failed.");
		return 3;
	}

	/* not needed, since we have alarm() in childrens */
	/* wait 4 next system clock tick */
	/*
	 cas=time(NULL);
	 while(time(NULL)==cas)
	 sched_yield();
	 */

	/* fork childs */
	for (i = 0; i < clients; i++) {
		// fork() 函數在運行過程中會返回兩次，一次在自進程種返回，一次返回結果給父進程
		pid = fork();
		if (pid <= (pid_t) 0) {
			/* child process or error*/
			sleep(1); /* make childs faster */
			break;
		}
	}

	if (pid < (pid_t) 0) {
		fprintf(stderr, "problems forking worker no. %d\n", i);
		perror("fork failed.");
		return 3;
	}

	if (pid == (pid_t) 0) {
		/* 該函數在子進程中會返回0, 表徵程序運行正常，所以返回0表明是在自進程中。 I am a child */
		if (proxyhost == NULL){
			benchcore(host, proxyport, request);
		}else{
			benchcore(proxyhost, proxyport, request);
		}
		/* write results to pipe */
		f = fdopen(mypipe[1], "w");
		if (f == NULL) {
			perror("open pipe for writing failed.");
			return 3;
		}
		/* fprintf(stderr,"Child - %d %d\n",speed,failed); */
		fprintf(f, "%d %d %d\n", speed, failed, bytes);
		fclose(f);

		return 0;
	} else {
		f = fdopen(mypipe[0], "r");
		if (f == NULL) {
			perror("open pipe for reading failed.");
			return 3;
		}

		setvbuf(f, NULL, _IONBF, 0);

		speed = 0;
		failed = 0;
		bytes = 0;

		while (1) {
			pid = fscanf(f, "%d %d %d", &i, &j, &k);
			if (pid < 2) {
				fprintf(stderr, "Some of our childrens died.\n");
				break;
			}

			speed += i;
			failed += j;
			bytes += k;
			if (--clients == 0)
				break;
		}

		fclose(f);

		printf(
				"\nSpeed=%d pages/min, %d bytes/sec.\nRequests: %d susceed, %d failed.\n",
				(int) ((speed + failed) / (benchtime / 60.0f)),
				(int) (bytes / (float) benchtime), speed, failed);
	}
	return i;
}

// @TODO 待研究
void benchcore(const char *host, const int port, const char *req) {
	int rlen;
	char buf[1500];
	int s, i;
	struct sigaction sa;

	/* setup alarm signal handler */
	sa.sa_handler = alarm_handler;
//	sa.sa_flags = 0;
//	SA_SIGINFO
//	sa.sa_flags = SA_SIGINFO;// Invoke signal-catching function with three arguments instead of one
	if (sigaction(SIGALRM, &sa, NULL))
		exit(3);

	alarm(benchtime); // after bench time,then exit

	rlen = strlen(req);
	nexttry: while (1) {
		if (timerexpired) {
			if (failed > 0) {
				/* fprintf(stderr,"Correcting failed by signal\n"); */
				failed--;
			}
			return;
		}

		s = Socket(host, port);
		if (s < 0) {
			failed++;
			continue;
		}
		if (rlen != write(s, req, rlen)) {
			failed++;
			close(s);
			continue;
		}
		if (http10 == 0)
//[枚举类型](http://www.jianshu.com/p/1b4e7dfef9e5)
// [shutdown]http://blog.csdn.net/u012480384/article/details/44179557
			if (shutdown(s, SHUT_WR)) {
				failed++;
				close(s);
				continue;
			}
		if (force == 0) {
			/* read all available data from socket */
			while (1) {
				if (timerexpired)
					break;
				i = read(s, buf, 1500);
				/* fprintf(stderr,"%d\n",i); */
				if (i < 0) {
					failed++;
					close(s);
					goto nexttry;
				} else if (i == 0)
					break;
				else
					bytes += i;
			}
		}
		if (close(s)) {
			failed++;
			continue;
		}
		speed++;
	}
}
