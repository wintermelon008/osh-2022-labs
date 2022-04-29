
// 一些错误信息
#define ILLEGAL_COMMANDS -1
#define BUFFER_OVERFLOW -2
#define INSUFFICIENT_ARGUEMENS -3
#define FORK_ERROR -4
#define THREAD_SON_ERROR -5
#define NUMBER_TRANS_ERROR -6

#define COMMAND_DONE 0
#define EXIT 1
#define HISTORY_COMMAND_BASE 100
#define LAST_ONE_COMMAND 99


// 一些常量
#define MAX_PIPE_NUM 10   // 最大支持的管道数目


// 全局变量
volatile sig_atomic_t CtrlC_flag = 0;

// 数据结构
struct command {
  std::string command;
  std::vector<std::string> parameter;
};




int do_command(struct command cmd);
// mode = 0: no pipe
// mode = 1: pipe

int Pipe_apply(int thread_i, int thread_num, int fd[][2]);
  // 根据进程编号选择连接 or 关闭管道

std::vector<std::string> split(std::string s, const std::string &delimiter);

static void CtrlC_handler(int sig);

