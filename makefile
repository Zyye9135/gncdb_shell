CC = gcc
CFLAGS = -Wall -g -fdiagnostics-color=always -I gncdblib/include
LDFLAGS = -Lgncdblib/lib -lgncdb -lm

# 源文件目录和对象文件目录
SRC_DIR = src
OBJ_DIR = obj

# 查找所有的 .c 文件并替换为 .o 文件
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# 最终可执行文件
TARGET = /home/zyy/桌面/gncdb_shell/main

# 默认目标
all: $(TARGET)

# 链接目标文件生成最终的可执行文件
$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

# 编译规则：从 .c 文件编译 .o 文件
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理中间文件
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
